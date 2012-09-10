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

#include <runtime/ext/ext_amf.h>
#include <util/logger.h>

#include <system/lib/systemlib.h>


#include <iostream>
#include <string>
#include <hash_map>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DEFAULT_EXTENSION(amf);

#ifdef SUCCESS
#undef SUCCESS
#endif
#define SUCCESS 0
#ifdef FAILURE
#undef FAILURE
#endif
#define FAILURE -1                 /* this MUST stay a negative number, or it may affect functions! */


static int printstrings (const char * buf, const int bufLen);

#define amf_error_docref php_error_docref
#define amf_error_docref1 php_error_docref


#define RETURN_FALSE_ { amf_error_docref(NULL , E_WARNING, "Error ---->");amf_error_docflush();RETURN_FALSE } while(0);
#define RETURN_TRUE_ if (0) {amf_error_docref(NULL , E_WARNING, "No Issues ---->");amf_error_docflush();}

static  long dump_strings_on_decode_err = 0;
static  long max_alloc_size = 10485760;


#define PRINT(x) if(0) php_error_docref (NULL , E_WARNING, x);

/********* Debugging Info ****************/
static int amf_bailout();
static void printData (char * p, int len);
#define php_error_docref(a,b,...) {  \
if (E_WARNING == b) {                \
	Logger::Warning(__VA_ARGS__);\
} else {                             \
	Logger::Error(__VA_ARGS__);  \
} }                                

static int encode2hex (const char * data, const unsigned int dataLen,
                 char *hexData, unsigned int *hexDataLen)
{
  	const char  hexArr[] = "0123456789ABCDEF";
  	unsigned int i, j ;
  	if (!data || !hexData || !hexDataLen || *hexDataLen < (2*dataLen)) 
		return -1;

  	memset ((char *)hexData, 0, *hexDataLen);
  	for (i = 0, j = 0 ; i < dataLen; i++)
  	{
    		hexData[j++] = hexArr[(data[i] & 0xf0) >> 4];
    		hexData[j++] = hexArr[(data[i] & 0x0f)];
  	}

  	*hexDataLen = j;

  	return 0;
}

static void printData (char * p, int len)
{
  	if (!p)
		return;
  	unsigned int tmpLen = (len + 3) * 2;
  	char * tmp = NULL;

  	if (dump_strings_on_decode_err)
  	{
    		tmp = (char *) malloc (tmpLen);
    		if (tmp)
    		{
      			if (0 == encode2hex (p, len, tmp, &tmpLen))
      			{
        			amf_error_docref1(NULL , E_WARNING, "The Hex String = %s",tmp);
      			}
      			free (tmp);
    		}
    		else
    		{
      			printstrings (p, len);
    		}
  	}
  	else
  	{
    		printstrings (p, len);
  	}
}

static int trim (const char * buf, int bufLen)
{
  	return  (buf [bufLen - 1] == ' ') ? trim (buf, --bufLen) : bufLen;
}
static int printstrings (const char * buf, const int bufLen)
{
  	int i,j,k,l;
  	unsigned char * buffer = (unsigned char *) malloc (bufLen + 4);
  	int index = 0;
  	if (buffer)
 	{
    		memset (buffer, 0, bufLen + 4);
    		i = 0;
    		j = -1;
    		while (i < bufLen + 1)
    		{
      			if (buf[i] >= 32 &&  buf[i] <= 126)
      			{
        			if (j == -1) j = i;
      			}
      			else
      			{
        			if (j != -1 && ((i - j) > 3))
        			{
          				l = trim (buf + j, i);
          				if ((l -j) > 4)
          				{
                                		for (k = j; k < l; k++) if (buf[k] >=32)  buffer[index++] = buf[k];
                                		buffer[index++] = ' ';
          				}
                                	j = -1;
        			}
      			}

      			i++;
    		}
    		amf_error_docref1(NULL , E_WARNING, "PHP Strings = %s" ,buffer);
    		free (buffer);
  	}
  	else
  	{
    		amf_error_docref1(NULL , E_WARNING, "Out of memory to print strings");
 	}
  	return 0;
}

/*  AMF enumeration {{{1*/

/**  AMF0 types */
enum AMF0Codes { 
	AMF0_NUMBER, 		//0 
	AMF0_BOOLEAN, 		//1
	AMF0_STRING, 		//2
	AMF0_OBJECT, 		//3
	AMF0_MOVIECLIP, 	//4
	AMF0_NULL, 		//5
	AMF0_UNDEFINED,		//6
	AMF0_REFERENCE,		//7
	AMF0_MIXEDARRAY,	//8
	AMF0_ENDOBJECT,		//9
	AMF0_ARRAY, 		//a
	AMF0_DATE, 		//b
	AMF0_LONGSTRING, 	//c
	AMF0_UNSUPPORTED,	//d
	AMF0_RECORDSET,		//e
	AMF0_XML,		//f
	AMF0_TYPEDOBJECT,	//10
	AMF0_AMF3		//11
};

/**  AMF3 types */
enum AMF3Codes { 
	AMF3_UNDEFINED,
	AMF3_NULL,
	AMF3_FALSE,
	AMF3_TRUE,
	AMF3_INTEGER,
	AMF3_NUMBER,
	AMF3_STRING,
	AMF3_XML, 
	AMF3_DATE, 
	AMF3_ARRAY,
	AMF3_OBJECT, 
	AMF3_XMLSTRING,
	AMF3_BYTEARRAY
};

/**  return values for callbacks */
enum AMFCallbackResult { 
	AMFC_RAW, 
	AMFC_XML, 
	AMFC_OBJECT, 
	AMFC_TYPEDOBJECT, 
	AMFC_ANY, 
	AMFC_ARRAY,
	AMFC_NONE,
	AMFC_BYTEARRAY
};

/**  flags passed to amf_encode and amf_decode */
enum AMFFlags { 
	AMF_AMF3 = 1, 
	AMF_BIGENDIAN=2,
	AMF_ASSOC=4,
	AMF_POST_DECODE = 8,
	AMF_AS_STRING_BUILDER = 16, 
	AMF_TRANSLATE_CHARSET = 32,
	AMF_TRANSLATE_CHARSET_FAST = 32|64
};

/**  events invoked by the callback */
enum AMFEvent { 
	AMFE_MAP = 1, 
	AMFE_POST_OBJECT, 
	AMFE_POST_XML, 
	AMFE_MAP_EXTERNALIZABLE,
	AMFE_POST_BYTEARRAY,
	AMFE_TRANSLATE_CHARSET
};

/**  flags for the recordset _amf_recordset_ */
enum AMFRecordSet { 
	AMFR_NONE = 0, 
	AMFR_ARRAY = 1, 
	AMFR_ARRAY_COLLECTION = 2 
};

/**  flags for AMF3_OBJECT */
enum AMF3ObjectDecl {   
	AMF_INLINE_ENTITY = 1, 
	AMF_INLINE_CLASS = 2,
	AMF_CLASS_EXTERNAL = 4,
	AMF_CLASS_DYNAMIC = 8,
	AMF_CLASS_MEMBERCOUNT_SHIFT = 4, 
	AMF_CLASS_SHIFT = 2
};

/**
 *  flags for emitting strings that could possibly being translated
 *  Typically use AMF_STRING_AS_TEXT. When you have bytearrays or XML data it no transformation should be
 *  made, so use AMF_STRING_AS_BYTE. In some cases internal ASCII strings are sent so just use
 *  AMF_STRING_AS_SAFE_TEXT that is equivalent to AMF_STRING_AS_BYTE.
*/
enum AMFStringData { 
	AMF_STRING_AS_TEXT = 0, 
	AMF_STRING_AS_BYTE = 1, 
	AMF_STRING_AS_SAFE_TEXT = 1
};

enum AMFStringTranslate { 
	AMF_TO_UTF8, 
	AMF_FROM_UTF8
};

/*  Memory Management {{{1*/

/**  context of serialization */

class stringhasher 
{
public:
  size_t operator() (const std::string& s) const
  {
    size_t h = 0;
    std::string::const_iterator p, p_end;
    for(p = s.begin(), p_end = s.end(); p != p_end; ++p)
    {
      h = 31 * h + (*p);
    }
    return h;
  }

  /**
   * 
   * @param s1 The first string
   * @param s2 The second string
   * @return true if the first string comes before the second in lexicographical order
   */
  bool operator() (const std::string& s1, const std::string& s2) const
  {
    return s1 < s2;
  }
};

typedef __gnu_cxx::hash_map<std::string, Variant*, stringhasher> HashTable;

struct __amf_serialize_data_t__
{
        HashTable objects0;  /*  stack of objects, no reference */
        HashTable objects;   /*  stack of objects for AMF3, no reference */
        HashTable strings;   /*  stack of strings for AMF3: string key => inde */
        HashTable classes;       /*  stack of classes for AMF3, allocate */
        std::vector<Variant> variantHolder;
        Variant  callbackTarget;
        Variant  callbackFx;
        Variant  zEmpty_string;
        int flags;
        int nextObjectIndex;
        int nextObject0Index;
        int nextClassIndex;
        int nextStringIndex;
	public:
         __amf_serialize_data_t__() {
		variantHolder.clear();
        	callbackTarget = null_variant;
        	callbackFx = null_variant;
        	zEmpty_string ="";
        	flags =0;
        	nextObjectIndex =0;
        	nextObject0Index=0;
        	nextClassIndex=0;
        	nextStringIndex=0;
	}
};
typedef struct __amf_serialize_data_t__ amf_serialize_data_t;
typedef struct __amf_serialize_data_t__ amf_unserialize_data_t;

static int my_call_user_function_ex(Variant& obj, Variant& function_name, Variant& retval, int param_count, Variant params[] , int no_separation, HashTable *symbol_table)
{

  	if(param_count<0 || param_count>2) {
     		return FAILURE;
  	}
  	MethodCallPackage mcp;
  	Array arr = Array::Create();
  	for(int i=0;i<param_count;i++) {
  		arr.append(params[i]);
  	}
  	if(obj != null_variant && !obj.isNull()  && obj.isInitialized()) {
  		Variant clsName = get_static_class_name(obj);
  		mcp.dynamicNamedCall(clsName, function_name, -1);
  		if (LIKELY(mcp.ci != NULL)) {
    			retval = (mcp.ci->getMeth())(mcp, arr);
  		} else {
    			return FAILURE;
  		}

   		return SUCCESS;
  	} else {  
		if(!function_exists(function_name)) {
			return FAILURE;
		}
		retval = invoke(function_name,arr);
		return SUCCESS;
  	}
}

/**
of the encoder is a string that grows depending on the input. When using memory streams or
* smart_str the allocation of memory is not efficient because these methods allow the generic access of the string.
* Instead in our case a StringBuilder approach is better suited. We have implemented such StringBuilder approach
* in which the resulting string is made of string parts. Each string part has a default length of AMFPARTSIZE
* that eventually can be bigger when long strings are appended. At the end of the processing such sequence of parts
* is joined into the resulting strings.
*
* Note: the AMFTSRMLS_CC and AMFTSRMLS_DC macros are required for supporting the stream method. In the StringBuilder
* method such macros are empty
*
*
* Optimized version: the StringBuilder is made of a sequence of references to string zval and blocks of raw data. In this
* way big strings from PHP are just referenced and copied at the end of the encoding. The memory management is modified
* by allocating a big block of memory in which raw and zval parts are placed. This behaviour is obtained by using a two
* state mechanism
*
* Structure
* |shortlength(2bytes)|rawdata|
* |0(2)|zval|
* |-1|
*/


typedef std::string amf_serialize_output_t;
typedef amf_serialize_output_t *amf_serialize_output;

#define amf_SERIALIZE_CTOR(x,cb) amf_serialize_ctor(&x, 1,cb );
#define AMF_UNSERIALIZE_CTOR(x,cb) amf_serialize_ctor(&x, 0, cb );

#define amf_SERIALIZE_DTOR(x,cb)\
                        var_hash.objects0.clear();\
                        var_hash.objects.clear();\
                        var_hash.strings.clear();\
                        var_hash.classes.clear();\
			var_hash.variantHolder.clear();

/**  initializes a zval to a HashTable of zval with a possible number of items */
static int amf_array_init(Variant&arg, int count )
{
	Array arr = Array::Create();
	//arg = arr.getArrayData();
	arg = arr;
        return SUCCESS;
}
static int add_index_zval(Variant& rval,int iIndex,const Variant& zValue)
{
	Array arr = rval.toArray();
	arr.set(iIndex, zValue);
	rval = arr;
        return SUCCESS;
}

static int hash_index_update(Variant& rval, int iIndex, const Variant& zValue) 
{
	Array arr = rval.toArray();
	arr.set(iIndex, zValue);
	rval = arr;
        return SUCCESS;
}

static int add_assoc_zval(Variant& rval, Variant zName, const Variant zValue) {
	Array arr = rval.toArray();
	arr.set(zName, zValue);
	rval = arr;
        return SUCCESS;
}

static int add_property_zval(Variant& val, Variant zName, const Variant zValue) {
   	val.toObject().o_setPublic(zName.toString(), zValue);
        return SUCCESS;
}
static int add_next_index_long(Variant& rval, int l)
{
        Array arr = rval.toArray();
        arr.add((int64)arr.length(), l);
        rval = arr;
        return SUCCESS;
}
static int add_next_index_zval(Variant& rval, const Variant& zval)
{
        Array arr = rval.toArray();
        arr.add((int64)arr.length(), zval);
        rval = arr;
        return SUCCESS;
}
static int hash_index_find(const Variant& rval, int64 idx, Variant& zval)
{
        Array arr = rval.toArray();
	if(arr.exists(idx)) {
		zval = arr.rvalAt(idx);
		return SUCCESS;
	} else {
		return FAILURE;
	}
}




/**  recevies a pointer to the data and to the callback */
static void amf_serialize_ctor(amf_serialize_data_t * x, int is_serialize, Variant& cb )
{
        int error = 1;
        x->callbackTarget = null_variant;
        x->callbackFx = null_variant;
        x->zEmpty_string = "";
        if(cb != null_variant)
        {
                if(cb.isArray())
                {
			Array ar = cb.toArray();
                        int n = ar.length();
                        if(n == 2)
                        {
				CVarRef tmp1 = ar.rvalAtRef(0);
                                if(null_variant!= tmp1 && tmp1.isObject())
                                {
					CVarRef tmp2 = ar.rvalAtRef(1);
                                	if(null_variant!= tmp2 && tmp2.isString())
                                        {
                                                x->callbackTarget = tmp1;
                                                x->callbackFx = tmp2;
                                                error = 0;
                                        }
                                }
                        }
                }
                else if(cb.isString())
                {
                        x->callbackFx = cb;
                        error = 0;
                }
                if(error == 1)
                {
                        amf_error_docref(NULL , E_WARNING, "amf callback requires a string or an array (targetobject,methodname)");
                }
        }

         /*  deserializer stores zval of strings for AMF */
        (x)->nextObjectIndex = 0;
        (x)->nextObject0Index = 0;
        (x)->nextClassIndex = 0;
        (x)->nextStringIndex = 0;
         /*  deserializer stores a hash for each class, while serializer is a long*/
}


