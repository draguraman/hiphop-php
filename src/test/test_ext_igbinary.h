
#ifndef __TEST_EXT_IGBINARY_H__
#define __TEST_EXT_IGBINARY_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <test/test_cpp_ext.h>

///////////////////////////////////////////////////////////////////////////////

class TestExtIgbinary : public TestCppExt {
 public:
  virtual bool RunTests(const std::string &which);

  bool test_igbinary_serialize();
  bool test_igbinary_unserialize();
};

///////////////////////////////////////////////////////////////////////////////

#endif // __TEST_EXT_IGBINARY_H__
