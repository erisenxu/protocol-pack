/*
 * @(#) Field.c Created on 2010-12-19
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

#include "Field.h"
#include "comm/ErrorCode.h"
#include "comm/BaseFuncDef.h"

#include <string.h>
#include <stdio.h>

/**
 * 整数byte字段编码
 * @param pchValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int byte_field_encode(void* pchValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pchValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_BYTE), iRet);
	CHECK_FUNC_RET(bytearray_append_s8(pstByteArray, *((S8*)pchValue)), iRet);

	return 0;
}

/**
 * 解码byte字段
 * @param pchValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int byte_field_decode(void* pchValue, const char* szBuf, int iBufLen)
{
	S8 chValue;
	const char* pszBuf;

	if (NULL == pchValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U8(chValue, pszBuf);

	*((S8*)pchValue) = chValue;

	return 0;
}

/**
 * 整数unsigned byte编码
 * @param pbValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_encode(void* pbValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pbValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_UBYTE), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, *((U8*)pbValue)), iRet);

	return 0;
}

/**
 * 解码unsigned byte字段
 * @param pbValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_decode(void* pbValue, const char* szBuf, int iBufLen)
{
	U8 bValue;
	const char* pszBuf;

	if (NULL == pbValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U8(bValue, pszBuf);

	*((U8*)pbValue) = bValue;

	return 0;
}

/**
 * 整数short字段编码
 * @param pshValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int short_field_encode(void* pshValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pshValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_SHORT), iRet);
	CHECK_FUNC_RET(bytearray_append_s16(pstByteArray, *((S16*)pshValue)), iRet);

	return 0;
}

/**
 * 解码short字段
 * @param pshValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int short_field_decode(void* pshValue, const char* szBuf, int iBufLen)
{
	S16 shValue;
	const char* pszBuf;

	if (NULL == pshValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U16(shValue, pszBuf);

	*((S16*)pshValue) = shValue;

	return 0;
}

/**
 * 整数unsigned short编码
 * @param pnValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_encode(void* pnValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pnValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_USHORT), iRet);
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, *((U16*)pnValue)), iRet);

	return 0;
}

/**
 * 解码unsigned short字段
 * @param pnValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_decode(void* pnValue, const char* szBuf, int iBufLen)
{
	U16 nValue;
	const char* pszBuf;

	if (NULL == pnValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U16(nValue, pszBuf);

	*((U16*)pnValue) = nValue;

	return 0;
}

/**
 * 整数字段编码
 * @param piValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int int_field_encode(void* piValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == piValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_INT), iRet);
	CHECK_FUNC_RET(bytearray_append_s32(pstByteArray, *((S32*)piValue)), iRet);

	return 0;
}

/**
 * 解码Int字段
 * @param piValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int int_field_decode(void* piValue, const char* szBuf, int iBufLen)
{
	S32 iValue;
	const char* pszBuf;

	if (NULL == piValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U32(iValue, pszBuf);

	*((S32*)piValue) = iValue;

	return 0;
}

/**
 * 整数字段编码
 * @param pdwValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int uint_field_encode(void* pdwValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pdwValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_UINT), iRet);
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, *((U32*)pdwValue)), iRet);

	return 0;
}

/**
 * 解码Int字段
 * @param pdwValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int uint_field_decode(void* pdwValue, const char* szBuf, int iBufLen)
{
	U32 dwValue;
	const char* pszBuf;

	if (NULL == pdwValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U32(dwValue, pszBuf);

	*((U32*)pdwValue) = dwValue;

	return 0;
}

/**
 * long整数字段编码
 * @param llValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int long_field_encode(void* pllValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pllValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_LONG), iRet);
	CHECK_FUNC_RET(bytearray_append_s64(pstByteArray, *((S64*)pllValue)), iRet);

	return 0;
}

/**
 * 解码long字段
 * @param pllValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int long_field_decode(void* pllValue, const char* szBuf, int iBufLen)
{
	S64 llValue;
	const char* pszBuf;

	if (NULL == pllValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U64(llValue, pszBuf);

	*((S64*)pllValue) = llValue;

	return 0;
}

/**
 * unsigned long整数字段编码
 * @param pullValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_encode(void* pullValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == pullValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_ULONG), iRet);
	CHECK_FUNC_RET(bytearray_append_u64(pstByteArray, *((U64*)pullValue)), iRet);

	return 0;
}

/**
 * 解码unsigned long字段
 * @param pullValue 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_decode(void* pullValue, const char* szBuf, int iBufLen)
{
	U64 ullValue;
	const char* pszBuf;

	if (NULL == pullValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U64(ullValue, pszBuf);

	*((U64*)pullValue) = ullValue;

	return 0;
}

/**
 * 字符串字段编码
 * @param szValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int string_field_encode(const char* szValue, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;
	U32 dwValueLen;

	if (NULL == szValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_STRING), iRet);

	// 字符串长度
	dwValueLen = strlen(szValue);
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, dwValueLen), iRet);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, dwValueLen), iRet);

	return 0;
}

/**
 * 解码字符串字段
 * @param pszValue 要解码的字段
 * @param dwBufSize 字段的最大长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int string_field_decode(char* pszValue, U32 dwBufSize, const char* szBuf, int iBufLen)
{
	U32 dwValueLen;
	const char* pszBuf;

	if (NULL == pszValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U32(dwValueLen, pszBuf);

	if (dwValueLen >= dwBufSize) return ERROR_DECODE_BUFSIZE_SHORT;

	memcpy(pszValue, pszBuf, dwValueLen);
	*(pszValue + dwValueLen) = 0;

	return 0;
}

/**
 * 字节数组字段编码
 * @param szValue 字段的值
 * @param nTag 字段的tag
 * @param pstByteArray 保存字段编码后的协议信息
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_encode(const char* szValue, U32 dwValueLen, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;

	if (NULL == szValue || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_BYTES), iRet);

	// 字符串长度
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, dwValueLen), iRet);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, dwValueLen), iRet);

	return 0;
}

/**
 * 解码字节数组字段
 * @param pszValue [INOUT] 要解码的字段
 * @param dwBufSize [IN] 字段的最大长度
 * @param pdwValueLen [OUT] 字段的长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_decode(char* pszValue, U32 dwBufSize, U32* pdwValueLen, const char* szBuf, int iBufLen)
{
	U32 dwValueLen;
	const char* pszBuf;

	if (NULL == pszValue || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	pszBuf = szBuf + sizeof(U16) + sizeof(U8);

	M_CHAR_TO_U32(dwValueLen, pszBuf);

	if (dwValueLen > dwBufSize) return ERROR_DECODE_BUFSIZE_SHORT;

	memcpy(pszValue, pszBuf, dwValueLen);

	*pdwValueLen = dwValueLen;

	return 0;
}

/**
 * 复合字段解码
 * @param pstField 要解码的字段
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param subFieldDecodeFunc 解码子字段的函数
 * @return 成功返回0，失败返回错误码
 */