/**  returns the i-th element from the array */
static int amf_get_index_long(const Variant& ht, int i, int def)
{
        for (ArrayIter iter = ht.begin(); iter; ++iter) {
                Variant key(iter.first());
                CVarRef var(iter.secondRef());
                if(key.isInteger()){
                        if(var.isInteger())
                        {
                                return var.getInt64();
                        }
                        else if(var.isDouble())
                        {
                                return var.getDouble();
                        }
                        else if(var.isBoolean())
                        {
                                return var.getBoolean()?1:0;
                        }
                        else
                        {
                                return def;
                        }

                }
        }
        return def;
}


/**  returns the i-th element from the array as long and returns default */
static int amf_get_assoc_long(const Variant& ht, const char * field, int def)
{
	for (ArrayIter iter = ht.begin(); iter; ++iter) {
		Variant key(iter.first());
		CVarRef var(iter.secondRef());
		if(key.isString() && !strcmp(key.toString().data(),field)) {
		        if(var.isInteger())
                	{
                        	return var.getInt64();
                	}
               	 	else if(var.isDouble())
                	{
                        	return var.getDouble();
                	}
                	else if(var.isBoolean())
                	{
                        	return var.getBoolean()?1:0;
                	}
                	else
                	{
                        	return def;
                	}

                }
	}
	return def;
}
static int util_hash_index_put(HashTable *ht, const char * field, Variant & pData) {
	string k = field;
	(*ht)[k] = &pData;
        return SUCCESS;

}
static int util_hash_index_put(HashTable *ht, ulong h, Variant& pData) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
	(*ht)[k]=&pData;
        return SUCCESS;
}
static int util_hash_index_put(HashTable *ht, ulong h, ulong l) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
	(*ht)[k]= (Variant*)l;
        return SUCCESS;
}

static int util_hash_next_index_put(HashTable *ht, Variant& pData) {
	std::ostringstream ss;
 	ss<<ht->size();
        string k = ss.str();
	(*ht)[k]=&pData;
        return SUCCESS;
}

static int util_hash_index_find(HashTable *ht, ulong h, Variant & pData) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
        HashTable::iterator res = ht->find(k);
        if ( res != ht->end())
        {
                pData = *(res->second);
                return SUCCESS;
        }
        
        return FAILURE;
                
}

static int util_hash_index_find(HashTable *ht, ulong h, ulong* idx) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
        HashTable::iterator res = ht->find(k);
        if ( res != ht->end())
        {
                *idx = (ulong)(res->second);
                return SUCCESS;
        }

        return FAILURE;

}

static int util_hash_index_find(HashTable *ht, char* h, ulong* idx) {
	std::string k = h;
        HashTable::iterator res = ht->find(k);
        if ( res != ht->end())
        {
		*idx = (ulong)(res->second);
                return SUCCESS;
        }
	
        return FAILURE;

}

static int util_hash_index_find(HashTable *ht, char* h, Variant& pData) {
	std::string k = h;
        HashTable::iterator res = ht->find(k);
        if ( res != ht->end())
        {
		pData = *res->second;
                return SUCCESS;
        }
	
        return FAILURE;

}
static int variant_hash_find(const Variant& ht, const char * field, Variant & pData)
{
        for (ArrayIter iter = ht.begin(); iter; ++iter) {
                Variant key(iter.first());
		CVarRef value(iter.secondRef());
                if(key.isString() && !strcmp(key.toString().data(),field)) {
		    pData = value;
		    return SUCCESS;
                }
                if(key.isInteger() ) {
		    int64 k = key.toInt64();
		    std::ostringstream ss;
 		    ss<<k;
        	    string ks = ss.str();
		    if(!strcmp(ks.c_str(),field)) {
		      pData = value;
		      return SUCCESS;
		    }
                }
        }
        return FAILURE;
}

static int variant_hash_find(const Variant& ht, const Variant& key, Variant& pData)
{
        if (ht.getType() == KindOfArray) {
	    if (ht.toArray().exists(key)) {
		pData = (ht.toArray())[key];	
		return SUCCESS;
	    } else {
		Logger::Error("Failed to find %s in array\n", key.toString().c_str());
		return FAILURE;
	    }
	} else if (ht.getType() == KindOfObject && (key.getType() == KindOfString  || key.getType() == KindOfStaticString)) {
	   if (ht.getObjectData()->o_exists(key.toString(),ht.getObjectData()->o_getClassName())) {
		pData = ht.getObjectData()->o_getUnchecked(key.toString(),ht.getObjectData()->o_getClassName());
		return SUCCESS;
	   } else {
		Logger::Error("Failed to find %s in array\n", key.toString().c_str());
		return FAILURE;
	   } 
	} else  {
	    return FAILURE;
	}
	return FAILURE;
}

#define util_hash_find(h,k,d) util_hash_index_find(h, k, d)


static int util_hash_num_elements(HashTable *ht) {
    return ht->size();
}
static int util_hash_quick_add(HashTable *ht, ulong h, Variant& pData) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
        (*ht)[k] = &pData;
	
        return SUCCESS;
}
static int util_hash_quick_add(HashTable *ht, char *h, ulong v) {
        string k = h;
        (*ht)[k] = (Variant*) v;
	
        return SUCCESS;
}
static int util_hash_quick_add(HashTable *ht, ulong h, ulong v) {
	std::ostringstream ss;
 	ss<<h;
        string k = ss.str();
        (*ht)[k] = (Variant*) v;
	
        return SUCCESS;
}
static int util_hash_quick_add(HashTable *ht, char* h, Variant& pData) {
	std::string k = h;
        (*ht)[k] = &pData;
	
        return SUCCESS;
}
static int util_array_num_elements(const Variant & var) {
  return var.toArray().length();

}
#define util_hash_add(h,k,d)  util_hash_quick_add(h,k,d)

/**
 *  places an object in the cache by using a string representation of its address
 *  it is not using the direct pointer because the key is not guaranteed to be
 *  sized as the pointer
 *  \param old is the pointer to the output code
 *  \param nextIndex is a pointer to a variable containing the nextIndex used by objects
 *  \param action if bit 0 is set do not lookup. If bit 1 is set do not add
 *  \return FAILURE if existent
 *  code taken from serializer
*/
static int amf_cache_zval(HashTable *var_hash, const Variant& var, ulong * old, int * nextIndex, int action, void *suggestedindex = NULL)
{
                ulong old_idx;
                //ulong idx = var.isObject()?(ulong)var.toObject().objectForCall():var.isArray()?(ulong)var.toArray().getArrayData():(ulong)var.getVariantData();
		ulong idx = 0;
		if (suggestedindex) {
			idx = (ulong)suggestedindex;
		} else {
			idx = (ulong) var.asDataPtr();
		}

                if((action & 1) == 0)
                {
                        if (util_hash_index_find(var_hash, idx, &old_idx) == SUCCESS)
                        {
                                *old = old_idx;
                                return FAILURE;
                        }
                }

                if((action & 2) == 0)
                {
                        /* +1 because otherwise hash will think we are trying to store NULL pointer */
                        if(nextIndex == NULL)
                        {
                                *old = util_hash_num_elements(var_hash);
                        }
                        else
                        {
                                *old = *nextIndex;
                                *nextIndex = *nextIndex+1;  /*  equal to the number of element */
                        }
			if (!(var.getType() == KindOfArray && var.toCArrRef().empty())) {
				util_hash_quick_add(var_hash, idx, *old);
			}
                }
        return SUCCESS;
}

static int amf_cache_zval_typed(amf_serialize_data_t*var_hash, const Variant& val, ulong * old, int version, int action )
{
        HashTable *cache = version == 0 ? &(var_hash->objects0) : &(var_hash->objects);
	if(val.isObject() || val.isArray() || val.isResource()) {
           return amf_cache_zval(cache,val,old,version == 0 ? &(var_hash->nextObject0Index) : &(var_hash->nextObjectIndex),action);
        } else {
           return SUCCESS;
        }
}
/*  Encode {{{1*/
static void amf0_serialize_var(amf_serialize_output buf, const Variant&struc, amf_serialize_data_t*var_hash, void * suggestedIndex = NULL);
static void amf3_serialize_var(amf_serialize_output buf, const Variant&struc, amf_serialize_data_t *var_hash, void * suggestedIndex = NULL);
static void amf3_serialize_array(amf_serialize_output buf, const Variant& myht, amf_serialize_data_t *var_hash );
static void amf0_serialize_array(amf_serialize_output buf, const Variant& myht, amf_serialize_data_t* var_hash );
static int amf3_write_string_zval(amf_serialize_output buf, const Variant& string_zval, enum AMFStringData raw, amf_serialize_data_t*var_hash );
static int amf3_write_string(amf_serialize_output buf, const char * cp, int n, enum AMFStringData raw, amf_serialize_data_t*var_hash );
static void amf3_write_int(amf_serialize_output buf, int num );

static void amf_write_byte(amf_serialize_output buf, int n )
{
        char c = (char)n;
        (*buf) += c;
}
static void amf_write_string(amf_serialize_output buf, const char * cp, int length )
{
     buf->append(cp,length);
}

/**  writes a string from a zval. Provides additional optimzation */
static void amf_write_zstring(amf_serialize_output buf, const Variant& zstr )
{
        if (zstr.toString().length() > max_alloc_size)
        {
                amf_bailout();
                return;
        }

#ifndef amf_DISABLE_OUTPUT
        const int len = zstr.toString().length();
        if(len == 0)
        {
                return;
        }
         else
        {
                amf_write_string(buf, zstr.toString().data(),len );
        }
#endif
}

/**  writes an integer in AMF0 format. It is formatted in Big Endian 4 byte */
static void amf0_write_int(amf_serialize_output buf, int n )
{
        char tmp[4] = { (n >> 24) & 0xFF, (n >> 16) & 0xFF, (n >> 8) & 0xFF, (n & 0xFF) };
        amf_write_string(buf, tmp,4 );
}

/**  writes a short in AMF0 format. It is formatted in Big Endian 2 byte */
static void amf0_write_short(amf_serialize_output buf, int n )
{
        amf_write_byte(buf,((n >> 8) & 0xFF));
        amf_write_byte(buf,(n & 0xFF));
}

/**  writes the end of obejct terminator of AMF0 */
static void amf0_write_endofobject(amf_serialize_output buf )
{
        static char endOfObject[] = {0,0,9};
        amf_write_string(buf,endOfObject,3  );
}

static Variant amf_translate_charset_zstring(const Variant& inz, enum AMFStringTranslate direction,amf_serialize_data_t*var_hash  );

static Variant amf_translate_charset_string(const char * cp, int length, enum AMFStringTranslate direction,amf_serialize_data_t*var_hash  );

