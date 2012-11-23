/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <runtime/base/class_info.h>
#include <runtime/base/complex_types.h>
#include <runtime/base/externals.h>
#include <runtime/base/hphp_system.h>
#include <runtime/base/variable_serializer.h>
#include <runtime/base/variable_unserializer.h>
#include <util/util.h>
#include <util/lock.h>
#include <util/logger.h>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
// statics

bool ClassInfo::s_loaded = false;
ClassInfo *ClassInfo::s_systemFuncs = NULL;
ClassInfo *ClassInfo::s_userFuncs = NULL;
ClassInfo::ClassMap ClassInfo::s_class_like;
ClassInfoHook *ClassInfo::s_hook = NULL;

Array ClassInfo::GetSystemFunctions() {
  ASSERT(s_loaded);

  Array ret = Array::Create();
  if (s_systemFuncs) {
    const MethodVec &methods = s_systemFuncs->getMethodsVec();
    for (unsigned i = 0; i < methods.size(); i++) {
      ret.append(methods[i]->name);
    }
  }
  return ret;
}

Array ClassInfo::GetUserFunctions() {
  ASSERT(s_loaded);

  Array ret = Array::Create();
  if (s_userFuncs) {
    const MethodVec &methods = s_userFuncs->getMethodsVec();
    for (unsigned i = 0; i < methods.size(); i++) {
      ret.append(methods[i]->name);
    }
  }
  if (s_hook) {
    Array dyn = s_hook->getUserFunctions();
    if (!dyn.isNull()) {
      ret.merge(dyn);
    }
  }
  return ret;
}

const ClassInfo::MethodInfo *ClassInfo::FindFunction(CStrRef name) {
  ASSERT(!name.isNull());
  ASSERT(s_loaded);

  const MethodInfo *ret = s_systemFuncs->getMethodInfo(name);
  if (ret == NULL && s_hook) {
    ret = s_hook->findFunction(name);
  }
  if (ret == NULL) {
    ret = s_userFuncs->getMethodInfo(name);
  }
  return ret;
}

const ClassInfo *ClassInfo::FindClassInterfaceOrTrait(CStrRef name) {
  ASSERT(!name.isNull());
  ASSERT(s_loaded);

  if (s_hook) {
    const ClassInfo *r = s_hook->findClassLike(name);
    if (r) return r;
  }

  ClassMap::const_iterator iter = s_class_like.find(name);
  if (iter != s_class_like.end()) {
    return iter->second->getDeclared();
  }

  return 0;
}

const ClassInfo *ClassInfo::FindClass(CStrRef name) {
  if (const ClassInfo *r = FindClassInterfaceOrTrait(name)) {
    return r->getAttribute() & (IsTrait|IsInterface) ? 0 : r;
  }
  return 0;
}

const ClassInfo *ClassInfo::FindInterface(CStrRef name) {
  if (const ClassInfo *r = FindClassInterfaceOrTrait(name)) {
    return r->getAttribute() & IsInterface ? r : 0;
  }
  return 0;
}

const ClassInfo *ClassInfo::FindTrait(CStrRef name) {
  if (const ClassInfo *r = FindClassInterfaceOrTrait(name)) {
    return r->getAttribute() & IsTrait ? r : 0;
  }
  return 0;
}

Array ClassInfo::GetClassLike(unsigned mask, unsigned value) {
  ASSERT(s_loaded);

  Array ret;
  for (ClassMap::const_iterator iter = s_class_like.begin();
       iter != s_class_like.end(); ++iter) {
    const ClassInfo *info = iter->second->getDeclared();
    if (!info || (info->m_attribute & mask) != value) continue;
    ret.append(info->m_name);
  }
  if (s_hook) {
    if (value & IsInterface) {
      Array dyn = s_hook->getInterfaces();
      if (!dyn.isNull()) {
        ret.merge(dyn);
      }
    } else if (value & IsTrait) {
      Array dyn = s_hook->getTraits();
      if (!dyn.isNull()) {
        ret.merge(dyn);
      }
    } else {
      Array dyn = s_hook->getClasses();
      if (!dyn.isNull()) {
        ret.merge(dyn);
      }
    }
  }
  return ret;
}

const ClassInfo::ConstantInfo *ClassInfo::FindConstant(CStrRef name) {
  ASSERT(!name.isNull());
  ASSERT(s_loaded);
  const ConstantInfo *info;
  info = s_systemFuncs->getConstantInfo(name);
  if (info) return info;
  if (s_hook) {
    info = s_hook->findConstant(name);
    if (info) return info;
  }
  info = s_userFuncs->getConstantInfo(name);
  return info;
}

ClassInfo::ConstantInfo::ConstantInfo() : callbacks(NULL), deferred(true) {
}

