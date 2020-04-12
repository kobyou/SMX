#pragma once
#include "def.h"
// 一般操作数的长度(长字个数)
#define DIG_LEN 8

typedef uint *big;

// ECC数据结构体
typedef struct {
	uint  x[DIG_LEN];
	uint  y[DIG_LEN];
} affpoint;

typedef affpoint *epoint;

// 点结构体
typedef struct {
	uint  x[DIG_LEN];
	uint  y[DIG_LEN];
	uint  z[DIG_LEN];
} projpoint;

typedef projpoint *point;

/***************************************************
* function			   : KDF
* description		   : KDF函数
* parameters:
-- data[in]		   : 数据
-- data_len[in]	   : 数据长度
-- key_len[in]	   : 密钥长度
-- key[out]		   : 密钥
* return 			   : 0--success;
非0--error code
***************************************************/
void KDF(byte *data, uint data_len, uint key_len, byte *key);

/***************************************************
* function          	: EccMakeKey
* description	        : ECC公/私钥生成接口函数
* parameters:
-- sk[in]	        : 私钥
-- sk_len[in]       : 私钥长度
-- type[in]         : 曲线类型
-- pk[out]			: 公钥
-- pk_len[out]		: 公钥长度
* return 		        : 0--success;
非0--error code
***************************************************/
int EccMakeKey(byte *sk, uint sk_len,
               byte *pk, uint pk_len, int type);

/***************************************************
* function          	: EccSign
* description	        : ECC签名生成接口函数
* parameters:
-- hash[in]	        : 数据哈希值
-- hash_len[in]     : 数据哈希值长度
-- random[in]		: 随机数
-- random_len[in]	: 随机数长度
-- sk[in]	        : 私钥
-- sk_len[in]       : 私钥长度
-- sign[out]	    : 签名值
-- sign_len[out]    : 签名值长度
* return 		        : 0--success;
非0--error code
***************************************************/
int EccSign(const byte *hash, uint hash_len,
            byte *random, uint random_len,
            byte *sk, uint sk_len,
            byte *sign, uint sign_len);

/***************************************************
* function				: EccVerify
* description			: ECC签名验证接口函数
* parameters:
-- hash[in] 		: 数据哈希值
-- hash_len[in] 	: 数据哈希值长度
-- pk[in]			: 公钥
-- pk_len[in]		: 公钥长度
-- sign[in]		    : 签名值
-- sign_len[in]	    : 签名值长度
* return				: 0--success;
非0--error code
***************************************************/
int EccVerify(const byte *hash, uint hash_len,
              byte *pk, uint pk_len,
              byte *sign, uint sign_len);

/***************************************************
* function				    : EccEncrypt
* description			    : ECC加密接口函数
* parameters:
-- plain[in] 	        : 明文数据
-- plain_len[in] 	    : 明文数据长度
-- random[in]		    : 随机数
-- random_len[in]	    : 随机数长度
-- pk[in]			    : 公钥
-- pk_len[in]		    : 公钥长度
-- cipher[out]		    : 密文数据
-- cipher_len[out]	    : 密文数据长度 (cipher_len = plain_len+96)
* return				: 0--success;
非0--error code
***************************************************/
int EccEncrypt(byte *plain, uint plain_len,
               byte *random, uint random_len,
               byte *pk, uint pk_len,
               byte *cipher, uint cipher_len);

/***************************************************
* function				: sdt_ecc_decrypt
* description			: ECC解密接口函数
* parameters:
-- cipher[in] 	    : 密文数据
-- cipher_len[in] 	: 密文数据长度
-- sk[in]			: 私钥
-- sk_len[in]		: 私钥长度
-- plain[out]		: 明文数据
-- plain_len[out]	: 明文数据长度 (plain_len = cipher_len-96)
* return				: 0--success;
非0--error code
***************************************************/
int EccDecrypt(byte *cipher, uint cipher_len,
               byte *sk, uint sk_len,
               byte *plain, uint plain_len);
