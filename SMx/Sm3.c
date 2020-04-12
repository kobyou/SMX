#include "Sm3.h"

/**
* SM3.c
* SM3�㷨�ӿ�ʵ��
*
* @date 2018/10/18
* @company UnionPay (Sqwang)
*/

#include "Sm3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define USE_HTONL 1
//#if USE_HTONL
//#ifdef WIN32
//#include <winsock2.h>
//#pragma comment(lib, "ws2_32.lib")
//#else
//#include <arpa/inet.h>
//#endif
//#endif

//��һ����ת��Ϊ4���ֽ�
#define uintTObyte(x,y)                           \
	{   (y)[0]=(byte)(((x) >> 24) & 255);  \
		(y)[1]=(byte)(((x) >> 16) & 255);  \
		(y)[2]=(byte)(((x) >> 8) & 255);   \
		(y)[3]=(byte)((x) & 255);          \
	}

//��4���ֽ�ת��Ϊһ����
#define byteTOuint(y,x)                     \
	{                                        \
		x=((uint)((y)[0] & 255) << 24) |  \
		  ((uint)((y)[1] & 255) << 16) |  \
		  ((uint)((y)[2] & 255) << 8) |   \
		  ((uint)((y)[3] & 255));         \
	}

#define rsl(x,n) (((x)<<(n)) | ((x)>> (32-n)))
#define P0(x) (x ^ rsl(x, 9) ^ rsl(x, 17))
#define p1(x) (x ^ rsl(x, 15) ^ rsl(x, 23))
#define FF0(x, y, z) (x^y^z)
#define FF1(x, y, z) ((x&y)|(x&z)|(y&z))
#define GG1(x, y, z) ((x&y)|(~x&z))


void msg_expand(uint *x, uint *y, uint *z)
{
	int i;
	uint tp;
	for(i = 0; i < 16; i++) {
		y[i] = x[i];
	}
	for(i = 16; i < 68; i++) {
		tp = y[i - 16] ^ y[i - 9] ^ rsl(y[i - 3], 15);
		y[i] = p1(tp) ^ rsl(y[i - 13], 7) ^ y[i - 6];
	}
	for(i = 0; i < 64; i++) {
		z[i] = y[i] ^ y[i + 4];
	}
}

/***************************************************
* function			   : SM3_Init
* description		   : ��ϣ��ʼ��
* parameters:
-- ctx[out]		   : ��ϣ������
* return 			   : void
***************************************************/
void SM3_Init(SM3_state *ctx)
{
	ctx->IV[0] = 0x7380166f;
	ctx->IV[1] = 0x4914b2b9;
	ctx->IV[2] = 0x172442d7;
	ctx->IV[3] = 0xda8a0600;
	ctx->IV[4] = 0xa96f30bc;
	ctx->IV[5] = 0x163138aa;
	ctx->IV[6] = 0xe38dee4d;
	ctx->IV[7] = 0xb0fb0e4e;

	ctx->len = 0;
}