Variant ClassInfo::ConstantInfo::getValue() const {
  if (deferred) {
    if (callbacks == NULL) {
      return get_constant(name);
    }
    return callbacks->os_constant(name);
  }
  if (!svalue.empty()) {
    try {
      VariableUnserializer vu(svalue.data(), svalue.size(),
                              VariableUnserializer::Serialize);
      return vu.unserialize();
    } catch (Exception &e) {
      ASSERT(false);
    }
  }
  return value;
}

void ClassInfo::ConstantInfo::setValue(CVarRef value) {
  VariableSerializer vs(VariableSerializer::Serialize);
  String s = vs.serialize(value, true);
  svalue = string(s.data(), s.size());
  deferred = false;
}

void ClassInfo::ConstantInfo::setStaticValue(CVarRef v) {
  value = v;
  value.setStatic();
  deferred = false;
}

Array ClassInfo::GetConstants() {
  ASSERT(s_loaded);
  Array res;
  Array dyn;
  {
    const ConstantMap &scm = s_systemFuncs->getConstants();
    for (ConstantMap::const_iterator it = scm.begin(); it != scm.end(); ++it) {
      res.set(it->first, it->second->getValue());
    }
  }
  {
    const ConstantMap &ucm = s_userFuncs->getConstants();
    for (ConstantMap::const_iterator it = ucm.begin(); it != ucm.end(); ++it) {
      res.set(it->first, it->second->getValue());
    }
  }
  if (s_hook) {
    dyn = s_hook->getConstants();
    if (!dyn.isNull()) {
      res.merge(dyn);
    }
  }
  dyn = get_globals()->getDynamicConstants();
  if (!dyn.isNull()) {
    res.merge(dyn);
  }
  return res;
}

bool ClassInfo::GetClassMethods(MethodVec &ret, CStrRef classname,
                                int type /* = 0 */) {
  if (classname.empty()) return false;

  const ClassInfo *classInfo = NULL;
  switch (type) {
    case 0:
      classInfo = FindClass(classname);
      if (classInfo == NULL) {
        classInfo = FindInterface(classname);
        type = 2;
      }
      if (classInfo == NULL) {
        classInfo = FindTrait(classname);
        type = 3;
      }
      break;
    case 1:
      classInfo = FindClass(classname);
      break;
    case 2:
      classInfo = FindInterface(classname);
      break;
    case 3:
      classInfo = FindTrait(classname);
      break;
    default:
      ASSERT(false);
  }

  if (!classInfo) return false;

  const ClassInfo::MethodVec &methods = classInfo->getMethodsVec();
  ret.insert(ret.end(), methods.begin(), methods.end());

  if (type < 2) {
    CStrRef parentClass = classInfo->getParentClass();
    if (!parentClass.empty()) {
      if (!GetClassMethods(ret, parentClass, 1)) return false;
    }
  }

  const ClassInfo::InterfaceVec &interfaces =
    classInfo->getInterfacesVec();
  for (unsigned int i = 0; i < interfaces.size(); i++) {
    if (!GetClassMethods(ret, interfaces[i], 2)) return false;
  }

  return true;
}

void ClassInfo::GetClassProperties(PropertyMap &props, CStrRef classname) {
  if (!classname.empty()) {
    const ClassInfo *classInfo = FindClass(classname);
    if (classInfo) {
      classInfo->getAllProperties(props);
    }
  }
}

void ClassInfo::GetClassProperties(PropertyVec &props, CStrRef classname) {
  if (!classname.empty()) {
    const ClassInfo *classInfo = FindClass(classname);
    if (classInfo) {
      classInfo->getAllProperties(props);
    }
  }
}

void ClassInfo::GetClassSymbolNames(CArrRef names, bool interface, bool trait,
                                    std::vector<String> &classes,
                                    std::vector<String> *clsMethods,
                                    std::vector<String> *clsProperties,
                                    std::vector<String> *clsConstants) {
  if (clsMethods || clsProperties || clsConstants) {
    for (ArrayIter iter(names); iter; ++iter) {
      String clsname = iter.second().toString();
      classes.push_back(clsname);

      const ClassInfo *cls;
      if (interface) {
        cls = FindInterface(clsname.data());
      } else if (trait) {
        cls = FindTrait(clsname.data());
      } else {
        try {
          cls = FindClass(clsname.data());
        } catch (Exception &e) {
          Logger::Error("Caught exception %s", e.getMessage().c_str());
          continue;
        } catch(...) {
          Logger::Error("Caught unknown exception");
          continue;
        }
      }
      ASSERT(cls);
      if (clsMethods) {
        const ClassInfo::MethodVec &methods = cls->getMethodsVec();
        for (unsigned int i = 0; i < methods.size(); i++) {
          clsMethods->push_back(clsname + "::" + methods[i]->name);
        }
      }
      if (clsProperties) {
        const ClassInfo::PropertyVec &properties = cls->getPropertiesVec();
        for (ClassInfo::PropertyVec::const_iterator iter = properties.begin();
             iter != properties.end(); ++iter) {
          clsProperties->push_back(clsname + "::$" + (*iter)->name);
        }
      }
      if (clsConstants) {
        const ClassInfo::ConstantVec &constants = cls->getConstantsVec();
        for (ClassInfo::ConstantVec::const_iterator iter = constants.begin();
             iter != constants.end(); ++iter) {
          clsConstants->push_back(clsname + "::" + (*iter)->name);
        }
      }
    }
  } else {
    for (ArrayIter iter(names); iter; ++iter) {
      classes.push_back(iter.second().toString());
    }
  }
}

