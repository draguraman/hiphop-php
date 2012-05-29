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
/*
 * php_config.h
 *
 *  Created on: Feb 16, 2012
 *      Author: wli
 */

#ifndef PHP_CONFIG_H_
#define PHP_CONFIG_H_

/* #undef uint */
#define ulong unsigned long

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a char *.  */
#define SIZEOF_CHAR_P 8

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 8

/* The number of bytes in a long int.  */
/* #undef SIZEOF_LONG_INT */

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in a long long int.  */
#define SIZEOF_LONG_LONG_INT 8

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* The number of bytes in a size_t.  */
#define SIZEOF_SIZE_T 8

#endif /* PHP_CONFIG_H_ */
