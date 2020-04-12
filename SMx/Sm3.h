#pragma once
#include "def.h"
/**
* SM3.h
* SM3�㷨�ӿڶ���
*
* @date 2018/10/18
* @company Unionpay (Sqwang)
*/


typedef struct {
	uint IV[8];
	byte  m[64];
	uint len;
} SM3_state;

#ifdef __cpluscplus
extern "C" {
#endif

	/***************************************************
	* function			   : SM3_Init
	* description		   : ��ϣ��ʼ��
	* parameters:
	-- ctx[out]		   : ��ϣ������
	* return 			   : void
	***************************************************/
	void SM3_Init(SM3_state *ctx);

	/***************************************************
	* function			   : SM3_Update
	* description		   : ��ϣ����
	* parameters:
	-- ctx[in]		   : ��ϣ������
	-- data[in]	       : ���ݳ���
	-- data_len[in]    : ���ݳ���(�ֽ���)
	* return 			   : 0--success;
	��0--error code
	***************************************************/
	int SM3_Update(SM3_state *ctx, const byte *data, uint data_len);

	/***************************************************
	* function			   : SM3_Final
	* description		   : ��ϣ����
	* parameters:
	-- hash[out]	   : ��ϣֵ
	-- hash_len[in]	   : ��ϣֵ����
	-- ctx[in]	       : ��ϣ������
	-- data_len[in]	   : �����ܳ���
	* return 			   : 0--success;
	��0--error code
	***************************************************/
	int SM3_Final(byte *hash, uint hash_len, SM3_state *ctx, uint data_len);

	/***************************************************
	* function			   : SM3_Hash
	* description		   : ��ϣ����
	* parameters:
	-- msg[in]		   : ����
	-- msg_len[in]	   : ���ݳ���
	-- hash[out]	   : ��ϣֵ
	-- hash_len[in]    : ��ϣֵ����
	* return 			   : 0--success;
	��0--error code
	***************************************************/
	int SM3_Hash(byte *msg, uint msg_len, byte *hash, uint hash_len);

	/***************************************************
	* function			   : SM3_HASH
	* description		   : ��ϣ����
	* parameters:
	-- msg[in]		   : ����
	-- msg_len[in]	   : ���ݳ���
	-- all_len[in]	   : �����ܳ���
	-- hash[out]	   : ��ϣֵ
	-- hash_len[in]    : ��ϣֵ����
	-- flag[in]        : ��ʶ
	* return 			   : 0--success;
	��0--error code
	***************************************************/
	int SM3_HASH(byte *msg, uint msg_len, uint all_len,
	             byte *hash, uint hash_len, uint flag);


#ifdef __cpluscplus
}
#endif