void ClassInfo::GetSymbolNames(std::vector<String> &classes,
                               std::vector<String> &functions,
                               std::vector<String> &constants,
                               std::vector<String> *clsMethods,
                               std::vector<String> *clsProperties,
                               std::vector<String> *clsConstants) {
  static unsigned int methodSize = 128;
  static unsigned int propSize   = 128;
  static unsigned int constSize  = 128;

  if (clsMethods) {
    clsMethods->reserve(methodSize);
  }
  if (clsProperties) {
    clsProperties->reserve(propSize);
  }
  if (clsConstants) {
    clsConstants->reserve(constSize);
  }

  GetClassSymbolNames(GetClasses(), false, false, classes,
                      clsMethods, clsProperties, clsConstants);
  GetClassSymbolNames(GetInterfaces(), true, false, classes,
                      clsMethods, clsProperties, clsConstants);
  GetClassSymbolNames(GetTraits(), false, true, classes,
                      clsMethods, clsProperties, clsConstants);

  if (clsMethods && methodSize < clsMethods->size()) {
    methodSize = clsMethods->size();
  }
  if (clsProperties && propSize < clsProperties->size()) {
    propSize = clsProperties->size();
  }
  if (constSize && constSize < clsConstants->size()) {
    constSize = clsConstants->size();
  }

  Array funcs1 = ClassInfo::GetSystemFunctions();
  Array funcs2 = ClassInfo::GetUserFunctions();
  functions.reserve(funcs1.size() + funcs2.size());
  for (ArrayIter iter(funcs1); iter; ++iter) {
    functions.push_back(iter.second().toString());
  }
  for (ArrayIter iter(funcs2); iter; ++iter) {
    functions.push_back(iter.second().toString());
  }
  Array consts = GetConstants();
  constants.reserve(consts.size());
  for (ArrayIter iter(consts); iter; ++iter) {
    constants.push_back(iter.first().toString());
  }
}

///////////////////////////////////////////////////////////////////////////////
// ClassInfo

const ClassInfo *ClassInfo::getDeclared() const {
  if (m_attribute & IsRedeclared) {
    return getCurrentOrNull();
  } else if (m_attribute & IsVolatile) {
    return *(bool*)((char*)get_globals() + m_cdec_offset) ? this : 0;
  } else {
    return this;
  }
}

const ClassInfo *ClassInfo::getParentClassInfo() const {
  CStrRef parentName = getParentClass();
  if (parentName.empty()) return NULL;
  return FindClass(parentName);
}

void ClassInfo::getAllParentsVec(ClassVec &parents) const {
  CStrRef parent = getParentClass();
  if (!parent.empty()) {
    parents.push_back(parent);
    const ClassInfo *info = FindClass(parent);
    if (info) info->getAllParentsVec(parents);
  }
}

void ClassInfo::getAllInterfacesVec(InterfaceVec &interfaces) const {
  const InterfaceVec &ifs = getInterfacesVec();
  for (unsigned int i = 0; i < ifs.size(); i++) {
    CStrRef intf = ifs[i];
    interfaces.push_back(intf);
    const ClassInfo *info = FindInterface(intf);
    if (info) info->getAllInterfacesVec(interfaces);
  }
}

bool ClassInfo::derivesFrom(CStrRef name, bool considerInterface) const {
  ASSERT(!name.isNull());
  return derivesFromImpl(name, considerInterface);
}

bool ClassInfo::derivesFromImpl(CStrRef name, bool considerInterface) const {
  if (name->isame(getParentClass().get())) {
    return true;
  }

  const ClassInfo *parent = getParentClassInfo();
  if (parent && parent->derivesFromImpl(name, considerInterface)) {
    return true;
  }

  if (considerInterface) {
    const InterfaceSet &interfaces = getInterfaces();
    for (InterfaceSet::const_iterator iter = interfaces.begin();
         iter != interfaces.end(); ++iter) {
      if (name->isame(iter->get())) {
        return true;
      }
      const ClassInfo *parent = FindInterface(*iter);
      if (parent && parent->derivesFromImpl(name, considerInterface)) {
        return true;
      }
    }
  }
  return false;
}

bool ClassInfo::IsSubClass(CStrRef className1, CStrRef className2,
                           bool considerInterface) {
  const ClassInfo *clsInfo1 = ClassInfo::FindClass(className1);
  if (!clsInfo1) return false;

  return clsInfo1->derivesFrom(className2, considerInterface);
}

