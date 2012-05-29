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
 * igbinary_types.h
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#ifndef __HPHP_IGBINARY_TYPES_H__
#define __HPHP_IGBINARY_TYPES_H__

#define TSRMLS_DC
#define TSRMLS_CC

#include "php_config.h"
#include "ig_win32.h"
#include "php_smart_str.h"
#include <runtime/base/types.h>

/** Binary protocol version of igbinary. */
#define IGBINARY_FORMAT_VERSION 0x00000002

/* Data type mapping */
#define IS_NULL           KindOfNull
#define IS_LONG           KindOfInt64
#define IS_DOUBLE         KindOfDouble
#define IS_BOOL           KindOfBoolean
#define IS_ARRAY          KindOfArray
#define IS_OBJECT         KindOfObject
#define IS_STRING         KindOfString
#define IS_STATIC_STRING  KindOfStaticString
#define IS_RESOURCE       50

/* zend.h
#define IS_NULL         0
#define IS_LONG         1
#define IS_DOUBLE       2
#define IS_BOOL         3
#define IS_ARRAY        4
#define IS_OBJECT       5
#define IS_STRING       6
#define IS_RESOURCE     7
#define IS_CONSTANT     8
#define IS_CONSTANT_ARRAY       9
*/

/* types.h
enum DataType {
  KindOfUninit  = 0,
  KindOfNull    = 1,
  KindOfBoolean = 2,
  KindOfInt32   = 3,
  KindOfInt64   = 4,
  KindOfDouble  = 5,
  KindOfStaticString  = 6,
  KindOfString  = 7,
  KindOfArray   = 8,
  KindOfObject  = 9,
  KindOfVariant = 10,

  MaxNumDataTypes = 11, // marker, not a valid type

  MaxDataType   = 0x7fffffff // Allow KindOf* > 11 in HphpArray.
};
  */

#define Z_ISREF_P(z) z.isReferenced()
#define Z_TYPE_P(z) (!z.isInitialized() ? IS_NULL : (z.isResource() ? IS_RESOURCE : z.getType()))

#define Z_STRVAL_P(zval_p)      ((char *)(zval_p).asCStrRef().data())
#define Z_STRLEN_P(zval_p)      (zval_p).asCStrRef().size()

#define Z_LVAL_P(zval)          (zval).toInt32()
#define Z_DVAL_P(zval)          (zval).toDouble()

#define Z_OBJPROP_P(zval_p)     (zval_p).asCObjRef().toArray()

/* php_incomplete_class.h */
#define INCOMPLETE_CLASS "__PHP_Incomplete_Class"
#define MAGIC_MEMBER "__PHP_Incomplete_Class_Name"

/* {{{ Types */
enum igbinary_type
{
  /* 00 */igbinary_type_null, /**< Null. */

  /* 01 */igbinary_type_ref8, /**< Array reference. */
  /* 02 */igbinary_type_ref16, /**< Array reference. */
  /* 03 */igbinary_type_ref32, /**< Array reference. */

  /* 04 */igbinary_type_bool_false, /**< Boolean true. */
  /* 05 */igbinary_type_bool_true, /**< Boolean false. */

  /* 06 */igbinary_type_long8p, /**< Long 8bit positive. */
  /* 07 */igbinary_type_long8n, /**< Long 8bit negative. */
  /* 08 */igbinary_type_long16p, /**< Long 16bit positive. */
  /* 09 */igbinary_type_long16n, /**< Long 16bit negative. */
  /* 0a */igbinary_type_long32p, /**< Long 32bit positive. */
  /* 0b */igbinary_type_long32n, /**< Long 32bit negative. */

  /* 0c */igbinary_type_double, /**< Double. */

  /* 0d */igbinary_type_string_empty, /**< Empty string. */

  /* 0e */igbinary_type_string_id8, /**< String id. */
  /* 0f */igbinary_type_string_id16, /**< String id. */
  /* 10 */igbinary_type_string_id32, /**< String id. */

  /* 11 */igbinary_type_string8, /**< String. */
  /* 12 */igbinary_type_string16, /**< String. */
  /* 13 */igbinary_type_string32, /**< String. */

  /* 14 */igbinary_type_array8, /**< Array. */
  /* 15 */igbinary_type_array16, /**< Array. */
  /* 16 */igbinary_type_array32, /**< Array. */

  /* 17 */igbinary_type_object8, /**< Object. */
  /* 18 */igbinary_type_object16, /**< Object. */
  /* 19 */igbinary_type_object32, /**< Object. */

  /* 1a */igbinary_type_object_id8, /**< Object string id. */
  /* 1b */igbinary_type_object_id16, /**< Object string id. */
  /* 1c */igbinary_type_object_id32, /**< Object string id. */

  /* 1d */igbinary_type_object_ser8, /**< Object serialized data. */
  /* 1e */igbinary_type_object_ser16, /**< Object serialized data. */
  /* 1f */igbinary_type_object_ser32, /**< Object serialized data. */

  /* 20 */igbinary_type_long64p, /**< Long 64bit positive. */
  /* 21 */igbinary_type_long64n, /**< Long 64bit negative. */

  /* 22 */igbinary_type_objref8, /**< Object reference. */
  /* 23 */igbinary_type_objref16, /**< Object reference. */
  /* 24 */igbinary_type_objref32, /**< Object reference. */

  /* 25 */igbinary_type_ref,
/**< Simple reference */
};

#endif /* __HPHP_IGBINARY_TYPES_H__ */
