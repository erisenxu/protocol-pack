/*
 * @(#) Field.h Created on 2010-12-19
 *
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FIELD_H
#define FIELD_H

#include "comm/ByteArray.h"

#define MAX_FIELD_INFO_LEN  1024
#define MAX_FIELD_NAME_LEN  256

/**
 * 字段信息对象
 */
typedef struct tagFieldInfo     FIELDINFO;
typedef struct tagFieldInfo*    LPFIELDINFO;

/**
 * 字段类型
 */
enum tagFieldDataType
{
	FIELD_TYPE_INVALID = 0, // 不合法(未初始化)的字段类型
	FIELD_TYPE_BYTE = 1,    // S8，占1个字节
	FIELD_TYPE_UBYTE = 2,   // U8，占1个字节
	FIELD_TYPE_SHORT = 3,   // S16，占2个字节
	FIELD_TYPE_USHORT = 4,  // U16，占2个字节
	FIELD_TYPE_INT = 5,     // S32，占4个字节
	FIELD_TYPE_UINT = 6,    // U32，占4个字节
	FIELD_TYPE_LONG = 7,    // S64，占8个字节
	FIELD_TYPE_ULONG = 8,   // U64，占8个字节
	FIELD_TYPE_STRING = 9,  // 字符串，特殊的TLV字段
	FIELD_TYPE_BYTES = 10,  // 字节数组，特殊的TLV字段
	FIELD_TYPE_TLV = 11,    // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
	FIELD_TYPE_ARRAY = 12   // 数组
};

/**
 * 按子字段标签，解码给定字段的子字段
 * @param pstField 给定字段对象
 * @param szBuf 要解码的消息
 * @param iBufLen 消息长度
 * @param nTag 子字段的标签
 * @return 成功返回0，失败返回错误码
 */
typedef int (*FNSUBFIELDDECODE)(void* pstField, const char* szBuf, int iBufLen, U16 nTag);

/**
 * 数组元素字段编码。数组元素暂时不支持字符串
 * @param pstField 要编码的数组字段
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
typedef int (*FNARRAYFIELDENCODE)(void* pstField, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 数组元素字段解码。数组元素暂时不支持字符串
 * @param pstField 给定字段对象
 * @param szBuf 要解码的消息
 * @param iBufLen 消息长度
 * @return 成功返回0，失败返回错误码
 */
