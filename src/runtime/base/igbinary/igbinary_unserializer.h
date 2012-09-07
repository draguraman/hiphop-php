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
 * igbinary_unserializer.h
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#ifndef __HPHP_IGBINARY_UNSERIALIZER_H__
#define __HPHP_IGBINARY_UNSERIALIZER_H__

#include <runtime/base/types.h>
#include <runtime/base/util/string_buffer.h>
#include <runtime/base/igbinary/igbinary_types.h>
#include <runtime/base/complex_types.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

class IGBinaryUnserializer {

    /** String/len pair for the igbinary_unserializer_data.
     * @author Oleg Grenrus <oleg.grenrus@dynamoid.com>
     * @see igbinary_unserialize_data.
     */
    struct igbinary_unserialize_string_pair
    {
      char *data; /**< Data. */
      size_t len; /**< Data length. */
    };

    /** Unserializer data.
     * @author Oleg Grenrus <oleg.grenrus@dynamoid.com>
     */
    struct igbinary_unserialize_data
    {
      uint8_t *buffer; /**< Buffer. */
      size_t buffer_size; /**< Buffer size. */
      size_t buffer_offset; /**< Current read offset. */

      struct igbinary_unserialize_string_pair *strings; /**< Unserialized strings. */
      size_t strings_count; /**< Unserialized string count. */
      size_t strings_capacity; /**< Unserialized string array capacity. */

      std::vector<Variant*> m_refs;
      std::vector<Variant> holderVariants;
//      void **references; /**< Unserialized Arrays/Objects. */
//      size_t references_count; /**< Unserialized array/objects count. */
//      size_t references_capacity; /**< Unserialized array/object array capacity. */

      bool lookingForRef;
      int error; /**< Error number. Not used. */
      // wli-todo: remove php_smart_str_public.h
//      smart_str string0_buf; /**< Temporary buffer for strings */
    };

public:

  /**
   * Constructor and destructor.
   */
  IGBinaryUnserializer();
  ~IGBinaryUnserializer() {
  }

  Variant unserialize(CStrRef v);

private:
  inline static Variant& getHolderVariant(struct igbinary_unserialize_data *igsd TSRMLS_DC);
  inline static int igbinary_unserialize_data_init(struct igbinary_unserialize_data *igsd TSRMLS_DC);
  inline static void igbinary_unserialize_data_deinit(struct igbinary_unserialize_data *igsd TSRMLS_DC);

  inline static int igbinary_unserialize_header(struct igbinary_unserialize_data *igsd TSRMLS_DC);

  inline static uint8_t igbinary_unserialize8(struct igbinary_unserialize_data *igsd TSRMLS_DC);
  inline static uint16_t igbinary_unserialize16(struct igbinary_unserialize_data *igsd TSRMLS_DC);
  inline static uint32_t igbinary_unserialize32(struct igbinary_unserialize_data *igsd TSRMLS_DC);
  inline static uint64_t igbinary_unserialize64(struct igbinary_unserialize_data *igsd TSRMLS_DC);

  inline static int igbinary_unserialize_long(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);
  inline static int igbinary_unserialize_double(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);
  inline static int igbinary_unserialize_string(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);
  inline static int igbinary_unserialize_chararray(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);

  inline static int igbinary_unserialize_array(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);
  inline static int igbinary_unserialize_object(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);
  inline static int igbinary_unserialize_object_ser(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Object& obj TSRMLS_DC);
  inline static int igbinary_unserialize_ref(struct igbinary_unserialize_data *igsd, enum igbinary_type t, Variant& z TSRMLS_DC);

  static int igbinary_unserialize_zval(struct igbinary_unserialize_data *igsd, Variant& z TSRMLS_DC);
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_IGBINARY_UNSERIALIZER_H__
