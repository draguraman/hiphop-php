
#include <test/test_ext_igbinary.h>
#include <runtime/ext/ext_igbinary.h>

IMPLEMENT_SEP_EXTENSION_TEST(Igbinary);
///////////////////////////////////////////////////////////////////////////////

bool TestExtIgbinary::RunTests(const std::string &which) {
  bool ret = true;

  RUN_TEST(test_igbinary_serialize);
  RUN_TEST(test_igbinary_unserialize);

  return ret;
}

///////////////////////////////////////////////////////////////////////////////

bool TestExtIgbinary::test_igbinary_serialize() {
  return Count(true);
}

bool TestExtIgbinary::test_igbinary_unserialize() {
  return Count(true);
}