int composite_field_decode(void* pstField, const char* szBuf, int iBufLen, FNSUBFIELDDECODE subFieldDecodeFunc)
{
	int iMinLen;    // 字段最小长度
	U16 nTag = 0;
	U8 bType = 0;
	const char* pszBuf;
	int iLeftLen;
	int iFieldLen;
	int iRet = -1;

	if (NULL == pstField || NULL == szBuf) return ERROR_INPUT_PARAM_NULL;

	iMinLen = sizeof(U16) + sizeof(U8);    // 字段最小长度
	pszBuf = szBuf + iMinLen + sizeof(U32);
	iLeftLen = iBufLen - iMinLen - sizeof(U32);

	if (iLeftLen < 0)
	{
		return ERROR_DECODE_BUFSIZE_SHORT;
	}

	// 求字段长度
	iLeftLen = read_int(szBuf + iMinLen);

	while (iLeftLen > 0)
	{
		// 解析Tag和Type
		if (iLeftLen < iMinLen)
		{
			return ERROR_DECODE_BUFSIZE_SHORT;
		}

		// Tag和类型
		nTag = read_short(pszBuf);
		bType = read_byte(pszBuf + sizeof(nTag));

		// 消息长度
		iFieldLen = get_length_by_type(bType, pszBuf, iLeftLen);
		if (iFieldLen == ERROR_DECODE_BUFSIZE_SHORT || iLeftLen < iFieldLen)
		{
			return ERROR_DECODE_BUFSIZE_SHORT;
		}

		/* 取消息对象 */
		iRet = subFieldDecodeFunc(pstField, pszBuf, iLeftLen, nTag);
		/* 对认识的字段进行解码，不认识的字段直接丢弃 */
		if (iRet != 0) return iRet;
		/* 不认识的字段，直接丢弃 (兼容旧版本) */
		pszBuf += iFieldLen;
		iLeftLen -= iFieldLen;
	}

	return 0;
}

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
int array_field_encode(void* pstField, U32 dwFieldSize, U16 nArrNum, U16 nTag, LPBYTEARRAY pstByteArray, FNARRAYFIELDENCODE arrFieldEncodeFunc)
{
	void* pstSubField;
	int iOldLen;
	U32 nAddLen;
	char* pszMsg;
	U16 i;
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == arrFieldEncodeFunc) return ERROR_INPUT_PARAM_NULL;

	/* 编码Tag及Type */
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, (U8)FIELD_TYPE_ARRAY), iRet);

	/* 先将数组长度设置为0 */
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, (U32)0), iRet);

	/* 记录下当前数组长度 */
	iOldLen = pstByteArray->dwLen;

	/* 数组数量 */
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nArrNum), iRet);

	/* 数组子字段 */
	for (i = 0; i < nArrNum; i++)
	{
		pstSubField = (char*)pstField + dwFieldSize * i;

		CHECK_FUNC_RET(arrFieldEncodeFunc(pstSubField, nTag, pstByteArray), iRet);
	}

	/* 修正数组长度 */
	/* 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变 */
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * 数组字段解码
 * @param pstField 要解码的数组字段
 * @param dwFieldSize 数组元素的大小
 * @param nMaxNum 数组的最大长度
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param arrFieldDecodeFunc 解码数组元素字段的函数
 * @return 成功返回0，失败返回错误码
 */
