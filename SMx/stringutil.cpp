#include "stringutil.h"
#include <time.h>
#include <stdlib.h>
//std::string byte2HexStr(const std::string &src)
//{
//	uint l = src.size();
//	std::string ret(l * 2, '0');
//	for(uint i = 0; i < l; i++) {
//		ret[i * 2] = lett16[(byte)src[i] / 16];
//		ret[i * 2 + 1] = lett16[(byte)src[i] % 16];
//	}
//	return ret;
//}
//
//std::string HexStr2byte(const std::string &src)
//{
//	std::string ret(src.size() / 2, '0');
//	uint le16[70 + 1] = { 0 };
//	for(int i = 48; i < 58; i++)
//		le16[i] = i - 48;
//	le16['A'] = 10;
//	le16['B'] = 11;
//	le16['C'] = 12;
//	le16['D'] = 13;
//	le16['E'] = 14;
//	le16['F'] = 15;
//
//	for(uint i = 0; i * 2 < src.size(); i++) {
//		ret[i] = (byte)(le16[(uint)src[i * 2]] * 16 + le16[(uint)src[i * 2 + 1]]);
//	}
//	return ret;
//}
//
//std::string int2Hexstr(const int &a)
//{
//	std::string ret(2, '0');
//	ret[0] = lett16[a / 16];
//	ret[1] = lett16[a % 16];
//
//	return ret;
//}
//
//std::string uint2String(uint *src)
//{
//	std::string ret;
//	byte a = '0', b = '0', c = '0', d = '0';
//	std::string s_a;
//	std::string s_b;
//	std::string s_c;
//	std::string s_d;
//
//	for(int i = 0; i < 8; i++) {
//
//		a = (byte)(src[i] & 0xFF);
//		s_a = int2Hexstr((int)a);
//
//		b = (byte)((src[i] >> 8) & 0xFF);
//		s_b = int2Hexstr((int)b);
//
//		c = (byte)((src[i] >> 16) & 0xFF);
//		s_c = int2Hexstr((int)c);
//
//		d = (byte)((src[i] >> 24) & 0xFF);
//		s_d = int2Hexstr((int)d);
//
//		ret += s_d + s_c + s_b + s_a;
//	}
//
//	return ret;
//}
//
//
//void pkcs7(const byte *input, const uint len, const uint n, byte *output)
//{
//	uint l = n - len;
//	for(uint i = 0; i < len; i++)
//		output[i] = input[i];
//	for(uint i = 0; i < l; i++) {
//		output[i + len] = l;
//	}
//}
//
//void pkcs7_2(char *input, const uint len, const uint n, byte *output)
//{
//	uint l = n - len;
//	for(uint i = 0; i < len; i++)
//		output[i] = (byte)input[i];
//	for(uint i = 0; i < l; i++) {
//		output[i + len] = l;
//	}
//}
//
//std::string sblank(const uint &n)
//{
//	std::string res = "";
//	for(uint i = 0; i < n; ++i)
//		res += " ";
//	return res;
//}

int HexChar2Int(char c)
{
	if(c >= '0' && c <= '9') return (c - '0');
	if(c >= 'A' && c <= 'F') return (c - 'A' + 10);
	if(c >= 'a' && c <= 'f') return (c - 'a' + 10);
	return 0;
}

void HexStr2Bytes(const std::string s, char* bytes)
{
	int sz = s.length();
	for(int i = 0; i < sz; i += 2) {
		bytes[i / 2] = (char)((HexChar2Int(s.at(i)) << 4)
		                      | HexChar2Int(s.at(i + 1)));
	}
}

std::string Bytes2HexStr(char* bytes, int bytelength)
{
	std::string s("");
	std::string str2("0123456789abcdef");
	for(int i = 0; i < bytelength; i++) {
		int b;
		b = 0x0f & (bytes[i] >> 4);
		char s1 = str2.at(b);
		s.append(1, str2.at(b));
		b = 0x0f & bytes[i];
		s.append(1, str2.at(b));
		char s2 = str2.at(b);
	}
	return s;
}

void ToUpper(std::string &s)
{
	transform(s.begin(), s.end(), s.begin(), toupper);
}

void ToLower(std::string &s)
{
	transform(s.begin(), s.end(), s.begin(), tolower);
}

/*
功能：生成指定长度随机数
输入：len随机数长度
输出：rand随机数
返回：无
*/
void GenRand(unsigned char rnd[], int len)
{
	srand((uint)time(NULL));
	for(int i = 0; i < len; i++) {
		rnd[i] = (BYTE)(rand() % 256);
	}
}



