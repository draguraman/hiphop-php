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
/**
 *
 * igbinary_serializer.cpp
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#include <runtime/base/igbinary/igbinary_serializer.h>
#include <runtime/base/execution_context.h>
#include <runtime/base/complex_types.h>
#include <util/exception.h>
#include <runtime/base/zend/zend_printf.h>
#include <runtime/base/zend/zend_functions.h>
#include <runtime/base/zend/zend_string.h>
#include <runtime/base/class_info.h>
#include <math.h>
#include <runtime/base/runtime_option.h>
#include <runtime/base/array/array_iterator.h>
#include <runtime/base/util/request_local.h>
#include <runtime/ext/ext_json.h>

#include "hash_function.h"

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

static StaticString s___callStatic("__callStatic");
static StaticString s_serialize("serialize");

Variant f_print_r(CVarRef expression, bool ret /* = false */);

IGBinarySerializer::IGBinarySerializer() {
}

String
IGBinarySerializer::serialize(CVarRef v) {
  struct igbinary_serialize_data igsd;
  if (igbinary_serialize_data_init(&igsd,
      Z_TYPE_P(v) != IS_OBJECT && Z_TYPE_P(v) != IS_ARRAY TSRMLS_CC)) {
    raise_warning("igbinary_serialize: cannot init igsd");
    return null_string;
  }

  if (igbinary_serialize_header(&igsd TSRMLS_CC) != 0) {
    raise_warning("igbinary_serialize: cannot write header");
    igbinary_serialize_data_deinit(&igsd TSRMLS_CC);
    return null_string;
  }

  if (igbinary_serialize_zval(&igsd, v TSRMLS_CC) != 0) {
    igbinary_serialize_data_deinit(&igsd TSRMLS_CC);
    return null_string;
  }

  String ret((const char*)igsd.buffer, igsd.buffer_size, CopyString);

  igbinary_serialize_data_deinit(&igsd TSRMLS_CC);

  return ret;
}