#if 0
void SM3_compress(SM3_state *ctx)
{
	int i;
	uint HA, HB, HC, HD, HE, HF, HG, HH;
	uint SS1, SS2, TT1, TT2;
	uint m[16];
	uint W[68], W1[64];

	static const uint T[64] = {
		0x79cc4519, 0xf3988a32, 0xe7311465, 0xce6228cb,
		0x9cc45197, 0x3988a32f, 0x7311465e, 0xe6228cbc,
		0xcc451979, 0x988a32f3, 0x311465e7, 0x6228cbce,
		0xc451979c, 0x88a32f39, 0x11465e73, 0x228cbce6,

		0x9d8a7a87, 0x3b14f50f, 0x7629ea1e, 0xec53d43c,
		0xd8a7a879, 0xb14f50f3, 0x629ea1e7, 0xc53d43ce,
		0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec,
		0xa7a879d8, 0x4f50f3b1, 0x9ea1e762, 0x3d43cec5,
		0x7a879d8a, 0xf50f3b14, 0xea1e7629, 0xd43cec53,
		0xa879d8a7, 0x50f3b14f, 0xa1e7629e, 0x43cec53d,
		0x879d8a7a, 0x0f3b14f5, 0x1e7629ea, 0x3cec53d4,
		0x79d8a7a8, 0xf3b14f50, 0xe7629ea1, 0xcec53d43,
		0x9d8a7a87, 0x3b14f50f, 0x7629ea1e, 0xec53d43c,
		0xd8a7a879, 0xb14f50f3, 0x629ea1e7, 0xc53d43ce,
		0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec,
		0xa7a879d8, 0x4f50f3b1, 0x9ea1e762, 0x3d43cec5,
	};//���㷨���ֳ�����λ��õ��ĳ���

	for(i = 0; i < 16; i++) {
		byteTOuint(ctx->m + 4 * i, m[i]);
	}

	msg_expand(m, W, W1); //��Ϣ��չ�任

	HA = ctx->IV[0];
	HB = ctx->IV[1];
	HC = ctx->IV[2];
	HD = ctx->IV[3];
	HE = ctx->IV[4];
	HF = ctx->IV[5];
	HG = ctx->IV[6];
	HH = ctx->IV[7];

	for(i = 0; i < 16; i++) {
		SS1 = rsl(HA, 12) + HE + T[i];
		SS1 = rsl(SS1, 7);
		SS2 = SS1 ^ rsl(HA, 12);
		TT1 = FF0(HA, HB, HC) + HD + SS2 + W1[i];
		TT2 = FF0(HE, HF, HG) + HH + SS1 + W[i];
		HD = HC;
		HC = rsl(HB, 9);
		HB = HA;
		HA = TT1;
		HH = HG;
		HG = rsl(HF, 19);
		HF = HE;
		HE = P0(TT2);
	}
	for(i = 16; i < 64; i++) {
		SS1 = rsl(HA, 12) + HE + T[i];
		SS1 = rsl(SS1, 7);
		SS2 = SS1 ^ rsl(HA, 12);
		TT1 = FF1(HA, HB, HC) + HD + SS2 + W1[i];
		TT2 = GG1(HE, HF, HG) + HH + SS1 + W[i];
		HD = HC;
		HC = rsl(HB, 9);
		HB = HA;
		HA = TT1;
		HH = HG;
		HG = rsl(HF, 19);
		HF = HE;
		HE = P0(TT2);
	}

	ctx->IV[0] ^= HA;
	ctx->IV[1] ^= HB;
	ctx->IV[2] ^= HC;
	ctx->IV[3] ^= HD;
	ctx->IV[4] ^= HE;
	ctx->IV[5] ^= HF;
	ctx->IV[6] ^= HG;
	ctx->IV[7] ^= HH;

}  //ѹ������
#else
#define ROUND0(HA,HB,HC,HD,HE,HF,HG,HH,W,W1,T) do {	\
		SS1 = rsl(HA, 12) + HE + T;	\
		SS1 = rsl(SS1, 7);			\
		SS2 = SS1 ^ rsl(HA, 12);	\
		TT1 = FF0(HA, HB, HC) + HD + SS2 + W1;	\
		TT2 = FF0(HE, HF, HG) + HH + SS1 + W;	\
		HB = rsl(HB, 9);	\
		HD = P0(TT2);		\
		HF = rsl(HF, 19);	\
		HH = TT1;			\
	} while (0)

#define ROUND1(HA,HB,HC,HD,HE,HF,HG,HH,W,W1,T) do {	\
		SS1 = rsl(HA, 12) + HE + T;	\
		SS1 = rsl(SS1, 7);			\
		SS2 = SS1 ^ rsl(HA, 12);	\
		TT1 = FF1(HA, HB, HC) + HD + SS2 + W1;	\
		TT2 = GG1(HE, HF, HG) + HH + SS1 + W;	\
		HB = rsl(HB, 9);	\
		HD = P0(TT2);		\
		HF = rsl(HF, 19);	\
		HH = TT1;			\
	} while (0)

