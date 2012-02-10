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

#include <runtime/ext/ext_memcache.h>
#include <runtime/base/util/request_local.h>
#include <runtime/base/ini_setting.h>
#include <runtime/ext/minilzo/minilzo.h>
#include <zlib.h>

#define MMC_SERIALIZED 			(1 << 0)
#define MMC_COMPRESSED 			(1 << 1)
#define MMC_COMPRESSED_LZO 		(1 << 2)
#define MMC_CHKSUM	   			(1 << 3)
#define MMC_COMPRESSED_BZIP2 	(1 << 4)
#define MMC_SERIALIZED_IGBINARY (1 << 5)

namespace HPHP {
IMPLEMENT_DEFAULT_EXTENSION(memcache);

bool ini_on_update_hash_strategy(CStrRef value, void *p);
bool ini_on_update_hash_function(CStrRef value, void *p);

static int memcache_lzo_enabled = (lzo_init() == LZO_E_OK)? 1: 0;

lzo_align_t __LZO_MMODEL lzo_wmem[ ((LZO1X_1_MEM_COMPRESS) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ];

class MEMCACHEGlobals : public RequestEventHandler {
public:
  std::string hash_strategy;
  std::string hash_function;

  MEMCACHEGlobals() {}

  virtual void requestInit() {
    hash_strategy = "standard";
    hash_function = "crc32";

    IniSetting::Bind("memcache.hash_strategy",     "standard",
                     ini_on_update_hash_strategy,  &hash_strategy);
    IniSetting::Bind("memcache.hash_function",     "crc32",
                     ini_on_update_hash_function,  &hash_function);
  }

  virtual void requestShutdown() {
  }
};

IMPLEMENT_STATIC_REQUEST_LOCAL(MEMCACHEGlobals, s_memcache_globals);
#define MEMCACHEG(name) s_memcache_globals->name

bool ini_on_update_hash_strategy(CStrRef value, void *p) {
  if (!strncasecmp(value.data(), "standard", sizeof("standard"))) {
    MEMCACHEG(hash_strategy) = "standard";
  } else if (!strncasecmp(value.data(), "standard", sizeof("consistent"))) {
    MEMCACHEG(hash_strategy) = "consistent";
  } else {
    return false;
  }
  return true;
}

bool ini_on_update_hash_function(CStrRef value, void *p) {
  if (!strncasecmp(value.data(), "crc32", sizeof("crc32"))) {
    MEMCACHEG(hash_strategy) = "crc32";
  } else if (!strncasecmp(value.data(), "fnv", sizeof("fnv"))) {
    MEMCACHEG(hash_strategy) = "fnv";
  } else {
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// methods

c_Memcache::c_Memcache(const ObjectStaticCallbacks *cb) :
    ExtObjectData(cb), m_memcache(), m_compress_threshold(0),
    m_min_compress_savings(0.2) {

  if(!memcache_lzo_enabled) {
    raise_error("memcache_lzo_enabled=false. lzo_init() failed.");
  }

  memcached_create(&m_memcache);

  if (MEMCACHEG(hash_strategy) == "consistent") {
    // need to hook up a global variable to set this
    memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_DISTRIBUTION,
                           MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA);
  } else {
    memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_DISTRIBUTION,
                           MEMCACHED_DISTRIBUTION_MODULA);
  }

  if (MEMCACHEG(hash_function) == "fnv") {
    memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_HASH,
                           MEMCACHED_HASH_FNV1A_32);
  } else {
    memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_HASH,
                           MEMCACHED_HASH_CRC);
  }
}

c_Memcache::~c_Memcache() {
  memcached_free(&m_memcache);
}

void c_Memcache::t___construct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::__construct);
  return;
}

bool c_Memcache::t_connect(CStrRef host, int port /*= 0*/,
                           int timeout /*= 0*/,
                           int timeoutms /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::connect);
  memcached_return_t ret;

  if (!host.empty() && host[0] == '/') {
    ret = memcached_server_add_unix_socket(&m_memcache, host.c_str());
  } else {
    ret = memcached_server_add(&m_memcache, host.c_str(), port);
  }

  return (ret == MEMCACHED_SUCCESS);
}

