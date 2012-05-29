/**
 *
 * ext_igbinary.cpp
 *
 * @author Weijun Li
 * @copyright 2012, Zynga Game Network, Inc.
 */

#include <runtime/ext/ext_igbinary.h>
#include <runtime/base/igbinary/igbinary_serializer.h>
#include <runtime/base/igbinary/igbinary_unserializer.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

String f_igbinary_serialize(CVarRef var) {
  IGBinarySerializer igs;
  return igs.serialize(var);
}

Variant f_igbinary_unserialize(CStrRef str) {
  IGBinaryUnserializer igus;
  return igus.unserialize(str);
}

///////////////////////////////////////////////////////////////////////////////
}