ClassInfo::MethodInfo *ClassInfo::getMethodInfo(CStrRef name) const {
  ASSERT(!name.isNull());

  const MethodMap &methods = getMethods();
  MethodMap::const_iterator iter = methods.find(name);
  if (iter != methods.end()) {
    ClassInfo::MethodInfo *m = iter->second;
    if (m->attribute & (IsVolatile|IsRedeclared)) {
      return m->getDeclared();
    }
    return m;
  }
  return NULL;
}

ClassInfo::MethodInfo *ClassInfo::hasMethod(CStrRef name,
                                            ClassInfo* &classInfo,
                                            bool interfaces /* = false */)
const {
  ASSERT(!name.isNull());
  classInfo = (ClassInfo *)this;
  const MethodMap &methods = getMethods();
  MethodMap::const_iterator it = methods.find(name);
  if (it != methods.end()) {
    ASSERT(!(it->second->attribute & (IsVolatile|IsRedeclared)));
    return it->second;
  }
  ClassInfo::MethodInfo *result = NULL;
  const ClassInfo *parent = getParentClassInfo();
  if (parent) result = parent->hasMethod(name, classInfo);
  if (result || !interfaces || !(m_attribute & IsAbstract)) return result;
  // TODO: consider caching the iface lookups
  const InterfaceVec &ifaces = getInterfacesVec();
  for (InterfaceVec::const_iterator it = ifaces.begin();
       it != ifaces.end(); ++it) {
    const ClassInfo *iface = FindInterface(*it);
    if (iface) result = iface->hasMethod(name, classInfo, true);
    if (result) return result;
  }
  return NULL;
}

// internal function  className::methodName or callObject->methodName
bool ClassInfo::HasAccess(CStrRef className, CStrRef methodName,
                          bool staticCall, bool hasCallObject) {
  // It has to be either a static call or a call with an object.
  ASSERT(staticCall || hasCallObject);
  const ClassInfo *clsInfo = ClassInfo::FindClass(className);
  if (!clsInfo) return false;
  ClassInfo *defClass;
  ClassInfo::MethodInfo *methodInfo =
    clsInfo->hasMethod(methodName, defClass);
  if (!methodInfo) return false;
  if (methodInfo->attribute & ClassInfo::IsPublic) return true;
  const ClassInfo *ctxClass =
    ClassInfo::FindClass(FrameInjection::GetClassName(true));
  bool hasObject = hasCallObject || FrameInjection::GetThis(true);
  if (ctxClass) {
    return ctxClass->checkAccess(defClass, methodInfo, staticCall, hasObject);
  }
  return false;
}

bool ClassInfo::checkAccess(ClassInfo *defClass,
                            MethodInfo *methodInfo,
                            bool staticCall,
                            bool hasObject) const {
  ASSERT(defClass && methodInfo);
  if ((m_name->isame(defClass->m_name.get()))) {
    if (methodInfo->attribute & ClassInfo::IsStatic) return true;
    return hasObject;
  }

  if (methodInfo->attribute & ClassInfo::IsStatic) {
    if (methodInfo->attribute & ClassInfo::IsPublic) return true;
    if (methodInfo->attribute & ClassInfo::IsProtected) {
      return derivesFrom(defClass->m_name, false) ||
             defClass->derivesFrom(m_name, false);
    }
    return false;
  }
  if (!hasObject && !staticCall) return false;
  if (methodInfo->attribute & ClassInfo::IsPublic) return true;
  if (methodInfo->attribute & ClassInfo::IsProtected) {
    return derivesFrom(defClass->m_name, false) ||
           defClass->derivesFrom(m_name, false);
  }
  return false;
}

const char *ClassInfo::getConstructor() const {
  ClassInfo *defClass;
  if (hasMethod("__construct", defClass)) {
    return "__construct";
  }
  if (!(m_attribute & IsTrait) && hasMethod(m_name, defClass)) {
    return m_name;
  }
  return NULL;
}

void ClassInfo::getAllProperties(PropertyMap &props) const {
  const PropertyMap &properties = getProperties();
  props.insert(properties.begin(), properties.end());

  CStrRef parentClass = getParentClass();
  if (!parentClass.empty()) {
    GetClassProperties(props, parentClass);
  }
}

void ClassInfo::getAllProperties(PropertyVec &props) const {
  const PropertyVec &properties = getPropertiesVec();
  props.insert(props.end(), properties.begin(), properties.end());

  CStrRef parentClass = getParentClass();
  if (!parentClass.empty()) {
    GetClassProperties(props, parentClass);
  }
}

void ClassInfo::filterProperties(Array &props, Attribute toRemove) const {
  const PropertyVec &properties = getPropertiesVec();
  for (unsigned i = 0; i < properties.size(); i++) {
    if (properties[i]->attribute & toRemove) {
      props.remove(properties[i]->name, true);
    }
  }
  const ClassInfo *parent = getParentClassInfo();
  if (parent) {
    parent->filterProperties(props, toRemove);
  }
}

