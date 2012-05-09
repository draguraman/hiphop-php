/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
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
*/

#ifndef __EXTPROFILE_STREAM_H__
#define __EXTPROFILE_STREAM_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/ext/ext_stream.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

inline Object x_stream_context_create(CArrRef options = null_array, CArrRef params = null_array) {
  FUNCTION_INJECTION_BUILTIN(stream_context_create);
  return f_stream_context_create(options, params);
}

inline Object x_stream_context_get_default(CArrRef options = null_array) {
  FUNCTION_INJECTION_BUILTIN(stream_context_get_default);
  return f_stream_context_get_default(options);
}

inline Variant x_stream_context_get_options(CObjRef stream_or_context) {
  FUNCTION_INJECTION_BUILTIN(stream_context_get_options);
  return f_stream_context_get_options(stream_or_context);
}

inline bool x_stream_context_set_option(CObjRef stream_or_context, CVarRef wrapper, CStrRef option = null_string, CVarRef value = null_variant) {
  FUNCTION_INJECTION_BUILTIN(stream_context_set_option);
  return f_stream_context_set_option(stream_or_context, wrapper, option, value);
}

inline bool x_stream_context_set_param(CObjRef stream_or_context, CArrRef params) {
  FUNCTION_INJECTION_BUILTIN(stream_context_set_param);
  return f_stream_context_set_param(stream_or_context, params);
}

inline Variant x_stream_copy_to_stream(CObjRef source, CObjRef dest, int maxlength = -1, int offset = 0) {
  FUNCTION_INJECTION_BUILTIN(stream_copy_to_stream);
  return f_stream_copy_to_stream(source, dest, maxlength, offset);
}

inline bool x_stream_encoding(CObjRef stream, CStrRef encoding = null_string) {
  FUNCTION_INJECTION_BUILTIN(stream_encoding);
  return f_stream_encoding(stream, encoding);
}

inline void x_stream_bucket_append(CObjRef brigade, CObjRef bucket) {
  FUNCTION_INJECTION_BUILTIN(stream_bucket_append);
  f_stream_bucket_append(brigade, bucket);
}

inline void x_stream_bucket_prepend(CObjRef brigade, CObjRef bucket) {
  FUNCTION_INJECTION_BUILTIN(stream_bucket_prepend);
  f_stream_bucket_prepend(brigade, bucket);
}

inline Object x_stream_bucket_make_writeable(CObjRef brigade) {
  FUNCTION_INJECTION_BUILTIN(stream_bucket_make_writeable);
  return f_stream_bucket_make_writeable(brigade);
}

inline Object x_stream_bucket_new(CObjRef stream, CStrRef buffer) {
  FUNCTION_INJECTION_BUILTIN(stream_bucket_new);
  return f_stream_bucket_new(stream, buffer);
}

inline bool x_stream_filter_register(CStrRef filtername, CStrRef classname) {
  FUNCTION_INJECTION_BUILTIN(stream_filter_register);
  return f_stream_filter_register(filtername, classname);
}

inline bool x_stream_filter_remove(CObjRef stream_filter) {
  FUNCTION_INJECTION_BUILTIN(stream_filter_remove);
  return f_stream_filter_remove(stream_filter);
}

inline Object x_stream_filter_append(CObjRef stream, CStrRef filtername, int read_write = 0, CVarRef params = null_variant) {
  FUNCTION_INJECTION_BUILTIN(stream_filter_append);
  return f_stream_filter_append(stream, filtername, read_write, params);
}

inline Object x_stream_filter_prepend(CObjRef stream, CStrRef filtername, int read_write = 0, CVarRef params = null_variant) {
  FUNCTION_INJECTION_BUILTIN(stream_filter_prepend);
  return f_stream_filter_prepend(stream, filtername, read_write, params);
}

inline Variant x_stream_get_contents(CObjRef handle, int maxlen = 0, int offset = 0) {
  FUNCTION_INJECTION_BUILTIN(stream_get_contents);
  return f_stream_get_contents(handle, maxlen, offset);
}

inline Array x_stream_get_filters() {
  FUNCTION_INJECTION_BUILTIN(stream_get_filters);
  return f_stream_get_filters();
}

inline Variant x_stream_get_line(CObjRef handle, int length = 0, CStrRef ending = null_string) {
  FUNCTION_INJECTION_BUILTIN(stream_get_line);
  return f_stream_get_line(handle, length, ending);
}

