/**
 *
 * igbinary_serializer.h
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#ifndef __HPHP_IGBINARY_SERIALIZER_H__
#define __HPHP_IGBINARY_SERIALIZER_H__

#include <runtime/base/types.h>
#include <runtime/base/class_info.h>
#include <runtime/base/util/string_buffer.h>
#include <runtime/base/igbinary/igbinary_types.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

#include "hash.h"

class IGBinarySerializer {

    /** Serializer data.
     * @author Oleg Grenrus <oleg.grenrus@dynamoid.com>
     */
    struct igbinary_serialize_data
    {
      uint8_t *buffer; /**< Buffer. */
      size_t buffer_size; /**< Buffer size. */
      size_t buffer_capacity; /**< Buffer capacity. */
      bool scalar; /**< Serializing scalar. */
      bool compact_strings; /**< Check for duplicate strings. */
      struct hash_si strings; /**< Hash of already serialized strings. */
      struct hash_si objects; /**< Hash of already serialized objects. */
      int string_count; /**< Serialized string count, used for back referencing */
      int error; /**< Error number. Not used. */
    };

public:

  /**
   * Constructor and destructor.
   */
  IGBinarySerializer();
  ~IGBinarySerializer() {
  }

  String serialize(CVarRef v);

private:

  inline static int igbinary_serialize_data_init(struct igbinary_serialize_data *igsd, bool scalar TSRMLS_DC);
  inline static void igbinary_serialize_data_deinit(struct igbinary_serialize_data *igsd TSRMLS_DC);

  inline static int igbinary_serialize_header(struct igbinary_serialize_data *igsd TSRMLS_DC);
  inline static int igbinary_serialize_resize(struct igbinary_serialize_data *igsd, size_t size TSRMLS_DC);

  inline static int igbinary_serialize8(struct igbinary_serialize_data *igsd, uint8_t i TSRMLS_DC);
  inline static int igbinary_serialize16(struct igbinary_serialize_data *igsd, uint16_t i TSRMLS_DC);
  inline static int igbinary_serialize32(struct igbinary_serialize_data *igsd, uint32_t i TSRMLS_DC);
  inline static int igbinary_serialize64(struct igbinary_serialize_data *igsd, uint64_t i TSRMLS_DC);

  inline static int igbinary_serialize_null(struct igbinary_serialize_data *igsd TSRMLS_DC);
  inline static int igbinary_serialize_bool(struct igbinary_serialize_data *igsd, int b TSRMLS_DC);
  inline static int igbinary_serialize_long(struct igbinary_serialize_data *igsd, long l TSRMLS_DC);
  inline static int igbinary_serialize_double(struct igbinary_serialize_data *igsd, double d TSRMLS_DC);
  inline static int igbinary_serialize_string(struct igbinary_serialize_data *igsd, const char *s, size_t len TSRMLS_DC);
  inline static int igbinary_serialize_chararray(struct igbinary_serialize_data *igsd, const char *s, size_t len TSRMLS_DC);

  inline static int igbinary_serialize_array(struct igbinary_serialize_data *igsd, CVarRef z, const ClassInfo* clsInfo, bool incomplete_class TSRMLS_DC);
  inline static int igbinary_serialize_array_ref(struct igbinary_serialize_data *igsd, CVarRef z, bool object TSRMLS_DC);
  inline static int igbinary_serialize_array_sleep(struct igbinary_serialize_data *igsd, CVarRef z, CArrRef ht, const ObjectData *ce, bool incomplete_class, const ClassInfo* clsInfo TSRMLS_DC);
  inline static int igbinary_serialize_object_name(struct igbinary_serialize_data *igsd, const char *name, size_t name_len TSRMLS_DC);
  inline static int igbinary_serialize_object(struct igbinary_serialize_data *igsd, CVarRef z TSRMLS_DC);

  static int igbinary_serialize_zval(struct igbinary_serialize_data *igsd, CVarRef z TSRMLS_DC);

  static void writeSerializedProperty(struct igbinary_serialize_data *igsd, CStrRef prop, const ClassInfo *cls);

  inline static void writeToBuffer(struct igbinary_serialize_data *igsd, uint8_t c);
  inline static void writeToBuffer(struct igbinary_serialize_data *igsd, const char* p);
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_IGBINARY_SERIALIZER_H__
