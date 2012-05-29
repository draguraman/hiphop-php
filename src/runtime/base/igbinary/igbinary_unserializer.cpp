/**
 *
 * igbinary_unserializer.cpp
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#include <runtime/base/igbinary/igbinary_unserializer.h>
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
#include <runtime/base/array/array_init.h>
#include <runtime/base/util/request_local.h>
#include <runtime/ext/ext_json.h>
#include <runtime/base/externals.h>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

static StaticString s_unserialize("unserialize");
static StaticString s_PHP_Incomplete_Class("__PHP_Incomplete_Class");
static StaticString s_PHP_Incomplete_Class_Name("__PHP_Incomplete_Class_Name");

IGBinaryUnserializer::IGBinaryUnserializer() {
}

Variant
IGBinaryUnserializer::unserialize(CStrRef v) {
  struct igbinary_unserialize_data igsd;

  igbinary_unserialize_data_init(&igsd TSRMLS_CC);

  igsd.buffer = (uint8_t *) v.data();
  igsd.buffer_size = v.size();

  if (igbinary_unserialize_header(&igsd TSRMLS_CC)) {
    igbinary_unserialize_data_deinit(&igsd TSRMLS_CC);
    return FALSE;
  }

  Variant z;

  int r = igbinary_unserialize_zval(&igsd, z TSRMLS_CC);

  igbinary_unserialize_data_deinit(&igsd TSRMLS_CC);

  if(r) {
    z.setUninitNull();
    return FALSE;
  }
  else {
    return z;
  }
}

/* {{{ igbinary_unserialize_data_init */
/** Inits igbinary_unserialize_data_init. */
int IGBinaryUnserializer::igbinary_unserialize_data_init(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
//  smart_str empty_str = { 0 };

  igsd->buffer = NULL;
  igsd->buffer_size = 0;
  igsd->buffer_offset = 0;

  igsd->strings = NULL;
  igsd->strings_count = 0;
  igsd->strings_capacity = 4;

  igsd->error = 0;

  igsd->strings = (struct igbinary_unserialize_string_pair *) malloc(
      sizeof(struct igbinary_unserialize_string_pair) * igsd->strings_capacity);
  if (igsd->strings == NULL) {
    return 1;
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_data_deinit */
/** Deinits igbinary_unserialize_data_init. */
void IGBinaryUnserializer::igbinary_unserialize_data_deinit(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  if (igsd->strings) {
    efree(igsd->strings);
  }

  return;
}
/* }}} */
/* {{{ igbinary_unserialize_header */
/** Unserialize header. Check for version. */
int IGBinaryUnserializer::igbinary_unserialize_header(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  uint32_t version;

  if (igsd->buffer_offset + 4 >= igsd->buffer_size) {
    return 1;
  }

  version = igbinary_unserialize32(igsd TSRMLS_CC);

  /* Support older version 1 and the current format 2 */
  if (version == IGBINARY_FORMAT_VERSION || version == 0x00000001) {
    return 0;
  } else {
    raise_warning(
        "igbinary_unserialize_header: unsupported version: %u, should be %u or %u",
        (unsigned int) version, 0x00000001,
        (unsigned int) IGBINARY_FORMAT_VERSION);
    return 1;
  }
}
/* }}} */
/* {{{ igbinary_unserialize8 */
/** Unserialize 8bit value. */
uint8_t IGBinaryUnserializer::igbinary_unserialize8(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  uint8_t ret = 0;
  ret = igsd->buffer[igsd->buffer_offset++];
  return ret;
}
/* }}} */
/* {{{ igbinary_unserialize16 */
/** Unserialize 16bit value. */
uint16_t IGBinaryUnserializer::igbinary_unserialize16(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  uint16_t ret = 0;
  ret |= ((uint16_t) igsd->buffer[igsd->buffer_offset++] << 8);
  ret |= ((uint16_t) igsd->buffer[igsd->buffer_offset++] << 0);
  return ret;
}
/* }}} */
/* {{{ igbinary_unserialize32 */
/** Unserialize 32bit value. */
uint32_t IGBinaryUnserializer::igbinary_unserialize32(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  uint32_t ret = 0;
  ret |= ((uint32_t) igsd->buffer[igsd->buffer_offset++] << 24);
  ret |= ((uint32_t) igsd->buffer[igsd->buffer_offset++] << 16);
  ret |= ((uint32_t) igsd->buffer[igsd->buffer_offset++] << 8);
  ret |= ((uint32_t) igsd->buffer[igsd->buffer_offset++] << 0);
  return ret;
}
/* }}} */
/* {{{ igbinary_unserialize64 */
/** Unserialize 64bit value. */
uint64_t IGBinaryUnserializer::igbinary_unserialize64(
    struct igbinary_unserialize_data *igsd TSRMLS_DC) {
  uint64_t ret = 0;
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 56);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 48);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 40);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 32);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 24);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 16);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 8);
  ret |= ((uint64_t) igsd->buffer[igsd->buffer_offset++] << 0);
  return ret;
}
/* }}} */
/* {{{ igbinary_unserialize_long */
/** Unserializes long */
int IGBinaryUnserializer::igbinary_unserialize_long(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {
  long ret;

  uint32_t tmp32;
#if SIZEOF_LONG == 8
  uint64_t tmp64;
#endif

  if (t == igbinary_type_long8p || t == igbinary_type_long8n) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_long: end-of-data");
      return 1;
    }

    ret = (long) (t == igbinary_type_long8n ? -1 : 1)
        * igbinary_unserialize8(igsd TSRMLS_CC);
  } else if (t == igbinary_type_long16p || t == igbinary_type_long16n) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_long: end-of-data");
      return 1;
    }

    ret = (long) (t == igbinary_type_long16n ? -1 : 1)
        * igbinary_unserialize16(igsd TSRMLS_CC);
  } else if (t == igbinary_type_long32p || t == igbinary_type_long32n) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_long: end-of-data");
      return 1;
    }

    /* check for boundaries */
    tmp32 = igbinary_unserialize32(igsd TSRMLS_CC);