int array_field_decode(void* pstField, U32 dwFieldSize, U16 nMaxNum, const char* szBuf, int iBufLen, FNARRAYFIELDDECODE arrFieldDecodeFunc)
{
	int iHdrLen;
	const char* pszArray;
	U16 nArrayNum = 0;
	int iLeftLen;
	int iRet = -1;
	int iMsgLen = 0;
	U16 i;
	U8 bType;
	void *pstSubField;

	if (NULL == pstField || NULL == szBuf || NULL == arrFieldDecodeFunc) return ERROR_INPUT_PARAM_NULL;

	iHdrLen = sizeof(U16) + sizeof(U8) + sizeof(U32);
	pszArray = szBuf + iHdrLen;
	iLeftLen = iBufLen - iHdrLen;

	/* 数组长度 */
	M_CHAR_TO_U16(nArrayNum, pszArray);
	iLeftLen -= sizeof(nArrayNum);

	/* 数组长度超过了最大值的处理 */
	if (nArrayNum > nMaxNum) return ERROR_DECODE_ARRAY_LONG;

	/* 数组元素类型 */
	bType = *(pszArray + sizeof(U16));

	/* 解析子字段 */
	for (i = 0; i < nArrayNum; i++)
	{
		pstSubField = (char*)pstField + dwFieldSize * i;

		/* 通过类型获得数据长度 */
		iMsgLen = get_length_by_type(bType, pszArray, iLeftLen);

		if (iLeftLen < iMsgLen)
		{
			return ERROR_DECODE_BUFSIZE_SHORT;
		}

		iRet = arrFieldDecodeFunc(pstSubField, pszArray, iLeftLen);

		if (iRet != 0) return iRet;

		pszArray += iMsgLen;
		iLeftLen -= iMsgLen;
	}

	return 0;
}

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int get_length_by_type(U8 bType, const char* szBuf, int iBufLen)
{
    int iMinLen = sizeof(U16) + sizeof(U8);

    switch (bType)
    {
        case FIELD_TYPE_BYTE:
            return iMinLen + sizeof(S8);
        case FIELD_TYPE_UBYTE:
            return iMinLen + sizeof(U8);
        case FIELD_TYPE_SHORT:
            return iMinLen + sizeof(S16);
        case FIELD_TYPE_USHORT:
            return iMinLen + sizeof(U16);
        case FIELD_TYPE_INT:
            return iMinLen + sizeof(S32);
        case FIELD_TYPE_UINT:
            return iMinLen + sizeof(U32);
        case FIELD_TYPE_LONG:
            return iMinLen + sizeof(S64);
        case FIELD_TYPE_ULONG:
            return iMinLen + sizeof(U64);
        case FIELD_TYPE_STRING:
        case FIELD_TYPE_BYTES:
        case FIELD_TYPE_TLV:
        case FIELD_TYPE_ARRAY:
        {
            if (NULL != szBuf && iBufLen >= iMinLen + (int)sizeof(U32))
            {
                U32 nLen;
                const char* pszBuf = szBuf + iMinLen;
                M_CHAR_TO_U32(nLen, pszBuf);
                return iMinLen + sizeof(nLen) + nLen;
            }
            return ERROR_DECODE_BUFSIZE_SHORT;
        }
        default:
            return ERROR_DECODE_INVALID_MSG;
    }
    //return iMinLen;
}

