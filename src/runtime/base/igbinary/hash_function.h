/*
  +----------------------------------------------------------------------+
  | See COPYING file for further copyright information                   |
  +----------------------------------------------------------------------+ 
  | Author: Oleg Grenrus <oleg.grenrus@dynamoid.com>                     |
  | See CREDITS for contributors                                         |
  +----------------------------------------------------------------------+ 
*/

#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H
#ifdef PHP_WIN32
# include "ig_win32.h"
#else
# include <stdint.h>     /* defines uint32_t etc */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hash function
 *
 * At this moment lookup3 by Bob Jerkins
 *
 * @param key key
 * @param length key length
 * @param initval hash init val
 * @return hash value of key
 * @see http://burtleburtle.net/bob/hash/index.html
 * @author Bob Jerkins <bob_jenkins@burtleburtle.net>
 */
uint32_t hash_function(const void *key, size_t length, uint32_t initval);

#ifdef __cplusplus
}
#endif

#endif /* HASH_FUNCTION_H */
