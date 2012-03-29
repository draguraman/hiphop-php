
#include <test/test_ext_amf.h>
#include <runtime/ext/ext_amf.h>

IMPLEMENT_SEP_EXTENSION_TEST(Amf);
///////////////////////////////////////////////////////////////////////////////

bool TestExtAmf::RunTests(const std::string &which) {
  bool ret = true;

  RUN_TEST(test_amf_encode);
  RUN_TEST(test_amf_decode);

  return ret;
}

///////////////////////////////////////////////////////////////////////////////

bool TestExtAmf::test_amf_encode() {
  return Count(true);
}

bool TestExtAmf::test_amf_decode() {
  return Count(true);
}