bool c_Memcache::t_pconnect(CStrRef host, int port /*= 0*/,
                            int timeout /*= 0*/,
                            int timeoutms /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::pconnect);
  return t_connect(host, port, timeout, timeoutms);
}

static const char* get_zlib_status_string(int status)
  {
    const char* s;
    switch (status)
      {
      case Z_MEM_ERROR:
        s = "Not enough memory to perform compression";
        break;
      case Z_BUF_ERROR:
        s = "Not enough room in the output buffer to perform compression";
        break;
      case Z_STREAM_ERROR:
        s = "Invalid compression level";
        break;
      default:
        s = "Unknown error during compression";
        break;
      }
    return s;
  }

static String mmc_compress(const String &sdata, int &flag) {
  int status = Z_ERRNO, data_len;
  char *result;
  unsigned long result_len = 0;

  data_len = sdata.length();
  // *result_len = data_len + (data_len / 1000) + 25 + 1; /* some magic from zlib.c */
  result_len = data_len + (data_len / 16) + 64 + 3; /* worst-case expansion for lzo */
  result = (char *)malloc(result_len);

  if (flag & MMC_COMPRESSED) {
    int level = 0;  // MEMCACHE_G(compression_level)
    if (level == 0)
      level = 6;

    if (level >= 0) {
      status = compress2((unsigned char *)result, &result_len,
          (unsigned const char *) sdata.c_str(), data_len, level);
    }
    else {
      status = compress((unsigned char *)result, &result_len,
          (unsigned const char *) sdata.c_str(), data_len);
    }
  }
  else if (flag & MMC_COMPRESSED_LZO) {
    status = lzo1x_1_compress((const unsigned char*)sdata.c_str(), data_len, (unsigned char*)result, &result_len, lzo_wmem);
    switch (status)
      {
    case LZO_E_OK:
      status = Z_OK;
      break;
    case LZO_E_OUTPUT_OVERRUN:
      status = Z_BUF_ERROR;
      break;
    default:
      status = Z_DATA_ERROR;
      break;
      }
  }

  if (status == Z_OK) {
    result = (char*)realloc(result, result_len + 1);
    result[result_len] = '\0';
    return String(result, result_len, AttachString);
  }
  else {
    free(result);
    raise_error("mmc_compress(): compression failed data_len=%d status=%d error=%s",
        data_len, status, get_zlib_status_string(status));
    return null;
  }
}

String static memcache_prepare_for_storage(CVarRef var, int &flag) {
    if (var.isString()) {
      return var.toString();
    }
    else if (var.isNumeric() || var.isBoolean()) {
      return var.toString();
    }
    else {
      flag |= MMC_SERIALIZED;
      String sdata = f_serialize(var);

      if(flag & (MMC_COMPRESSED | MMC_COMPRESSED_LZO) ) {
        sdata = mmc_compress(sdata, flag);
      }
      return sdata;
    }
  }

static String mmc_uncompress(const char *payload, size_t payload_len, uint32_t flags) {
  unsigned int factor = 1, maxfactor = 16;
  char *result;
  unsigned long result_len = 0;
  char *tmp1 = NULL;
  int status = Z_ERRNO;

  do {
    result_len = (unsigned long) payload_len * (1 << factor++);
    result = (char *) realloc(tmp1, result_len);
    if (flags & MMC_COMPRESSED) {
      status = uncompress((unsigned char *)result, &result_len,
          (unsigned const char *) payload, payload_len);
    }
    /*
    else if (flags & MMC_COMPRESSED_BZIP2) {
      status = bz2_decompress_safe((unsigned char**) result, result_len, (unsigned const char *) data, data_len);
    }
    */
    else if(flags & MMC_COMPRESSED_LZO) {
      status = lzo1x_decompress_safe((const unsigned char*)payload, payload_len,
          (unsigned char*)result, &result_len, NULL);
      if (status == LZO_E_OUTPUT_OVERRUN )
        status = Z_BUF_ERROR;
      else if (status == LZO_E_OK )
        status = Z_OK;
      else
        status = Z_DATA_ERROR;
    }
    tmp1 = result;
  }
  while (status == Z_BUF_ERROR && factor < maxfactor);

  if (status == Z_OK) {
    result = (char*)realloc(result, result_len + 1);
    result[result_len] = '\0';
    return String(result, result_len, AttachString);
  }
  else {
    raise_error("memcache_fetch_from_storage: decompression failed payload_len=%d flags=%x status=%d error=%s",
        payload_len, flags, status, get_zlib_status_string(status));
    return null;
  }
}

