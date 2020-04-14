#pragma once
#include "def.h"
/**
* SM3.h
* SM3算法接口定义
*
* @date 2018/10/18
* @company Unionpay (Sqwang)
*/

const static byte sm2_par_dig[] = {
	0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
	0x28, 0xE9, 0xFA, 0x9E, 0x9D, 0x9F, 0x5E, 0x34, 0x4D, 0x5A, 0x9E, 0x4B, 0xCF, 0x65, 0x09, 0xA7,
	0xF3, 0x97, 0x89, 0xF5, 0x15, 0xAB, 0x8F, 0x92, 0xDD, 0xBC, 0xBD, 0x41, 0x4D, 0x94, 0x0E, 0x93,
	0x32, 0xC4, 0xAE, 0x2C, 0x1F, 0x19, 0x81, 0x19, 0x5F, 0x99, 0x04, 0x46, 0x6A, 0x39, 0xC9, 0x94,
	0x8F, 0xE3, 0x0B, 0xBF, 0xF2, 0x66, 0x0B, 0xE1, 0x71, 0x5A, 0x45, 0x89, 0x33, 0x4C, 0x74, 0xC7,
	0xBC, 0x37, 0x36, 0xA2, 0xF4, 0xF6, 0x77, 0x9C, 0x59, 0xBD, 0xCE, 0xE3, 0x6B, 0x69, 0x21, 0x53,
	0xD0, 0xA9, 0x87, 0x7C, 0xC6, 0x2A, 0x47, 0x40, 0x02, 0xDF, 0x32, 0xE5, 0x21, 0x39, 0xF0, 0xA0
};


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