/* {{{ igbinary_serialize_data_init */
/** Inits igbinary_serialize_data. */
int IGBinarySerializer::igbinary_serialize_data_init(
    struct igbinary_serialize_data *igsd, bool scalar TSRMLS_DC) {
  int r = 0;

  igsd->buffer = NULL;
  igsd->buffer_size = 0;
  igsd->buffer_capacity = 32;
  igsd->string_count = 0;
  igsd->error = 0;

  igsd->buffer = (uint8_t *) emalloc(igsd->buffer_capacity);
  if (igsd->buffer == NULL) {
    return 1;
  }

  igsd->scalar = scalar;
  if (!igsd->scalar) {
    hash_si_init(&igsd->strings, 16);
    hash_si_init(&igsd->objects, 16);
  }

  igsd->compact_strings = true; // (bool) IGBINARY_G(compact_strings);

  return r;
}
/* }}} */
/* {{{ igbinary_serialize_data_deinit */
/** Deinits igbinary_serialize_data. */
void IGBinarySerializer::igbinary_serialize_data_deinit(
    struct igbinary_serialize_data *igsd TSRMLS_DC) {
  if (igsd->buffer) {
    efree(igsd->buffer);
  }

  if (!igsd->scalar) {
    hash_si_deinit(&igsd->strings);
    hash_si_deinit(&igsd->objects);
  }
}
/* }}} */
/* {{{ igbinary_serialize_header */
/** Serializes header. */
int IGBinarySerializer::igbinary_serialize_header(
    struct igbinary_serialize_data *igsd TSRMLS_DC) {
  return igbinary_serialize32(igsd, IGBINARY_FORMAT_VERSION TSRMLS_CC); /* version */
}
/* }}} */
/* {{{ igbinary_serialize_resize */
/** Expands igbinary_serialize_data. */
int IGBinarySerializer::igbinary_serialize_resize(
    struct igbinary_serialize_data *igsd, size_t size TSRMLS_DC) {
  if (igsd->buffer_size + size < igsd->buffer_capacity) {
    return 0;
  }

  while (igsd->buffer_size + size >= igsd->buffer_capacity) {
    igsd->buffer_capacity *= 2;
  }

  igsd->buffer = (uint8_t *) erealloc(igsd->buffer, igsd->buffer_capacity);
  if (igsd->buffer == NULL
  )
    return 1;

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize8 */
/** Serialize 8bit value. */
int IGBinarySerializer::igbinary_serialize8(struct igbinary_serialize_data *igsd,
    uint8_t i TSRMLS_DC) {
  if (igbinary_serialize_resize(igsd, 1 TSRMLS_CC)) {
    return 1;
  }

  igsd->buffer[igsd->buffer_size++] = i;
  return 0;
}
/* }}} */
/* {{{ igbinary_serialize16 */
/** Serialize 16bit value. */
int IGBinarySerializer::igbinary_serialize16(struct igbinary_serialize_data *igsd,
    uint16_t i TSRMLS_DC) {
  if (igbinary_serialize_resize(igsd, 2 TSRMLS_CC)) {
    return 1;
  }

  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 8 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i & 0xff);

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize32 */
/** Serialize 32bit value. */
int IGBinarySerializer::igbinary_serialize32(struct igbinary_serialize_data *igsd,
    uint32_t i TSRMLS_DC) {
  if (igbinary_serialize_resize(igsd, 4 TSRMLS_CC)) {
    return 1;
  }

  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 24 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 16 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 8 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i & 0xff);

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize64 */
/** Serialize 64bit value. */
int IGBinarySerializer::igbinary_serialize64(struct igbinary_serialize_data *igsd,
    uint64_t i TSRMLS_DC) {
  if (igbinary_serialize_resize(igsd, 8 TSRMLS_CC)) {
    return 1;
  }

  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 56 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 48 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 40 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 32 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 24 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 16 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i >> 8 & 0xff);
  igsd->buffer[igsd->buffer_size++] = (uint8_t) (i & 0xff);

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_null */
/** Serializes null. */
int IGBinarySerializer::igbinary_serialize_null(
    struct igbinary_serialize_data *igsd TSRMLS_DC) {
  return igbinary_serialize8(igsd, igbinary_type_null TSRMLS_CC);
}
/* }}} */
/* {{{ igbinary_serialize_bool */
/** Serializes bool. */
int IGBinarySerializer::igbinary_serialize_bool(
    struct igbinary_serialize_data *igsd, int b TSRMLS_DC) {
  return igbinary_serialize8(
      igsd,
      (uint8_t) (
          b ? igbinary_type_bool_true : igbinary_type_bool_false) TSRMLS_CC);
}
/* }}} */
/* {{{ igbinary_serialize_long */
/** Serializes long. */
int IGBinarySerializer::igbinary_serialize_long(
    struct igbinary_serialize_data *igsd, long l TSRMLS_DC) {
  long k = l >= 0 ? l : -l;
  bool p = l >= 0 ? true : false;

  /* -LONG_MIN is 0 otherwise. */
  if (l == LONG_MIN) {
#if SIZEOF_LONG == 8
    igbinary_serialize8(igsd, (uint8_t) igbinary_type_long64n TSRMLS_CC);
    igbinary_serialize64(igsd, (uint64_t) 0x8000000000000000 TSRMLS_CC);
#elif SIZEOF_LONG == 4
    igbinary_serialize8(igsd, (uint8_t) igbinary_type_long32n TSRMLS_CC);
    igbinary_serialize32(igsd, (uint32_t) 0x80000000 TSRMLS_CC);
#else
#error "Strange sizeof(long)."
#endif
    return 0;
  }

  if (k <= 0xff) {
    igbinary_serialize8(igsd,
        (uint8_t) (p ? igbinary_type_long8p : igbinary_type_long8n) TSRMLS_CC);
    igbinary_serialize8(igsd, (uint8_t) k TSRMLS_CC);
  } else if (k <= 0xffff) {
    igbinary_serialize8(
        igsd,
        (uint8_t) (
            p ? igbinary_type_long16p : igbinary_type_long16n) TSRMLS_CC);
    igbinary_serialize16(igsd, (uint16_t) k TSRMLS_CC);
#if SIZEOF_LONG == 8
  } else if (k <= 0xffffffff) {
    igbinary_serialize8(
        igsd,
        (uint8_t) (
            p ? igbinary_type_long32p : igbinary_type_long32n) TSRMLS_CC);
    igbinary_serialize32(igsd, (uint32_t) k TSRMLS_CC);
  } else {
    igbinary_serialize8(
        igsd,
        (uint8_t) (
            p ? igbinary_type_long64p : igbinary_type_long64n) TSRMLS_CC);
    igbinary_serialize64(igsd, (uint64_t) k TSRMLS_CC);
  }
#elif SIZEOF_LONG == 4
} else {
  igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long32p : igbinary_type_long32n) TSRMLS_CC);
  igbinary_serialize32(igsd, (uint32_t) k TSRMLS_CC);
}
#else
#error "Strange sizeof(long)."
#endif

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_double */
/** Serializes double. */
int IGBinarySerializer::igbinary_serialize_double(
    struct igbinary_serialize_data *igsd, double d TSRMLS_DC) {
  union {
    double d;
    uint64_t u;
  } u;

  igbinary_serialize8(igsd, igbinary_type_double TSRMLS_CC);

  u.d = d;

  igbinary_serialize64(igsd, u.u TSRMLS_CC);

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_string */
/** Serializes string.
 * Serializes each string once, after first time uses pointers.
 */
int IGBinarySerializer::igbinary_serialize_string(
    struct igbinary_serialize_data *igsd, const char *s, size_t len TSRMLS_DC) {
  uint32_t t;
  uint32_t *i = &t;

  if (len == 0) {
    igbinary_serialize8(igsd, igbinary_type_string_empty TSRMLS_CC);
    return 0;
  }

  if (igsd->scalar || !igsd->compact_strings
      || hash_si_find(&igsd->strings, s, len, i) == 1) {
    if (!igsd->scalar && igsd->compact_strings) {
      hash_si_insert(&igsd->strings, s, len, igsd->string_count);
    }

    igsd->string_count += 1;

    if (igbinary_serialize_chararray(igsd, s, len TSRMLS_CC) != 0) {
      return 1;
    }
  } else {
    if (*i <= 0xff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id8 TSRMLS_CC);
      igbinary_serialize8(igsd, (uint8_t) *i TSRMLS_CC);
    } else if (*i <= 0xffff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id16 TSRMLS_CC);
      igbinary_serialize16(igsd, (uint16_t) *i TSRMLS_CC);
    } else {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id32 TSRMLS_CC);
      igbinary_serialize32(igsd, (uint32_t) *i TSRMLS_CC);
    }
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_chararray */
/** Serializes string data. */
int IGBinarySerializer::igbinary_serialize_chararray(
    struct igbinary_serialize_data *igsd, const char *s, size_t len TSRMLS_DC) {
  if (len <= 0xff) {
    igbinary_serialize8(igsd, igbinary_type_string8 TSRMLS_CC);
    igbinary_serialize8(igsd, len TSRMLS_CC);
  } else if (len <= 0xffff) {
    igbinary_serialize8(igsd, igbinary_type_string16 TSRMLS_CC);
    igbinary_serialize16(igsd, len TSRMLS_CC);
  } else {
    igbinary_serialize8(igsd, igbinary_type_string32 TSRMLS_CC);
    igbinary_serialize32(igsd, len TSRMLS_CC);
  }

  if (igbinary_serialize_resize(igsd, len TSRMLS_CC)) {
    return 1;
  }

  memcpy(igsd->buffer + igsd->buffer_size, s, len);
  igsd->buffer_size += len;

  return 0;
}