void SM3_compress(SM3_state *ctx)
{
	int i;
	uint HA, HB, HC, HD, HE, HF, HG, HH;
	uint SS1, SS2, TT1, TT2;
	uint W[68], W1[64];
	//���㷨���ֳ�����λ��õ��ĳ���
	static const uint T[64] = {
		0x79cc4519, 0xf3988a32, 0xe7311465, 0xce6228cb,
		0x9cc45197, 0x3988a32f, 0x7311465e, 0xe6228cbc,
		0xcc451979, 0x988a32f3, 0x311465e7, 0x6228cbce,
		0xc451979c, 0x88a32f39, 0x11465e73, 0x228cbce6,

		0x9d8a7a87, 0x3b14f50f, 0x7629ea1e, 0xec53d43c,
		0xd8a7a879, 0xb14f50f3, 0x629ea1e7, 0xc53d43ce,
		0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec,
		0xa7a879d8, 0x4f50f3b1, 0x9ea1e762, 0x3d43cec5,
		0x7a879d8a, 0xf50f3b14, 0xea1e7629, 0xd43cec53,
		0xa879d8a7, 0x50f3b14f, 0xa1e7629e, 0x43cec53d,
		0x879d8a7a, 0x0f3b14f5, 0x1e7629ea, 0x3cec53d4,
		0x79d8a7a8, 0xf3b14f50, 0xe7629ea1, 0xcec53d43,
		0x9d8a7a87, 0x3b14f50f, 0x7629ea1e, 0xec53d43c,
		0xd8a7a879, 0xb14f50f3, 0x629ea1e7, 0xc53d43ce,
		0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec,
		0xa7a879d8, 0x4f50f3b1, 0x9ea1e762, 0x3d43cec5,
	};

#if USE_HTONL
	uint *ptr = (uint*)ctx->m;
#endif

	for(i = 0; i < 16; i++) {
#if USE_HTONL
		W[i] = htonl(ptr[i]);
#else
		byteTOuint(ctx->m + 4 * i, W[i]);
#endif
	}
	for(i = 16; i < 68; i++) {
		HA = W[i - 16] ^ W[i - 9] ^ rsl(W[i - 3], 15);
		W[i] = p1(HA) ^ rsl(W[i - 13], 7) ^ W[i - 6];
	}
	for(i = 0; i < 64; i++) {
		W1[i] = W[i] ^ W[i + 4];
	}

	HA = ctx->IV[0];
	HB = ctx->IV[1];
	HC = ctx->IV[2];
	HD = ctx->IV[3];
	HE = ctx->IV[4];
	HF = ctx->IV[5];
	HG = ctx->IV[6];
	HH = ctx->IV[7];

	ROUND0(HA, HB, HC, HD, HE, HF, HG, HH, W[0], W1[0], T[0]);
	ROUND0(HH, HA, HB, HC, HD, HE, HF, HG, W[1], W1[1], T[1]);
	ROUND0(HG, HH, HA, HB, HC, HD, HE, HF, W[2], W1[2], T[2]);
	ROUND0(HF, HG, HH, HA, HB, HC, HD, HE, W[3], W1[3], T[3]);
	ROUND0(HE, HF, HG, HH, HA, HB, HC, HD, W[4], W1[4], T[4]);
	ROUND0(HD, HE, HF, HG, HH, HA, HB, HC, W[5], W1[5], T[5]);
	ROUND0(HC, HD, HE, HF, HG, HH, HA, HB, W[6], W1[6], T[6]);
	ROUND0(HB, HC, HD, HE, HF, HG, HH, HA, W[7], W1[7], T[7]);
	ROUND0(HA, HB, HC, HD, HE, HF, HG, HH, W[8], W1[8], T[8]);
	ROUND0(HH, HA, HB, HC, HD, HE, HF, HG, W[9], W1[9], T[9]);
	ROUND0(HG, HH, HA, HB, HC, HD, HE, HF, W[10], W1[10], T[10]);
	ROUND0(HF, HG, HH, HA, HB, HC, HD, HE, W[11], W1[11], T[11]);
	ROUND0(HE, HF, HG, HH, HA, HB, HC, HD, W[12], W1[12], T[12]);
	ROUND0(HD, HE, HF, HG, HH, HA, HB, HC, W[13], W1[13], T[13]);
	ROUND0(HC, HD, HE, HF, HG, HH, HA, HB, W[14], W1[14], T[14]);
	ROUND0(HB, HC, HD, HE, HF, HG, HH, HA, W[15], W1[15], T[15]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[16], W1[16], T[16]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[17], W1[17], T[17]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[18], W1[18], T[18]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[19], W1[19], T[19]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[20], W1[20], T[20]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[21], W1[21], T[21]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[22], W1[22], T[22]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[23], W1[23], T[23]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[24], W1[24], T[24]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[25], W1[25], T[25]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[26], W1[26], T[26]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[27], W1[27], T[27]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[28], W1[28], T[28]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[29], W1[29], T[29]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[30], W1[30], T[30]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[31], W1[31], T[31]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[32], W1[32], T[32]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[33], W1[33], T[33]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[34], W1[34], T[34]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[35], W1[35], T[35]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[36], W1[36], T[36]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[37], W1[37], T[37]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[38], W1[38], T[38]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[39], W1[39], T[39]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[40], W1[40], T[40]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[41], W1[41], T[41]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[42], W1[42], T[42]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[43], W1[43], T[43]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[44], W1[44], T[44]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[45], W1[45], T[45]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[46], W1[46], T[46]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[47], W1[47], T[47]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[48], W1[48], T[48]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[49], W1[49], T[49]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[50], W1[50], T[50]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[51], W1[51], T[51]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[52], W1[52], T[52]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[53], W1[53], T[53]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[54], W1[54], T[54]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[55], W1[55], T[55]);
	ROUND1(HA, HB, HC, HD, HE, HF, HG, HH, W[56], W1[56], T[56]);
	ROUND1(HH, HA, HB, HC, HD, HE, HF, HG, W[57], W1[57], T[57]);
	ROUND1(HG, HH, HA, HB, HC, HD, HE, HF, W[58], W1[58], T[58]);
	ROUND1(HF, HG, HH, HA, HB, HC, HD, HE, W[59], W1[59], T[59]);
	ROUND1(HE, HF, HG, HH, HA, HB, HC, HD, W[60], W1[60], T[60]);
	ROUND1(HD, HE, HF, HG, HH, HA, HB, HC, W[61], W1[61], T[61]);
	ROUND1(HC, HD, HE, HF, HG, HH, HA, HB, W[62], W1[62], T[62]);
	ROUND1(HB, HC, HD, HE, HF, HG, HH, HA, W[63], W1[63], T[63]);

	ctx->IV[0] ^= HA;
	ctx->IV[1] ^= HB;
	ctx->IV[2] ^= HC;
	ctx->IV[3] ^= HD;
	ctx->IV[4] ^= HE;
	ctx->IV[5] ^= HF;
	ctx->IV[6] ^= HG;
	ctx->IV[7] ^= HH;
}
#endif

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
int SM3_Update(SM3_state *ctx, const byte *data, uint data_len)
{
	uint x;

	while(data_len) {
		x = (64 - ctx->len) < data_len ? 64 - ctx->len : data_len;
		data_len -= x;
		memcpy(ctx->m + ctx->len, data, x);
		ctx->len += x;
		data += x;
		if(ctx->len == 64) {
			SM3_compress(ctx);
			ctx->len = 0;
		}
	}
	return 0;
}

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
int SM3_Final(byte *hash, uint hash_len, SM3_state *ctx, uint data_len)
{
	uint l1, l2;
	unsigned int i;
	byte th[32];

	l2 = data_len >> 29;
	l1 = data_len << 3;

	ctx->m[ctx->len++] = 0x80;

	if(ctx->len > 56) {
		while(ctx->len < 64) {
			ctx->m[ctx->len++] = 0x00;
		}
		SM3_compress(ctx);
		ctx->len = 0;
	}

	while(ctx->len < 56) {
		ctx->m[ctx->len++] = 0x00;
	}

	uintTObyte(l2, ctx->m + 56);
	uintTObyte(l1, ctx->m + 60);

	SM3_compress(ctx);
	if(hash_len % 4 == 0) {
		for(i = 0; i < hash_len / 4; i++) {
			uintTObyte(ctx->IV[i], hash + 4 * i);
		}
	}
	else {
		for(i = 0; i < 8; i++) {
			uintTObyte(ctx->IV[i], th + 4 * i);
		}
		for(i = 0; i < hash_len; i++) {
			hash[i] = th[i];
		}
	}
	return 0;
}

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
int SM3_Hash(byte *msg, uint msg_len, byte *hash, uint hash_len)
{
	SM3_state ctx;

	if((hash_len < 1) || (hash_len > 32))
		return -1;

	SM3_Init(&ctx);
	SM3_Update(&ctx, msg, msg_len);
	SM3_Final(hash, hash_len, &ctx, msg_len);
	return 0;
}

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
             byte *hash, uint hash_len, uint flag)
{
	unsigned int i;

	if((hash_len < 1) | (hash_len > 32))
		return -1;

	if(flag == 0) {
		SM3_state ctx;
		SM3_Init(&ctx);
		SM3_Update(&ctx, msg, all_len);
		SM3_Final(hash, hash_len, &ctx, all_len);
	}

	if(flag == 1) {
		SM3_state ctx;

		if(msg_len % 64)
			return -1;

		SM3_Init(&ctx);
		SM3_Update(&ctx, msg, msg_len);

		for(i = 0; i < 8; i++) {
			uintTObyte(ctx.IV[i], hash + 4 * i);
		}
	}

	if(flag == 2) {
		SM3_state ctx;

		if(msg_len % 64)
			return -1;

		for(i = 0; i < 8; i++) {
			byteTOuint(hash + 4 * i, ctx.IV[i]);
		}
		ctx.len = 0;

		SM3_Update(&ctx, msg, msg_len);

		for(i = 0; i < 8; i++) {
			uintTObyte(ctx.IV[i], hash + 4 * i);
		}
	}

	if(flag == 3) {
		SM3_state ctx;
		for(i = 0; i < 8; i++) {
			byteTOuint(hash + 4 * i, ctx.IV[i]);
		}
		ctx.len = 0;

		SM3_Update(&ctx, msg, msg_len);
		SM3_Final(hash, hash_len, &ctx, all_len);
	}
	return 0;
}