Variant static memcache_fetch_from_storage(const char *payload,
                                           size_t payload_len,
                                           uint32_t flags) {
  Variant ret = null;
  String payload2;

  if (flags & (MMC_COMPRESSED | MMC_COMPRESSED_LZO) ) {
    payload2 = mmc_uncompress(payload, payload_len, flags);
  }

  if (flags & MMC_SERIALIZED) {
    ret = f_unserialize(payload2.length() > 0 ? payload2 : String(payload, payload_len, AttachLiteral));
    if( ret == null ) {
      raise_warning("unable to unserialize data payload_len=%d flags=%x", payload_len, flags);
    }
  } else {
    ret = payload2.length() > 0 ? payload2 : String(payload, payload_len, CopyString);
  }

  return ret;
}

bool c_Memcache::t_add(CStrRef key, CVarRef var, int flag /*= 0*/,
                       int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::add);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  String serialized = memcache_prepare_for_storage(var, flag);

  memcached_return_t ret = memcached_add(&m_memcache,
                                        key.c_str(), key.length(),
                                        serialized.c_str(),
                                        serialized.length(),
                                        expire, flag);

  return (ret == MEMCACHED_SUCCESS);
}

bool c_Memcache::t_set(CStrRef key, CVarRef var, int flag /*= 0*/,
                       int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::set);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  String serialized = memcache_prepare_for_storage(var, flag);

  memcached_return_t ret = memcached_set(&m_memcache,
                                        key.c_str(), key.length(),
                                        serialized.c_str(),
                                        serialized.length(),
                                        expire, flag);

  if (ret == MEMCACHED_SUCCESS) {
    return true;
  }

  return false;
}

bool c_Memcache::t_cas(CStrRef key, CVarRef var, int flag /*= 0*/,
                       int expire /*= 0*/, int64 cas /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::cas);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  String serialized = memcache_prepare_for_storage(var, flag);

  memcached_return_t ret = memcached_cas(&m_memcache,
                                        key.c_str(), key.length(),
                                        serialized.c_str(),
                                        serialized.length(),
                                        expire, flag, cas);

  if (ret == MEMCACHED_SUCCESS) {
    return true;
  }

  return false;
}

bool c_Memcache::t_replace(CStrRef key, CVarRef var, int flag /*= 0*/,
                           int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::replace);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  String serialized = memcache_prepare_for_storage(var, flag);

  memcached_return_t ret = memcached_replace(&m_memcache,
                                             key.c_str(), key.length(),
                                             serialized.c_str(),
                                             serialized.length(),
                                             expire, flag);
  return (ret == MEMCACHED_SUCCESS);
}

Variant c_Memcache::t_get(CVarRef key, VRefParam flags /*= null*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::get);
  TAINT_OBSERVER(TAINT_BIT_ALL, TAINT_BIT_NONE);
  if (key.is(KindOfArray)) {
    std::vector<const char *> real_keys;
    std::vector<size_t> key_len;
    Array keyArr = key.toArray();

    real_keys.reserve(keyArr.size());
    key_len.reserve(keyArr.size());

    for (ArrayIter iter(keyArr); iter; ++iter) {
      real_keys.push_back(const_cast<char *>(iter.second().toString().c_str()));
      key_len.push_back(iter.second().toString().length());
    }

    if (!real_keys.empty()) {
      const char *payload = NULL;
      size_t payload_len = 0;
      uint32_t flags = 0;
      const char *res_key = NULL;
      size_t res_key_len = 0;

      memcached_result_st result;

      memcached_return_t ret = memcached_mget(&m_memcache, &real_keys[0],
                                              &key_len[0], real_keys.size());
      memcached_result_create(&m_memcache, &result);
      Array return_val;

      while ((memcached_fetch_result(&m_memcache, &result, &ret)) != NULL) {
        if (ret != MEMCACHED_SUCCESS) {
          // should probably notify about errors
          continue;
        }

        payload     = memcached_result_value(&result);
        payload_len = memcached_result_length(&result);
        flags       = memcached_result_flags(&result);
        res_key     = memcached_result_key_value(&result);
        res_key_len = memcached_result_key_length(&result);

        return_val.set(String(res_key, res_key_len, CopyString),
                       memcache_fetch_from_storage(payload,
                                                   payload_len, flags));
      }
      memcached_result_free(&result);

      return return_val;
    }
  } else {
    char *payload = NULL;
    size_t payload_len = 0;
    uint32_t flags = 0;

    memcached_return_t ret;
    String skey = key.toString();

    if (skey.length() == 0) {
      return false;
    }

    payload = memcached_get(&m_memcache, skey.c_str(), skey.length(),
                            &payload_len, &flags, &ret);

    /* This is for historical reasons from libmemcached*/
    if (ret == MEMCACHED_END) {
      ret = MEMCACHED_NOTFOUND;
    }

    if (ret == MEMCACHED_NOTFOUND) {
      return false;
    }

    Variant retval = memcache_fetch_from_storage(payload, payload_len, flags);
    free(payload);

    return retval;
  }
  return false;
}

