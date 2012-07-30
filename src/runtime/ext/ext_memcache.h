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

#ifndef __EXT_MEMCACHE_H__
#define __EXT_MEMCACHE_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <libmemcached/memcached.h>
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Object f_memcache_connect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
Object f_memcache_pconnect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
bool f_memcache_add(CObjRef memcache, CStrRef key, CVarRef var, int flag = 0, int expire = 0);
bool f_memcache_set(CObjRef memcache, CStrRef key, CVarRef var, int flag = 0, int expire = 0);
bool f_memcache_cas(CObjRef memcache, CStrRef key, CVarRef var, int flag = 0, int expire = 0, int64 cas = 0);
bool f_memcache_replace(CObjRef memcache, CStrRef key, CVarRef var, int flag = 0, int expire = 0);
Variant f_memcache_get(CObjRef memcache, CVarRef key, VRefParam flags = null);
bool f_memcache_delete(CObjRef memcache, CStrRef key, int expire = 0);
bool f_memcache_unlock(CObjRef memcache, CStrRef key);
Variant f_memcache_increment(CObjRef memcache, CStrRef key, int offset = 1);
Variant f_memcache_decrement(CObjRef memcache, CStrRef key, int offset = 1);
bool f_memcache_close(CObjRef memcache);
bool f_memcache_debug(bool onoff);
Variant f_memcache_get_version(CObjRef memcache);
bool f_memcache_flush(CObjRef memcache, int timestamp = 0);
bool f_memcache_setoptimeout(CObjRef memcache, int timeoutms);
int f_memcache_get_server_status(CObjRef memcache, CStrRef host, int port = 0);
bool f_memcache_set_compress_threshold(CObjRef memcache, int threshold, double min_savings = 0.2);
Array f_memcache_get_stats(CObjRef memcache, CStrRef type = null_string, int slabid = 0, int limit = 100);
Array f_memcache_get_extended_stats(CObjRef memcache, CStrRef type = null_string, int slabid = 0, int limit = 100);
bool f_memcache_set_server_params(CObjRef memcache, CStrRef host, int port = 11211, int timeout = 0, int retry_interval = 0, bool status = true, CVarRef failure_callback = null_variant);
bool f_memcache_add_server(CObjRef memcache, CStrRef host, int port = 11211, bool persistent = false, int weight = 0, int timeout = 0, int retry_interval = 0, bool status = true, CVarRef failure_callback = null_variant, int timeoutms = 0);
extern const int64 k_MEMCACHE_COMPRESSED;
extern const int64 k_MEMCACHE_COMPRESSED_LZO;
extern const int64 k_MEMCACHE_COMPRESSED_BZIP2;
extern const int64 k_MEMCACHE_SERIALIZED_IGBINARY;

///////////////////////////////////////////////////////////////////////////////
// class Memcache

FORWARD_DECLARE_CLASS_BUILTIN(Memcache);
class c_Memcache : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(Memcache, Memcache, ObjectData)

  // need to implement
  public: c_Memcache(const ObjectStaticCallbacks *cb = &cw_Memcache);
  public: ~c_Memcache();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: bool t_connect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
  DECLARE_METHOD_INVOKE_HELPERS(connect);
  public: bool t_pconnect(CStrRef host, int port = 0, int timeout = 0, int timeoutms = 0);
  DECLARE_METHOD_INVOKE_HELPERS(pconnect);
  public: bool t_add(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(add);
  public: bool t_set(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(set);
  public: bool t_cas(CStrRef key, CVarRef var, int flag = 0, int expire = 0, int64 cas = 0);
  DECLARE_METHOD_INVOKE_HELPERS(cas);
  public: bool t_replace(CStrRef key, CVarRef var, int flag = 0, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(replace);
  public: Variant t_get(CVarRef key, VRefParam flags = null, VRefParam cas = null);
  DECLARE_METHOD_INVOKE_HELPERS(get);
  public: Variant t_get2(CVarRef key, VRefParam val, VRefParam flags = null, VRefParam cas = null);
  DECLARE_METHOD_INVOKE_HELPERS(get2);
  public: Variant t_getl(CStrRef key, int timeout = 15, VRefParam flags = null);
  DECLARE_METHOD_INVOKE_HELPERS(getl);
  public: Variant t_getbykey(CStrRef key, CStrRef shardKey, VRefParam val, VRefParam flags = null, VRefParam cas = null);
  DECLARE_METHOD_INVOKE_HELPERS(getbykey);
  public: bool t_setbykey(CStrRef key, CVarRef val, int flag = 0, int expire = 0, VRefParam cas = null, CStrRef shardKey = null);
  DECLARE_METHOD_INVOKE_HELPERS(setbykey);
  public: bool t_casbykey(CStrRef key, CVarRef val, int flag = 0, int expire = 0, VRefParam cas = null, CStrRef shardKey = null);
  DECLARE_METHOD_INVOKE_HELPERS(casbykey);
  public: bool t_delete(CStrRef key, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(delete);
  public: bool t_unlock(CStrRef key);
  DECLARE_METHOD_INVOKE_HELPERS(unlock);
  public: bool t_deletebykey(CStrRef key, CStrRef shardKey, int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(deletebykey);
  public: Variant t_increment(CStrRef key, int offset = 1);
  DECLARE_METHOD_INVOKE_HELPERS(increment);
  public: Variant t_decrement(CStrRef key, int offset = 1);
  DECLARE_METHOD_INVOKE_HELPERS(decrement);
  public: Variant t_getversion();
  DECLARE_METHOD_INVOKE_HELPERS(getversion);
  public: bool t_flush(int expire = 0);
  DECLARE_METHOD_INVOKE_HELPERS(flush);
  public: bool t_setoptimeout(int64 timeoutms);
  DECLARE_METHOD_INVOKE_HELPERS(setoptimeout);
  public: bool t_close();
  DECLARE_METHOD_INVOKE_HELPERS(close);
  public: int t_getserverstatus(CStrRef host, int port = 0);
  DECLARE_METHOD_INVOKE_HELPERS(getserverstatus);
  public: bool t_setcompressthreshold(int threshold, double min_savings = 0.2);
  DECLARE_METHOD_INVOKE_HELPERS(setcompressthreshold);
  public: bool t_setproperty(CStrRef prop, CVarRef var);
  DECLARE_METHOD_INVOKE_HELPERS(setproperty);
  public: Array t_getstats(CStrRef type = null_string, int slabid = 0, int limit = 100);
  DECLARE_METHOD_INVOKE_HELPERS(getstats);
  public: Array t_getextendedstats(CStrRef type = null_string, int slabid = 0, int limit = 100);
  DECLARE_METHOD_INVOKE_HELPERS(getextendedstats);
  public: bool t_setserverparams(CStrRef host, int port = 11211, int timeout = 0, int retry_interval = 0, bool status = true, CVarRef failure_callback = null_variant);
  DECLARE_METHOD_INVOKE_HELPERS(setserverparams);
  public: bool t_addserver(CStrRef host, int port = 11211, bool persistent = false, int weight = 0, int timeout = 0, int retry_interval = 0, bool status = true, CVarRef failure_callback = null_variant, int timeoutms = 0);
  DECLARE_METHOD_INVOKE_HELPERS(addserver);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_Memcache *create();


 private:
  std::map<std::string, uint64_t> getl_cas_map;
  memcached_st m_memcache;
  int m_compress_threshold;
  double m_min_compress_savings;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_MEMCACHE_H__