/**  serializes a zval as zstring in AMF0 using AMF0_STRING or AMF0_LONGSTRING */
static void amf0_serialize_zstring(amf_serialize_output buf, Variant& zv,enum AMFStringData raw, amf_serialize_data_t*var_hash  )
{
        int length;
        if(raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
        {
                Variant zzv;
                if((zzv = amf_translate_charset_zstring(zv, AMF_TO_UTF8, var_hash )) != null_variant)
                {
                        zv = zzv;
                }
        }

         /*  AMF string: b(2) w(length) text(utf) if length < 6553 */
         /*  AMF string: b(12) dw(length) text(utf */
        length = zv.toString().length();
        if(length < 65536)
        {
                amf_write_byte(buf,AMF0_STRING);
                amf0_write_short(buf,length );
                if(length == 0)
                {
                        return;
                }
        }
        else
        {
                amf_write_byte(buf,AMF0_LONGSTRING);
                amf0_write_int(buf,length );
        }
        amf_write_zstring(buf,zv );
}

static void amf0_serialize_emptystring(amf_serialize_output buf )
{
        amf_write_byte(buf,AMF0_STRING);
        amf0_write_short(buf,0 );
}


/**  serializes a string variable */
static void amf0_serialize_string(amf_serialize_output buf, const char * cp,enum AMFStringData raw, amf_serialize_data_t*var_hash   )
{
        int length = strlen(cp);

        if(length > 0 && raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
        {
                Variant zzv = null_variant;
                if((zzv = amf_translate_charset_string(cp,length, AMF_TO_UTF8,var_hash )) != null_variant)
                {
                        amf0_serialize_zstring(buf, (Variant&)zzv,AMF_STRING_AS_BYTE,var_hash );
                        return;
                }
        }

        length = strlen(cp);
        if(length < 65536)
        {
                amf_write_byte(buf,AMF0_STRING);
                amf0_write_short(buf,length );
        }
        else
        {
                amf_write_byte(buf,AMF0_LONGSTRING);
                amf0_write_int(buf,length );
        }
        amf_write_string(buf,cp,length );
}

/**  sends a short string to AMF */
static void amf0_write_string(amf_serialize_output buf, const char * cp, enum AMFStringData raw, amf_serialize_data_t*var_hash    )
{
        int length = strlen(cp);
        if(length > 0 && raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
        {
                Variant  zzv = null_variant;
                if((zzv = amf_translate_charset_string(cp,length,AMF_TO_UTF8,var_hash )) != null_variant)
                {
                        int length = zzv.toString().length();
                        if(length >= 65536)
                        {
                                length = 65536-2;
                        }
                        amf0_write_short(buf,length );
                        amf_write_zstring(buf, zzv );
                        return;
                }
        }

        length = strlen(cp);
        amf0_write_short(buf,length );
        amf_write_string(buf,cp,length );
}

/**  serializes an empty AMF3 string */
static void amf3_write_emptystring(amf_serialize_output buf )
{
        amf_write_byte(buf, 1);
}
/**  writes the AMF3_OBJECT followed by the class information */
static void amf3_write_objecthead(amf_serialize_output buf, int head )
{
        amf_write_byte(buf,AMF3_OBJECT);
        amf3_write_int(buf, head );
}

/**  serializes an Hash Table as AMF3 as plain object */
static void amf3_serialize_object_default(amf_serialize_output buf,const Variant& myht, const char * className,int classNameLen,amf_serialize_data_t*var_hash )
{
        Variant val;
        int memberCount = 0;

        if (util_hash_find(&(var_hash->classes), (char*)className, val) == SUCCESS)
        {
                amf3_write_objecthead(buf,val.toInt64() << AMF_CLASS_SHIFT | AMF_INLINE_ENTITY );
        }
        else
        {
                ulong var_no = var_hash->nextClassIndex++;
                const int isDynamic = AMF_CLASS_DYNAMIC;
                const int isExternalizable = 0;  /*  AMF_CLASS_EXTERNALIZABL */

                util_hash_add(&(var_hash->classes), (ulong)(char*)className, var_no);
                amf3_write_objecthead(buf,memberCount << AMF_CLASS_MEMBERCOUNT_SHIFT | isExternalizable | isDynamic | AMF_INLINE_CLASS | AMF_INLINE_ENTITY  );
                amf3_write_string(buf, className,classNameLen,AMF_STRING_AS_TEXT,var_hash );
        }

         /*  We are always working with dynamic objects except for RecordSe */
         /*  for(j = 0; j < memberCount; j++) fixed value */
         /*  iterate over all the key */
          Array odata = Array::Create();
          CArrRef h = myht.isArray() ? myht.toCArrRef() : (myht.getObjectData()->o_toArray_withInfo(&odata,true)); 

	for (ArrayIter iter(h); iter; ++iter) {
		Variant key(iter.first());
		CVarRef val(iter.secondRef());


                 /*  is it possible */
                if(key.isInteger())
                {
                        char txt[20];
                        unsigned long a = key.toInt64();
                        sprintf(txt,"%d",a);
                        amf3_write_string(buf,txt,strlen(txt), AMF_STRING_AS_SAFE_TEXT,var_hash );
                }
                else if(key.isString())
                {
                         /*  skip arra */
                        if(key.toString().length() == 0 || key.toString().c_str()[0]=='\0')
                        {
                                continue;
                        }
			//TODO -1, why?
                        amf3_write_string(buf,key.toString().c_str(),key.toString().length(),AMF_STRING_AS_TEXT,var_hash );
                }

                /* we should still add element even if it's not OK, since we already wrote the length of the array before */
                //if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) != SUCCESS || !data )
                //{
                //        amf_write_byte(buf, AMF3_UNDEFINED);
                //}
                //else
		 {
			Variant *p = NULL;
			Variant tmp;
			//get the real property name for private members
			DataType retType;
			if (myht.getType() == KindOfObject) {
			String realKey = key.toString().lastToken((char)0);
			Variant typeinfo,offsetinfo;
			if (odata.exists(realKey)) {
				Array typedata = odata[realKey];
				typeinfo = typedata["type"];
				offsetinfo = typedata["offset"];
			} else {
				// this is a dynamic member
				typeinfo = (int)KindOfVariant;
				offsetinfo = 0;
			}
			if (typeinfo.toInt64() == (int)KindOfVariant) { 
			p = (Variant*)myht.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,myht.getObjectData()->o_getClassName());
			if (p && p->getRawType() == KindOfVariant) {
				CVarRef pass = *p;
                                amf3_serialize_var(buf, pass, var_hash);
				continue;
			}
			}
			} else if (myht.getType() == KindOfArray) {
				if (key.getType() == KindOfString || key.getType() == KindOfStaticString) {
				   p = myht.toArray().lvalPtr(key.toCStrRef(),false,false);	
				} else {
				   p = myht.toArray().lvalPtr(key.asInt64Val(),false, false);	
				}
			} else  {
				raise_error("Invalid type of object seen in serialize array");
			}
			if (p && p->getRawType() == KindOfVariant) {
			    CVarRef pass = *p;
                            amf3_serialize_var(buf, pass, var_hash);
			    continue;
			}
		} 
		amf3_serialize_var(buf, (Variant&)val, var_hash );
	        

        }
        amf3_write_emptystring(buf );
}

static int amf_perform_serialize_callback_event(int ievent, const Variant& arg0,Variant& zResultValue, int shared, amf_serialize_data_t * var_hash )
{
        if(var_hash->callbackFx != null_variant)
        {
                int r;  /*  result from functio */
                Variant zEmpty1=null_variant,zievent;
                Variant zResultValuePtr;
                Variant arg0orig = arg0;
                zievent = ievent;
                if(arg0 == null_variant)
                {
                        zEmpty1.setNull();
                }

                {
                        Variant params[2] = { arg0 == null_variant? zEmpty1 : arg0, zievent};
                        if((r = my_call_user_function_ex(var_hash->callbackTarget, var_hash->callbackFx, zResultValuePtr, 2, params, 0, NULL )) == SUCCESS)
                        {
                                if(zResultValuePtr != zResultValue && zResultValuePtr != null_variant)
                                {
                                        if(zResultValue == null_variant)
                                        {
                                                zResultValue = Variant();
                                        }
                                        else if(shared != 0)  /*  cannot replace the zval */
                                        {
                                                zResultValue = Variant();
                                        }
					zResultValue = zResultValuePtr;

                                }
                        }
                }
                return r;
        }
        else
        {
                return FAILURE;
        }
}


/**
 *  invokes the encoding callback
 *  \param event is the event = AMFE_MAP
 *  \param struc is the value
 *  \param className is the resulting class name of the class of the object
 *  \return
*/
static int amf_perform_serialize_callback(const Variant& struc, const char **className, int * classNameLen,
                                                                        Variant& resultValue, amf_serialize_data_t * var_hash )
{
        int resultType = AMFC_TYPEDOBJECT;

        if(var_hash->callbackFx != null_variant)
        {
                Variant zievent;
                Variant rresultValue = null_variant;
                zievent = AMFE_MAP;
                Variant params[] = { struc,zievent};
                if(my_call_user_function_ex(var_hash->callbackTarget, var_hash->callbackFx, rresultValue, 2, params, 0, NULL ) == SUCCESS)
                {
                        if(rresultValue != null_variant && rresultValue.isArray())
                        {
                                Variant tmp;
                                if(rresultValue.toArray().length()>0)
                                {
                                        resultValue = rresultValue.rvalAt(0);
/*
                                        if(zend_hash_index_find(ht, 1,(void**)&tmp) == SUCCESS)
                                        {
                                                convert_to_long_ex(tmp);
                                                resultType = Z_LVAL_PP(tmp);
                                                if(zend_hash_index_find(ht, 2,(void**)&tmp) == SUCCESS && Z_TYPE_PP(tmp) == IS_STRING)
                                                {
                                                        *className = Z_STRVAL_PP(tmp);
                                                        *classNameLen = Z_STRLEN_PP(tmp);
                                                }
                                        }
*/
                                }
                        }
                }
        }
        return resultType;
}

/*  AMF3 object */
static void amf3_serialize_object(amf_serialize_output buf,const Variant& struc, amf_serialize_data_t*var_hash )
{
        const char * className = struc.isResource()? "" : struc.toObject().objectForCall()->o_getClassName();
        int classNameLen = strlen(className);
        ulong objectIndex;

         /*  if the object is already in cache then just go for i */
        if(amf_cache_zval_typed(var_hash, struc, &objectIndex, 1, 2 ) == FAILURE)
        {
                amf3_write_objecthead(buf, (objectIndex << 1) );
                return;
        }
        if(strcmp(className, "stdclass") == 0)  /*  never for resource */
                amf3_serialize_object_default(buf, struc, "",0,var_hash );
        else
        {
                int resultType = AMFC_TYPEDOBJECT;
                Variant resultValue = struc;

                resultType = amf_perform_serialize_callback(struc, &className,&classNameLen,resultValue,var_hash );

                if(resultValue.isResource() )
                {
                        amf_error_docref(NULL , E_WARNING, "amf encoding callback. Resources should be transformed in something");
                        amf_write_byte(buf,AMF3_UNDEFINED);
                        return;
                }

                switch(resultType)
                {
                case AMFC_RAW:
                        if(resultValue.isString())
                        {
                                amf_write_zstring(buf,resultValue );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_RAW requires a string");
                        }
                        break;
                case AMFC_XML:
                        if(resultValue.isString())
                        {
                                amf_write_byte(buf,AMF3_XML);
                                amf3_write_string_zval(buf, resultValue,AMF_STRING_AS_BYTE,var_hash );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_XML requires a string");
                        }
                        break;
                case AMFC_OBJECT:
                        if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,1,0 ) == FAILURE)
                        {
                                amf3_write_objecthead(buf, objectIndex << 1 );
                        }
                        else if(resultValue.isObject())
                        {
                                amf3_serialize_object_default(buf, resultValue, "",0,var_hash );
                        }
                        else if(resultValue.isArray())
                        {
                                amf3_serialize_object_default(buf, resultValue, "",0,var_hash );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_OBJECT requires an object or an array");
                        }

                        break;
                case AMFC_ARRAY:
                        if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,1,0 ) == FAILURE)
                        {
                                amf3_write_objecthead(buf, objectIndex << 1 );
                        }
                        else if(resultValue.isArray())
                        {
                                amf3_serialize_array(buf, resultValue, var_hash );
                        }
                        else if(resultValue.isObject())
                        {
                                amf3_serialize_array(buf, resultValue, var_hash );
                        }
                        else
                        {
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_ARRAY requires an object or an array");
                        }
                        break;
                case AMFC_TYPEDOBJECT:
                        if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,1,0 ) == FAILURE)
                        {
                                amf3_write_objecthead(buf, objectIndex << 1 );
                        }
                        else if(resultValue.isObject())
                        {
                                amf3_serialize_object_default(buf, resultValue,className,classNameLen, var_hash );
                        }
                        else if(resultValue.isArray())
                        {
                                amf3_serialize_object_default(buf, resultValue, className,classNameLen,var_hash );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_TYPEDOBJECT requires an object or an array");
                        }
                        break;
                case AMFC_ANY: amf3_serialize_var(buf, resultValue, var_hash ); break;
                case AMFC_NONE: amf_write_byte(buf,AMF3_UNDEFINED); break;
                case AMFC_BYTEARRAY:
                        if(resultValue.isString())
                        {
                                amf_write_byte(buf, AMF3_BYTEARRAY);
                                amf3_write_string_zval(buf, resultValue, AMF_STRING_AS_BYTE,var_hash );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_BYTEARRAY requires a string");
                        }
                        break;
                default:
                        amf_write_byte(buf,AMF3_UNDEFINED);
                        amf_error_docref(NULL , E_WARNING, "amf encoding callback. unknown type %d", resultType);
                        break;
                }
        }
}

/*
 serializes an object
 objectdata:
   utfname data
   w(0) b(9) = endof

 objectdata:
   utfname data
   w(0) b(9)
*/
static void amf0_serialize_objectdata(amf_serialize_output buf, const Variant&z, int isArray, amf_serialize_data_t*var_hash )
{
	  Array odata = Array::Create();
	  CArrRef h = isArray ? z.toCArrRef() : (z.getObjectData()->o_toArray_withInfo(&odata,true)); 

        for (ArrayIter iter(h); iter; ++iter) {
                Variant key(iter.first());
		CVarRef val(iter.secondRef());

                if(key.isInteger())
                {
                        char txt[20];
                        int length;
			unsigned long a = key.toInt64();
                        sprintf(txt,"%d",a);
                        length = strlen(txt);
                        amf0_write_short(buf,length  );
                        amf_write_string(buf,txt,length  );
                }
                else
                {
                         /*  skip private member */
                        if(isArray == 0 && (key.toString().length()==0 || (key.toString().c_str()[0] == '\0')))
                        {
                                continue;
                        }
                        amf0_write_short(buf,key.toString().length() );
                        amf_write_string(buf,key.toString(),key.toString().length() );
                }

                /* we should still add element even if it's not OK,since we already wrote the length of the array before */
                //if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) != SUCCESS || !data )
                //{
                //        amf_write_byte(buf, AMF0_UNDEFINED);
                //}
                //else
		{
			Variant *p = NULL;
			Variant tmp;
			//get the real property name for private members
			DataType retType;
			if (z.getType() == KindOfObject) {
			String realKey = key.toString().lastToken((char)0);
			Variant typeinfo,offsetinfo;
			if (odata.exists(realKey)) {
				Array typedata = odata[realKey];
				typeinfo = typedata["type"];
				offsetinfo = typedata["offset"];
			} else {
				// this is a dynamic member
				typeinfo = (int)KindOfVariant;
				offsetinfo = 0;
			}
			if (typeinfo.toInt64() == (int)KindOfVariant) { 
			p = (Variant*)z.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,z.getObjectData()->o_getClassName());
			if (p && p->getRawType() == KindOfVariant) {
			    CVarRef pass = *p;
                            amf0_serialize_var(buf, pass, var_hash );
			    continue;
			}
			}
			/* Fall Through */
			} else if (z.getType() == KindOfArray) {
				if (key.getType() == KindOfString || key.getType() == KindOfStaticString) {
				   p = z.toArray().lvalPtr(key.toCStrRef(),false,false);	
				} else {
				   p = z.toArray().lvalPtr(key.asInt64Val(),false, false);	
				}
			} else  {
				raise_error("Invalid type of object seen in serialize array");
			}
			if (p) {
			    CVarRef pass = *p;
                            amf0_serialize_var(buf, pass, var_hash );
			    continue;
			} 		
		} 
		amf0_serialize_var(buf, val, var_hash );
        }
        amf0_write_endofobject(buf );
}

