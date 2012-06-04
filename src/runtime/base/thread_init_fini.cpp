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

#include <runtime/base/thread_init_fini.h>
#include <runtime/base/memory/smart_allocator.h>
#include <runtime/base/execution_context.h>
#include <runtime/base/preg.h>
#include <runtime/base/server/server_stats.h>
#include <runtime/base/server/server_note.h>
#include <runtime/base/zend/zend_strtod.h>
#include <runtime/base/zend/zend_math.h>
#include <util/async_func.h>
#include <util/alloc.h>
#include <runtime/ext/ext_icu.h>
#include <runtime/eval/runtime/variable_environment.h>
#include <runtime/base/intercept.h>
#include <runtime/base/array/arg_array.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

void init_thread_locals(void *arg /* = NULL */) {
  ObjectData::GetMaxId();
  ResourceData::GetMaxResourceId();
  ServerStats::GetLogger();
  preg_get_pcre_cache();
  zend_get_bigint_data();
  zend_get_rand_data();
  get_server_note();
  g_persistentObjects.getCheck();
  Sweepable::GetSweepData();
  MemoryManager::TheMemoryManager().getCheck();
  InitAllocatorThreadLocal();
  get_global_variables_check();
  ThreadInfo::s_threadInfo.getCheck();
  g_context.getCheck();
  icu_get_checks();
  s_hasRenamedFunction.getCheck();
  if (has_eval_support) {
    Eval::VariableEnvironment::InitTempStack();
    ArgArray::s_stack.getCheck();
  }
}

void finish_thread_locals(void *arg /* = NULL */) {
  // socket depends on file (yeah its wierd)
  if (g_persistentObjects.getNoCheck()) g_persistentObjects.destroy();
  if (g_context.getNoCheck()) g_context.destroy();
}

static class SetThreadInitFini {
public:
  SetThreadInitFini() {
    AsyncFuncImpl::SetThreadInitFunc(init_thread_locals, NULL);
    AsyncFuncImpl::SetThreadFiniFunc(finish_thread_locals, NULL);
  }
} s_SetThreadInitFini;

///////////////////////////////////////////////////////////////////////////////
}