typedef int (*FNARRAYFIELDDECODE)(void* pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pstValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
typedef int (*FNARRAYFIELDFORMAT)(const char* szFieldName, void* pstValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成xml形式
 * @param szFieldName 要格式化的字段名称
 * @param pstValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
typedef int (*FNARRAYFIELDTOXML)(const char* szFieldName, void* pstValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 设置按字段名字设置子字段的值
 * @param pstField 给定字段对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @param szValue 字段的值
 */
typedef void (*FNSETSUBFIELDVALUEBYNAME)(void* pstField, const char* szSubFieldName, U16 nIdx, const char* szValue);

/**
 * 设置按字段名字获取子字段对象
 * @param pstField 给定字段对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @return 返回子字段名称对应的子字段对象
 */
typedef void* (*FNGETSUBFIELDBYNAME)(void* pstField, const char* szSubFieldName, U16 nIdx);

/**
 * 构建子字段信息对象
 * @param pstSubFieldInfo 要构建的子字段信息对象
 * @param szSubFieldName 子字段的名称
 */
typedef void (*FNBUILDSUBFIELDINFOBYNAME)(LPFIELDINFO pstSubFieldInfo, const char* szSubFieldName);

/**
 * 构建字段信息对象
 * @param pstFieldInfo 要构建的字段信息对象
 */
typedef void (*FNBUILDFIELDINFO)(LPFIELDINFO pstFieldInfo);

/**
 * 字段信息
 */
struct tagFieldInfo
{
    int iMemIndex;                                          /* 内存池索引 */
    LPFIELDINFO pstParent;                                  /* 父字段对象 */
    char szFieldName[MAX_FIELD_NAME_LEN];                   /* 本字段的名称 */
    U8 bFieldType;                                          /* 字段的类型 */
    void* pstExtData;                                       /* 扩展数据 */
    FNSETSUBFIELDVALUEBYNAME setSubFieldValueByName;        /* 设置子字段的值的函数 */
    FNGETSUBFIELDBYNAME getSubFieldByName;                  /* 获取子字段对象的函数 */
    FNBUILDSUBFIELDINFOBYNAME buildSubFieldInfoByName;      /* 构建子字段信息对象的函数 */
};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 整数byte字段编码
 * @param pchValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int byte_field_encode(void* pchValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码byte字段
 * @param pchValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int byte_field_decode(void* pchValue, const char* szBuf, int iBufLen);

/**
 * 整数unsigned byte编码
 * @param pbValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_encode(void* pbValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码unsigned byte字段
 * @param pbValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_decode(void* pbValue, const char* szBuf, int iBufLen);

/**
 * 整数short字段编码
 * @param pshValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int short_field_encode(void* pshValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码short字段
 * @param pshValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int short_field_decode(void* pshValue, const char* szBuf, int iBufLen);

/**
 * 整数unsigned short编码
 * @param pnValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_encode(void* pnValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码unsigned short字段
 * @param pnValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_decode(void* pnValue, const char* szBuf, int iBufLen);

/**
 * 整数字段编码
 * @param piValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int int_field_encode(void* piValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码Int字段
 * @param piValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int int_field_decode(void* piValue, const char* szBuf, int iBufLen);

/**
 * 整数字段编码
 * @param pdwValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int uint_field_encode(void* pdwValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码Int字段
 * @param pdwValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int uint_field_decode(void* pdwValue, const char* szBuf, int iBufLen);

/**
 * long整数字段编码
 * @param pllValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int long_field_encode(void* pllValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码long字段
 * @param pllValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int long_field_decode(void* pllValue, const char* szBuf, int iBufLen);

/**
 * unsigned long整数字段编码
 * @param pullValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_encode(void* pullValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码unsigned long字段
 * @param pullValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_decode(void* pullValue, const char* szBuf, int iBufLen);

/**
 * 字符串字段编码
 * @param szValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int string_field_encode(const char* szValue, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码字符串字段
 * @param pszValue 要解码的字段
 * @param dwBufSize 字段的最大长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int string_field_decode(char* pszValue, U32 dwBufSize, const char* szBuf, int iBufLen);

/**
 * 字节数组字段编码
 * @param szValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_encode(const char* szValue, U32 dwValueLen, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * 解码字节数组字段
 * @param pszValue [INOUT] 要解码的字段
 * @param dwBufSize [IN] 字段的最大长度
 * @param pdwValueLen [OUT] 字段的长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_decode(char* pszValue, U32 dwBufSize, U32* pdwValueLen, const char* szBuf, int iBufLen);

/**
 * 复合字段解码
 * @param pstField 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param subFieldDecodeFunc 解码子字段的函数
 * @return 成功返回0，失败返回错误码
 */
int composite_field_decode(void* pstField, const char* szBuf, int iBufLen, FNSUBFIELDDECODE subFieldDecodeFunc);

/**
 * 数组字段编码
 * @param pstField 要编码的数组字段
 * @param dwFieldSize 数组元素的大小
 * @param nArrNum 数组元素的数量
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @param arrFieldEncodeFunc 数组元素字段编码函数
 * @return 成功返回0，失败返回错误码
 */
int array_field_encode(void* pstField, U32 dwFieldSize, U16 nArrNum, U16 nTag, LPBYTEARRAY pstByteArray, FNARRAYFIELDENCODE arrFieldEncodeFunc);

/**
 * 数组字段解码
 * @param pstField 要解码的字段
 * @param dwFieldSize 数组元素的大小
 * @param nMaxNum 数组的最大长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param arrFieldDecodeFunc 解码数组元素字段的函数
 * @return 成功返回0，失败返回错误码
 */
int array_field_decode(void* pstField, U32 dwFieldSize, U16 nMaxNum, const char* szBuf, int iBufLen, FNARRAYFIELDDECODE arrFieldDecodeFunc);

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int get_length_by_type(U8 bType, const char* szBuf, int iBufLen);

/**
 * 从消息中读取一个字节，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的字节
 */
U8 read_byte(const char* szBuf);

/**
 * 从消息中读取一个short，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U16 read_short(const char* szBuf);

/**
 * 从消息中读取一个int，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的int
 */
U32 read_int(const char* szBuf);

/**
 * 从消息中读取一个long，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的long
 */
U64 read_long(const char* szBuf);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pchValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int byte_field_format(const char* szFieldName, void* pchValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pchValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int byte_field_to_xml(const char* szFieldName, void* pchValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pbValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_format(const char* szFieldName, void* pbValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pbValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_to_xml(const char* szFieldName, void* pbValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pshValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int short_field_format(const char* szFieldName, void* pshValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pshValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int short_field_to_xml(const char* szFieldName, void* pshValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pnValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_format(const char* szFieldName, void* pnValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pnValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_to_xml(const char* szFieldName, void* pnValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param piValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int int_field_format(const char* szFieldName, void* piValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param piValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int int_field_to_xml(const char* szFieldName, void* piValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pdwValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int uint_field_format(const char* szFieldName, void* pdwValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pdwValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int uint_field_to_xml(const char* szFieldName, void* pdwValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pllValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int long_field_format(const char* szFieldName, void* pllValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pllValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int long_field_to_xml(const char* szFieldName, void* pllValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_format(const char* szFieldName, void* pullValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_to_xml(const char* szFieldName, void* pullValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int string_field_format(const char* szFieldName, const char* szFieldValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int string_field_to_xml(const char* szFieldName, const char* szFieldValue, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 将数组字段格式化
 * @param szFieldName 要格式化的字段名称
 * @param pstField 要格式化的数组字段
 * @param dwFieldSize 数组元素的大小
 * @param nArrNum 数组元素的数量
 * @param pstByteArray 保存字段编码后的协议信息
 * @param arrFieldFormatFunc 数组元素字段格式化函数
 * @return 成功返回0，失败返回错误码
 */
int array_field_format(const char* szFieldName, void* pstField, U32 dwFieldSize, U16 nArrNum, LPBYTEARRAY pstByteArray, const char* szPrefix, FNARRAYFIELDFORMAT arrFieldFormatFunc);

/**
 * 将数组字段格式化
 * @param szFieldName 要格式化的字段名称
 * @param pstField 要格式化的数组字段
 * @param dwFieldSize 数组元素的大小
 * @param nArrNum 数组元素的数量
 * @param pstByteArray 保存字段编码后的协议信息
 * @param arrFieldToXmlFunc 数组元素字段格式化函数
 * @return 成功返回0，失败返回错误码
 */
int array_field_to_xml(const char* szFieldName, void* pstField, U32 dwFieldSize, U16 nArrNum, LPBYTEARRAY pstByteArray, const char* szPrefix, FNARRAYFIELDTOXML arrFieldToXmlFunc);

#ifdef __cplusplus
}
#endif

#endif