ClassInfo::PropertyInfo *ClassInfo::getPropertyInfo(CStrRef name) const {
  ASSERT(!name.isNull());
  const PropertyMap &properties = getProperties();
  PropertyMap::const_iterator iter = properties.find(name);
  if (iter != properties.end()) {
    return iter->second;
  }
  const ClassInfo *parent = getParentClassInfo();
  while (parent) {
    const PropertyMap &inhproperties = parent->getProperties();
    PropertyMap::const_iterator piter = inhproperties.find(name);
    if (piter != inhproperties.end()) {
      // parent properties are only available if NOT private
      if (!(piter->second->attribute & ClassInfo::IsPrivate)) {
	      return piter->second;
      }
    }
    parent = parent->getParentClassInfo();
  }
  return NULL;
}

bool ClassInfo::hasProperty(CStrRef name) const {
  ASSERT(!name.isNull());
  const PropertyMap &properties = getProperties();
  return properties.find(name) != properties.end();
}

ClassInfo::ConstantInfo *ClassInfo::getConstantInfo(CStrRef name) const {
  ASSERT(!name.isNull());
  const ConstantMap &constants = getConstants();
  ConstantMap::const_iterator iter = constants.find(name);
  if (iter != constants.end()) {
    return iter->second;
  }
  return NULL;
}

bool ClassInfo::hasConstant(CStrRef name) const {
  ASSERT(!name.isNull());
  const ConstantMap &constants = getConstants();
  return constants.find(name) != constants.end();
}

bool ClassInfo::PropertyInfo::isVisible(const ClassInfo *context) const {
  if ((attribute & ClassInfo::IsPublic) || context == owner) return true;
  if (!context) return false;
  if (attribute & ClassInfo::IsProtected) {
    return owner->derivesFrom(context->getName(), false) ||
           context->derivesFrom(owner->getName(), false);
  }
  ASSERT(attribute & ClassInfo::IsPrivate);
  return false;
}

///////////////////////////////////////////////////////////////////////////////
// load functions

static String makeStaticString(const char *s) {
  if (!s) return null_string;
  String str(s);
  if (!str.checkStatic()) {
    str->setStatic();
    if (!has_eval_support) {
      StaticString::TheStaticStringSet().insert(str.get());
    }
  }
  return str;
}

ClassInfo::MethodInfo *ClassInfo::MethodInfo::getDeclared() {
  if (attribute & ClassInfo::IsRedeclared) {
    RedeclaredCallInfo *ci = *(RedeclaredCallInfo**)((char*)get_globals() +
                                                     volatile_redec_offset);
    if (!ci) return 0;
    return (ClassInfo::MethodInfo*)(void*)parameters[ci->redeclaredId];
  } else if (attribute & ClassInfo::IsVolatile) {
    return *(bool*)((char*)get_globals() + volatile_redec_offset) ? this : 0;
  }
  return this;
}

ClassInfo::MethodInfo::MethodInfo(const char **&p) {
  attribute = (Attribute)(int64)(*p++);
  name = makeStaticString(*p++);
  docComment = 0;
  if (attribute & ClassInfo::IsRedeclared) {
    volatile_redec_offset = (int)(int64)(*p++);
    while (*p) {
      MethodInfo *m = new MethodInfo(p);
      parameters.push_back((ParameterInfo*)(void*)m);
    }
  } else {
    file = *p++;
    line1 = (int)(int64)(*p++);
    line2 = (int)(int64)(*p++);
    if (attribute & IsVolatile) {
      volatile_redec_offset = (int)(int64)(*p++);
    }

    if (attribute & HasDocComment) {
      docComment = *p++;
    }

    while (*p) {
      ParameterInfo *parameter = new ParameterInfo();
      parameter->attribute = (Attribute)(int64)(*p++);
      parameter->name = *p++;
      parameter->type = *p++;
      ASSERT(Util::toLower(parameter->type) == parameter->type);
      parameter->value = *p++;
      parameter->valueText = *p++;

      parameters.push_back(parameter);
    }
    p++;

    while (*p) {
      ConstantInfo *staticVariable = new ConstantInfo();
      staticVariable->name = makeStaticString(*p++);
      staticVariable->valueLen = (int64)(*p++);
      staticVariable->valueText = *p++;
      VariableUnserializer vu(staticVariable->valueText,
                              staticVariable->valueLen,
                              VariableUnserializer::Serialize);
      try {
        staticVariable->setStaticValue(vu.unserialize());
      } catch (Exception &e) {
        ASSERT(false);
      }
      staticVariables.push_back(staticVariable);
    }
  }

  p++;
}

