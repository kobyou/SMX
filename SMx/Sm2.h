#pragma once
#include "def.h"
// һ��������ĳ���(���ָ���)
#define DIG_LEN 8

typedef uint *big;

// ECC���ݽṹ��
typedef struct {
	uint  x[DIG_LEN];
	uint  y[DIG_LEN];
} affpoint;

typedef affpoint *epoint;

// ��ṹ��
typedef struct {
	uint  x[DIG_LEN];
	uint  y[DIG_LEN];
	uint  z[DIG_LEN];
} projpoint;

typedef projpoint *point;

/***************************************************
* function			   : KDF
* description		   : KDF����
* parameters:
-- data[in]		   : ����
-- data_len[in]	   : ���ݳ���
-- key_len[in]	   : ��Կ����
-- key[out]		   : ��Կ
* return 			   : 0--success;
��0--error code
***************************************************/
void KDF(byte *data, uint data_len, uint key_len, byte *key);

/***************************************************
* function          	: EccMakeKey
* description	        : ECC��/˽Կ���ɽӿں���
* parameters:
-- sk[in]	        : ˽Կ
-- sk_len[in]       : ˽Կ����
-- type[in]         : ��������
-- pk[out]			: ��Կ
-- pk_len[out]		: ��Կ����
* return 		        : 0--success;
��0--error code
***************************************************/
int EccMakeKey(byte *sk, uint sk_len,
               byte *pk, uint pk_len, int type);

/***************************************************
* function          	: EccSign
* description	        : ECCǩ�����ɽӿں���
* parameters:
-- hash[in]	        : ���ݹ�ϣֵ
-- hash_len[in]     : ���ݹ�ϣֵ����
-- random[in]		: �����
-- random_len[in]	: ���������
-- sk[in]	        : ˽Կ
-- sk_len[in]       : ˽Կ����
-- sign[out]	    : ǩ��ֵ
-- sign_len[out]    : ǩ��ֵ����
* return 		        : 0--success;
��0--error code
***************************************************/
int EccSign(const byte *hash, uint hash_len,
            byte *random, uint random_len,
            byte *sk, uint sk_len,
            byte *sign, uint sign_len);

/***************************************************
* function				: EccVerify
* description			: ECCǩ����֤�ӿں���
* parameters:
-- hash[in] 		: ���ݹ�ϣֵ
-- hash_len[in] 	: ���ݹ�ϣֵ����
-- pk[in]			: ��Կ
-- pk_len[in]		: ��Կ����
-- sign[in]		    : ǩ��ֵ
-- sign_len[in]	    : ǩ��ֵ����
* return				: 0--success;
��0--error code
***************************************************/
int EccVerify(const byte *hash, uint hash_len,
              byte *pk, uint pk_len,
              byte *sign, uint sign_len);

/***************************************************
* function				    : EccEncrypt
* description			    : ECC���ܽӿں���
* parameters:
-- plain[in] 	        : ��������
-- plain_len[in] 	    : �������ݳ���
-- random[in]		    : �����
-- random_len[in]	    : ���������
-- pk[in]			    : ��Կ
-- pk_len[in]		    : ��Կ����
-- cipher[out]		    : ��������
-- cipher_len[out]	    : �������ݳ��� (cipher_len = plain_len+96)
* return				: 0--success;
��0--error code
***************************************************/
int EccEncrypt(byte *plain, uint plain_len,
               byte *random, uint random_len,
               byte *pk, uint pk_len,
               byte *cipher, uint cipher_len);

/***************************************************
* function				: sdt_ecc_decrypt
* description			: ECC���ܽӿں���
* parameters:
-- cipher[in] 	    : ��������
-- cipher_len[in] 	: �������ݳ���
-- sk[in]			: ˽Կ
-- sk_len[in]		: ˽Կ����
-- plain[out]		: ��������
-- plain_len[out]	: �������ݳ��� (plain_len = cipher_len-96)
* return				: 0--success;
��0--error code
***************************************************/
int EccDecrypt(byte *cipher, uint cipher_len,
               byte *sk, uint sk_len,
               byte *plain, uint plain_len);