/*
 serializes an object
 objectdata:
   utfname data
   w(0) b(9) = endof

 objectdata:
   utfname data
   w(0) b(9)
*/
static void amf0_serialize_object(amf_serialize_output buf, const Variant& struc, amf_serialize_data_t*var_hash )
{
        const char * className = struc.isResource() ? "" : struc.toObject().objectForCall()->o_getClassName();
        int classNameLen = strlen(className);
        ulong objectIndex;

         /*  if the object is already in cache then just go for i */
        if(amf_cache_zval_typed(var_hash, struc, &objectIndex, 1, 2 ) == FAILURE)
        {
                amf_write_byte(buf,AMF0_REFERENCE);
                amf0_write_short(buf, objectIndex );
                return;
        }
        if(strcmp(className, "stdclass") == 0)
        {
                amf_write_byte(buf,AMF0_OBJECT);
                amf0_serialize_objectdata(buf, struc, 0, var_hash );
        }
        else
        {
                int resultType = AMFC_TYPEDOBJECT;
                int resultValueLength = 0;
                Variant resultValue = struc;

                resultType = amf_perform_serialize_callback(struc, &className,&classNameLen,resultValue,var_hash );

                if(resultValue.isResource())
                {
                        amf_error_docref(NULL , E_WARNING, "amf encoding callback. Resources should be transformed in something");
                        amf_write_byte(buf,AMF0_UNDEFINED);
                        return;
                }

                switch(resultType)
                {
                case AMFC_RAW:
                         /*  it's a string purely sen */
                        amf_write_zstring(buf,resultValue  );
                        break;
                case AMFC_XML:
                         /*  TODO: handle referenc */
                        resultValueLength = resultValue.toString().length();
                        amf_write_byte(buf,AMF0_XML);
                        amf0_write_int(buf,resultValueLength  );
                        amf_write_zstring(buf,resultValue );
                        break;
                case AMFC_OBJECT:
                        if(resultValue.isObject())
                        {
                                if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,0,0 ) == FAILURE)
                                {
                                        amf_write_byte(buf,AMF0_REFERENCE);
                                        amf0_write_short(buf, objectIndex );
                                }
                                else
                                {
                                        amf_write_byte(buf,AMF0_OBJECT);
                                        amf0_serialize_objectdata(buf, resultValue, 0, var_hash );
                                }
                        }
                        else
                        {
                                amf_write_byte(buf,AMF0_NULL);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_OBJECT requires an object");
                        }
                        break;
                case AMFC_ARRAY:
                        if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,0,0 ) == FAILURE)
                        {
                                amf_write_byte(buf,AMF0_REFERENCE);
                                amf0_write_short(buf, objectIndex );
                        }
                        else if(resultValue.isArray())
                        {
                                amf0_serialize_array(buf, resultValue, var_hash );
                        }
                        else if(resultValue.isObject())
                        {
                                amf0_serialize_array(buf, resultValue, var_hash );
                        }
                        else
                        {
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_ARRAY requires an object or an array");
                        }
                        break;
                case AMFC_TYPEDOBJECT:
                        if(amf_cache_zval_typed(var_hash, resultValue, &objectIndex,0,0 ) == FAILURE)
                        {
                                amf_write_byte(buf,AMF0_REFERENCE);
                                amf0_write_short(buf, objectIndex );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF0_TYPEDOBJECT);
                                if(resultValue.isObject() )
                                {
                                        amf0_write_string(buf,className,AMF_STRING_AS_TEXT,var_hash );
                                        amf0_serialize_objectdata(buf, resultValue, 0, var_hash );
                                }
                                else
                                {
                                        amf0_write_string(buf, className,AMF_STRING_AS_TEXT,var_hash  );
                                        amf0_serialize_objectdata(buf, resultValue, 0,var_hash );
                                }
                        }
                        break;
                case AMFC_ANY:  amf0_serialize_var(buf, resultValue, var_hash ); break;
                case AMFC_NONE: amf_write_byte(buf,AMF0_UNDEFINED); break;
                case AMFC_BYTEARRAY:
                        if(resultValue.isString())
                        {
                                amf0_serialize_zstring(buf, (Variant&)resultValue,AMF_STRING_AS_BYTE,var_hash );
                        }
                        else
                        {
                                amf_write_byte(buf,AMF0_UNDEFINED);
                                amf_error_docref(NULL , E_WARNING, "amf encoding callback. AMFC_BYTEARRAY requires a string");
                        }
                        break;
                default:
                        amf_write_byte(buf,AMF0_UNDEFINED);
                        amf_error_docref(NULL , E_WARNING, "amf encoding callback. unknown type %d", resultType);
                        break;
                }
        }
}

/**  writes an integer in AMF3 format as a variable bytes */
static void amf3_write_int(amf_serialize_output buf, int value  )
{
        value &= 0x1fffffff;
        if(value < 0x80)
        {
                amf_write_byte(buf,value);
        }
        else if(value < 0x4000)
        {
                amf_write_byte(buf,value >> 7 & 0x7f | 0x80);
                amf_write_byte(buf,value & 0x7f);
        }
        else if(value < 0x200000)
        {
                amf_write_byte(buf,value >> 14 & 0x7f | 0x80);
                amf_write_byte(buf,value >> 7 & 0x7f | 0x80);
                amf_write_byte(buf,value & 0x7f);
        }
        else
        {
                char tmp[4] = { value >> 22 & 0x7f | 0x80, value >> 15 & 0x7f | 0x80, value >> 8 & 0x7f | 0x80, value & 0xff };
                amf_write_string(buf,tmp,4 );
        }
}

/**  writes a double number in AMF format. It is stored as Big Endian */
static void amf0_write_number(amf_serialize_output buf, double num, amf_serialize_data_t * var_hash )
{
        union aligned {
                double dval;
                char cval[8];
        } d;
        const char * number = d.cval;
        d.dval = num;

         /*  AMF number: b(0) double(8 bytes big endian */
        if((var_hash->flags & AMF_BIGENDIAN) != 0)
        {
                char numberr[8] = {number[7],number[6],number[5],number[4],number[3],number[2],number[1],number[0]};
                amf_write_string(buf, numberr,8 );
        }
        else
        {
                amf_write_string(buf, number,8 );
        }
}

/**  writes a number in AMF3 format, the same as AMF0 */
static void amf3_write_number(amf_serialize_output buf, double num,amf_serialize_data_t*var_hash )
{
        amf0_write_number(buf,num,var_hash );
}