ClassInfoUnique::ClassInfoUnique(const char **&p) {
  m_attribute = (Attribute)(int64)(*p++);
  ASSERT(!(m_attribute & IsRedeclared));

  // ClassInfoUnique is only created by ClassInfo::Load(), which is called
  // from hphp_process_init() in the thread-neutral initialization phase.
  // It is OK to create StaticStrings here, and throw the smart ptrs away,
  // because the underlying static StringData will not be released.
  m_name = makeStaticString(*p++);
  m_parent = makeStaticString(*p++);

  m_file = *p++;
  m_line1 = (int)(int64)(*p++);
  m_line2 = (int)(int64)(*p++);

  if (m_attribute & IsVolatile) {
    m_cdec_offset = (int)(int64)(*p++);
  }

  if (m_attribute & HasDocComment) {
    m_docComment = *p++;
  }

  while (*p) {
    String iface_name = makeStaticString(*p++);
    ASSERT(m_interfaces.find(iface_name) == m_interfaces.end());
    m_interfaces.insert(iface_name);
    m_interfacesVec.push_back(iface_name);
  }
  p++;

  if (m_attribute & ClassInfo::UsesTraits) {
    while (*p) {
      String trait_name = makeStaticString(*p++);
      ASSERT(m_traits.find(trait_name) == m_traits.end());
      m_traits.insert(trait_name);
      m_traitsVec.push_back(trait_name);
    }
    p++;
  }

  if (m_attribute & ClassInfo::HasAliasedMethods) {
    while (*p) {
      String new_name = makeStaticString(*p++);
      String old_name = makeStaticString(*p++);
      m_traitAliasesVec.push_back(pair<String, String>(new_name, old_name));
    }
    p++;
  }

  while (*p) {
    MethodInfo *method = new MethodInfo(p);

    ASSERT(m_methods.find(method->name) == m_methods.end());
    m_methods[method->name] = method;
    m_methodsVec.push_back(method);
  }
  p++;

  while (*p) {
    PropertyInfo *property = new PropertyInfo();
    property->attribute = (Attribute)(int64)(*p++);
    property->name = makeStaticString(*p++);
    property->owner = this;
    ASSERT(m_properties.find(property->name) == m_properties.end());
    m_properties[property->name] = property;
    m_propertiesVec.push_back(property);
  }
  p++;

  while (*p) {
    ConstantInfo *constant = new ConstantInfo();
    constant->name = makeStaticString(*p++);
    const char *len_or_cw = *p++;
    constant->valueText = *p++;

    if (constant->valueText) {
      constant->valueLen = (int64)len_or_cw;
      VariableUnserializer vu(constant->valueText,
                              constant->valueLen,
                              VariableUnserializer::Serialize);
      try {
        constant->setStaticValue(vu.unserialize());
      } catch (Exception &e) {
        ASSERT(false);
      }
    } else {
      constant->valueLen = 0;
      if (!m_name.empty()) {
        const ObjectStaticCallbacks *cwo =
          (const ObjectStaticCallbacks*)len_or_cw;

        ASSERT(cwo);
        constant->callbacks = cwo;
      }
    }

    ASSERT(m_constants.find(constant->name) == m_constants.end());
    m_constants[constant->name] = constant;
    m_constantsVec.push_back(constant);
  }
  p++;
}

ClassInfoRedeclared::ClassInfoRedeclared(const char **&p) {
  m_attribute = (Attribute)(int64)(*p++);
  m_name = makeStaticString(*p++);
  m_redeclaredIdOffset = (int)(int64)*p++;
  while (*p) {
    ClassInfo *cls = new ClassInfoUnique(p);
    m_redeclaredClasses.push_back(cls);
  }
  p++;
}

const ClassInfo *ClassInfoRedeclared::getCurrentOrNull() const {
  const RedeclaredObjectStaticCallbacks *rosc =
    *(const RedeclaredObjectStaticCallbacks**)((char*)get_globals() +
                                               m_redeclaredIdOffset);
  int id = rosc->getRedeclaringId();
  if (LIKELY(id >= 0)) {
    return m_redeclaredClasses[id];
  }
  return 0;
}

void ClassInfo::Load() {
  ASSERT(!s_loaded);
  const char **p = g_class_map;
  while (*p) {
    Attribute attribute = (Attribute)(int64)*p;
    ClassInfo *info = (attribute & IsRedeclared) ?
      static_cast<ClassInfo*>(new ClassInfoRedeclared(p)) :
      static_cast<ClassInfo*>(new ClassInfoUnique(p));

    if (info->m_name.empty()) {
      if (attribute & IsSystem) {
        ASSERT(s_systemFuncs == NULL);
        s_systemFuncs = info;
      } else {
        ASSERT(s_userFuncs == NULL);
        s_userFuncs = info;
      }
    } else {
      ClassInfo *&i = s_class_like[info->m_name];
      ASSERT(!i);
      i = info;
    }
  }

  ASSERT(s_systemFuncs);
  ASSERT(s_userFuncs);
  s_loaded = true;
}