Variant c_Memcache::t_get2(CVarRef key, VRefParam var, VRefParam flags /*= null*/, VRefParam cas /*= null*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::get2);
  TAINT_OBSERVER(TAINT_BIT_ALL, TAINT_BIT_NONE);
  if (key.is(KindOfArray)) {
    std::vector<const char *> real_keys;
    std::vector<size_t> key_len;
    Array keyArr = key.toArray();

    real_keys.reserve(keyArr.size());
    key_len.reserve(keyArr.size());

    for (ArrayIter iter(keyArr); iter; ++iter) {
      real_keys.push_back(const_cast<char *>(iter.second().toString().c_str()));
      key_len.push_back(iter.second().toString().length());
    }

    if (!real_keys.empty()) {
      const char *payload = NULL;
      size_t payload_len = 0;
      uint32_t flag = 0;
      const char *res_key = NULL;
      size_t res_key_len = 0;

      memcached_result_st result;

      memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_SUPPORT_CAS, 
          cas.isReferenced() ? 1 : 0);

      memcached_return_t status = memcached_mget(&m_memcache, &real_keys[0],
                                              &key_len[0], real_keys.size());
      memcached_result_create(&m_memcache, &result);
      Array return_val;

      /* init return value */
      for (ArrayIter iter(keyArr); iter; ++iter) {
        return_val.set(iter.second().toString(), false);
      }
	

      Array var_array, flags_array, cas_array;

      while ((memcached_fetch_result(&m_memcache, &result, &status)) != NULL) {
        res_key     = memcached_result_key_value(&result);
        res_key_len = memcached_result_key_length(&result);

        String skey = String(res_key, res_key_len, CopyString);

        if (status == MEMCACHED_END) status = MEMCACHED_NOTFOUND;

        if (status != MEMCACHED_SUCCESS) {
          return_val.set(String(res_key, res_key_len, CopyString), status == MEMCACHED_NOTFOUND);
          continue;
        }

        payload     = memcached_result_value(&result);
        payload_len = memcached_result_length(&result);
        flag        = memcached_result_flags(&result);

        var = memcache_fetch_from_storage(payload, payload_len, flag);

        var_array.set(skey, var);

        flags_array.set(skey, (int)flag);

        if(cas.isReferenced()) {
          cas_array.set(skey, (int64)memcached_result_cas(&result));
        }
        return_val.set(skey, status == MEMCACHED_SUCCESS);
      }

      memcached_result_free(&result);

      /* Process missing keys */
      std::vector<char> key_server_stats;
      key_server_stats.reserve(keyArr.size() * sizeof(bool));
      bool* statBuf = (bool*)&key_server_stats[0];
      memcached_check_servers_by_keys(&m_memcache, NULL, 0,
    		  &real_keys[0], &key_len[0], real_keys.size(), statBuf);

      int i = 0;
      for (ArrayIter iter(keyArr); iter; ++iter) {
    	const char *key = iter.second().toString().c_str();
    	if( !var_array.exists(key) ) {
          return_val.set(key, statBuf[i]);
    	}
    	i++;
      }

      flags = flags_array;
      var = var_array;
      cas = cas_array;

      return return_val;
    }
  } else {
    const char *payload = NULL;
    size_t payload_len = 0;
    uint32_t flag = 0;

    memcached_return_t ret, status;
    memcached_result_st value;
    String skey = key.toString();
    const char *ckey = skey.c_str();
    size_t ckeylen = skey.length();

    if (skey.length() == 0) {
      return false;
    }

    memcached_behavior_set(&m_memcache, MEMCACHED_BEHAVIOR_SUPPORT_CAS, 
                            cas.isReferenced() ? 1 : 0);

    ret = memcached_mget(&m_memcache, &ckey, &ckeylen, 1);

    (void)(ret); /* make the compiler happy, but do nothing */
    
    memcached_result_create(&m_memcache, &value);

    if (!memcached_fetch_result(&m_memcache, &value, &status)) {
      /* This is for historical reasons from libmemcached*/
      if (status == MEMCACHED_END) status = MEMCACHED_NOTFOUND;
      if (status != MEMCACHED_SUCCESS) {
        if(cas.isReferenced()) cas = (int64) 0;
        return (status == MEMCACHED_NOTFOUND); /* get2 returns TRUE on key miss, but false on server fail */
      }
    }

    payload = memcached_result_value(&value);
    payload_len = memcached_result_length(&value);
    flag = memcached_result_flags(&value);

    if (flags.isReferenced()) {
      flags = (int)flag;
    }

    if (cas.isReferenced()) {
      cas = (int64) memcached_result_cas(&value);
    }

    var = memcache_fetch_from_storage(payload, payload_len, flag);

    memcached_result_free(&value);

    return true;
  }

  return false;
}

