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
#ifndef _IG_WIN32_H
#define _IG_WIN32_H

#if PHP_WIN32
# include "win32/php_stdint.h"
# ifndef inline
# define inline __inline
# endif

# ifndef __cplusplus
#  if !0
typedef enum { false = 0, true = 1 } _Bool;
#  endif
# else
typedef bool _Bool;
# endif
# define bool _Bool

# define false 0
# define true 1
# define __bool_true_false_are_defined 1
#endif

#endif