#if SIZEOF_LONG == 4
    if (tmp32 > 0x80000000 || (tmp32 == 0x80000000 && t == igbinary_type_long32p)) {
      raise_warning("igbinary_unserialize_long: 64bit long on 32bit platform?");
      tmp32 = 0; /* t == igbinary_type_long32p ? LONG_MAX : LONG_MIN; */
    }
#endif
    ret = (long) (t == igbinary_type_long32n ? -1 : 1) * tmp32;
  } else if (t == igbinary_type_long64p || t == igbinary_type_long64n) {
#if SIZEOF_LONG == 8
    if (igsd->buffer_offset + 8 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_long: end-of-data");
      return 1;
    }

    /* check for boundaries */
    tmp64 = igbinary_unserialize64(igsd TSRMLS_CC);
    if (tmp64 > 0x8000000000000000
        || (tmp64 == 0x8000000000000000 && t == igbinary_type_long64p)) {
      raise_warning("igbinary_unserialize_long: too big 64bit long.");
      tmp64 = 0; /* t == igbinary_type_long64p ? LONG_MAX : LONG_MIN */
      ;
    }

    ret = (long) (t == igbinary_type_long64n ? -1 : 1) * tmp64;
#elif SIZEOF_LONG == 4
    /* can't put 64bit long into 32bit one, placeholder zero */
    *ret = 0;
    igbinary_unserialize64(igsd TSRMLS_CC);
    raise_warning("igbinary_unserialize_long: 64bit long on 32bit platform");
#else
#error "Strange sizeof(long)."
#endif
  } else {
    ret = 0;
    raise_warning(
        "igbinary_unserialize_long: unknown type '%02x', position %zu", t,
        igsd->buffer_offset);
    return 1;
  }

  z.assignVal(ret);

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_double */
/** Unserializes double. */
int IGBinaryUnserializer::igbinary_unserialize_double(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {
  union {
    double d;
    uint64_t u;
  } u;

  (void) t;

  if (igsd->buffer_offset + 8 > igsd->buffer_size) {
    raise_warning("igbinary_unserialize_double: end-of-data");
    return 1;
  }

  u.u = igbinary_unserialize64(igsd TSRMLS_CC);

  z.assignVal(u.d);

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_string */
/** Unserializes string. Unserializes both actual string or by string id. */
int IGBinaryUnserializer::igbinary_unserialize_string(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {
  size_t i;
  if (t == igbinary_type_string_id8 || t == igbinary_type_object_id8) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_string: end-of-data");
      return 1;
    }
    i = igbinary_unserialize8(igsd TSRMLS_CC);
  } else if (t == igbinary_type_string_id16 || t == igbinary_type_object_id16) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_string: end-of-data");
      return 1;
    }
    i = igbinary_unserialize16(igsd TSRMLS_CC);
  } else if (t == igbinary_type_string_id32 || t == igbinary_type_object_id32) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_string: end-of-data");
      return 1;
    }
    i = igbinary_unserialize32(igsd TSRMLS_CC);
  } else {
    raise_warning(
        "igbinary_unserialize_string: unknown type '%02x', position %zu", t,
        igsd->buffer_offset);
    return 1;
  }

  if (i >= igsd->strings_count) {
    raise_warning("igbinary_unserialize_string: string index is out-of-bounds");
    return 1;
  }

  z = NEW(StringData)(igsd->strings[i].data, igsd->strings[i].len, CopyString);
  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_chararray */