ClassInfo::MethodInfo::~MethodInfo() {
  if (attribute & ClassInfo::IsRedeclared) {
    for (vector<const ParameterInfo *>::iterator it = parameters.begin();
         it != parameters.end(); ++it) {
      delete (MethodInfo*)(void*)*it;
    }
  } else {
    for (vector<const ParameterInfo *>::iterator it = parameters.begin();
         it != parameters.end(); ++it) {
      delete *it;
    }
    for (vector<const ConstantInfo *>::iterator it = staticVariables.begin();
         it != staticVariables.end(); ++it) {
      delete *it;
    }
  }
}

Variant ClassPropTable::getInitVal(const ClassPropTableEntry *prop) const {
  int64 id = m_static_inits[prop->init_offset];
  if (LIKELY(!(id & 7))) {
    return *(Variant*)id;
  }
  switch (id & 7) {
    case 1: {
      int off = id >> 32;
      CStrRef s = getInitS((id>>4) & 0xfffffff);
      if (off) {
        char *addr = (char*)get_global_variables() + off;
        return getDynamicConstant(*(Variant*)addr, s);
      } else {
        return getUndefinedConstant(s);
      }
    }
    case 2: {
      const ObjectStaticCallbacks *osc =
        (const ObjectStaticCallbacks *)getInitP((id >> 4) & 0xfffffff);
      const char *addr =
        (const char *)osc->lazy_initializer(get_global_variables()) +
        (id >> 32);
      return *(Variant*)addr;
    }
    case 3: {
      char *addr = (char*)get_global_variables() + (id & 0x7ffffff8);
      ObjectStaticCallbacks *osc = *(ObjectStaticCallbacks**)addr;
      return osc->os_constant(getInitS(id>>32).c_str());
    }
    case 4: {
      ObjectStaticCallbacks *osc =
        (ObjectStaticCallbacks*)getInitP((id & 0x7fffffff)>>4);
      return osc->os_constant(getInitS(id>>32).c_str());
    }
    case 5:
      throw FatalErrorException(0, "unknown class constant %s::%s",
                                getInitS((id & 0x7fffffff)>>4).c_str(),
                                getInitS(id>>32).c_str());

    case 6: {
      void *func = getInitP((id >> 4) & 0x7ffffff);
      if (id >> 32) {
        return ((CVarRef (*)())func)();
      } else {
        return ((Variant (*)())func)();
      }
    }

    case 7:
      return ClassPropTableEntry::GetVariant((id >> 4) & 15,
                                             getInitP(id >> 32));
  }
  throw FatalErrorException("Failed to get init val");
}

void ClassInfo::GetArray_forSer(const ObjectData *obj, const ClassPropTable *ct,
                         Array &props, bool pubOnly, Array *odata/* = Null*/) {
  while (ct) {
    const ClassPropTableEntry *p = ct->m_entries;
    int off = ct->m_offset;
    String keyName;
    String header;
    if (off >= 0) do {
      p += off;
      keyName = *p->keyName;
      if (p->isProtected()) {
	  header = String("\0*\0",3,AttachLiteral);
	  keyName = header + keyName;
      } else if (p->isPrivate()) {
	  if (keyName.charAt(0) != '\0') {
          header =String("\0",1, AttachLiteral);
	 
	  keyName = header + obj->o_getClassName()+header + keyName; 
	  }
      }
      if (odata) {
	Array pe = Array::Create();
        pe.set("type",(p->type));	
        pe.set("offset",(p->offset));	
	odata->set(keyName,pe,true);
      }
      if (!pubOnly || p->isPublic()) {
        if (p->isOverride()) {
          /* The actual property is stored in a base class,
             but we need to set the entry here, to get the
             iteration order right */
          props.set(keyName, null_variant, true);
          continue;
        }
        const char *addr = ((const char *)obj) + p->offset;
        if (LIKELY(p->type == KindOfVariant)) {
          if (isInitialized(*(Variant*)addr)) {
            props.lvalAt(keyName, AccessFlags::Key)
                 .setWithRef(*(Variant*)addr);
          }
          continue;
        }
        Variant v = p->getVariant(addr);
        if (p->isPrivate() || p->isProtected()) {
 
          props.add(keyName, v, true);
        } else {
          props.set(keyName, v, true);
        }
      }
    } while ((off = p->next) != 0);
    ct = ct->m_parent;
    if (!ct) {
      ObjectData *parent = obj->getRedeclaredParent();
      if (parent) {
        ASSERT(parent != obj);
        obj = parent;
        ct = obj->o_getClassPropTable();
      }
    }
  }
  obj->o_getArray(props, pubOnly);
}

