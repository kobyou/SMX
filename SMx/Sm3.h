#pragma once
#include "def.h"
/**
* SM3.h
* SM3算法接口定义
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
	* description		   : 哈希初始化
	* parameters:
	-- ctx[out]		   : 哈希上下文
	* return 			   : void
	***************************************************/
	void SM3_Init(SM3_state *ctx);

	/***************************************************
	* function			   : SM3_Update
	* description		   : 哈希更新
	* parameters:
	-- ctx[in]		   : 哈希上下文
	-- data[in]	       : 数据长度
	-- data_len[in]    : 数据长度(字节数)
	* return 			   : 0--success;
	非0--error code
	***************************************************/
	int SM3_Update(SM3_state *ctx, const byte *data, uint data_len);

	/***************************************************
	* function			   : SM3_Final
	* description		   : 哈希结束
	* parameters:
	-- hash[out]	   : 哈希值
	-- hash_len[in]	   : 哈希值长度
	-- ctx[in]	       : 哈希上下文
	-- data_len[in]	   : 数据总长度
	* return 			   : 0--success;
	非0--error code
	***************************************************/
	int SM3_Final(byte *hash, uint hash_len, SM3_state *ctx, uint data_len);

	/***************************************************
	* function			   : SM3_Hash
	* description		   : 哈希函数
	* parameters:
	-- msg[in]		   : 数据
	-- msg_len[in]	   : 数据长度
	-- hash[out]	   : 哈希值
	-- hash_len[in]    : 哈希值长度
	* return 			   : 0--success;
	非0--error code
	***************************************************/
	int SM3_Hash(byte *msg, uint msg_len, byte *hash, uint hash_len);

	/***************************************************
	* function			   : SM3_HASH
	* description		   : 哈希函数
	* parameters:
	-- msg[in]		   : 数据
	-- msg_len[in]	   : 数据长度
	-- all_len[in]	   : 数据总长度
	-- hash[out]	   : 哈希值
	-- hash_len[in]    : 哈希值长度
	-- flag[in]        : 标识
	* return 			   : 0--success;
	非0--error code
	***************************************************/
	int SM3_HASH(byte *msg, uint msg_len, uint all_len,
	             byte *hash, uint hash_len, uint flag);


#ifdef __cpluscplus
}
#endif