/*  serializes a string */
static int amf3_write_string(amf_serialize_output buf, const char * string_ptr, int string_length, enum AMFStringData raw, amf_serialize_data_t*var_hash )
{
        if(string_length == 0)
        {
                amf_write_byte(buf, 1);  /*  inline and empt */
                return -1;
        }
        else
        {
                ulong val;
                if (util_hash_find(&(var_hash->strings), (char*)string_ptr, &val) == SUCCESS)
                {
                        amf3_write_int(buf,(val-1) << 1 );
                        return val-1;
                }
                else
                {
                        ulong index = ++var_hash->nextStringIndex;
                        util_hash_add(&(var_hash->strings), (char*)string_ptr,  index);
                        amf3_write_int(buf,((string_length << 1) | AMF_INLINE_ENTITY) );

                        if(raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
                        {
                                Variant  zv = null_variant;
                                if((zv = amf_translate_charset_string(string_ptr, string_length,AMF_TO_UTF8,var_hash )) != null_variant)
                                {
                                        amf_write_zstring(buf, zv );
                                        return index-1;
                                }
                        }
                        amf_write_string(buf, string_ptr,string_length );
                        return index-1;
                }
        }
}

/**  writes a string from ZVAL in AMF3 format. Useful for memory reference optimization */
static int amf3_write_string_zval(amf_serialize_output buf, const Variant& string_zval, enum AMFStringData raw, amf_serialize_data_t*var_hash )
{
        int string_length = string_zval.toString().length();
        const char * string_ptr = string_zval.toString().data();
        if(string_length == 0)
        {
                amf_write_byte(buf, 1);  /*  inline and empt */
                return -1;
        }
        else
        {
                ulong val;

                if (util_hash_find(&(var_hash->strings), (char*)string_ptr,  &val) == SUCCESS)
                {
                        amf3_write_int(buf,(val-1) << 1 );
                        return val-1;
                }
                else
                {
                        ulong index = ++var_hash->nextStringIndex;
                        util_hash_add(&(var_hash->strings), (char*)string_ptr,  index);
                        amf3_write_int(buf,string_length << 1 | AMF_INLINE_ENTITY );
                        if(raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
                        {
                                Variant  zv = null_variant;
                                if((zv = amf_translate_charset_zstring(string_zval,AMF_TO_UTF8, var_hash )) != null_variant )
                                {
                                        amf_write_zstring(buf, zv );
                                        return index-1;
                                }
                        }
                        amf_write_zstring(buf, string_zval );
                        return index-1;
                }
        }
}

static void amf3_serialize_array(amf_serialize_output buf, const Variant& myht, amf_serialize_data_t *var_hash )
{
        if (myht && util_array_num_elements(myht) != 0)
        {
                //char *key;
                Variant data;
                int keyIndex;
                //uint key_len;
                int rt;
		Array odata = Array::Create();
		CArrRef h = myht.isArray() ? myht.toCArrRef() : (myht.getObjectData()->o_toArray_withInfo(&odata,true));
		const Variant ROWSTRING="rows";
		const Variant COLSTRING="columns";

                /**
                 * Special Handling for arrays with __amf_recordset__
                 */
                if((rt = amf_get_assoc_long(myht,"__amf_recordset__",0)) != AMFR_NONE)
                {
                        Variant columns,rows;
                        Variant htRows;
                        Variant htColumns;
                        int nColumns,nRows,iRow;
                        int iClassDef = 0; //keeping compiler happy


                        if (variant_hash_find(myht, ROWSTRING, rows) == SUCCESS &&
                                        variant_hash_find(myht, COLSTRING, columns) == SUCCESS &&
                                        rows.isArray() &&
                                        columns.isArray() )
                        {
                                htRows = rows;
                                htColumns = columns;
                                nColumns = util_array_num_elements(htColumns);
                                nRows = util_array_num_elements(htRows);

                                if(rt == AMFR_ARRAY_COLLECTION)
                                {
                                        const char * ac = "flex.messaging.io.ArrayCollection";
                                        amf3_write_objecthead(buf, AMF_INLINE_ENTITY|AMF_INLINE_CLASS|AMF_CLASS_EXTERNAL );
                                        amf3_write_string(buf, ac,strlen(ac),AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        var_hash->nextClassIndex++;
                                        var_hash->nextObjectIndex++;
                                }

                                 /*  emi */
                                amf_write_byte(buf,AMF3_ARRAY);
                                amf3_write_int(buf, (nRows << 1) | AMF_INLINE_ENTITY );
                                amf3_write_emptystring(buf );
                                 /*  increment the object count in the cach */
                                iRow = 0;
        			for (ArrayIter iter = htRows.begin(); iter; ++iter) {
                			Variant key(iter.first());
					CVarRef zRow(iter.secondRef());

                                        int nColumnSizeOfRow;
                                        int iColumn;
                                        Variant htRow;

                                        if (!key.isInteger())
                                        {
                                                break;
                                        }
                                        if (! zRow.isArray() ) 
                                        {
                                                amf_write_byte(buf, AMF3_UNDEFINED);
                                                continue;
                                        }
                                        htRow = zRow;
                                        nColumnSizeOfRow = util_array_num_elements(htRow);
                                        if(nColumnSizeOfRow > nColumns)  /*  long row */
                                        {
                                                nColumnSizeOfRow = nColumns;
                                        }

                                        if(iRow == 0)
                                        {
                                                amf3_write_objecthead(buf, nColumns << AMF_CLASS_MEMBERCOUNT_SHIFT |AMF_INLINE_CLASS|AMF_INLINE_ENTITY);
                                                amf3_write_emptystring(buf );  /*  empty class nam */
                                                iClassDef = var_hash->nextClassIndex++;
						Variant iColumnVar = iColumn;
                                                Variant columnName;

                                                for(iColumn = 0; iColumn < nColumns; iColumn++)
                                                {
							iColumnVar = iColumn;
                                                        variant_hash_find(htColumns, iColumnVar,columnName);
                                                        if(!columnName.isString())
                                                        {
                                                                char key[255];
                                                                sprintf(key,"unk%d",iColumn);
                                                                amf3_write_string(buf,key,strlen(key),AMF_STRING_AS_SAFE_TEXT,var_hash );
                                                        }
                                                        else
                                                        {
                                                                amf3_write_string_zval(buf,columnName,AMF_STRING_AS_TEXT,var_hash );
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                amf3_write_objecthead(buf, iClassDef << AMF_CLASS_SHIFT | AMF_INLINE_ENTITY);
                                        }
                                        var_hash->nextObjectIndex++;
					iColumn = 0;
        				for (ArrayIter iter = htRow.begin(); iter; ++iter) {
                				Variant key(iter.first());
						CVarRef zValue(iter.secondRef());
                                                if (!key.isInteger())
                                                {
                                                        break;
                                                }
                                                if(zValue == null_variant)
                                                {
                                                        amf_write_byte(buf, AMF3_UNDEFINED);
                                                }
                                                else
                                                {
							// Fixme relookup
							Variant *p = htRow.toArray().lvalPtr(key.toInt64(),false, false);
							if (p && p->getRawType() == KindOfVariant) {
							amf3_serialize_var(buf, *p, var_hash );
							} else {
							amf3_serialize_var(buf, zValue, var_hash );
							}

                                                }
                                                iColumn++;
                                        }

                                         /*  short row */
                                        for(; iColumn < nColumns; iColumn++)
                                                amf_write_byte(buf, AMF3_UNDEFINED);
                                        iRow++;
                                }
                                return;
                        }
                        else
                        {
                                amf_error_docref(NULL , E_WARNING, "amf cannot understand special recordset array: should have __AMF_recordset__, rows and columns keys");
                        }
                }

                {
                        int max_index = -1;
                        ulong str_count = 0, num_count = 0;
                        int has_negative = 0;

        		for (ArrayIter iter(h); iter; ++iter) {
                		Variant key(iter.first());
				keyIndex = key.toInt64();
                                switch (key.getType()) {
                                case KindOfInt32:
                                case KindOfInt64:
                                        if(keyIndex > max_index)
                                        {
                                                max_index =  keyIndex;
                                        }
                                        if(keyIndex < 0)
                                        {
                                                has_negative = 1;
                                                str_count++;
                                        }
                                        else
                                        {
                                                num_count++;
                                        }
                                        break;
                                case KindOfString:
                                case KindOfStaticString:
                                        str_count++;
                                        break;
				default: break;
                                }
                        }
                         /*  string array or not sequenced array => associativ */
                         /* if(num_count > 0 && (str_count > || max_index != num_count-1) */
                        if((str_count > 0 && num_count == 0) || (num_count > 0 && max_index != (int)num_count-1))
                        {

                                amf3_write_objecthead(buf, AMF_INLINE_ENTITY|AMF_INLINE_CLASS|AMF_CLASS_DYNAMIC);
                                amf3_write_emptystring(buf );  /*  classname=" */
                                var_hash->nextClassIndex++; //http://pecl.php.net/bugs/bug.php?id=12668&edit=1
        			for (ArrayIter iter(h); iter; ++iter) {
                			Variant key(iter.first());
					CVarRef val(iter.secondRef());
                                        switch (key.getType()) {
                                        case KindOfInt32:
                                        case KindOfInt64:
                                                        {
                                                                char txt[20];
								unsigned long a = key.toInt64();

                                                                sprintf(txt,"%d",a);
                                                                amf3_write_string(buf, txt,strlen(txt),AMF_STRING_AS_SAFE_TEXT,var_hash );
                                                        }
                                                        break;
                                                case KindOfString:
                                                case KindOfStaticString:
                                                        amf3_write_string(buf, key.toString().data(),key.toString().length(),AMF_STRING_AS_TEXT,var_hash );
                                                        break;
						default: 
							break;
                                        }
                                        //if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) != SUCCESS || !data )
                                        //{
                                        //        amf_write_byte(buf, AMF3_UNDEFINED);
                                       // }
                                        //else
					{
						Variant *p = NULL;
						Variant tmp;
						//get the real property name for private members
						DataType retType;
						if (myht.getType() == KindOfObject) {
						String realKey = key.toString().lastToken((char)0);
						Variant typeinfo,offsetinfo;
						if (odata.exists(realKey)) {
							Array typedata = odata[realKey];
							typeinfo = typedata["type"];
							offsetinfo = typedata["offset"];
						} else {
							// this is a dynamic member
							typeinfo = (int)KindOfVariant;
							offsetinfo = 0;
						}
						if (typeinfo.toInt64() == (int)KindOfVariant) { 
						p = (Variant*)myht.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,myht.getObjectData()->o_getClassName());
						if (p && p->getRawType() == KindOfVariant) {
						    amf3_serialize_var(buf, (Variant&)(*p), var_hash );
						    continue;
						}
						} 						
						} else if (myht.getType() == KindOfArray) {
							if (key.getType() == KindOfString || key.getType() == KindOfStaticString) {
							   p = myht.toArray().lvalPtr(key.toCStrRef(),false,false);	
							} else {
							   p = myht.toArray().lvalPtr(key.asInt64Val(),false, false);	
							}
						} else  {
							raise_error("Invalid type of object seen in serialize array");
						}
						if (p && p->getRawType() == KindOfVariant) {
						    amf3_serialize_var(buf, (Variant&)(*p), var_hash );
						    continue;
						}
					}
					amf3_serialize_var(buf, (Variant&)val, var_hash );
					}
                                amf3_write_emptystring(buf );

                        }
                        else
                        {
                                amf_write_byte(buf,AMF3_ARRAY);
                                amf3_write_int(buf,(num_count << 1) | AMF_INLINE_ENTITY );

                                 /*  string keys or negativ */
                                if(str_count > 0)
                                {
        				for (ArrayIter iter = myht.begin(); iter; ++iter) {
                				Variant key(iter.first());
						CVarRef val(iter.secondRef());
                                                int skip = 0;
                                                switch (key.getType()) {
                                                case KindOfInt32:
                                                case KindOfInt64:
								keyIndex = key.toInt64();
                                                                if(keyIndex < 0)
                                                                {
                                                                        char txt[20];
                                                                        sprintf(txt,"%d",keyIndex);
                                                                        amf3_write_string(buf, txt,strlen(txt),AMF_STRING_AS_SAFE_TEXT,var_hash );
                                                                }
                                                                else
                                                                {
                                                                        skip = 1;  /*  numeric keys are dumped in sequential mod */
                                                                }
                                                                break;
                                                        case KindOfString:
                                                        case KindOfStaticString:
                                                                amf3_write_string(buf, key.toString().data(),key.toString().length(),AMF_STRING_AS_TEXT,var_hash );
                                                                break;
							default:
								break;
                                                }
                                                if(skip)
                                                        continue;
						{
							Variant *p = NULL;
							Variant tmp;
							//get the real property name for private members
							DataType retType;
							if (myht.getType() == KindOfObject) {
							String realKey = key.toString().lastToken((char)0);
							Variant typeinfo,offsetinfo;
							if (odata.exists(realKey)) {
								Array typedata = odata[realKey];
								typeinfo = typedata["type"];
								offsetinfo = typedata["offset"];
							} else {
								// this is a dynamic member
								typeinfo = (int)KindOfVariant;
								offsetinfo = 0;
							}
							if (typeinfo.toInt64() == (int)KindOfVariant) { 
							p = (Variant*)myht.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,myht.getObjectData()->o_getClassName());
							if (p && p->getRawType() == KindOfVariant) {
							    amf3_serialize_var(buf, (Variant&)(*p), var_hash );
							    continue;
							}
							} 							
						} else if (myht.getType() == KindOfArray) {
								if (key.getType() == KindOfString || key.getType() == KindOfStaticString) {
								   p = myht.toArray().lvalPtr(key.toCStrRef(),false,false);	
								} else {
								   p = myht.toArray().lvalPtr(key.asInt64Val(),false, false);	
								}
							} else  {
								raise_error("Invalid type of object seen in serialize array");
							}
							if (p && p->getRawType() == KindOfVariant) {
							    amf3_serialize_var(buf, (Variant&)(*p), var_hash );
							    continue;
							}	
						}
						amf3_serialize_var(buf, (Variant&)val, var_hash );
						}

                                                //if (zend_hash_get_current_data_ex(myht, (void **) &data, &pos) == SUCCESS && data != NULL)
                                                //else
                                                //{
                                                //        amf_write_byte(buf, AMF3_UNDEFINED);
                                                //}
                                }
                                 /*  place the empty strin */
                                amf3_write_emptystring(buf );

                                 /*  now the linear data, we need to lookup the data because of the sortin */
                                if(num_count > 0)
                                {
                                        int iIndex;
					Variant iIndexVar;
                                         /*  lookup the key if existent (use 0x0 undefined */
                                        for(iIndex = 0; iIndex <= max_index; iIndex++)
                                        {
						iIndexVar = iIndex;
                                                if(variant_hash_find(myht, iIndexVar,data) == FAILURE)
                                                {
                                                        amf_write_byte(buf, AMF3_UNDEFINED);
                                                }
                                                else
                                                {
							{
                                                // Fixme relookup
							Variant *p = myht.toArray().lvalPtr(iIndex,false, false);
							if (p && p->getRawType() == KindOfVariant) {
							amf3_serialize_var(buf, *p, var_hash );
							} else {
	
                                                        amf3_serialize_var(buf, data, var_hash );
							}
							}
                                                }
                                        }
                                }
                        }
                }
        }
        else
        {
                 /*  just an empty arra */
                amf_write_byte(buf,AMF3_ARRAY);
                amf3_write_int(buf,0 | 1 );
                amf3_write_emptystring(buf );
        }
}

static void amf3_serialize_var(amf_serialize_output buf, const Variant& struc, amf_serialize_data_t *var_hash , void *suggestIndex)
{
        ulong objectIndex;

        switch (struc.getType()) {
                case KindOfBoolean: amf_write_byte(buf, struc.toBoolean() ? AMF3_TRUE : AMF3_FALSE); return;
                case KindOfNull: amf_write_byte(buf, AMF3_NULL); return;
                case KindOfInt32:
                case KindOfInt64:
                         /*  AMF3 integer: b(4) ber encoding(1-4) only if not too big 29 bit */
                        {
                                long d = struc.toInt64();
                                if(d >= -268435456 && d <= 268435455)
                                {
                                        amf_write_byte(buf, AMF3_INTEGER);
                                        amf3_write_int(buf,d );
                                }
                                else
                                {
                                        amf_write_byte(buf, AMF3_NUMBER);
                                        amf3_write_number(buf,d,var_hash );
                                }
                        }
                        return;
                case KindOfDouble:
                        amf_write_byte(buf, AMF3_NUMBER);
                        amf3_write_number(buf,struc.toDouble(),var_hash );
                        return;
                case KindOfString:
                case KindOfStaticString:
                        amf_write_byte(buf, AMF3_STRING);
                        amf3_write_string_zval(buf, struc, AMF_STRING_AS_TEXT,var_hash );
                        return;
                //case KindOfResource:
                case KindOfObject:
                        amf3_serialize_object(buf,struc,var_hash );
                        return;
                case KindOfArray:
                        if(amf_cache_zval(&(var_hash->objects), struc, &objectIndex,&(var_hash->nextObjectIndex),0,suggestIndex) == FAILURE)
                        {
                                amf_write_byte(buf, AMF3_ARRAY);
                                amf3_write_int(buf, (objectIndex << 1) );
                        }
                        else
                        {
                                amf3_serialize_array(buf, struc, var_hash );
                        }
                        break;
                default:
                        amf_error_docref(NULL , E_WARNING, "amf unknown PHP type\n");
                        amf_write_byte(buf, AMF3_UNDEFINED);
                        return;
                }

}

Variant& amf_get_holder(amf_serialize_data_t* var_hash) {
	var_hash->variantHolder.push_back(null_variant);
	return var_hash->variantHolder.back();
}
/**
 *  serializes an array in AMF0 format
 *  It checks form _amf_recordset_
*/
static void amf0_serialize_array(amf_serialize_output buf, const Variant& myht, amf_serialize_data_t* var_hash )
{
        if (util_array_num_elements(myht) != 0)
        {
                //char *key;
                int keyIndex;
                //uint key_len;
                uint str_count = 0, num_count = 0;
                int has_negative = 0;
                int max_index = -1;

                /**
                 * Special Handling for arrays with __amf_recordset__
                 * AMF0: no ArrayCollection
                 */
                if(amf_get_assoc_long(myht,"__amf_recordset__",0) != AMFR_NONE)
                {
                        Variant columns,rows,id;
                        Variant htRows;
                        Variant htColumns;
                        int nColumns,nRows,iRow;
			const Variant ROWSTRING="rows";
			const Variant IDSTRING ="id";
			const Variant COLSTRING="columns";

                        if (variant_hash_find(myht, ROWSTRING, rows) == SUCCESS &&
                                        variant_hash_find(myht, COLSTRING, columns) == SUCCESS &&
                                        rows.isArray() &&
                                        columns.isArray() )
                        {
                                id = null_variant;
                                variant_hash_find(myht, IDSTRING, id);
                                htRows = rows;
                                htColumns = columns;
                                nColumns = util_array_num_elements(htColumns);
                                nRows = util_array_num_elements(htRows);

                                 /*  typedobject class=RecordSe */
                                amf_write_byte(buf, AMF0_TYPEDOBJECT);
                                amf0_write_string(buf,"RecordSet",AMF_STRING_AS_SAFE_TEXT,var_hash );

                                amf0_write_string(buf,"serverInfo",AMF_STRING_AS_SAFE_TEXT,var_hash  );
                                amf_write_byte(buf, AMF0_OBJECT);
                                var_hash->nextObject0Index++;
                                {
                                        amf0_write_string(buf,"version",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf_write_byte(buf, AMF0_NUMBER);
                                        amf0_write_number(buf, 1, var_hash );

                                        amf0_write_string(buf,"totalCount",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf_write_byte(buf, AMF0_NUMBER);
                                        amf0_write_number(buf, nRows, var_hash );

                                        amf0_write_string(buf,"cursor",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf_write_byte(buf, AMF0_NUMBER);
                                        amf0_write_number(buf, 1, var_hash );

                                        amf0_write_string(buf,"serviceName",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf0_serialize_string(buf,"PageAbleResult",AMF_STRING_AS_SAFE_TEXT,var_hash );

                                        amf0_write_string(buf,"id",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        if(id != null_variant)
                                        {
					
						Variant *p = NULL;
						if (myht.getType() == KindOfArray) {
							p = myht.toArray().lvalPtr("id",false, false);
							if (p && p->getRawType() == KindOfVariant) {
							    amf0_serialize_var(buf, *p, var_hash );
							} else {
							    amf0_serialize_var(buf, id, var_hash );
							}
						} else if (myht.getType() == KindOfObject) {
							Array odata = Array::Create();
							Variant typeinfo,offsetinfo;
							myht.getObjectData()->o_toArray_withInfo(&odata,true);
							String realKey("id");
							DataType retType;
							if (odata.exists(realKey)) {
								Array typedata = odata[realKey];
								typeinfo = typedata["type"];
								offsetinfo = typedata["offset"];
							} else {
								// this is a dynamic member
								typeinfo = (int)KindOfVariant;
								offsetinfo = 0;
							}
							if (typeinfo.toInt64() == (int)KindOfVariant) {
							p = (Variant*)myht.getObjectData()->o_realPropPtr(realKey, ObjectData::RealPropUnchecked|ObjectData::RealPropWrite, &retType, false,myht.getObjectData()->o_getClassName());
							if (p && p->getRawType() == KindOfVariant) {
								amf0_serialize_var(buf, *p, var_hash );
							} else {
								amf0_serialize_var(buf, id, var_hash );
							}
							} else {
							amf0_serialize_var(buf, id , var_hash);
							}
						} else {
							raise_error("Invalid arraytype found during serialize");
						}
                                        }
                                        else
                                        {
                                                amf0_serialize_emptystring(buf );
                                        }

                                        amf0_write_string(buf,"columnNames",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf_write_byte(buf, AMF0_ARRAY);
                                        amf0_write_int(buf, nColumns );
                                        {
                                                int iColumn;
						Variant columnName;
						Variant iColumnVar;
                                                for(iColumn = 0; iColumn < nColumns; iColumn++)
                                                {
							iColumnVar = iColumn;
                                                        variant_hash_find(htColumns, iColumnVar,columnName);
                                                        if(!columnName.isString())
                                                        {
                                                                amf0_serialize_string(buf,"unk",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                                        }
                                                        else
                                                        {
                                                                amf0_serialize_zstring(buf,(Variant&)columnName,AMF_STRING_AS_TEXT,var_hash );
                                                        }
                                                }
                                        }

                                        amf0_write_string(buf,"initialData",AMF_STRING_AS_SAFE_TEXT,var_hash );
                                        amf_write_byte(buf, AMF0_ARRAY);
                                        amf0_write_int(buf, nRows );
                                        {
                                                iRow = 0;
						for (ArrayIter iter = htRows.begin(); iter; ++iter) {
							Variant key(iter.first());
							CVarRef var(iter.secondRef());

                                                        int nColumnSizeOfRow;
                                                        int iColumn;
                                                        Variant htRow;
                                                        if (!key.isInteger())
                                                                break;
							keyIndex = key.toInt64();
                                                        if ( var == null_variant || !var.isArray() )
                                                        {
                                                                amf_write_byte(buf, AMF3_UNDEFINED);
                                                                continue;
                                                        }
                                                        htRow = var;
                                                        amf_write_byte(buf, AMF0_ARRAY);
                                                        amf0_write_int(buf, nColumns );
                                                        nColumnSizeOfRow = util_array_num_elements(htRow);
                                                        if(nColumnSizeOfRow > nColumns)  /*  long row */
                                                        {
                                                                nColumnSizeOfRow = nColumns;
                                                        }
							iColumn=0;
							for (ArrayIter iter = htRow.begin(); iter; ++iter) {
								Variant key(iter.first());
								CVarRef var(iter.secondRef());
                                                                if (!key.isInteger())
                                                                {
                                                                        break;
                                                                }
								keyIndex=key.toInt64();
                                                                if(var == null_variant)
                                                                {
                                                                        amf_write_byte(buf, AMF0_UNDEFINED);
                                                                }
                                                                else
                                                                {
									Variant *p = htRow.toArray().lvalPtr(keyIndex,false, false);
									if (p && p->getRawType() == KindOfVariant) {
                                                                           amf0_serialize_var(buf, *p, var_hash );
									} else {
                                                                           amf0_serialize_var(buf, var, var_hash );
									}
                                                                }
                                                                iColumn++;
                                                        }

                                                         /*  short row */
                                                        for(; iColumn < nColumns; iColumn++)
                                                                amf_write_byte(buf, AMF0_UNDEFINED);
                                                        iRow++;
                                                }
                                        }
                                        amf0_write_endofobject(buf );  /*  serverInf */
                                }
                                amf0_write_endofobject(buf );  /*  returned RecordSe */
                                return;
                        }
                        else
                        {
                                amf_error_docref(NULL , E_WARNING, "amf cannot understand special recordset array: should have __AMF_recordset__, rows and columns keys");
                        }
                }

                 /*  first check if it is a mixed (8) or a numeric objec */
		for (ArrayIter iter = myht.begin(); iter; ++iter) {
			Variant key(iter.first());
			//CVarRef var(iter.secondRef());
                        switch (key.getType()) {
                        	case KindOfInt32:
                        	case KindOfInt64:
					keyIndex = key.toInt64();
                                        if(keyIndex > max_index)
                                        {
                                                max_index =  keyIndex;
                                        }
                                        if(keyIndex < 0)
                                        {
                                                has_negative = 1;
                                                str_count++;
                                        }
                                        else
                                        {
                                                num_count++;
                                        }
                                        break;
                                case KindOfString:
                                case KindOfStaticString:
                                        str_count++;
                                        break;
				default:
					break;
                        }
                }

                 /* / key with name or negative indices means mixed arra */
                if(num_count > 0 && (str_count > 0 || max_index != (int)num_count-1))
                {
                        amf_write_byte(buf,AMF0_MIXEDARRAY);
                        amf0_write_int(buf,max_index );
                        amf0_serialize_objectdata(buf,myht,1, var_hash );
                }
                 /* / numeric keys onl */
                else if(num_count > 0)
                {
                        int iIndex;
                        amf_write_byte(buf,AMF0_ARRAY);
                        amf0_write_int(buf,num_count );

                         /*  lookup the key if existent (use 0x6 undefined */
			Variant iIndexVar;
                        for(iIndex = 0; iIndex < (int)num_count; iIndex++)
                        {
                                Variant zzValue;// = amf_get_holder(var_hash);
				iIndexVar = iIndex;
                                if(variant_hash_find(myht, iIndexVar ,zzValue) == FAILURE)
                                {
                                        amf_write_byte(buf, AMF0_UNDEFINED);
                                }
                                else
                                {
					Variant *p = myht.toArray().lvalPtr(iIndex,false, false);
					if (p && p->getRawType() == KindOfVariant) {
						amf0_serialize_var(buf, *p, var_hash );
					} else {
						amf0_serialize_var(buf, zzValue, var_hash );
					}
                                }
                        }
                }
                 /* / string keys onl */
                else
                {
                        amf_write_byte(buf,AMF0_OBJECT);
                        amf0_serialize_objectdata(buf,myht,1,var_hash );
                }
                return;

        }
        else
        {
                static char emptyArray[] = {10,0,0,0,0};
                amf_write_string(buf,emptyArray,5 );
        }
}

static void amf0_serialize_var(amf_serialize_output buf, const Variant & struc, amf_serialize_data_t *var_hash , void *suggestIndex)
{
        ulong objectIndex;

        switch (struc.getType()) {
                case KindOfBoolean:
                        amf_write_byte(buf, AMF0_BOOLEAN);
                        amf_write_byte(buf, struc.toBoolean() ? 1 : 0);
                        return;
                case KindOfNull: amf_write_byte(buf, AMF0_NULL); return;
                case KindOfInt32:
                case KindOfInt64:
                        amf_write_byte(buf, AMF0_NUMBER);
                        amf0_write_number(buf,struc.toInt64(),var_hash );
                        return;
                case KindOfDouble:
                        amf_write_byte(buf, AMF0_NUMBER);
                        amf0_write_number(buf,struc.toDouble(),var_hash );
                        return;
                case KindOfStaticString:
                case KindOfString:
                        amf0_serialize_zstring(buf, (Variant&)struc,AMF_STRING_AS_TEXT,var_hash );
                        return;
                //case KindOfResource:
                case KindOfObject:
                        amf0_serialize_object(buf,struc,var_hash );
                        return;
                case KindOfArray:
                        if(amf_cache_zval(&(var_hash->objects0), struc, &objectIndex,&(var_hash->nextObject0Index),0, suggestIndex) == FAILURE)
                        {
                                amf_write_byte(buf, AMF0_REFERENCE);
                                amf0_write_short(buf, objectIndex );
                        }
                        else
                        {
                                amf0_serialize_array(buf, struc, var_hash );
                        }
                        break;
                default:
                        amf_error_docref(NULL , E_WARNING, "amf cannot understand php type");
                        amf_write_byte(buf, AMF0_UNDEFINED);
                        break;
                }
}

/** Check if address within bounds */
static int amf_in_max_limit(const unsigned char * ptr, const unsigned char * max)
{
        long offset = (long)(max - ptr);
        if (!ptr || !max)
        {
                amf_error_docref(NULL , E_WARNING,
                "Null pointer for AMF String");
                return FAILURE;
        }

        if (offset  < 0)
        {
                amf_error_docref(NULL , E_WARNING,
                "Abnormal offset for AMF String %d",
                offset);
                return FAILURE;
        }

        if (offset > max_alloc_size)
        {
                amf_error_docref(NULL , E_WARNING,
                "Abnormally long AMF String %d",
                offset);
                return FAILURE;
        }

        return SUCCESS;
}

static int amf_bailout()
{
        amf_error_docref (NULL , E_WARNING,
        "Corrupt data encountered...bailing out");
	return 0; //to make compiler happy
}

static int amf_in_limit(const unsigned char * ptr, const unsigned char * max, long offset)
{
        if (amf_in_max_limit(ptr,max) == FAILURE) return FAILURE;

        if ((ptr + offset) > max)
        {
                amf_error_docref(NULL , E_WARNING,
                "Internally trying to increment pointer beyond max by %d",
                offset);
                return FAILURE;
        }
        return SUCCESS;
}

static void print_hex_string(Variant  param[])
{
PRINT("print_hex_string");

  if (!param)
  {
    return;
  }
  int argLen =  ((param[1])).isInteger() ?  (param[1]).toInt64() : 0;
  unsigned char *arg = (((param[0])).isString() ) ?
                   (unsigned char*)(param[0]).toString().data() : NULL;

  printData ((char *)arg, argLen);
}



/*  Decoding {{{1*/

static int amf3_unserialize_var(Variant& rval, const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash );
static int amf_var_unserialize(Variant& rval, const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash );

static int amf_perform_unserialize_callback(int ievent, const Variant& arg0,Variant& zResultValue, int shared, amf_serialize_data_t * var_hash )
{
        if(var_hash->callbackFx != null_variant)
        {
                int r;  /*  result from functio */
                Variant zEmpty1=null_variant;
		Variant zievent;
                Variant zResultValuePtr;
                Variant arg0orig = arg0;
                zievent = ievent;
                if(arg0 == null_variant)
                {
                        zEmpty1.setNull();
                }

                {
                        Variant params[2] = { arg0 == null_variant? zEmpty1 : arg0, zievent};
                        if((r = my_call_user_function_ex(var_hash->callbackTarget, var_hash->callbackFx, zResultValuePtr, 2, params, 0, NULL )) == SUCCESS)
                        {
                                 /* / if the result is different from the original value we cannot rely on that zval* if it is not empt */
                                if(arg0 != arg0orig)
                                {
					//TODO, do check?
                                        //zval_add_ref(&arg0orig);
                                }

                                if(zResultValuePtr != zResultValue && zResultValuePtr != null_variant)
                                {
                                        if(zResultValue == null_variant)
                                        {
                                                zResultValue = Variant();
                                        }
                                        else if(shared != 0)  /*  cannot replace the zval */
                                        {
                                                zResultValue = Variant();
                                        }
                                        zResultValue = zResultValuePtr;

                                }
                        }
                }
                return r;
        }
        else
        {
                return FAILURE;
        }
}

/**
 *  obtains an object from the cache
 *  \param rval is the pointer to reference
 *  \return SUCCESS or FAILURE
 *  No reference count is changed
*/
static int amf_get_from_cache(HashTable * ht, Variant & rval, int index)
{
        return util_hash_index_find(ht, index,rval);
}

/**  places an entity in the cache with no change in reference */
static int amf_put_in_cache(HashTable * var_hash, Variant & var)
{
	return util_hash_next_index_put(var_hash, var);
}

/*void dump_cache(HashTable *var_hash, char* prompt) {
	HashTable::const_iterator iter = var_hash->begin();
	std::cout<<"====Dump:"<<prompt<<"====\n";
	while(iter != var_hash->end()) {
		std::cout<<"Entry:"<<iter->first<<"\n";
		std::cout<<"Type:"<<iter->second->getType()<<"\n";
		iter->second->dump();
		std::cout<<"\n";
		iter++;
	}
}*/
/**  reads an integer in AMF0 format */
static int amf_read_int(const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash, int * num)
{
        if (!p || !max || !num)
        {
            amf_bailout();
            return FAILURE;
        }

        const unsigned char * cp = *p;
        if (amf_in_limit(cp, max, 4) == FAILURE) return FAILURE;

        *p += 4;
        *num =  ((cp[0] << 24) | (cp[1] << 16) | (cp[2] << 8) | cp[3]);
        return SUCCESS;
}

/**  reads a short integer in AMF0 format */
static int amf_read_int16(const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash, int * num)
{
        if (!p || !max || !num)
        {
            amf_bailout();
            return FAILURE;
        }

        const unsigned char * cp = *p;
        if (amf_in_limit(cp, max, 2) == FAILURE) return FAILURE;

        *p += 2;
        *num = ((cp[0] << 8) | cp[1]);
        return SUCCESS;
}

/**  reads a double in AMF0 format, eventually flipping it for bigendian */
static double amf_read_double(const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash, double * num)
{
        if (!p || !max || !num)
        {
            amf_bailout();
            return FAILURE;
        }

         /*  this structure is used to have proper double alignmen */
        union aligned {
                double dval;
                char cval[8];
        } d;
        const unsigned char * cp = *p;
        if (amf_in_limit(cp, max, 8) == FAILURE) return FAILURE;

        *p += 8;
        if((var_hash->flags & AMF_BIGENDIAN) != 0)
        {
                d.cval[0] = cp[7]; d.cval[1] = cp[6]; d.cval[2] = cp[5]; d.cval[3] = cp[4];
                d.cval[4] = cp[3]; d.cval[5] = cp[2]; d.cval[6] = cp[1]; d.cval[7] = cp[0];
        }
        else
        {
                memcpy(d.cval,cp, 8);
        }
        *num = d.dval;
    return SUCCESS;
}

/**  reads an integer in AMF3 format */
static int amf3_read_integer(const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash, int * num)
{
        if (!p || !max || !num)
        {
            amf_bailout();
            return FAILURE;
        }

        const unsigned char * cp = *p;

        if (amf_in_limit(cp, max, 1) == FAILURE) return FAILURE;

        int acc = *cp++;
        int mask,r,tmp;
        if(acc < 128)
        {
                *p = cp;
                *num = acc;
                return SUCCESS;
        }
        else
        {
                acc = (acc & 0x7f) << 7;
                if (amf_in_limit(cp, max, 1) == FAILURE) return FAILURE;

                tmp = *cp++;
                if(tmp < 128)
                {
                        acc = acc | tmp;
                }
                else
                {
                        acc = (acc | tmp & 0x7f) << 7;
                        if (amf_in_limit(cp, max, 1) == FAILURE) return FAILURE;

                        tmp = *cp++;
                        if(tmp < 128)
                        {
                                acc = acc | tmp;
                        }
                        else
                        {
                                acc = (acc | tmp & 0x7f) << 8;
                                if (amf_in_limit(cp, max, 1) == FAILURE) return FAILURE;

                                tmp = *cp++;
                                acc = acc | tmp;
                        }
                }
                *p = cp;

        }
         /* To sign extend a value from some number of bits to a greater number of bits just copy the sign bit into all the additional bits in the new format */
         /* convert/sign extend the 29bit two's complement number to 32 bi */
        mask = 1 << 28;  /*  mas */
        r = -(acc & mask) | acc;
        *num = r;
        return SUCCESS;
}

/**
 *  reads a string in AMF format, with the specified size
 *  \param rrval is modified into string with correct size
*/
static int amf0_read_string(Variant& rval, const unsigned char **p, const unsigned char *max,int length, enum AMFStringData raw, amf_unserialize_data_t *var_hash )
{
        if (!p || !max)
        {
                amf_bailout();
                return FAILURE;
        }

        int slength = 0;

        if (length == 2)
        {
            if (amf_read_int16(p,max, var_hash, &slength) == FAILURE) return FAILURE;
        }
        else
        {
            if (amf_read_int(p,max,var_hash, &slength) == FAILURE) return FAILURE;
        }

        unsigned char * src = (unsigned char*)*p;

        if (amf_in_limit(src, max, slength) == FAILURE) return FAILURE;

        *p += slength;

        if(slength > 0 && raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0)
        {
                Variant  rv;
                if((rv = amf_translate_charset_string((char*)src,slength, AMF_FROM_UTF8,var_hash )) != null_variant)
                {
                        rval = rv;
                        return SUCCESS;
                }
        }
	String str = String((char*)src,slength,CopyString);
	rval = str;
        return SUCCESS;
}

/**
 *  Reads a string in AMF3 format with caching
 *  \param storeReference tells to place the string in the cache or not
 *  \param rval is the new pointer
 *  \return PHP success code
 *
 *  Note: the reference count is not changed
*/
static int amf3_read_string(Variant& rval, const unsigned char **p, const unsigned char *max,int storeReference, enum AMFStringData raw, amf_unserialize_data_t *var_hash )
{
        if (!p || !max)
        {
            amf_bailout();
            return FAILURE;
        }

        int len = 0;
    if (amf3_read_integer(p,max,var_hash, &len) == FAILURE) return FAILURE;

        if(len == 1)
        {
                rval = var_hash->zEmpty_string;
        }
        else if((len & AMF_INLINE_ENTITY) != 0)
        {
                const unsigned char * src = *p;
                Variant newval = null_variant;
                len >>= 1;
                if (amf_in_limit(*p, max, len) == FAILURE) return FAILURE;

                *p += len;

                if(!(raw == AMF_STRING_AS_TEXT && (var_hash->flags & AMF_TRANSLATE_CHARSET) != 0 && (newval = amf_translate_charset_string((char*)src, len, AMF_FROM_UTF8, var_hash )) != null_variant))
                {
			String str= String((char*)src, len , CopyString);
                        newval = str;
                }
                rval = newval;
                if(storeReference == 1)
                {
                        util_hash_next_index_put(&(var_hash->strings),rval);  /*  pass referenc */
                }
                else
                {
			//TODO check
                        //newval->refcount--;
                }
        }
        else
        {
                return amf_get_from_cache(&(var_hash->strings),rval, (len>>1));
        }
        return SUCCESS;
}

/**
 *  reads object data with
 *  \param className the name of the class
 *  \param asArray means to store the result in an associative array (className not meaningful)
 *  \param maxIndex is the maximum index of the numerical part of the array, useful for optimization
 *
 *  Eventually if flags has AMF_ASSOC then an object is treated as an array
*/
static int amf_read_objectdata(Variant& rval, const unsigned char **p, const unsigned char *max, Variant& zClassname,int asArray, int maxIndex, amf_unserialize_data_t *var_hash )
{
        if (!p || !max)
        {
            amf_bailout();
            return FAILURE;
        }

         /*  Cases */
         /*  asArray means that we are building an associative array with up to maxInde */
         /*  flag associativ */
         /*  classname can be used as wel */
        Variant htOutput = null_variant;
        int callbackDone = 0;

         /*  not an array and classname is not empt */
        if(asArray == 0 && zClassname != null_variant && strlen(zClassname.toObject().objectForCall()->o_getClassName()) != 0)
        {
                if(amf_perform_unserialize_callback(AMFE_MAP, zClassname,rval,0,var_hash ) == SUCCESS)
                {
                        if((rval).isArray())
                        {
                                asArray = 1;
                                callbackDone = 1;
                                htOutput = rval;
                        }
                        else if((rval).isObject() )
                        {
                                callbackDone = 1;
                                htOutput = rval;
                        }
                }
        }

        if(callbackDone == 0)
        {
                if(asArray == 1 || (var_hash->flags & AMF_ASSOC) !=0)
                {
                        amf_array_init(rval, maxIndex );
                        asArray = 1;
                        htOutput = rval;
                }
                else if(zClassname != null_variant)
                {
                         /*  build the corresponding clas */
			Object obj;
    			try {
      				obj = create_object(zClassname.toString().data(), Array::Create(), false);
				rval = obj;
    			} catch (ClassNotFoundException &e) {
                                amf_error_docref(NULL , E_WARNING, "amf cannot find class %s\n",zClassname.toString().data());
				rval = Object(SystemLib::AllocStdClassObject());
    			}


                        htOutput = rval;
                }
                else
                {
			rval = Object(SystemLib::AllocStdClassObject());
                        htOutput = rval;
                }
        }

         /* zval_add_ref(rval) */
        amf_put_in_cache(&(var_hash->objects0),rval);
        while(1)
        {
                Variant &zName = amf_get_holder(var_hash);
                Variant &zValue = amf_get_holder(var_hash);
                //zValue = Object(SystemLib::AllocStdClassObject());
                if(amf0_read_string(zName,p,max,2,AMF_STRING_AS_TEXT,var_hash ) == FAILURE)
                {
                        amf_error_docref(NULL , E_WARNING, "amf cannot read string in array/object");
                        return FAILURE;
                }
                if(**p == AMF0_ENDOBJECT)
                {
                        if (amf_in_limit(*p,max,1) == FAILURE) return FAILURE;

                        *p = *p + 1;
                        break;
                }
                if(amf_var_unserialize(zValue,p, max, var_hash ) == FAILURE)
                {
                        amf_error_docref(NULL , E_WARNING, "amf cannot unserialize key");
                        return FAILURE;
                }
                if(asArray == 1)
                {
                         /*  try to convert the string into a numbe */
                        char * pEndOfString;
                        char tmp[32];
                        unsigned int keyLength = zName.toString().length();
                        int iIndex;
                        if(keyLength < sizeof(tmp))
                        {
                                 /*  TODO: use sscan */
                                memcpy(tmp,zName.toString().data(),keyLength);
                                tmp[keyLength] = 0;
                                iIndex = strtoul(tmp, &pEndOfString, 10);
                        }
                        else
                        {
                                iIndex = 0;
                        }

                         /*  TODO test for key as 0 and key as " */
                        if(iIndex != 0 && (pEndOfString == NULL || *pEndOfString == 0))
                        {
                                hash_index_update(rval, iIndex, zValue);  /*  pas */
                        }
                        else
                        {
                                add_assoc_zval(rval,zName,zValue);  /*  pas */
                        }
                }
                else if(zName.toString().length() > 0)
                {
                        add_property_zval(rval,zName,zValue);   /*  pas */
                }
                else
                {
                        amf_error_docref(NULL , E_WARNING, "amf cannot set empty \"\" property for an object. Use AMF_ASSOCIATIVE_DECODE flag");
                }
        }

        if(rval.isArray())
        {
                if(zClassname != null_variant)
                {
                        add_assoc_zval(rval, (char*)"_explicitType",zClassname);
                }
        }
        else if((var_hash->flags & AMF_POST_DECODE) != 0)
        {
                amf_perform_unserialize_callback(AMFE_POST_OBJECT, rval, rval,0,var_hash );
        }
        return SUCCESS;
}
/**
 *  generic unserialization in AMF3 format
 *  \param rval a zval already allocated
*/
static int amf3_unserialize_var(Variant& rval, const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash )
{
        if (!p || !max)
        {
            amf_bailout();
            return FAILURE;
        }

        const int type = **p;
        int handle;

        if (amf_in_limit (*p, max, 1) == FAILURE) return FAILURE;

        *p = *p + 1;
        switch(type)
        {
        case AMF3_UNDEFINED:
        case AMF3_NULL:
                rval.setNull(); break;
        case AMF3_FALSE:
                rval = false; break;
        case AMF3_TRUE:
                rval = true; break;
        case AMF3_INTEGER:
        {
                int inum = 0;
                if (amf3_read_integer(p,max,var_hash, &inum) == FAILURE) return FAILURE;
                                rval = inum;
                break;
        }

        case AMF3_NUMBER:
        {
                double dnum = 0;
                if (amf_read_double(p, max, var_hash, &dnum) == FAILURE) return FAILURE;
                                rval = dnum;
                break;
        }
        case AMF3_STRING:
                if(amf3_read_string(rval, p, max, 1, AMF_STRING_AS_TEXT,var_hash ) == FAILURE)
                {
                        amf_error_docref(NULL , E_WARNING, "amf cannot lookup string");
                        return FAILURE;
                }
                break;
        case AMF3_XML:
        case AMF3_XMLSTRING:
        case AMF3_BYTEARRAY:
                {
                        int event = type == AMF3_BYTEARRAY ? AMFE_POST_BYTEARRAY : AMFE_POST_XML;
                        if(amf3_read_string(rval, p, max, 1, AMF_STRING_AS_BYTE, var_hash ) == FAILURE)
                        {
                                const char * name = type == AMF3_BYTEARRAY ? "bytearray" : "xml";
                                amf_error_docref(NULL , E_WARNING, "amf cannot read string for %s", name);
                                return FAILURE;
                        }
                        amf_perform_unserialize_callback(event, rval, rval,1,var_hash );
                }
                break;
        case AMF3_DATE:
        if (amf3_read_integer(p,max,var_hash, &handle) == FAILURE) return FAILURE;

                if((handle & AMF_INLINE_ENTITY) != 0)
                {
                        double d = 0;
                        if (amf_read_double(p,max,var_hash, &d) == FAILURE) return FAILURE;

                        rval=d;
                        amf_put_in_cache(&(var_hash->objects),rval);
                }
                else
                {
                        if(amf_get_from_cache(&(var_hash->objects),rval, (handle>>1)) == FAILURE)
                        {
                                amf_error_docref(NULL , E_WARNING, "amf cannot lookup date %d",handle>>1);
                                return FAILURE;
                        }
                        //zval_add_ref(rval);
                }
                break;
        case AMF3_ARRAY:
                if (amf3_read_integer(p,max,var_hash, &handle) == FAILURE) return FAILURE;

                if((handle & AMF_INLINE_ENTITY) != 0)
                {
                        int iIndex;
                        int maxIndex = handle >> 1;
                        amf_array_init(rval, maxIndex );

                        Variant htOutput = rval;
                         /* zval_add_ref(rval) */
                        amf_put_in_cache(&(var_hash->objects),rval);

                        while(1)
                        {
                                Variant &zKey=amf_get_holder(var_hash),  &zValue=amf_get_holder(var_hash);
                                char * pEndOfString;
                                char tmp[32];
                                unsigned int keyLength;
                                int iIndex;
                                if(amf3_read_string(zKey,p, max, 1, AMF_STRING_AS_TEXT, var_hash ) == FAILURE)
                                {
                                        break;
                                }
                                if(zKey.toString().length() == 0)
                                {
                                        break;
                                }
                                if(amf3_unserialize_var(zValue,p,max, var_hash ) == FAILURE)
                                {
                                        amf_error_docref(NULL , E_WARNING, "amf cannot unserialize key %s",(zKey.toString().data()));
                                        break;
                                }
                                keyLength = zKey.toString().length();
                                if(keyLength < sizeof(tmp))
                                {
                                         /*  TODO: use sscan */
                                        memcpy(tmp,zKey.toString().data(),keyLength);
                                        tmp[keyLength] = 0;
                                        iIndex = strtoul(tmp, &pEndOfString, 10);
                                }
                                else
                                {
                                        iIndex = 0;
                                }

                                 /*  TODO test for key as 0 and key as " */
                                if(iIndex != 0 && (pEndOfString == NULL || *pEndOfString == 0))
                                {
                                        hash_index_update(htOutput, iIndex, zValue);  /*  pas */
                                }
                                else
                                {
                                        add_assoc_zval(rval,zKey,zValue);  /*  pas */
                                }
                        }
                        for(iIndex = 0; iIndex < maxIndex; iIndex++)
                        {
                                if(**p == AMF3_UNDEFINED)
                                {
                                        if (amf_in_limit (*p, max, 1) == FAILURE) return FAILURE;
                                        *p = *p + 1;
                                }
                                else
                                {
                                        Variant &zValue=amf_get_holder(var_hash);
                                        if(amf3_unserialize_var(zValue,p,max,var_hash ) == FAILURE)
                                        {
                                                amf_error_docref(NULL , E_WARNING, "amf cannot unserialize array item %d", iIndex);
                                                return FAILURE;
                                       }
                                        add_index_zval(rval,iIndex,zValue);  /*  pas */
                                        // Do not call as it referenced zval_ptr_dtor(&zValue); //memleak
                                }
                        }
                }
                else
                {
                        if(amf_get_from_cache(&(var_hash->objects),rval, (handle>>1)) == FAILURE)
                        {
                                amf_error_docref(NULL , E_WARNING, "amf cannot lookup array %d",handle>>1);
                                return FAILURE;
                        }
                        //zval_add_ref(rval);
                }
                break;
        case AMF3_OBJECT:
                if (amf3_read_integer(p,max,var_hash, &handle) == FAILURE) return FAILURE;
                if((handle & AMF_INLINE_ENTITY) != 0)
                {
                        int bInlineclassdef;
                        int nClassMemberCount = 0;
                        int bTypedObject;
                        int iDynamicObject;
                        int iExternalizable;
                        Variant  &zClassDef=amf_get_holder(var_hash),&zClassname = amf_get_holder(var_hash);
                        int iMember;
                        int bIsArray = 0;
                        int iSuccess = FAILURE;

                        bInlineclassdef = (handle & AMF_INLINE_CLASS) != 0;

                        if(bInlineclassdef == 0)
                        {
                                Variant htClassDef;
                                Variant tmp;
				const Variant ONEINT=1;
                                int iClassDef = (handle >> AMF_CLASS_SHIFT);
                                if(amf_get_from_cache(&(var_hash->classes),zClassDef,iClassDef) == FAILURE)
                                {
                                        amf_error_docref(NULL , E_WARNING, "amf cannot find class by number %d", iClassDef);
                                        return FAILURE;
                                }
                                htClassDef = zClassDef;

                                 /* / extract information from classdef packed into the first elemen */
                                handle = amf_get_index_long(htClassDef,0,0);
                                nClassMemberCount = handle >> AMF_CLASS_MEMBERCOUNT_SHIFT;
                                bTypedObject = (handle & 1) != 0;  /*  specia */
                                iExternalizable = handle & AMF_CLASS_EXTERNAL;
                                iDynamicObject = handle & AMF_CLASS_DYNAMIC;

                                if (variant_hash_find(htClassDef, ONEINT,tmp) == SUCCESS)
                                {
                                        zClassname = tmp;
                                }
                                else
                                {
                                        zClassname = null_variant;
                                }
                        }
                        else
                        {
                                iExternalizable = handle & AMF_CLASS_EXTERNAL;
                                iDynamicObject = handle & AMF_CLASS_DYNAMIC;
                                nClassMemberCount = handle >> AMF_CLASS_MEMBERCOUNT_SHIFT;
                                if (amf3_read_string(zClassname,p,max,1,AMF_STRING_AS_TEXT,var_hash ) == FAILURE) return FAILURE;

                                bTypedObject = zClassname.toString().length() > 0;
                                 /*  a classdef is an array with named keys for special informatio */
                                 /*  and then a indexed values for the member */
                                zClassDef = Variant();
                                amf_array_init(zClassDef,nClassMemberCount+2 );
                                add_next_index_long(zClassDef,(bTypedObject?1:0)|nClassMemberCount << AMF_CLASS_MEMBERCOUNT_SHIFT |iDynamicObject|iExternalizable);
                                add_next_index_zval(zClassDef, zClassname);

                                 /*  loop over classMemberCoun */
                                for(iMember = 0; iMember < nClassMemberCount; iMember++)
                                {
                                        Variant &zMemberName = amf_get_holder(var_hash);
                                        if(amf3_read_string(zMemberName,p,max,1,AMF_STRING_AS_TEXT,var_hash ) == FAILURE)
                                        {
                                                break;
                                        }
                                        add_next_index_zval(zClassDef,zMemberName);  /*  pass referenc */
                                }

                                amf_put_in_cache(&(var_hash->classes),zClassDef);  /*  pass referenc */
                        }

                         /*  callback for externalizable or classnames not nul */
                        if(iExternalizable != 0 || (zClassname != null_variant && zClassname.toString().length() != 0))
                        {
                                if((iSuccess = amf_perform_unserialize_callback(iExternalizable != 0 ? AMFE_MAP_EXTERNALIZABLE:AMFE_MAP, zClassname,rval,0,var_hash )) == SUCCESS)
                                {
                                        if(rval.isArray())
                                        {
                                                bIsArray = 1;
                                        }
                                        else if(rval.isObject() )
                                        {
                                                bIsArray = 0;
                                        }
                                        else
                                        {
                                                 /*  TODO: erro */
                                                iSuccess = FAILURE;  /*  nor an object or an arra */
                                        }
                                }
                        }
                         /*  invoke the callback passing: classname, externalizabl */
                         /*  return: treat as any or as object, place in object or in arra */

                        if(iExternalizable != 0)
                        {
                                if(iSuccess == FAILURE || !rval.isInitialized() ||rval.isNull())
                                {
                                        amf_put_in_cache(&(var_hash->objects),(Variant&)null_variant);
                                        amf3_unserialize_var(rval,p,max,var_hash );
                                }
                                else
                                {
                                         /* zval_add_ref(rval) */
                                        amf_put_in_cache(&(var_hash->objects),rval);
                                }
                        }
                        else
                        {
                                 /*  default behaviou */
                                if(iSuccess == FAILURE || !rval.isInitialized() || rval.isNull())
                                {
                                        if((var_hash->flags & AMF_ASSOC) != 0)
                                        {
                                                amf_array_init(rval,nClassMemberCount );
                                                bIsArray = 1;
                                        }
                                        else
                                        {
                                                if(bTypedObject != 0)
                                                {
                        				Object obj;
                        				try {
                                				obj = create_object(zClassname.toString().data(), Array::Create(), false);
                                				rval = obj;
                        				} catch (ClassNotFoundException &e) {
                                				amf_error_docref(NULL , E_WARNING, "%s:amf cannot find class %s\n",__FUNCTION__,zClassname.toString().data());
                                				rval = Object(SystemLib::AllocStdClassObject());
                        				}

                                                }
                                                else
                                                {
                                			rval = Object(SystemLib::AllocStdClassObject());
                                                }
                                        }
                                }

                                 /* zval_add_ref(rval) */
                                amf_put_in_cache(&(var_hash->objects),rval);
                                for(iMember = 0; iMember < nClassMemberCount;iMember++)
                                {
                                        Variant &pzName=amf_get_holder(var_hash), &zValue=amf_get_holder(var_hash);
                                        pzName =  null_variant;
                                        zValue = null_variant;
                                        if(hash_index_find(zClassDef,iMember+2,pzName) == FAILURE)
                                        {
                                                amf_error_docref(NULL , E_WARNING, "amf cannot find index for class member %d over %d",iMember,nClassMemberCount);
                                                return FAILURE;
                                        }
                                        if(amf3_unserialize_var(zValue,p,max, var_hash ) == FAILURE)
                                        {
                                                amf_error_docref(NULL , E_WARNING, "amf cannot read value for class member");
                                                return FAILURE;
                                        }
                                        if(bIsArray == 1)
                                        {
                                                add_assoc_zval(rval, pzName, zValue);
                                        }
                                        else
                                        {
                                                add_property_zval(rval, pzName, zValue);  /*  pass zValu */
                                        }
                                }


                                if(iDynamicObject != 0)
                                {
                                        while(1)
                                        {
                                                Variant &zKey = amf_get_holder(var_hash);
                                                Variant &zValue = amf_get_holder(var_hash);
                                                if(amf3_read_string(zKey,p,max,1,AMF_STRING_AS_TEXT,var_hash ) == FAILURE)
                                                {
                                                        amf_error_docref(NULL , E_WARNING, "amf cannot understand key name %X","");
                                                        break;
                                                }
                                                if (!zKey.isString() || zKey.toString().length() == 0)
                                                {
                                                        break;
                                                }
                                                if(amf3_unserialize_var(zValue,p,max, var_hash ) == FAILURE)
                                                {
                                                        amf_error_docref(NULL , E_WARNING, "amf cannot unserialize member %s",zKey.toString().data());
                                                        return FAILURE;
                                                }
                                                if(bIsArray == 1)
                                                {
                                                        if (zKey.isString() )
                                                        {
                                                                add_assoc_zval(rval, zKey, zValue); /*  pass zValu */
                                                        }
                                                }
                                                else
                                                {
                                                        if (zKey.isString())
                                                        {
                                                                add_property_zval(rval, zKey, zValue);  /*  pass zValu */
                                                        }
                                                }
                                        }
                                }

                                if(bIsArray == 1)
                                {
                                        if(bTypedObject != 0)
                                        {
                                                add_assoc_zval(rval, (char*)"_explicitType",zClassname);
                                        }
                                }
                                else if((var_hash->flags & AMF_POST_DECODE) != 0)
                                {
                                        amf_perform_unserialize_callback(AMFE_POST_OBJECT, rval, rval,0,var_hash );
                                }
                        }
                }
                else
                {
                        if(amf_get_from_cache(&(var_hash->objects),rval, (handle>>1)) == FAILURE)
                        {
                                amf_error_docref(NULL , E_WARNING, "amf cannot lookup object %d",handle >> 1);
                                return FAILURE;
                        }
                        //zval_add_ref(rval);
                }
                break;
        default:
                amf_error_docref(NULL , E_WARNING, "amf unknown AMF3 type %d", type);
                return FAILURE;
        }
        return SUCCESS;
}

/**  generic unserialization in AMF0 format */
static int amf_var_unserialize(Variant& rval, const unsigned char **p, const unsigned char *max, amf_unserialize_data_t *var_hash )
{
	//dump_cache(&(var_hash->objects0),"objects0");
	//dump_cache(&(var_hash->objects),"objects");
PRINT("amf_var_unserialize");
        if (!p || !max)
        {
            amf_bailout();
            return FAILURE;
        }

PRINT("amf_var_unserialize 1");
        const unsigned char *cursor = *p;
        if (amf_in_limit (*p, max, 1) == FAILURE) return FAILURE;
        int type = *cursor++;
        *p = cursor;
        switch(type)
        {
        case AMF0_NUMBER:
        {
PRINT("amf_var_unserialize double");
                double d = 0;
                if (amf_read_double(p, max, var_hash, &d) == FAILURE) return FAILURE;
                rval = d;
                break;
        }
        case AMF0_ENDOBJECT:
                return FAILURE;
        case AMF0_BOOLEAN:
		{
PRINT("amf_var_unserialize boolean");
                int bval = *cursor++;
		if (bval) {
			rval = true;
		} else {
			rval = false;
		}
                *p = cursor;
		}
                break;
        case AMF0_DATE:
                 /*  date: double in */
                {
PRINT("amf_var_unserialize date");
                        double tm = 0;
                        if (amf_read_double(p,max,var_hash, &tm) == FAILURE) return FAILURE;
                        int tz = 0;
                        if (amf_read_int(p,max,var_hash, &tz) == FAILURE) return FAILURE;
                        rval=tm;
                }
                break;
        case AMF0_STRING:
PRINT("amf_var_unserialize string");
                return amf0_read_string(rval, p, max, 2,AMF_STRING_AS_TEXT,var_hash  );
        case AMF0_NULL:
        case AMF0_UNDEFINED:
PRINT("amf_var_unserialize undefined");
                rval.setNull();
                break;
        case AMF0_REFERENCE:
                {
PRINT("amf_var_unserialize undefined");
                        int objectIndex = 0;
                        if (amf_read_int16(p,max,var_hash, &objectIndex) == FAILURE) return FAILURE;

                        if(amf_get_from_cache(&(var_hash->objects0),rval, objectIndex) == FAILURE)
                        {
                                amf_error_docref(NULL , E_WARNING, "cannot find object reference %d",objectIndex);
                                return FAILURE;
                        }
                        //zval_add_ref(rval);
                        break;
                }
        case AMF0_OBJECT:
PRINT("amf_var_unserialize amf0 object");
                 /*  AMF0 read object: key=value up to AMF0_ENDOBJECT that is used for terminatio */
                return amf_read_objectdata(rval, p, max,(Variant&)null_variant,0,0, var_hash );
        case AMF0_MIXEDARRAY:
                 /*  AMF0 Mixed: I(maxindex) then name=value up to AMF0_ENDOBJEC */
                {
PRINT("amf_var_unserialize amf0 mixed array");
                        int maxIndex = 0;
                        if (amf_read_int(p,max,var_hash, &maxIndex) == FAILURE) return FAILURE;
                        return amf_read_objectdata(rval, p, max, (Variant&)null_variant,1, maxIndex, var_hash );
                }
                break;
        case AMF0_ARRAY:
                {
PRINT("amf_var_unserialize amf0 array");
                        int iIndex;
                        int length = 0;
                        if (amf_read_int(p,max,var_hash, &length) == FAILURE) return FAILURE;
                        amf_array_init(rval,length );

                        //Variant ht = rval;
                         /* zval_add_ref(rval) */
                        amf_put_in_cache(&(var_hash->objects0),rval);

                        for(iIndex = 0; iIndex < length; iIndex++)
                        {
                                if(**p == AMF0_UNDEFINED)
                                {
                                        if (amf_in_limit (*p, max, 1) == FAILURE) return FAILURE;
                                        *p = *p + 1;
                                }
                                else
                                {
                                        Variant& zValue=amf_get_holder(var_hash);
                                        if(amf_var_unserialize(zValue,p,max, var_hash ) == FAILURE)
                                        {
                                                amf_error_docref(NULL , E_WARNING, "amf bad unserialized value for array index %d",iIndex);
                                                return FAILURE;
                                        }
                                        add_index_zval(rval,iIndex,zValue);
                                }
                        }
                }
                break;
        case AMF0_TYPEDOBJECT:
                 /*  object with classnam */
                {
PRINT("amf_var_unserialize amf0 typeobject");
                        Variant  zClassname;
                        if(amf0_read_string(zClassname,p, max,2,AMF_STRING_AS_TEXT,var_hash  ) == FAILURE)
                        {
                                return FAILURE;
                        }
                        if(amf_read_objectdata(rval, p, max,zClassname, 0, 0,var_hash ) == FAILURE)
                        {
                                return FAILURE;
                        }
                }
                break;
        case AMF0_LONGSTRING:
PRINT("amf_var_unserialize amf0 longstring");
                return amf0_read_string(rval, p, max, 4,AMF_STRING_AS_TEXT,var_hash );
        case AMF0_XML:
PRINT("amf_var_unserialize amf0 xml");
                if(amf0_read_string(rval, p, max, 4,AMF_STRING_AS_BYTE,var_hash ) == FAILURE)
                {
                        return FAILURE;
                }
                amf_perform_unserialize_callback(AMFE_POST_XML, rval, rval,0,var_hash );
                break;
        case AMF0_AMF3:
PRINT("amf_var_unserialize amf0 amf3");
                var_hash->flags |= AMF_AMF3;
                return amf3_unserialize_var(rval, p, max,var_hash );
        case AMF0_MOVIECLIP:
        case AMF0_UNSUPPORTED:
        case AMF0_RECORDSET:
PRINT("amf_var_unserialize unsupported");
                amf_error_docref(NULL , E_WARNING, "amf unsupported AMF type %d", type);
                return FAILURE;
        default:
                amf_error_docref(NULL , E_WARNING, "amf unknown AMF type %d", type);
                return FAILURE;
PRINT("amf_var_unserialize 1");
        }

PRINT("amf_var_unserialize 2");

        return SUCCESS;
}

/*  Charset {{{1*/

static int amf_string_is_ascii(const char * cp, int length)
{
        while(length-- > 0)
                if(*cp++ >= 0x7F)  /*  isasci */
                {
                        return 0;
                }
        return 1;
}

/**  invoke the callback as (AMFE_TRANSLATE_CHARSET, inputstring) => resulting string */
static Variant amf_translate_charset_zstring(const Variant&  inz, enum AMFStringTranslate direction, amf_serialize_data_t*var_hash  )
{
        Variant  r = null_variant;
        int rr;

         /*  maybe direction == AMF_FROM_UTF */
        if((var_hash->flags & AMF_TRANSLATE_CHARSET_FAST) == AMF_TRANSLATE_CHARSET_FAST && amf_string_is_ascii(inz.toString().data(),inz.toString().length()) == 1)
        {
                return null_variant;
        }
        rr = direction == AMF_TO_UTF8 ? amf_perform_serialize_callback_event(AMFE_TRANSLATE_CHARSET, inz, r, 0, var_hash ): amf_perform_unserialize_callback(AMFE_TRANSLATE_CHARSET, inz, r, 0, var_hash );

        if(rr == SUCCESS && r != null_variant)
        {
                if(r.isString())
                {
                        return r;
                }
                else
                {
                        return null_variant;
                }
        }
        else
        {
                return null_variant;
        }
}


/**
 *  The translation is performed from a source C string. In this case we create a ZSTRING and try to translate
 *   it. In case of failure we return the generate ZSTRNG
 *  If we add direct charset handling we can perform the operation directly here without allocating the ZSTRING
*/
static Variant amf_translate_charset_string(const char * cp, int length, enum AMFStringTranslate direction, amf_serialize_data_t*var_hash  )
{
        Variant tmp,r = null_variant;
        int rr;

         /*  maybe direction == AMF_FROM_UTF */
        if((var_hash->flags & AMF_TRANSLATE_CHARSET_FAST) == AMF_TRANSLATE_CHARSET_FAST && amf_string_is_ascii(cp,length) == 1)
        {
                return null_variant;
        }

	String str = String(cp,length,CopyString);
        tmp = str;

        rr = direction == AMF_TO_UTF8 ? amf_perform_serialize_callback_event(AMFE_TRANSLATE_CHARSET, tmp, r, 0, var_hash ): amf_perform_unserialize_callback(AMFE_TRANSLATE_CHARSET, tmp, r, 0, var_hash );
        if(rr == SUCCESS && r != null_variant)
        {
                if((r).isString() )
                {
                        return r;
                }
        }
        return tmp;
}


        


String f_amf_encode(CVarRef var, CVarRef flag /* = null */, CVarRef callback /* = null */, CVarRef output /* = null */) {
PRINT("amf_encode");
        //zval **struc,**strucFlags,**zzCallback = NULL, **zzOutputSB = NULL;
        int flags = 0;
        amf_serialize_data_t var_hash;

	string outputbuf="";
	amf_serialize_output pbuf = &outputbuf;

        if(flag.is(KindOfInt32)||flag.is(KindOfInt64)) {
		flags = flag.toInt64();
	}
	var_hash.flags = flags;
	if(callback.isInitialized() && !callback.isNull()) {
	  amf_SERIALIZE_CTOR(var_hash,(Variant&)callback);
	}
        if((flags & AMF_AMF3) != 0)
        {
                amf_write_byte(pbuf,AMF0_AMF3);
                amf3_serialize_var(pbuf, var, &var_hash );
        }
        else
        {
                amf0_serialize_var(pbuf, var, &var_hash );
        }

	amf_SERIALIZE_DTOR(var_hash,callback);
	return String(outputbuf);
        
}

Variant f_amf_decode(CStrRef var, CVarRef flag /* = null */, CVarRef offsetParam /* = null */, CVarRef callback /* = null */) {
  	int offset = 0;
  	int flags = 0;
  	amf_unserialize_data_t var_hash;

        if(flag.is(KindOfInt32)||flag.is(KindOfInt64)) {
                flags = flag.toInt64();
        }
        if(offsetParam.is(KindOfInt32)||offsetParam.is(KindOfInt64)) {
                offset= offsetParam.toInt64();
        }
        var_hash.flags = flags;

        //if ( var.isString())
        {
                if(var.length()<=offset)
                {
                        return false;
                }

                unsigned char *p = (unsigned char*)var.data()+offset;

                Variant  tmp;


                AMF_UNSERIALIZE_CTOR(var_hash,(Variant&)callback)
                int status = amf_var_unserialize(tmp, (const unsigned char**)&p, p + var.length(),  &var_hash );

                if (status == FAILURE)
                {
                        amf_error_docref(NULL , E_WARNING, "Error at offset %ld of %d bytes", p, var.length());
                        amf_SERIALIZE_DTOR(var_hash,NULL)
                        return tmp;
                }


                amf_SERIALIZE_DTOR(var_hash,callback);// memleak
		return tmp;
        }
	/*
        else
        {
                amf_error_docref(NULL , E_WARNING, "amf_decode requires a string argument");
                return false;
        }
	*/
}


///////////////////////////////////////////////////////////////////////////////
}
