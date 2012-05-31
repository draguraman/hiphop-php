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
// @generated by HipHop Compiler

#ifndef __GENERATED_cls_ErrorException_h8c3c27d5__
#define __GENERATED_cls_ErrorException_h8c3c27d5__

#include <runtime/base/hphp_system.h>
#include <system/gen/sys/literal_strings_remap.h>
#include <system/gen/sys/scalar_arrays_remap.h>
#include <cls/Exception.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

extern StaticString s_sys_ss00000000;

extern const VarNR &s_sys_svif01bca90;

extern VarNR s_sys_svs00000000;

/* SRC: classes/exception.php line 286 */
FORWARD_DECLARE_CLASS(ErrorException);
extern const ObjectStaticCallbacks cw_ErrorException;
class c_ErrorException : public c_Exception {
  public:

  // Properties
  Variant m_severity;

  // Class Map
  DECLARE_CLASS_NO_SWEEP(ErrorException, ErrorException, Exception)
  static const ClassPropTable os_prop_table;
  c_ErrorException(const ObjectStaticCallbacks *cb = &cw_ErrorException) : c_Exception(cb), m_severity(Variant::nullInit) {}
  public: void t___construct(Variant v_message = NAMSTR(s_sys_ss00000000, ""), Variant v_code = 0LL, Variant v_severity = 0LL, Variant v_filename = null, Variant v_lineno = null);
  public: c_ErrorException *create(CVarRef v_message = NAMVAR(s_sys_svs00000000, ""), CVarRef v_code = NAMVAR(s_sys_svif01bca90, 0LL), CVarRef v_severity = NAMVAR(s_sys_svif01bca90, 0LL), CVarRef v_filename = null_variant, CVarRef v_lineno = null_variant);
  public: Variant t_getseverity();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  DECLARE_METHOD_INVOKE_HELPERS(getseverity);
};
ObjectData *coo_ErrorException() NEVER_INLINE;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_ErrorException_h8c3c27d5__
