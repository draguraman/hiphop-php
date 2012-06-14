/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#ifndef __EXT_SIMPLEXML_H__
#define __EXT_SIMPLEXML_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <runtime/ext/ext_simplexml_include.h>
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
Variant f_simplexml_import_dom(CObjRef dom, CStrRef class_name = "SimpleXMLElement");
Variant f_simplexml_load_string(CStrRef data, CStrRef class_name = "SimpleXMLElement", int64 options = 0, CStrRef ns = "", bool is_prefix = false);
Variant f_simplexml_load_file(CStrRef filename, CStrRef class_name = "SimpleXMLElement", int64 options = 0, CStrRef ns = "", bool is_prefix = false);
Variant f_libxml_get_errors();
Variant f_libxml_get_last_error();
void f_libxml_clear_errors();
bool f_libxml_use_internal_errors(CVarRef use_errors = null_variant);
void f_libxml_set_streams_context(CObjRef streams_context);
bool f_libxml_disable_entity_loader(bool disable = true);

///////////////////////////////////////////////////////////////////////////////
// class SimpleXMLElement
FORWARD_DECLARE_CLASS_BUILTIN(SimpleXMLElement);
class c_SimpleXMLElement :
      public ExtObjectDataFlags<ObjectData::UseGet|
                                ObjectData::UseSet|
                                ObjectData::UseIsset|
                                ObjectData::UseUnset> {
 public:
  DECLARE_CLASS(SimpleXMLElement, SimpleXMLElement, ObjectData)

  // need to implement
  public: c_SimpleXMLElement(const ObjectStaticCallbacks *cb = &cw_SimpleXMLElement);
  public: ~c_SimpleXMLElement();
  public: void t___construct(CStrRef data, int64 options = 0, bool data_is_url = false, CStrRef ns = "", bool is_prefix = false);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: bool t_offsetexists(CVarRef index);
  DECLARE_METHOD_INVOKE_HELPERS(offsetexists);
  public: Variant t_offsetget(CVarRef index);
  DECLARE_METHOD_INVOKE_HELPERS(offsetget);
  public: void t_offsetset(CVarRef index, CVarRef newvalue);
  DECLARE_METHOD_INVOKE_HELPERS(offsetset);
  public: void t_offsetunset(CVarRef index);
  DECLARE_METHOD_INVOKE_HELPERS(offsetunset);
  public: Variant t_getiterator();
  DECLARE_METHOD_INVOKE_HELPERS(getiterator);
  public: int64 t_count();
  DECLARE_METHOD_INVOKE_HELPERS(count);
  public: Variant t_xpath(CStrRef path);
  DECLARE_METHOD_INVOKE_HELPERS(xpath);
  public: bool t_registerxpathnamespace(CStrRef prefix, CStrRef ns);
  DECLARE_METHOD_INVOKE_HELPERS(registerxpathnamespace);
  public: Variant t_asxml(CStrRef filename = "");
  DECLARE_METHOD_INVOKE_HELPERS(asxml);
  public: Array t_getnamespaces(bool recursive = false);
  DECLARE_METHOD_INVOKE_HELPERS(getnamespaces);
  public: Array t_getdocnamespaces(bool recursive = false);
  DECLARE_METHOD_INVOKE_HELPERS(getdocnamespaces);
  public: Object t_children(CStrRef ns = "", bool is_prefix = false);
  DECLARE_METHOD_INVOKE_HELPERS(children);
  public: String t_getname();
  DECLARE_METHOD_INVOKE_HELPERS(getname);
  public: Object t_attributes(CStrRef ns = "", bool is_prefix = false);
  DECLARE_METHOD_INVOKE_HELPERS(attributes);
  public: Variant t_addchild(CStrRef qname, CStrRef value = null_string, CStrRef ns = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(addchild);
  public: void t_addattribute(CStrRef qname, CStrRef value = null_string, CStrRef ns = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(addattribute);
  public: String t___tostring();
  DECLARE_METHOD_INVOKE_HELPERS(__tostring);
  public: Variant t___get(Variant name);
  DECLARE_METHOD_INVOKE_HELPERS(__get);
  public: Variant t___set(Variant name, Variant value);
  DECLARE_METHOD_INVOKE_HELPERS(__set);
  public: bool t___isset(Variant name);
  DECLARE_METHOD_INVOKE_HELPERS(__isset);
  public: Variant t___unset(Variant name);
  DECLARE_METHOD_INVOKE_HELPERS(__unset);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);
  public: void __attach_attributes();

  // implemented by HPHP
  public: c_SimpleXMLElement *create(String data, int64 options = 0, bool data_is_url = false, String ns = "", bool is_prefix = false);


 public:
  Object m_doc;
  xmlNodePtr m_node;
  Variant m_children;
  Variant m_attributes;
  Array m_array;
  bool m_is_text;
  bool m_free_text;
  bool m_is_attribute;
  bool m_is_children;
  bool m_is_property;
  virtual bool o_toBoolean() const;
  virtual int64 o_toInt64() const;
  virtual double o_toDouble() const;
  virtual Array o_toArray() const;
  virtual Variant *___lval(Variant v_name);
  virtual bool o_propExists(CStrRef s, CStrRef context = null_string);
  SmartPtr<c_SimpleXMLElement> m_parent;

 private:
  xmlXPathContextPtr m_xpath;
 public:
  Array __populate_m_array();
  virtual bool customSerializer() const {
	return m_is_text;
  };
  void customSerialize(VariableSerializer *serializer) const;
};

///////////////////////////////////////////////////////////////////////////////
// class LibXMLError

FORWARD_DECLARE_CLASS_BUILTIN(LibXMLError);
class c_LibXMLError : public ExtObjectData {
 public:
  DECLARE_CLASS(LibXMLError, LibXMLError, ObjectData)

  // need to implement
  public: c_LibXMLError(const ObjectStaticCallbacks *cb = &cw_LibXMLError);
  public: ~c_LibXMLError();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_LibXMLError *create();


};

///////////////////////////////////////////////////////////////////////////////
// class SimpleXMLElementIterator

FORWARD_DECLARE_CLASS_BUILTIN(SimpleXMLElementIterator);
class c_SimpleXMLElementIterator : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(SimpleXMLElementIterator, SimpleXMLElementIterator, ObjectData)

  // need to implement
  public: c_SimpleXMLElementIterator(const ObjectStaticCallbacks *cb = &cw_SimpleXMLElementIterator);
  public: ~c_SimpleXMLElementIterator();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: Variant t_current();
  DECLARE_METHOD_INVOKE_HELPERS(current);
  public: Variant t_key();
  DECLARE_METHOD_INVOKE_HELPERS(key);
  public: Variant t_next();
  DECLARE_METHOD_INVOKE_HELPERS(next);
  public: Variant t_rewind();
  DECLARE_METHOD_INVOKE_HELPERS(rewind);
  public: Variant t_valid();
  DECLARE_METHOD_INVOKE_HELPERS(valid);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_SimpleXMLElementIterator *create();


public:
  void set_parent(c_SimpleXMLElement* parent);
  void reset_iterator();

  SmartPtr<c_SimpleXMLElement> m_parent;
  ArrayIter *m_iter1;
  ArrayIter *m_iter2;
  bool m_property_iterator;
  String m_property_name;
  Variant m_prop_children;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_SIMPLEXML_H__