void IGBinarySerializer::writeToBuffer(struct igbinary_serialize_data *igsd, uint8_t c) {
  igsd->buffer[igsd->buffer_size++] = c;
}

void IGBinarySerializer::writeToBuffer(struct igbinary_serialize_data *igsd, const char* p) {
  int len = strlen(p);
  for(int i = 0; i < len; i++) {
    writeToBuffer(igsd, p[i]);
  }
}

std::vector<uint8_t>& append(std::vector<uint8_t>& buf, const char* p, int len) {
  for( int i = 0; i < len; i++ ) {
    buf.push_back(p[i]);
  }
  return buf;
}

void IGBinarySerializer::writeSerializedProperty(struct igbinary_serialize_data *igsd, CStrRef prop, const ClassInfo *cls) {
  const ClassInfo *origCls = cls;
  if (cls && (prop.size() > 0 && prop.charAt(0) != '\00') ) {
    ClassInfo::PropertyInfo *p = cls->getPropertyInfo(prop);
    // Try to find defining class
    while (!p && cls) {
      cls = cls->getParentClassInfo();
      if (cls) p = cls->getPropertyInfo(prop);
    }
    if (p) {
      const ClassInfo *dcls = p->owner;
      ClassInfo::Attribute a = p->attribute;
      if (a & ClassInfo::IsProtected) {
        std::vector<uint8_t> buf;

        buf.push_back('\0');
        buf.push_back('*');
        buf.push_back('\0');
        append(buf, prop.data(), prop.size());

        igbinary_serialize_string(igsd, (const char*)buf.data(), buf.size());
        return;
      } else if ((a & ClassInfo::IsPrivate) && cls == origCls) {
        std::vector<uint8_t> buf;

        const char *clsname = dcls->getName();
        int clsLen = strlen(clsname);

        buf.push_back('\0');
        append(buf, clsname, clsLen);
        buf.push_back('\0');
        append(buf, prop.data(), prop.size());

        igbinary_serialize_string(igsd, (const char*)buf.data(), buf.size());

        return;
      }
    }
  }

  igbinary_serialize_string(igsd, prop.data(), prop.size());
}