bool c_Memcache::t_delete(CStrRef key, int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::delete);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  memcached_return_t ret = memcached_delete(&m_memcache,
                                            key.c_str(), key.length(),
                                            expire);
  return (ret == MEMCACHED_SUCCESS);
}

int64 c_Memcache::t_increment(CStrRef key, int offset /*= 1*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::increment);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  uint64_t value;
  memcached_return_t ret = memcached_increment(&m_memcache, key.c_str(),
                                              key.length(), offset, &value);

  if (ret == MEMCACHED_SUCCESS) {
    return (int64)value;
  }

  return false;
}

int64 c_Memcache::t_decrement(CStrRef key, int offset /*= 1*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::decrement);
  if (key.empty()) {
    raise_warning("Key cannot be empty");
    return false;
  }

  uint64_t value;
  memcached_return_t ret = memcached_decrement(&m_memcache, key.c_str(),
                                              key.length(), offset, &value);

  if (ret == MEMCACHED_SUCCESS) {
    return (int64)value;
  }

  return false;
}

bool c_Memcache::t_close() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::close);
  memcached_quit(&m_memcache);
  return true;
}

Variant c_Memcache::t_getversion() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::getversion);
  int server_count = memcached_server_count(&m_memcache);
  char version[16];
  int version_len = 0;

  if (memcached_version(&m_memcache) != MEMCACHED_SUCCESS) {
    return false;
  }

  for (int x = 0; x < server_count; x++) {
    memcached_server_instance_st instance =
      memcached_server_instance_by_position(&m_memcache, x);

    if (!instance->major_version) {
      continue;
    }

    version_len = snprintf(version, sizeof(version), "%d.%d.%d",
        instance->major_version, instance->minor_version,
        instance->micro_version);
    return String(version, version_len, CopyString);
  }

  return false;
}

bool c_Memcache::t_flush(int expire /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::flush);
  return memcached_flush(&m_memcache, expire) == MEMCACHED_SUCCESS;
}

bool c_Memcache::t_setoptimeout(int64 timeoutms) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::setoptimeout);
  if (timeoutms < 1) {
    timeoutms = 1000; // make default
  }

  /* intentionally doing nothing for now */

  return true;
}

int c_Memcache::t_getserverstatus(CStrRef host, int port /* = 0 */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::getserverstatus);
  /* intentionally doing nothing for now */
  return 1;
}

bool c_Memcache::t_setcompressthreshold(int threshold,
                                        double min_savings /* = 0.2 */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::setcompressthreshold);
  if (threshold < 0) {
    raise_warning("threshold must be a positive integer");
    return false;
  }

  if (min_savings < 0 || min_savings > 1) {
    raise_warning("min_savings must be a float in the 0..1 range");
    return false;
  }

  m_compress_threshold = threshold;
  m_min_compress_savings = min_savings;

  return true;
}

