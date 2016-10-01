/*
 * @(#) MField.h Created on 2014-03-27
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

#ifndef MFIELD_H
#define MFIELD_H

#include "comm/MByteArray.h"
#include "comm/MBaseFuncDef.h"

#include <stdlib.h>

enum MFieldDataType
{
    M_FIELD_TYPE_INVALID = 0, // 不合法(未初始化)的字段类型
    M_FIELD_TYPE_BYTE = 1,    // S8，占1个字节
    M_FIELD_TYPE_UBYTE = 2,   // U8，占1个字节
    M_FIELD_TYPE_SHORT = 3,   // S16，占2个字节
    M_FIELD_TYPE_USHORT = 4,  // U16，占2个字节
    M_FIELD_TYPE_INT = 5,     // S32，占4个字节
    M_FIELD_TYPE_UINT = 6,    // U32，占4个字节
    M_FIELD_TYPE_LONG = 7,    // S64，占8个字节
    M_FIELD_TYPE_ULONG = 8,   // U64，占8个字节
    M_FIELD_TYPE_STRING = 9,  // 字符串，特殊的TLV字段
    M_FIELD_TYPE_BYTES = 10,  // 字节数组，特殊的TLV字段
    M_FIELD_TYPE_TLV = 11,    // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
    M_FIELD_TYPE_ARRAY = 12   // 数组
};

/**
 * <code>MField</code>协议字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MField
{
public:

    /**
     * 取某个类型字段的长度
     * @param bType 字段类型
     * @param szBuf 要解析的协议，里面可能包含长度字段
     * @param iBufLen 协议的长度
     * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
     */
    static int getLengthByType(U8 bType, const char* szBuf, int iBufLen);

    /**
     * 整数byte字段编码
     * @param chValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(S8 chValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pchValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(S8* pchValue, const char* szBuf, int iBufLen);

    /**
     * 整数unsigned byte字段编码
     * @param bValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(U8 bValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pbValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(U8* pbValue, const char* szBuf, int iBufLen);

    /**
     * 整数short字段编码
     * @param shValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(S16 shValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pshValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(S16* pshValue, const char* szBuf, int iBufLen);

    /**
     * 整数unsigned short字段编码
     * @param nValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(U16 nValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pnValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(U16* pnValue, const char* szBuf, int iBufLen);

    /**
     * 整数int字段编码
     * @param iValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(S32 iValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param piValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(S32* piValue, const char* szBuf, int iBufLen);

    /**
     * 整数unsigned int字段编码
     * @param dwValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(U32 dwValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pdwValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(U32* pdwValue, const char* szBuf, int iBufLen);

    /**
     * 整数long long字段编码
     * @param llValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(S64 llValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pllValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(S64* pllValue, const char* szBuf, int iBufLen);

    /**
     * 整数unsigned long long字段编码
     * @param ullValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(U64 ullValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pullValue 要解码的字段的值
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(U64* pullValue, const char* szBuf, int iBufLen);

    /**
     * 整数byte字段编码
     * @param chValue 字段的值
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段的tag
     * @return 成功返回0，失败返回错误码
     */
    static int encode(const char* szValue, MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param pszValue 要解码的字段
     * @param dwBufSize 字段的最大长度
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    static int decode(char* pszValue, U32 dwBufSize, const char* szBuf, int iBufLen);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param chValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, S8 chValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param chValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, S8 chValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param bValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, U8 bValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param bValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, U8 bValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param shValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, S16 shValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param shValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, S16 shValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param nValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, U16 nValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param nValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, U16 nValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param iValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, S32 iValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param iValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, S32 iValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param dwValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, U32 dwValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param dwValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, U32 dwValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param llValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, S64 llValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param llValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, S64 llValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param ullValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, U64 ullValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param ullValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, U64 ullValue, const string& sPrefix);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param szValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void format(MByteArray& baBuf, const string& sFieldName, const char* szValue, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param szValue 字段的值
     * @param sPrefix 格式化字符串的前缀
     */
    static void toXml(MByteArray& baBuf, const string& sFieldName, const char* szValue, const string& sPrefix);

    /**
     * 从消息中读取一个字节，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的字节
     */
    static U8 readByte(const char* szBuf);

    /**
     * 从消息中读取一个short，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的short
     */
    static U16 readShort(const char* szBuf);

    /**
     * 从消息中读取一个int，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的short
     */
    static U32 readInt(const char* szBuf);
};

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段标签
 * @return 成功返回0，失败返回错误码
 */
