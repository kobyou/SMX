#pragma once
#include <string>
#include "def.h"
#include <algorithm>

const static byte lett16[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                              '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
                             };

std::string byte2HexStr(const std::string &src);
std::string HexStr2byte(const std::string &src);
std::string uint2String(uint *src);
void pkcs7(const byte *input, const uint len, const uint n, byte *output);
void pkcs7_2(char *input, const uint len, const uint n, byte *output);
std::string sblank(const uint &n);

//十六进制字符转int
int HexChar2Int(char c);
//十六进制字符串转字符数组
void HexStr2Bytes(const std::string s, char* bytes);
//字符数组转十六进制字符串
std::string Bytes2HexStr(char* bytes, int bytelength);
//string全部转大写
void ToUpper(std::string &s);
//string全部转小写
void ToLower(std::string &s);