/** Unserializes chararray of string. */
int IGBinaryUnserializer::igbinary_unserialize_chararray(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {
  size_t l;

  if (t == igbinary_type_string8 || t == igbinary_type_object8) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
    l = igbinary_unserialize8(igsd TSRMLS_CC);
    if (igsd->buffer_offset + l > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
  } else if (t == igbinary_type_string16 || t == igbinary_type_object16) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
    l = igbinary_unserialize16(igsd TSRMLS_CC);
    if (igsd->buffer_offset + l > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
  } else if (t == igbinary_type_string32 || t == igbinary_type_object32) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
    l = igbinary_unserialize32(igsd TSRMLS_CC);
    if (igsd->buffer_offset + l > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_chararray: end-of-data");
      return 1;
    }
  } else {
    raise_warning(
        "igbinary_unserialize_chararray: unknown type '%02x', position %zu", t,
        igsd->buffer_offset);
    return 1;
  }

  if (igsd->strings_count + 1 > igsd->strings_capacity) {
    while (igsd->strings_count + 1 > igsd->strings_capacity) {
      igsd->strings_capacity *= 2;
    }

    igsd->strings = (struct igbinary_unserialize_string_pair *) erealloc(
        igsd->strings,
        sizeof(struct igbinary_unserialize_string_pair)
            * igsd->strings_capacity);
    if (igsd->strings == NULL) {
      return 1;
    }
  }

  igsd->strings[igsd->strings_count].data = (char *) (igsd->buffer + igsd->buffer_offset);
  igsd->strings[igsd->strings_count].len = l;

  igsd->buffer_offset += l;

  if (igsd->strings[igsd->strings_count].data == NULL) {
    return 1;
  }

  z = NEW(StringData)(igsd->strings[igsd->strings_count].data,
      igsd->strings[igsd->strings_count].len, CopyString);

  igsd->strings_count += 1;

  return 0;
}