/* }}} */
/* {{{ igbinay_serialize_array */
/** Serializes array or objects inner properties. */
int IGBinarySerializer::igbinary_serialize_array(
    struct igbinary_serialize_data *igsd, CVarRef z, const ClassInfo* clsInfo,
    bool incomplete_class TSRMLS_DC , void *objIndex /* = NULL*/) {

  size_t n;

  Array odata=Array::Create();
  bool object = clsInfo != NULL;
  CArrRef h = object ? (z.getObjectData()->o_toArray_withInfo(&odata)) : z.toCArrRef();

  /* hash size */
  n = h.size();

  /* incomplete class magic member */
  if (n > 0 && incomplete_class) {
    --n;
  }
  if (!object && igbinary_serialize_array_ref(igsd, z, object TSRMLS_CC, objIndex) == 0) {
    return 0;
  }

  if (n <= 0xff) {
    igbinary_serialize8(igsd, igbinary_type_array8 TSRMLS_CC);
    igbinary_serialize8(igsd, n TSRMLS_CC);
  } else if (n <= 0xffff) {
    igbinary_serialize8(igsd, igbinary_type_array16 TSRMLS_CC);
    igbinary_serialize16(igsd, n TSRMLS_CC);
  } else {
    igbinary_serialize8(igsd, igbinary_type_array32 TSRMLS_CC);
    igbinary_serialize32(igsd, n TSRMLS_CC);
  }

  if (n == 0) {
    return 0;
  }

  /* serialize properties. */
  for (ArrayIter iter(h); iter; ++iter) {
    CVarRef key = iter.first();
    CVarRef val = iter.secondRef();

    /* skip magic member in incomplete classes */
    if (incomplete_class && strcmp(Z_STRVAL_P(key), MAGIC_MEMBER) == 0) {
      continue;
    }

    switch (key.getType()) {
      case KindOfInt32:
      case KindOfInt64:
        //wli TODO: the PHP version uses different way to get key_index
        igbinary_serialize_long(igsd, key.asInt64Val() TSRMLS_CC);
        break;
        //case HASH_KEY_IS_STRING:
      case KindOfStaticString:
      case KindOfString:
        writeSerializedProperty(igsd, key.toCStrRef(), clsInfo);
        break;
      default:
        raise_warning("igbinary_serialize_array: key is not string nor array type=%d", (int)key.getType());
        /* not reached */
        return 1;
    }

    /* we should still add element even if it's not OK,
     * since we already wrote the length of the array before */
    if (val.getType() == KindOfNull) {
      if (igbinary_serialize_null(igsd TSRMLS_CC)) {
        return 1;
      }
    } else {
	void *objIndex = NULL;
	if (val.getType() == KindOfArray /*&& val.toCArrRef()->size() == 0*/) {
		Variant *p = NULL;
		Variant tmp;
		//get the real property name for private members
		String realKey = key.toString().lastToken((char)0);
		DataType retType;
		if (z.getType() == KindOfObject) {
		Variant typeinfo,offsetinfo;
		if (odata.exists(realKey)) {
		Array typedata = odata[realKey];
		typeinfo = typedata["type"];
		offsetinfo = typedata["offset"];
		} else {
			// this is a dynamic member
			typeinfo = (int)KindOfVariant;
			offsetinfo = 0;
		}
		if (typeinfo.toInt64() == (int)KindOfVariant) { 
		p = (Variant*)z.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,clsInfo->getName());
		} else {
		objIndex = (char *)(z.getObjectData()) + offsetinfo.toInt64();
		}
		} else if (z.getType() == KindOfArray) {
			if (key.getType() == KindOfString || key.getType() == KindOfStaticString) {
			   p = z.toArray().lvalPtr(key.toCStrRef(),true, false);	
			} else {
			   p = z.toArray().lvalPtr(key.asInt64Val(),true, false);	
			}
		} else  {
			raise_error("Invalid type of object seen in serialize array");
		}
		if (p) {
	        if (igbinary_serialize_zval(igsd, *p TSRMLS_CC)) {
		  return 1;
	        } 
		} else if (objIndex) {
		
		if (igbinary_serialize_zval(igsd, val TSRMLS_CC, objIndex)) {
                  return 1;
                }
		} else {
			raise_error("Failure in serialize");
		}
	} else {
      if (igbinary_serialize_zval(igsd, val TSRMLS_CC)) {
        return 1;
      }
      }
    }
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_array_ref */
/** Serializes array reference. */
int IGBinarySerializer::igbinary_serialize_array_ref(
    struct igbinary_serialize_data *igsd, CVarRef z, bool object TSRMLS_DC, void *objIndex) {

  uint32_t t = 0;
  uint32_t *i = &t;

  union {
    void *z;
  } key = { 0 };

  if (!objIndex) {
  key.z = z.asDataPtr();
  } else {
  key.z = objIndex;
  }

  if (hash_si_find(&igsd->objects, (char *) &key, sizeof(key), i) == 1) {
    t = hash_si_size(&igsd->objects);
    hash_si_insert(&igsd->objects, (char *) &key, sizeof(key), t);
    return 1;
  } else {
    enum igbinary_type type;
    if (*i <= 0xff) {
      type = object ? igbinary_type_objref8 : igbinary_type_ref8;
      igbinary_serialize8(igsd, (uint8_t) type TSRMLS_CC);
      igbinary_serialize8(igsd, (uint8_t) *i TSRMLS_CC);
    } else if (*i <= 0xffff) {
      type = object ? igbinary_type_objref16 : igbinary_type_ref16;
      igbinary_serialize8(igsd, (uint8_t) type TSRMLS_CC);
      igbinary_serialize16(igsd, (uint16_t) *i TSRMLS_CC);
    } else {
      type = object ? igbinary_type_objref32 : igbinary_type_ref32;
      igbinary_serialize8(igsd, (uint8_t) type TSRMLS_CC);
      igbinary_serialize32(igsd, (uint32_t) *i TSRMLS_CC);
    }

    return 0;
  }

  return 1;
}
/* }}} */
/* {{{ igbinary_serialize_array_sleep */
/** Serializes object's properties array with __sleep -function. */
int IGBinarySerializer::igbinary_serialize_array_sleep(
    struct igbinary_serialize_data *igsd, CVarRef z, CArrRef props,
    const ObjectData *od, bool incomplete_class, const ClassInfo* clsInfo TSRMLS_DC) {

  size_t n = props.size();

  /* Serialize array id. */
  if (n <= 0xff) {
    igbinary_serialize8(igsd, igbinary_type_array8 TSRMLS_CC);
    igbinary_serialize8(igsd, n TSRMLS_CC);
  } else if (n <= 0xffff) {
    igbinary_serialize8(igsd, igbinary_type_array16 TSRMLS_CC);
    igbinary_serialize16(igsd, n TSRMLS_CC);
  } else {
    igbinary_serialize8(igsd, igbinary_type_array32 TSRMLS_CC);
    igbinary_serialize32(igsd, n TSRMLS_CC);
  }

  if (n == 0) {
    return 0;
  }
  Array odata = Array::Create();
  z.getObjectData()->o_toArray_withInfo(&odata);
  //Array wanted = Array::Create();
  for (ArrayIter iter(props); iter; ++iter) {
    CVarRef varName = iter.second();
    if( !varName.isString() ) {
      raise_warning("igbinary_serialize(): __sleep should return an array only containing the names of instance-variables to serialize. bad_prop=%s",
                f_print_r(varName, true).toCStrRef().data());
      igbinary_serialize_null(igsd TSRMLS_CC);
      continue;
    }

    String name = varName.toString();
    CVarRef val = od->o_exists(name, od->o_getClassName()) ?
        const_cast<ObjectData*>(od)->o_getUnchecked(name, od->o_getClassName()) : null;

    if( val.isNull() ) {
      raise_warning("\"%s\" returned as member variable from "
                    "__sleep() but does not exist", name.data());
    }

    /* skip magic member in incomplete classes */
    if (incomplete_class && strcmp(name.data(), MAGIC_MEMBER) == 0) {
      //TODO: what is it?
      continue;
    }

    if (val.isNull()) {
      /* we should still add element even if it's not OK,
       * since we already wrote the length of the array before
       * serialize null as key-value pair */
      igbinary_serialize_string(igsd, (const char*)name.data(), name.size());
      igbinary_serialize_null(igsd TSRMLS_CC);
    } else {
        writeSerializedProperty(igsd, name, clsInfo);
	// Need to handle empty arrays here also
	void *objIndex = NULL;
	if (val.getType() == KindOfArray /*&& val.toCArrRef()->size() == 0*/) {
		Variant *p = NULL;
		Variant tmp;
		DataType retType;
		Variant typeinfo,offsetinfo;
		//get the real property name for private members
		String realKey = varName.toString().lastToken((char)0);
		if (odata.exists(realKey)) {
		Array typedata = odata[realKey];
		typeinfo = typedata["type"];
		offsetinfo = typedata["offset"];
		} else {
			// this is a dynamic member
			typeinfo = (int)KindOfVariant;
			offsetinfo = 0;
		}
		if (typeinfo.toInt64() == (int)KindOfVariant) { 
		p = (Variant*)z.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,clsInfo->getName());
		} else {
		objIndex = (char *)(z.getObjectData()) + offsetinfo.toInt64();
		}
		if (p) {
	        if (igbinary_serialize_zval(igsd, *p TSRMLS_CC)) {
		  return 1;
	        } 
		} else if (objIndex) {
		
		if (igbinary_serialize_zval(igsd, val TSRMLS_CC, objIndex)) {
                  return 1;
                }
		} 
		} else {
        igbinary_serialize_zval(igsd, val TSRMLS_CC);
	}
    }
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_object_name */
/** Serialize object name. */
int IGBinarySerializer::igbinary_serialize_object_name(
    struct igbinary_serialize_data *igsd, const char *class_name,
    size_t name_len TSRMLS_DC) {
  uint32_t t;
  uint32_t *i = &t;

  if (hash_si_find(&igsd->strings, class_name, name_len, i) == 1) {
    hash_si_insert(&igsd->strings, class_name, name_len, igsd->string_count);
    igsd->string_count += 1;

    if (name_len <= 0xff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object8 TSRMLS_CC);
      igbinary_serialize8(igsd, (uint8_t) name_len TSRMLS_CC);
    } else if (name_len <= 0xffff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object16 TSRMLS_CC);
      igbinary_serialize16(igsd, (uint16_t) name_len TSRMLS_CC);
    } else {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object32 TSRMLS_CC);
      igbinary_serialize32(igsd, (uint32_t) name_len TSRMLS_CC);
    }

    if (igbinary_serialize_resize(igsd, name_len TSRMLS_CC)) {
      return 1;
    }

    memcpy(igsd->buffer + igsd->buffer_size, class_name, name_len);
    igsd->buffer_size += name_len;
  } else {
    /* already serialized string */
    if (*i <= 0xff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id8 TSRMLS_CC);
      igbinary_serialize8(igsd, (uint8_t) *i TSRMLS_CC);
    } else if (*i <= 0xffff) {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id16 TSRMLS_CC);
      igbinary_serialize16(igsd, (uint16_t) *i TSRMLS_CC);
    } else {
      igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id32 TSRMLS_CC);
      igbinary_serialize32(igsd, (uint32_t) *i TSRMLS_CC);
    }
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_serialize_object */
/** Serialize object.
 * @see ext/standard/var.c
 * */