Array static memcache_build_stats(memcached_st *ptr,
                                memcached_stat_st *memc_stat,
                                memcached_return_t *ret) {
  char **curr_key;
  char **stat_keys = memcached_stat_get_keys(ptr, memc_stat, ret);

  if (*ret != MEMCACHED_SUCCESS) {
    if (stat_keys) {
      free(stat_keys);
    }
    return NULL;
  }

  Array return_val = Array::Create();

  for (curr_key = stat_keys; *curr_key; curr_key++) {
    char *mc_val;
    mc_val = memcached_stat_get_value(ptr, memc_stat, *curr_key, ret);
    if (*ret != MEMCACHED_SUCCESS) {
      break;
    }
    return_val.set(String(*curr_key, CopyString),
                   String(mc_val, CopyString));
    free(mc_val);
  }

  free(stat_keys);
  return return_val;
}


Array c_Memcache::t_getstats(CStrRef type /* = null_string */,
                             int slabid /* = 0 */, int limit /* = 100 */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::getstats);
  if (!memcached_server_count(&m_memcache)) {
    return NULL;
  }

  char extra_args[30] = {0};

  if (slabid) {
    snprintf(extra_args, sizeof(extra_args), "%s %d %d", type.c_str(),
             slabid, limit);
  } else if (!type.empty()) {
    snprintf(extra_args, sizeof(extra_args), "%s", type.c_str());
  }

  memcached_server_instance_st instance =
    memcached_server_instance_by_position(&m_memcache, 0);

  memcached_stat_st stats;
  if (memcached_stat_servername(&stats, extra_args, instance->hostname,
                                instance->port) != MEMCACHED_SUCCESS) {
    return NULL;
  }

  memcached_return_t ret;
  return memcache_build_stats(&m_memcache, &stats, &ret);
}

Array c_Memcache::t_getextendedstats(CStrRef type /* = null_string */,
                                     int slabid /* = 0 */,
                                     int limit /* = 100 */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::getextendedstats);
  memcached_return_t ret;
  memcached_stat_st *stats;

  stats = memcached_stat(&m_memcache, NULL, &ret);
  if (ret != MEMCACHED_SUCCESS) {
    return NULL;
  }

  int server_count = memcached_server_count(&m_memcache);

  Array return_val;

  for (int server_id = 0; server_id < server_count; server_id++) {
    memcached_server_instance_st server;
    memcached_stat_st *stat;
    char stats_key[30] = {0};
    size_t key_len;

    server = memcached_server_instance_by_position(&m_memcache, server_id);
    stat = stats + server_id;

    Array server_stats = memcache_build_stats(&m_memcache, stat, &ret);
    if (ret != MEMCACHED_SUCCESS) {
      continue;
    }

    key_len = snprintf(stats_key, sizeof(stats_key),
                       "%s:%d", server->hostname, server->port);

    return_val.set(String(stats_key, key_len, CopyString), server_stats);
  }

  free(stats);
  return return_val;
}

bool c_Memcache::t_setserverparams(CStrRef host, int port /* = 11211 */,
                                   int timeout /* = 0 */,
                                   int retry_interval /* = 0 */,
                                   bool status /* = true */,
                                   CVarRef failure_callback /* = null_variant */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::setserverparams);
  /* intentionally doing nothing for now */
  return true;
}

bool c_Memcache::t_addserver(CStrRef host, int port /* = 11211 */,
                             bool persistent /* = false */,
                             int weight /* = 0 */, int timeout /* = 0 */,
                             int retry_interval /* = 0 */,
                             bool status /* = true */,
                             CVarRef failure_callback /* = null_variant */,
                             int timeoutms /* = 0 */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::addserver);
  memcached_return_t ret;

  if (!host.empty() && host[0] == '/') {
    ret = memcached_server_add_unix_socket_with_weight(&m_memcache,
                                                       host.c_str(), weight);
  } else {
    ret = memcached_server_add_with_weight(&m_memcache, host.c_str(),
                                           port, weight);
  }

  if (ret == MEMCACHED_SUCCESS) {
    return true;
  }

  return false;
}