/* }}} */
/* {{{ igbinary_unserialize_array */
/** Unserializes array. */
int IGBinaryUnserializer::igbinary_unserialize_array(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t,
    Variant& z TSRMLS_DC) {
  size_t n;
  size_t i;

  enum igbinary_type key_type;

  if (t == igbinary_type_array8) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_array: end-of-data");
      return 1;
    }
    n = igbinary_unserialize8(igsd TSRMLS_CC);
  } else if (t == igbinary_type_array16) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_array: end-of-data");
      return 1;
    }
    n = igbinary_unserialize16(igsd TSRMLS_CC);
  } else if (t == igbinary_type_array32) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_array: end-of-data");
      return 1;
    }
    n = igbinary_unserialize32(igsd TSRMLS_CC);
  } else {
    raise_warning(
        "igbinary_unserialize_array: unknown type '%02x', position %zu", t,
        igsd->buffer_offset);
    return 1;
  }

  // n cannot be larger than the number of minimum "objects" in the array
  if (n > igsd->buffer_size - igsd->buffer_offset) {
    raise_warning("%s: data size %zu smaller that requested array length %zu.",
        "igbinary_unserialize_array", igsd->buffer_size - igsd->buffer_offset,
        n);
    return 1;
  }

  if( z.isArray() ) {
    igsd->m_refs.push_back(&z);
  }

  /* empty array */
  if (n == 0) {
    return 0;
  }

  for (i = 0; i < n; i++) {
    Variant key = null;

    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_array: end-of-data");
      return 1;
    }

    key_type = (enum igbinary_type) igbinary_unserialize8(igsd TSRMLS_CC);

    switch (key_type) {
      case igbinary_type_long8p:
      case igbinary_type_long8n:
      case igbinary_type_long16p:
      case igbinary_type_long16n:
      case igbinary_type_long32p:
      case igbinary_type_long32n:
      case igbinary_type_long64p:
      case igbinary_type_long64n:
        if (igbinary_unserialize_long(igsd, key_type, key TSRMLS_CC)) {
          raise_warning("igbinary_unserialize_long() returned null");
          return 1;
        }
        break;
      case igbinary_type_string_id8:
      case igbinary_type_string_id16:
      case igbinary_type_string_id32:
        if (igbinary_unserialize_string(igsd, key_type, key TSRMLS_CC)) {
          raise_warning("igbinary_unserialize_string() returned null");
          return 1;
        }
        break;
      case igbinary_type_string8:
      case igbinary_type_string16:
      case igbinary_type_string32:
        if (igbinary_unserialize_chararray(igsd, key_type, key TSRMLS_CC)) {
          raise_warning("igbinary_unserialize_chararray() returned null");
          return 1;
        }
        break;
      case igbinary_type_string_empty:
        key = "";
        break;
      case igbinary_type_null:
        continue;
      default:
        raise_warning(
            "igbinary_unserialize_array: unknown key type '%02x', position %zu",
            key_type, igsd->buffer_offset);
        return 1;
    }

    if (z.isArray()) {
      if( key.isIntVal() ) {
        Variant &tmp = z.toArrRef().lvalAt(key.toInt64());
        if( igbinary_unserialize_zval(igsd, tmp TSRMLS_CC) ) {
          raise_warning("igbinary_unserialize_zval() returned 1");
          return 1;
        }
      }
      else {
        String propName = NEW(StringData)(key.asCStrRef().data(), key.asCStrRef().size(), CopyString);
        Variant &tmp = z.toArrRef().lvalAt(propName);
        if( igbinary_unserialize_zval(igsd, tmp TSRMLS_CC) ) {
          raise_warning("igbinary_unserialize_zval() returned 1");
          return 1;
        }
      }
    } else { // See type_variant.cpp:3828
      if( !key.isString() ) {
        raise_warning("key type is not string %d", (int)key.getType());
        return 1;
      }

      Object obj = z.toObjRef();
      CStrRef clsName = obj->o_getClassName();

      CStrRef skey = key.toCStrRef();
      int subLen = 0;
      if (skey.size() > 0 && skey.charAt(0) == '\00') {
        if (skey.charAt(1) == '*') {
          subLen = 3; // protected
        } else {
          subLen = skey.find('\00', 1) + 1; // private, skipping class name
          if (subLen == String::npos) {
            throw Exception("Mangled private object property");
          }
        }
      }

      Variant tmp;
      DataType myType;
      void* valuePtr =
          subLen != 0 ?
              (skey.charAt(1) == '*' ?
                  obj->o_lvalptr(skey.substr(subLen), tmp, &myType, clsName) :
                  obj->o_lvalptr(skey.substr(subLen), tmp, &myType,
                      String(skey.data() + 1, subLen - 2, AttachLiteral)))
                      :
              obj->o_lvalptr(skey, tmp, &myType);

      if (!valuePtr) {
        Variant& value =
            subLen != 0 ?
                (skey.charAt(1) == '*' ?
                    obj->o_lval(skey.substr(subLen), tmp, clsName) :
                    obj->o_lval(skey.substr(subLen), tmp,
                        String(skey.data() + 1, subLen - 2, AttachLiteral)))
                        :
                obj->o_lval(skey, tmp);
        //value.unserialize(uns);
        if( igbinary_unserialize_zval(igsd, value TSRMLS_CC) ) {
          raise_warning("igbinary_unserialize_zval() returned 1");
          return 1;
        }
      } else if (myType != KindOfVariant) {
        if (myType == KindOfArray) {
          Array& myArr = *(Array*) valuePtr;
          Variant value;
          //value.unserialize(uns);
          if( igbinary_unserialize_zval(igsd, value TSRMLS_CC) ) {
            raise_warning("igbinary_unserialize_zval() returned 1");
            return 1;
          }
          myArr = value;
        } else {
          Variant value;
          switch (myType) {
            case KindOfBoolean:
              value = *(bool*) valuePtr;
              break;
            case KindOfInt32:
              value = *(int*) valuePtr;
              break;
            case KindOfInt64:
              value = *(int64*) valuePtr;
              break;
            case KindOfDouble:
              value = *(double*) valuePtr;
              break;
            case KindOfString:
              value = *(String*) valuePtr;
              break;
            case KindOfArray:
              value = *(Array*) valuePtr;
              break;
            case KindOfObject:
              value = *(Object*) valuePtr;
              break;
            default:
              throw Exception("Unknown Type of object seen '%d'", myType);
          }
          //value.unserialize(uns);
          if( igbinary_unserialize_zval(igsd, value TSRMLS_CC) ) {
            raise_warning("igbinary_unserialize_zval() returned 1");
            return 1;
          }
        }
      } else {
        Variant &value = *(Variant*) valuePtr;
        //value.unserialize(uns);
        if( igbinary_unserialize_zval(igsd, value TSRMLS_CC) ) {
          raise_warning("igbinary_unserialize_zval() returned 1");
          return 1;
        }
      }

   /*
      String propName = NEW(StringData)(key.asCStrRef().data(), key.asCStrRef().size(), CopyString);
      //z.toObjRef()->o_set(propName, v);

      // wli-TODO - refer to type_variant.cpp 3838
      Variant tmp;
      Variant &value = z.toObjRef()->o_lval(propName, tmp);
      if( igbinary_unserialize_zval(igsd, value TSRMLS_CC) ) {
        raise_warning("igbinary_unserialize_zval() returned 1");
        return 1;
      }
   */
    }
  }

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_object_ser */
/** Unserializes object's property array of objects implementing Serializable -interface. */
int IGBinaryUnserializer::igbinary_unserialize_object_ser(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t,
    Object& obj TSRMLS_DC) {
  size_t n;

  if (t == igbinary_type_object_ser8) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_object_ser: end-of-data");
      return 1;
    }
    n = igbinary_unserialize8(igsd TSRMLS_CC);
  } else if (t == igbinary_type_object_ser16) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_object_ser: end-of-data");
      return 1;
    }
    n = igbinary_unserialize16(igsd TSRMLS_CC);
  } else if (t == igbinary_type_object_ser32) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_object_ser: end-of-data");
      return 1;
    }
    n = igbinary_unserialize32(igsd TSRMLS_CC);
  } else {
    raise_warning(
        "igbinary_unserialize_object_ser: unknown type '%02x', position %zu", t,
        igsd->buffer_offset);
    return 1;
  }

  if (igsd->buffer_offset + n > igsd->buffer_size) {
    raise_warning("igbinary_unserialize_object_ser: end-of-data");
    return 1;
  }

  String serialized(
      (const char*) (igsd->buffer + igsd->buffer_offset), n, CopyString);

  try {
    if (!obj->o_instanceof("Serializable")) {
      raise_warning("%s didn't implement Serializable", obj->o_getClassName().data());
      return 1;
    }

    obj->o_invoke(s_unserialize, CREATE_VECTOR1(serialized), -1);
  } catch (ClassNotFoundException &e) {
    raise_warning("Calling unserialize failed with exception %s", e.getMessage().c_str());
    //wli - copied from Variant::unserialize case 'C'
    obj = create_object_only(s_PHP_Incomplete_Class);
    obj->o_set(s_PHP_Incomplete_Class_Name, obj->o_getClassName());
    obj->o_set("serialized", serialized);
  }

  igsd->buffer_offset += n;

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_object */
/** Unserialize object.
 * @see ext/standard/var_unserializer.c
 */