#define M_ARRAY_FIELD_ENCODE(baBuf, nTag, nArrNum, fnGetFieldByIndex) \
    do \
    { \
        /* 编码Tag及Type */ \
        baBuf.append((U16)nTag).append((U8)M_FIELD_TYPE_ARRAY); \
        /* 先将数组长度设置为0 */ \
        baBuf.append((U32)0); \
        /* 记录下当前数组长度 */ \
        int iArrOldLen = baBuf.getLength(); \
        /* 对数组进行编码 */ \
        /* 数组数量 */ \
        baBuf.append((U16)nArrNum); \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            fnGetFieldByIndex(i).encode(baBuf, nTag); \
        } \
        /* 修正数组长度 */ \
        /* 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变 */ \
        U32 nArrAddLen = (U32)(baBuf.getLength() - iArrOldLen); \
        char* pszMsg = baBuf.getData() + (baBuf.getLength() - nArrAddLen - sizeof(U32)); \
        M_U32_TO_CHAR(pszMsg, nArrAddLen); \
    } while (0)

/**
 * 数组字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param nMaxNum 数组的最大长度
 * @param fnGetFieldByIndex 解码数组元素字段的函数
 * @return 成功返回0，失败返回错误码
 */
#define M_ARRAY_FIELD_DECODE(szBuf, iBufLen, nMaxNum, fnGetFieldByIndex) \
    do \
    { \
        int iHdrLen; \
        const char* pszArray; \
        U16 nArrayNum = 0; \
        int iLeftLen; \
        int iRet = -1; \
        int iMsgLen = 0; \
        U16 i; \
        U8 bType; \
        if (NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL; \
        iHdrLen = sizeof(U16) + sizeof(U8) + sizeof(U32); \
        pszArray = szBuf + iHdrLen; \
        iLeftLen = iBufLen - iHdrLen; \
        /* 数组长度 */ \
        M_CHAR_TO_U16(nArrayNum, pszArray); \
        iLeftLen -= sizeof(nArrayNum); \
        /* 数组长度超过了最大值的处理 */ \
        if (nArrayNum > nMaxNum) return M_ERROR_DECODE_ARRAY_LONG; \
        /* 数组元素类型 */ \
        bType = *(pszArray + sizeof(U16)); \
        /* 解析子字段 */ \
        for (i = 0; i < nArrayNum; i++) \
        { \
            /* 通过类型获得数据长度 */ \
            iMsgLen = MField::getLengthByType(bType, pszArray, iLeftLen); \
            if (iLeftLen < iMsgLen) \
            { \
                return M_ERROR_DECODE_BUFSIZE_SHORT; \
            } \
            iRet = fnGetFieldByIndex(i).decode(pszArray, iLeftLen); \
            if (iRet != 0) return iRet; \
            pszArray += iMsgLen; \
            iLeftLen -= iMsgLen; \
        } \
        return 0; \
    } while(0)

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段标签
 * @return 成功返回0，失败返回错误码
 */
#define M_ARRAY_ENCODE(baBuf, nTag, nArrNum, arrfield) \
    do \
    { \
        /* 编码Tag及Type */ \
        baBuf.append((U16)nTag).append((U8)M_FIELD_TYPE_ARRAY); \
        /* 先将数组长度设置为0 */ \
        baBuf.append((U32)0); \
        /* 记录下当前数组长度 */ \
        int iArrOldLen = baBuf.getLength(); \
        /* 对数组进行编码 */ \
        /* 数组数量 */ \
        baBuf.append((U16)nArrNum); \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            MField::encode(arrfield[i], baBuf, nTag); \
        } \
        /* 修正数组长度 */ \
        /* 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变 */ \
        U32 nArrAddLen = (U32)(baBuf.getLength() - iArrOldLen); \
        char* pszMsg = baBuf.getData() + (baBuf.getLength() - nArrAddLen - sizeof(U32)); \
        M_U32_TO_CHAR(pszMsg, nArrAddLen); \
    } while (0)

/**
 * 数组字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @param nMaxNum 数组的最大长度
 * @param arrfield 解码数组元素字段的函数
 * @return 成功返回0，失败返回错误码
 */