Variant c_Memcache::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Memcache, Memcache::__destruct);
  t_close();
  return null;
}

///////////////////////////////////////////////////////////////////////////////
// these all pass to their OO equivalents

Object f_memcache_connect(CStrRef host, int port /* = 0 */,
                          int timeout /* = 0 */, int timeoutms /* = 0 */) {
  c_Memcache *memcache_obj = NEWOBJ(c_Memcache)();
  Object ret(memcache_obj);
  memcache_obj->t_connect(host, port, timeout, timeoutms);
  return ret;
}

Object f_memcache_pconnect(CStrRef host, int port /* = 0 */,
                           int timeout /* = 0 */, int timeoutms /* = 0 */) {
  return f_memcache_connect(host, port, timeout, timeoutms);
}

bool f_memcache_add(CObjRef memcache, CStrRef key, CVarRef var,
                    int flag /* = 0 */, int expire /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_add(key, var, flag, expire);
}

bool f_memcache_set(CObjRef memcache, CStrRef key, CVarRef var,
                    int flag /* = 0 */, int expire /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_set(key, var, flag, expire);
}

bool f_memcache_cas(CObjRef memcache, CStrRef key, CVarRef var,
                    int flag /* = 0 */, int expire /* = 0 */,
                    int64 cas /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_cas(key, var, flag, expire, cas);
}

bool f_memcache_replace(CObjRef memcache, CStrRef key, CVarRef var,
                        int flag /* = 0 */, int expire /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_replace(key, var, flag, expire);
}

Variant f_memcache_get(CObjRef memcache, CVarRef key,
                       VRefParam flags /* = null */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_get(key, flags);
}

bool f_memcache_delete(CObjRef memcache, CStrRef key, int expire /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_delete(key, expire);
}

int64 f_memcache_increment(CObjRef memcache, CStrRef key,
                           int offset /* = 1 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_increment(key, offset);
}

int64 f_memcache_decrement(CObjRef memcache, CStrRef key,
                           int offset /* = 1 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_decrement(key, offset);
}

bool f_memcache_close(CObjRef memcache) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_close();
}

bool f_memcache_debug(bool onoff) {
  throw NotImplementedException(__func__);
}

Variant f_memcache_get_version(CObjRef memcache) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_getversion();
}

bool f_memcache_flush(CObjRef memcache, int timestamp /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_flush(timestamp);
}

bool f_memcache_setoptimeout(CObjRef memcache, int timeoutms) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_setoptimeout(timeoutms);
}

int f_memcache_get_server_status(CObjRef memcache, CStrRef host,
                                 int port /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_getserverstatus(host, port);
}

bool f_memcache_set_compress_threshold(CObjRef memcache, int threshold,
                                       double min_savings /* = 0.2 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_setcompressthreshold(threshold, min_savings);
}

Array f_memcache_get_stats(CObjRef memcache, CStrRef type /* = null_string */,
                           int slabid /* = 0 */, int limit /* = 100 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_getstats(type, slabid, limit);
}

Array f_memcache_get_extended_stats(CObjRef memcache,
                                    CStrRef type /* = null_string */,
                                    int slabid /* = 0 */,
                                    int limit /* = 100 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_getextendedstats(type, slabid, limit);
}

bool f_memcache_set_server_params(CObjRef memcache, CStrRef host,
                                 int port /* = 11211 */,
                                 int timeout /* = 0 */,
                                 int retry_interval /* = 0 */,
                                 bool status /* = true */,
                                 CVarRef failure_callback /* = null_variant */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_setserverparams(host, port, timeout, retry_interval,
                                         status, failure_callback);
}

bool f_memcache_add_server(CObjRef memcache, CStrRef host,
                           int port /* = 11211 */,
                           bool persistent /* = false */,
                           int weight /* = 0 */,
                           int timeout /* = 0 */,
                           int retry_interval /* = 0 */,
                           bool status /* = true */,
                           CVarRef failure_callback /* = null_variant */,
                           int timeoutms /* = 0 */) {
  c_Memcache *memcache_obj = memcache.getTyped<c_Memcache>();
  return memcache_obj->t_addserver(host, port, persistent, weight, timeout,
                                   retry_interval, status, failure_callback,
                                   timeoutms);
}


///////////////////////////////////////////////////////////////////////////////
}