int IGBinaryUnserializer::igbinary_unserialize_object(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {

  Variant clsName;
  int r;


  if (t == igbinary_type_object8 || t == igbinary_type_object16 || t == igbinary_type_object32) {
    if (igbinary_unserialize_chararray(igsd, t, clsName TSRMLS_CC)) {
      raise_warning("igbinary_unserialize_chararray returned empty class name");
      return 1;
    }
  } else if (t == igbinary_type_object_id8 || t == igbinary_type_object_id16 || t == igbinary_type_object_id32) {
    if (igbinary_unserialize_string(igsd, t, clsName TSRMLS_CC)) {
      raise_warning("igbinary_unserialize_string returned empty class name");
      return 1;
    }
  } else {
    raise_warning(
        "igbinary_unserialize_object: unknown object type '%02x', position %zu",
        t, igsd->buffer_offset);
    return 1;
  }

  Object obj;
  do {
    try {
      obj = create_object_only(clsName);
    } catch (ClassNotFoundException &e) {
      obj = create_object_only(s_PHP_Incomplete_Class);
      obj->o_set(s_PHP_Incomplete_Class_Name, clsName);
    }
  } while (0);

  z = obj;

  igsd->m_refs.push_back(&z);

  /* store incomplete class name */
//  if (incomplete_class) {
//    php_store_class_name(*z, name, name_len);
//  }
  t = (enum igbinary_type) igbinary_unserialize8(igsd TSRMLS_CC);
  switch (t) {
    case igbinary_type_array8:
    case igbinary_type_array16:
    case igbinary_type_array32:
      r = igbinary_unserialize_array(igsd, t, z TSRMLS_CC);
      if( r ){
        raise_warning(
            "igbinary_unserialize_array failed type='%02x' position=%zu", t,
            igsd->buffer_offset);
      }

      break;
    case igbinary_type_object_ser8:
    case igbinary_type_object_ser16:
    case igbinary_type_object_ser32:
      r = igbinary_unserialize_object_ser(igsd, t, obj TSRMLS_CC);
      if( r ) {
        raise_warning(
            "igbinary_unserialize_object_ser failed type='%02x' position=%zu",
            t, igsd->buffer_offset);
      }
      break;
    default:
      raise_warning(
          "igbinary_unserialize_object: unknown object inner type '%02x', position %zu",
          t, igsd->buffer_offset);
      return 1;
      break;
  }

  if (r) {
    return r;
  }

  obj->t___wakeup();

  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_ref */
/** Unserializes array or object by reference. */
int IGBinaryUnserializer::igbinary_unserialize_ref(
    struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC) {
  size_t n;

  if (t == igbinary_type_ref8 || t == igbinary_type_objref8) {
    if (igsd->buffer_offset + 1 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_ref: end-of-data");
      return 1;
    }
    n = igbinary_unserialize8(igsd TSRMLS_CC);
  } else if (t == igbinary_type_ref16 || t == igbinary_type_objref16) {
    if (igsd->buffer_offset + 2 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_ref: end-of-data");
      return 1;
    }
    n = igbinary_unserialize16(igsd TSRMLS_CC);
  } else if (t == igbinary_type_ref32 || t == igbinary_type_objref32) {
    if (igsd->buffer_offset + 4 > igsd->buffer_size) {
      raise_warning("igbinary_unserialize_ref: end-of-data");
      return 1;
    }
    n = igbinary_unserialize32(igsd TSRMLS_CC);
  } else {
    raise_warning("igbinary_unserialize_ref: unknown type '%02x', position %zu",
        t, igsd->buffer_offset);
    return 1;
  }

  if (n >= (size_t)igsd->m_refs.size()) {
    raise_warning("igbinary_unserialize_ref: invalid reference");
    return 1;
  }

  z.assignRef(*(igsd->m_refs[(int)n]));
  return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_zval */
/** Unserialize zval. */
int IGBinaryUnserializer::igbinary_unserialize_zval(
    struct igbinary_unserialize_data *igsd, Variant& z TSRMLS_DC) {
  enum igbinary_type t;

  if (igsd->buffer_offset + 1 > igsd->buffer_size) {
    raise_warning("igbinary_unserialize_zval: end-of-data");
    return 1;
  }

  t = (enum igbinary_type) igbinary_unserialize8(igsd TSRMLS_CC);

  switch (t) {
    case igbinary_type_ref:
      if (igbinary_unserialize_zval(igsd, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_ref failed type='%02x' igsd-position=%zu", t,
            igsd->buffer_offset);
        return 1;
      }
      // wli-TODO
      /* Scalar types should be added to the references hash */
      /* unless they're already added */
      /* in references list: marked as ref */
      if( !IS_REFCOUNTED_TYPE(z.getType()) )
        switch (z.getType()) {
          case IS_STRING:
          case IS_STATIC_STRING:
          case IS_LONG:
          case IS_NULL:
          case IS_DOUBLE:
          case IS_BOOL:
            /* reference */
            igsd->m_refs.push_back(&z);
          default:
            break;
        }
//      Z_SET_ISREF_TO_PP(z, true);
//      z.incRefCount(); //wli-TODO
      break;
    case igbinary_type_objref8:
    case igbinary_type_objref16:
    case igbinary_type_objref32:
    case igbinary_type_ref8:
    case igbinary_type_ref16:
    case igbinary_type_ref32:
      if (igbinary_unserialize_ref(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_ref failed type='%02x' igsd-position=%zu", t,
            igsd->buffer_offset);
        return 1;
      }
      break;
    case igbinary_type_object8:
    case igbinary_type_object16:
    case igbinary_type_object32:
    case igbinary_type_object_id8:
    case igbinary_type_object_id16:
    case igbinary_type_object_id32:
      if (igbinary_unserialize_object(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_object failed type='%02x' igsd-position=%zu",
            t, igsd->buffer_offset);
        return 1;
      }
      break;
    case igbinary_type_array8:
    case igbinary_type_array16:
    case igbinary_type_array32:
    {
      z = Array::Create();
      if( igbinary_unserialize_array(igsd, t, z TSRMLS_CC) ) {
        raise_warning(
            "igbinary_unserialize_array failed type='%02x' igsd-position=%zu",
            t, igsd->buffer_offset);
        return 1;
      }
      break;
    }
    case igbinary_type_string_empty:
      z = empty_string;
      break;
    case igbinary_type_string_id8:
    case igbinary_type_string_id16:
    case igbinary_type_string_id32:
      if (igbinary_unserialize_string(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_string failed type='%02x' igsd-position=%zu",
            t, igsd->buffer_offset);
        return 1;
      }
      break;
    case igbinary_type_string8:
    case igbinary_type_string16:
    case igbinary_type_string32:
      if (igbinary_unserialize_chararray(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_chararray failed type='%02x' igsd-position=%zu",
            t, igsd->buffer_offset);
        return 1;
      }
      break;
    case igbinary_type_long8p:
    case igbinary_type_long8n:
    case igbinary_type_long16p:
    case igbinary_type_long16n:
    case igbinary_type_long32p:
    case igbinary_type_long32n:
    case igbinary_type_long64p:
    case igbinary_type_long64n:
      if (igbinary_unserialize_long(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_long failed type='%02x' igsd-position=%zu", t,
            igsd->buffer_offset);
        return 1;
      }
      break;
    case igbinary_type_null:
      z.setNull();
      break;
    case igbinary_type_bool_false:
      z.assignVal((bool)false);
      break;
    case igbinary_type_bool_true:
      z.assignVal((bool)true);
      break;
    case igbinary_type_double:
      if (igbinary_unserialize_double(igsd, t, z TSRMLS_CC)) {
        raise_warning(
            "igbinary_unserialize_double failed type='%02x' igsd-position=%zu",
            t, igsd->buffer_offset);
        return 1;
      }
      break;
    default:
      raise_warning(
          "igbinary_unserialize_zval: unknown type '%02x', position %zu", t,
          igsd->buffer_offset);
      return 1;
  }

  return 0;
}
/* }}} */

///////////////////////////////////////////////////////////////////////////////
}