void ClassInfo::GetArray_withProtected(const ObjectData *obj, const ClassPropTable *ct,
                         Array &props, bool pubOnly, Array *odata/* = Null*/) {
  while (ct) {
    const ClassPropTableEntry *p = ct->m_entries;
    int off = ct->m_offset;
     String keyName; 
     String header;
    if (off >= 0) do {
      p += off;
      keyName = *p->keyName;
      if (p->isProtected()) {
          header = String("\0*\0",3,AttachLiteral);
          keyName = header + keyName;
      } else if (p->isPrivate()) {
          if (keyName.charAt(0) != '\0') {
          header =String("\0",1, AttachLiteral);

          keyName = header + obj->o_getClassName()+header + keyName;
          }
      }

      if (odata) {
        Array pe = Array::Create();
        pe.set("type",(p->type));
        pe.set("offset",(p->offset));
        odata->set(p->keyName->lastToken((char)0),pe,true);
      }
      if (!pubOnly || p->isPublic()) {
        if (p->isOverride()) {
          /* The actual property is stored in a base class,
             but we need to set the entry here, to get the
             iteration order right */
          props.set(keyName, null_variant, true);
          continue;
        }
        const char *addr = ((const char *)obj) + p->offset;
        if (LIKELY(p->type == KindOfVariant)) {
          if (isInitialized(*(Variant*)addr)) {
            props.lvalAt(keyName, AccessFlags::Key)
                 .setWithRef(*(Variant*)addr);
          }
          continue;
        }
        Variant v = p->getVariant(addr);
        if (p->isPrivate() || p->isProtected()) {

          props.add(keyName, v, true);
        } else {
          props.set(keyName, v, true);
        }
      }
    } while ((off = p->next) != 0);
    ct = ct->m_parent;
    if (!ct) {
      ObjectData *parent = obj->getRedeclaredParent();
      if (parent) {
        ASSERT(parent != obj);
        obj = parent;
        ct = obj->o_getClassPropTable();
      }
    }
  }
  obj->o_getArray(props, pubOnly);
}
void ClassInfo::GetArray(const ObjectData *obj, const ClassPropTable *ct,
                         Array &props, bool pubOnly, Array *odata/* = Null*/) {
  while (ct) {
    const ClassPropTableEntry *p = ct->m_entries;
    int off = ct->m_offset;
    if (off >= 0) do {
      p += off;
      if (odata) {
	Array pe = Array::Create();
        pe.set("type",(p->type));	
        pe.set("offset",(p->offset));	
	odata->set(p->keyName->lastToken((char)0),pe,true);
      }
      if (!pubOnly || p->isPublic()) {
        if (p->isOverride()) {
          /* The actual property is stored in a base class,
             but we need to set the entry here, to get the
             iteration order right */
          props.set(*p->keyName, null_variant, true);
          continue;
        }
        const char *addr = ((const char *)obj) + p->offset;
        if (LIKELY(p->type == KindOfVariant)) {
          if (isInitialized(*(Variant*)addr)) {
            props.lvalAt(*p->keyName, AccessFlags::Key)
                 .setWithRef(*(Variant*)addr);
          }
          continue;
        }
        Variant v = p->getVariant(addr);
        if (p->isPrivate()) {
 
          props.add(*p->keyName, v, true);
        } else {
          props.set(*p->keyName, v, true);
        }
      }
    } while ((off = p->next) != 0);
    ct = ct->m_parent;
    if (!ct) {
      ObjectData *parent = obj->getRedeclaredParent();
      if (parent) {
        ASSERT(parent != obj);
        obj = parent;
        ct = obj->o_getClassPropTable();
      }
    }
  }
  obj->o_getArray(props, pubOnly);
}

void ClassInfo::SetArray(ObjectData *obj, const ClassPropTable *ct,
                         CArrRef props) {
  while (ct) {
    for (const int *ppi = ct->privates(); *ppi >= 0; ppi++) {
      const ClassPropTableEntry *p = ct->m_entries + *ppi;
      ASSERT(p->isPrivate());
      const char *addr = ((const char *)obj) + p->offset;
      if (LIKELY(p->type == KindOfVariant)) {
        props->load(*p->keyName, *(Variant*)addr);
        continue;
      }
      if (!props->exists(*p->keyName)) continue;

      CVarRef value = props->get(*p->keyName);
      switch (p->type) {
      case KindOfBoolean: *(bool*)addr = value;   break;
      case KindOfInt32:   *(int*)addr = value;    break;
      case KindOfInt64:   *(int64*)addr = value;  break;
      case KindOfDouble:  *(double*)addr = value; break;
      case KindOfString:  *(String*)addr = value; break;
      case KindOfArray:   *(Array*)addr = value;  break;
      case KindOfObject:  *(Object*)addr = value; break;
      default:            ASSERT(false);          break;
      }
    }
    ct = ct->m_parent;
    if (!ct) {
      ObjectData *parent = obj->getRedeclaredParent();
      if (parent) {
        ASSERT(parent != obj);
        obj = parent;
        ct = obj->o_getClassPropTable();
      }
    }
  }
  obj->o_setArray(props);
}

///////////////////////////////////////////////////////////////////////////////
}