int IGBinarySerializer::igbinary_serialize_object(
    struct igbinary_serialize_data *igsd, CVarRef z TSRMLS_DC) {
  int r = 0;

  size_t serialized_len;

  bool incomplete_class = false;

  if (igbinary_serialize_array_ref(igsd, z, true TSRMLS_CC) == 0) {
    return r;
  }

  const ObjectData *od = z.getObjectData();
  CStrRef className = od->o_getClassName();
  const ClassInfo* clsInfo = ClassInfo::FindClass(className);

  Variant ret;
  if (od->o_instanceof("Serializable")) {
    ret = const_cast<ObjectData*>(od)->o_invoke(s_serialize, Array(), -1);

    /* custom serializer */
    if (ret.isString()) {
      serialized_len = Z_STRLEN_P(ret);

      igbinary_serialize_object_name(igsd, className.c_str(), className.size());

      if (serialized_len <= 0xff) {
        igbinary_serialize8(igsd,
            (uint8_t) igbinary_type_object_ser8 TSRMLS_CC);
        igbinary_serialize8(igsd, (uint8_t) serialized_len TSRMLS_CC);
      } else if (serialized_len <= 0xffff) {
        igbinary_serialize8(igsd,
            (uint8_t) igbinary_type_object_ser16 TSRMLS_CC);
        igbinary_serialize16(igsd, (uint16_t) serialized_len TSRMLS_CC);
      } else {
        igbinary_serialize8(igsd,
            (uint8_t) igbinary_type_object_ser32 TSRMLS_CC);
        igbinary_serialize32(igsd, (uint32_t) serialized_len TSRMLS_CC);
      }

      if (igbinary_serialize_resize(igsd, serialized_len TSRMLS_CC)) {
        r = 1;
        return r;
      }

      memcpy(igsd->buffer + igsd->buffer_size, Z_STRVAL_P(ret), serialized_len);
      igsd->buffer_size += serialized_len;
    } else {
      /* Serialization callback failed, assume null output */
      raise_warning("Failed to call Serializable for class %s",
          className.c_str());
      igbinary_serialize_null(igsd TSRMLS_CC);
    }

    return r;
  }

  /* serialize class name */
  igbinary_serialize_object_name(igsd, className.c_str(),
      className.size() TSRMLS_CC);

  if (const_cast<ObjectData*>(od)->php_sleep(ret)) {
    if (ret.isArray()) {
      r = igbinary_serialize_array_sleep(igsd, z, ret, od, incomplete_class, clsInfo TSRMLS_CC);
    } else {
      raise_notice(
          "__sleep should return an array only containing the names of instance-variables to serialize");

      /* empty array */
      igbinary_serialize8(igsd, igbinary_type_array8 TSRMLS_CC);
      r = igbinary_serialize8(igsd, 0 TSRMLS_CC);
    }
    return r;
  } else {
    return igbinary_serialize_array(igsd, z, clsInfo, incomplete_class TSRMLS_CC);
  }
}
/* }}} */
/* {{{ igbinary_serialize_zval */
/** Serialize zval. */
int IGBinarySerializer::igbinary_serialize_zval(
    struct igbinary_serialize_data *igsd, CVarRef z TSRMLS_DC, void *objIndex /* = NULL */) {

  if (Z_ISREF_P(z)) {
    igbinary_serialize8(igsd, (uint8_t) igbinary_type_ref TSRMLS_CC);
    /* Complex types serialize a reference, scalars do not... */
    /* FIXME: Absolutely wrong level to check this. */
    switch (Z_TYPE_P(z)) {
      case IS_RESOURCE:
      case IS_STRING:
      case IS_STATIC_STRING:
      case IS_LONG:
      case IS_NULL:
      case IS_BOOL:
      case IS_DOUBLE:
        /* Serialize a reference if zval already added */
        if (igbinary_serialize_array_ref(igsd, z, false TSRMLS_CC, objIndex) == 0) {
          return 0;
        }
        /* otherwise fall through */
    }
  }
 
  switch (Z_TYPE_P(z)) {
    case IS_RESOURCE:
      return igbinary_serialize_null(igsd TSRMLS_CC);
    case IS_OBJECT:
      return igbinary_serialize_object(igsd, z TSRMLS_CC);
    case IS_ARRAY:
      return igbinary_serialize_array(igsd, z, NULL, false TSRMLS_CC, objIndex);
    case IS_STRING:
    case IS_STATIC_STRING:
      return igbinary_serialize_string(igsd, Z_STRVAL_P(z) ,
          Z_STRLEN_P(z) TSRMLS_CC);
    case IS_LONG:
      return igbinary_serialize_long(igsd, Z_LVAL_P(z) TSRMLS_CC);
    case IS_NULL:
      return igbinary_serialize_null(igsd TSRMLS_CC);
    case IS_BOOL:
      return igbinary_serialize_bool(igsd, Z_LVAL_P(z) ? 1 : 0 TSRMLS_CC);
    case IS_DOUBLE:
      return igbinary_serialize_double(igsd, Z_DVAL_P(z) TSRMLS_CC);
    default:
      raise_warning("igbinary_serialize_zval: zval has unknown type %d",
          (int) Z_TYPE_P(z));
      /* not reached */
      return 1;
  }

  return 0;
}
///////////////////////////////////////////////////////////////////////////////
}
