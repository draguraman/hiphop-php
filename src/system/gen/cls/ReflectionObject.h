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

#ifndef __GENERATED_cls_ReflectionObject_h8fef8272__
#define __GENERATED_cls_ReflectionObject_h8fef8272__

#include <runtime/base/hphp_system.h>
#include <system/gen/sys/literal_strings_remap.h>
#include <system/gen/sys/scalar_arrays_remap.h>
#include <cls/ReflectionClass.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 1317 */
FORWARD_DECLARE_CLASS(ReflectionObject);
extern const ObjectStaticCallbacks cw_ReflectionObject;
class c_ReflectionObject : public c_ReflectionClass {
  public:

  // Properties

  // Class Map
  DECLARE_CLASS_NO_SWEEP(ReflectionObject, ReflectionObject, ReflectionClass)
  c_ReflectionObject(const ObjectStaticCallbacks *cb = &cw_ReflectionObject) : c_ReflectionClass(cb) {}
  public: static Variant t_export(Variant v_obj, CVarRef v_ret);
  DECLARE_METHOD_INVOKE_HELPERS(export);
};
ObjectData *coo_ReflectionObject() NEVER_INLINE;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_ReflectionObject_h8fef8272__