inline Variant x_stream_get_meta_data(CObjRef stream) {
  FUNCTION_INJECTION_BUILTIN(stream_get_meta_data);
  return f_stream_get_meta_data(stream);
}

inline Array x_stream_get_transports() {
  FUNCTION_INJECTION_BUILTIN(stream_get_transports);
  return f_stream_get_transports();
}

inline Array x_stream_get_wrappers() {
  FUNCTION_INJECTION_BUILTIN(stream_get_wrappers);
  return f_stream_get_wrappers();
}

inline bool x_stream_register_wrapper(CStrRef protocol, CStrRef classname) {
  FUNCTION_INJECTION_BUILTIN(stream_register_wrapper);
  return f_stream_register_wrapper(protocol, classname);
}

inline bool x_stream_wrapper_register(CStrRef protocol, CStrRef classname) {
  FUNCTION_INJECTION_BUILTIN(stream_wrapper_register);
  return f_stream_wrapper_register(protocol, classname);
}

inline bool x_stream_wrapper_restore(CStrRef protocol) {
  FUNCTION_INJECTION_BUILTIN(stream_wrapper_restore);
  return f_stream_wrapper_restore(protocol);
}

inline bool x_stream_wrapper_unregister(CStrRef protocol) {
  FUNCTION_INJECTION_BUILTIN(stream_wrapper_unregister);
  return f_stream_wrapper_unregister(protocol);
}

inline Variant x_stream_select(VRefParam read, VRefParam write, VRefParam except, CVarRef vtv_sec, int tv_usec = 0) {
  FUNCTION_INJECTION_BUILTIN(stream_select);
  return f_stream_select(read, write, except, vtv_sec, tv_usec);
}

inline bool x_stream_set_blocking(CObjRef stream, int mode) {
  FUNCTION_INJECTION_BUILTIN(stream_set_blocking);
  return f_stream_set_blocking(stream, mode);
}

inline bool x_stream_set_timeout(CObjRef stream, int seconds, int microseconds = 0) {
  FUNCTION_INJECTION_BUILTIN(stream_set_timeout);
  return f_stream_set_timeout(stream, seconds, microseconds);
}

inline int x_stream_set_write_buffer(CObjRef stream, int buffer) {
  FUNCTION_INJECTION_BUILTIN(stream_set_write_buffer);
  return f_stream_set_write_buffer(stream, buffer);
}

inline int x_set_file_buffer(CObjRef stream, int buffer) {
  FUNCTION_INJECTION_BUILTIN(set_file_buffer);
  return f_set_file_buffer(stream, buffer);
}

inline Variant x_stream_socket_accept(CObjRef server_socket, double timeout = 0.0, VRefParam peername = null) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_accept);
  return f_stream_socket_accept(server_socket, timeout, peername);
}

inline Variant x_stream_socket_server(CStrRef local_socket, VRefParam errnum = null, VRefParam errstr = null, int flags = 0, CObjRef context = null_object) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_server);
  return f_stream_socket_server(local_socket, errnum, errstr, flags, context);
}

inline Variant x_stream_socket_client(CStrRef remote_socket, VRefParam errnum = null, VRefParam errstr = null, double timeout = 0.0, int flags = 0, CObjRef context = null_object) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_client);
  return f_stream_socket_client(remote_socket, errnum, errstr, timeout, flags, context);
}

inline Variant x_stream_socket_enable_crypto(CObjRef stream, bool enable, int crypto_type = 0, CObjRef session_stream = null_object) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_enable_crypto);
  return f_stream_socket_enable_crypto(stream, enable, crypto_type, session_stream);
}

inline Variant x_stream_socket_get_name(CObjRef handle, bool want_peer) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_get_name);
  return f_stream_socket_get_name(handle, want_peer);
}

inline Variant x_stream_socket_pair(int domain, int type, int protocol) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_pair);
  return f_stream_socket_pair(domain, type, protocol);
}

inline Variant x_stream_socket_recvfrom(CObjRef socket, int length, int flags = 0, CStrRef address = null_string) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_recvfrom);
  return f_stream_socket_recvfrom(socket, length, flags, address);
}

inline Variant x_stream_socket_sendto(CObjRef socket, CStrRef data, int flags = 0, CStrRef address = null_string) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_sendto);
  return f_stream_socket_sendto(socket, data, flags, address);
}

inline bool x_stream_socket_shutdown(CObjRef stream, int how) {
  FUNCTION_INJECTION_BUILTIN(stream_socket_shutdown);
  return f_stream_socket_shutdown(stream, how);
}


///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXTPROFILE_STREAM_H__