/**
 * 从字节流中获取消息长度
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int get_length_from_buffer(const char* szBuf, int iBufLen)
{
    int iMinLen = sizeof(U16) + sizeof(U8);

    if (NULL != szBuf && iBufLen >= iMinLen)
    {
        U8 bType = *(szBuf + sizeof(U16));
        return get_length_by_type(bType, szBuf, iBufLen);
    }

    return ERROR_DECODE_BUFSIZE_SHORT;
}

/**
 * 从消息中读取一个字节，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的字节
 */
U8 read_byte(const char* szBuf)
{
    U8 bRet;

    M_CHAR_TO_U8(bRet, szBuf);

    return bRet;
}

/**
 * 从消息中读取一个short，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U16 read_short(const char* szBuf)
{
    U16 nRet;

    M_CHAR_TO_U16(nRet, szBuf);

    return nRet;
}

/**
 * 从消息中读取一个int，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的int
 */
U32 read_int(const char* szBuf)
{
    U32 dwRet;

    M_CHAR_TO_U32(dwRet, szBuf);

    return dwRet;
}

/**
 * 从消息中读取一个long，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的long
 */
U64 read_long(const char* szBuf)
{
    U64 ullRet;

    M_CHAR_TO_U64(ullRet, szBuf);

    return ullRet;
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pchValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int byte_field_format(const char* szFieldName, void* pchValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pchValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%d(0x%x)\n", szPrefix, szFieldName, *((S8*)pchValue), *((S8*)pchValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pchValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int byte_field_to_xml(const char* szFieldName, void* pchValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pchValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%d</%s>\n", szPrefix, szFieldName, *((S8*)pchValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pbValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_format(const char* szFieldName, void* pbValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pbValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%u(0x%x)\n", szPrefix, szFieldName, *((U8*)pbValue), *((U8*)pbValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pbValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ubyte_field_to_xml(const char* szFieldName, void* pbValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pbValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%u</%s>\n", szPrefix, szFieldName, *((U8*)pbValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pshValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int short_field_format(const char* szFieldName, void* pshValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pshValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%d(0x%x)\n", szPrefix, szFieldName, *((S16*)pshValue), *((S16*)pshValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pshValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int short_field_to_xml(const char* szFieldName, void* pshValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pshValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%d</%s>\n", szPrefix, szFieldName, *((S16*)pshValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pnValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_format(const char* szFieldName, void* pnValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pnValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%u(0x%x)\n", szPrefix, szFieldName, *((U16*)pnValue), *((U16*)pnValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pnValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ushort_field_to_xml(const char* szFieldName, void* pnValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pnValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%u</%s>\n", szPrefix, szFieldName, *((U16*)pnValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param piValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int int_field_format(const char* szFieldName, void* piValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == piValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%d(0x%x)\n", szPrefix, szFieldName, *((S32*)piValue), *((S32*)piValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param piValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int int_field_to_xml(const char* szFieldName, void* piValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == piValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%d</%s>\n", szPrefix, szFieldName, *((S32*)piValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pdwValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int uint_field_format(const char* szFieldName, void* pdwValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pdwValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%u(0x%x)\n", szPrefix, szFieldName, *((U32*)pdwValue), *((U32*)pdwValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pdwValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int uint_field_to_xml(const char* szFieldName, void* pdwValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pdwValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%u</%s>\n", szPrefix, szFieldName, *((U32*)pdwValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pllValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int long_field_format(const char* szFieldName, void* pllValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pllValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%lld(0x%llx)\n", szPrefix, szFieldName, *((S64*)pllValue), *((S64*)pllValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pllValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int long_field_to_xml(const char* szFieldName, void* pllValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pllValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%lld</%s>\n", szPrefix, szFieldName, *((S64*)pllValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_format(const char* szFieldName, void* pullValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pullValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%llu(0x%llx)\n", szPrefix, szFieldName, *((U64*)pullValue), *((U64*)pullValue));

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param pullValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int ulong_field_to_xml(const char* szFieldName, void* pullValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];

	if (NULL == szFieldName || NULL == pullValue || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%llu</%s>\n", szPrefix, szFieldName, *((U64*)pullValue), szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param szFieldValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int string_field_format(const char* szFieldName, const char* szFieldValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];
	const char* szStr = szFieldValue == NULL ? "" : szFieldValue;

	if (NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s%s=%s\n", szPrefix, szFieldName, szStr);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param szFieldValue 字段的值
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int string_field_to_xml(const char* szFieldName, const char* szFieldValue, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];
	const char* szStr = szFieldValue == NULL ? "" : szFieldValue;

	if (NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szValue, sizeof(szValue), "%s<%s>%s</%s>\n", szPrefix, szFieldName, szStr, szFieldName);

	return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成可读形式
 * @param szFieldName 要格式化的字段名称
 * @param szFieldValue 字段的值
 * @param dwValueLen 值的长度
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_format(const char* szFieldName, const char* szFieldValue, U32 dwValueLen, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    if (NULL == szFieldValue || 0 == dwValueLen)
    {
        SNPRINTF(szValue, sizeof(szValue), "%s%s=\n", szPrefix, szFieldName);
        return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
    }
    else
    {
        U32 i = 0;
        int iRet = 0;

        SNPRINTF(szValue, sizeof(szValue), "%s%s=", szPrefix, szFieldName);
        CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

        for (i = 0; i < dwValueLen; i++)
        {
            SNPRINTF(szValue, sizeof(szValue), "%02x ", (U8)szFieldValue[i]);
            CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
        }
    }

    return 0;
}

/**
 * 将字段格式化成XML形式
 * @param szFieldName 要格式化的字段名称
 * @param szFieldValue 字段的值
 * @param dwValueLen 值的长度
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @return 成功返回0，失败返回错误码
 */
int bytes_field_to_xml(const char* szFieldName, const char* szFieldValue, U32 dwValueLen, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    if (NULL == szFieldValue || 0 == dwValueLen)
    {
        SNPRINTF(szValue, sizeof(szValue), "%s<%s></%s>\n", szPrefix, szFieldName, szFieldName);
        return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
    }
    else
    {
        U32 i = 0;
        int iRet = 0;

        SNPRINTF(szValue, sizeof(szValue), "%s<%s>", szPrefix, szFieldName);
        CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

        for (i = 0; i < dwValueLen; i++)
        {
            SNPRINTF(szValue, sizeof(szValue), "%02x", (U8)szFieldValue[i]);
            CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
        }
        SNPRINTF(szValue, sizeof(szValue), "</%s>\n", szFieldName);
        CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
    }

    return 0;
}

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
int array_field_format(const char* szFieldName, void* pstField, U32 dwFieldSize, U16 nArrNum, LPBYTEARRAY pstByteArray, const char* szPrefix, FNARRAYFIELDFORMAT arrFieldFormatFunc)
{
	void* pstSubField;
	U16 i;
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == arrFieldFormatFunc) return ERROR_INPUT_PARAM_NULL;

	/* 数组子字段 */
	for (i = 0; i < nArrNum; i++)
	{
		pstSubField = (char*)pstField + dwFieldSize * i;

		CHECK_FUNC_RET(arrFieldFormatFunc(szFieldName, pstSubField, pstByteArray, szPrefix), iRet);
	}

	return 0;
}

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
int array_field_to_xml(const char* szFieldName, void* pstField, U32 dwFieldSize, U16 nArrNum, LPBYTEARRAY pstByteArray, const char* szPrefix, FNARRAYFIELDTOXML arrFieldToXmlFunc)
{
	void* pstSubField;
	U16 i;
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == arrFieldToXmlFunc) return ERROR_INPUT_PARAM_NULL;

	/* 数组子字段 */
	for (i = 0; i < nArrNum; i++)
	{
		pstSubField = (char*)pstField + dwFieldSize * i;

		CHECK_FUNC_RET(arrFieldToXmlFunc(szFieldName, pstSubField, pstByteArray, szPrefix), iRet);
	}

	return 0;
}
