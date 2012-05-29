/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Sascha Schumann <sascha@schumann.cx>                         |
   +----------------------------------------------------------------------+
 */

/* $Id: php_smart_str_public.h 293036 2010-01-03 09:23:27Z sebastian $ */

#ifndef PHP_SMART_STR_PUBLIC_H
#define PHP_SMART_STR_PUBLIC_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *c;
	size_t len;
	size_t a;
} smart_str;

#ifdef __cplusplus
}
#endif

#endif