#define M_ARRAY_DECODE(szBuf, iBufLen, nMaxNum, arrfield) \
    do \
    { \
        int iHdrLen; \
        const char* pszArray; \
        U16 nArrayNum = 0; \
        int iLeftLen; \
        int iRet = -1; \
        int iMsgLen = 0; \
        U16 i; \
        U8 bType; \
        if (NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL; \
        iHdrLen = sizeof(U16) + sizeof(U8) + sizeof(U32); \
        pszArray = szBuf + iHdrLen; \
        iLeftLen = iBufLen - iHdrLen; \
        /* 数组长度 */ \
        M_CHAR_TO_U16(nArrayNum, pszArray); \
        iLeftLen -= sizeof(nArrayNum); \
        /* 数组长度超过了最大值的处理 */ \
        if (nArrayNum > nMaxNum) return M_ERROR_DECODE_ARRAY_LONG; \
        /* 数组元素类型 */ \
        bType = *(pszArray + sizeof(U16)); \
        /* 解析子字段 */ \
        for (i = 0; i < nArrayNum; i++) \
        { \
            /* 通过类型获得数据长度 */ \
            iMsgLen = MField::getLengthByType(bType, pszArray, iLeftLen); \
            if (iLeftLen < iMsgLen) \
            { \
                return M_ERROR_DECODE_BUFSIZE_SHORT; \
            } \
            iRet = MField::decode(&arrfield[i], pszArray, iLeftLen); \
            if (iRet != 0) return iRet; \
            pszArray += iMsgLen; \
            iLeftLen -= iMsgLen; \
        } \
        return 0; \
    } while(0)

/**
 * 格式化成可读形式
 * @param baBuf 保存字段格式化后的信息
 * @param sFieldName 字段名称
 */
#define M_ARRAY_FIELD_FORMAT(baBuf, sFieldName, nArrNum, fnGetFieldByIndex, sPrefix) \
    do \
    { \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            fnGetFieldByIndex(i).format(baBuf, sFieldName, sPrefix); \
        } \
    } while (0)

/**
 * 格式化成可读形式
 * @param baBuf 保存字段格式化后的信息
 * @param sFieldName 字段名称
 */
#define M_ARRAY_FORMAT(baBuf, sFieldName, nArrNum, arrfield, sPrefix) \
    do \
    { \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            MField::format(baBuf, sFieldName, arrfield[i], sPrefix); \
        } \
    } while (0)

/**
 * 格式化成XML形式
 * @param baBuf 保存字段格式化后的信息
 * @param sFieldName 字段名称
 */
#define M_ARRAY_FIELD_TOXML(baBuf, sFieldName, nArrNum, fnGetFieldByIndex, sPrefix) \
    do \
    { \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            fnGetFieldByIndex(i).toXml(baBuf, sFieldName, sPrefix); \
        } \
    } while (0)

/**
 * 格式化成XML形式
 * @param baBuf 保存字段格式化后的信息
 * @param sFieldName 字段名称
 */
#define M_ARRAY_TOXML(baBuf, sFieldName, nArrNum, arrfield, sPrefix) \
    do \
    { \
        /* 数组子字段 */ \
        for (U16 i = 0; i < nArrNum; i++) { \
            MField::toXml(baBuf, sFieldName, arrfield[i], sPrefix); \
        } \
    } while (0)

/**
 * 复合字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
#define M_FIELD_DECODE(szBuf, iBufLen) \
    do \
    { \
        int iMinLen;    /* 字段最小长度 */ \
        U16 nTag = 0; \
        U8 bType = 0; \
        const char* pszBuf; \
        int iLeftLen; \
        int iFieldLen; \
        int iRet = -1; \
        if (NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL; \
        iMinLen = sizeof(U16) + sizeof(U8);    /* 字段最小长度 */ \
        pszBuf = szBuf + iMinLen + sizeof(U32); \
        iLeftLen = iBufLen - iMinLen - sizeof(U32); \
        if (iLeftLen < 0) \
        { \
            return M_ERROR_DECODE_BUFSIZE_SHORT; \
        } \
        /* 求字段长度 */ \
        iLeftLen = MField::readInt(szBuf + iMinLen); \
        while (iLeftLen > 0) \
        { \
            /* 解析Tag和Type */ \
            if (iLeftLen < iMinLen) \
            { \
                return M_ERROR_DECODE_BUFSIZE_SHORT; \
            } \
            /* Tag和类型 */ \
            nTag = MField::readShort(pszBuf); \
            bType = MField::readByte(pszBuf + sizeof(nTag)); \
            /* 消息长度 */ \
            iFieldLen = MField::getLengthByType(bType, pszBuf, iLeftLen); \
            if (iFieldLen == M_ERROR_DECODE_BUFSIZE_SHORT || iLeftLen < iFieldLen) \
            { \
                return M_ERROR_DECODE_BUFSIZE_SHORT; \
            } \
            /* 取消息对象 */ \
            iRet = decodeSubField(pszBuf, iLeftLen, nTag); \
            /* 对认识的字段进行解码，不认识的字段直接丢弃 */ \
            if (iRet != 0) return iRet; \
            /* 不认识的字段，直接丢弃 (兼容旧版本) */ \
            pszBuf += iFieldLen; \
            iLeftLen -= iFieldLen; \
        } \
        return 0; \
    } while (0)

#endif /* defined(MFIELD_H) */
