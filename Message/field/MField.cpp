/*
 * @(#) MField.cpp Created on 2014-03-27
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

#include "MField.h"

#include "comm/MErrorCode.h"

/**
 * 整数byte字段编码
 * @param chValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(S8 chValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_BYTE).append(chValue);

    return 0;
}

/**
 * 字段解码
 * @param pchValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(S8* pchValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    S8 chValue;

    if (NULL == pchValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U8(chValue, pszValue);

    *pchValue = chValue;

    return 0;
}

/**
 * 整数unsigned byte字段编码
 * @param bValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(U8 bValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_UBYTE).append(bValue);

    return 0;
}

/**
 * 字段解码
 * @param pbValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(U8* pbValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    U8 bValue;

    if (NULL == pbValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U8(bValue, pszValue);

    *pbValue = bValue;

    return 0;
}

/**
 * 整数short字段编码
 * @param shValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(S16 shValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_SHORT).append(shValue);

    return 0;
}

/**
 * 字段解码
 * @param pshValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(S16* pshValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    S16 shValue;

    if (NULL == pshValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U16(shValue, pszValue);

    *pshValue = shValue;

    return 0;
}

/**
 * 整数unsigned short字段编码
 * @param nValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(U16 nValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_USHORT).append(nValue);

    return 0;
}

/**
 * 字段解码
 * @param pnValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(U16* pnValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    U16 nValue;

    if (NULL == pnValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U16(nValue, pszValue);

    *pnValue = nValue;

    return 0;
}

/**
 * 整数int字段编码
 * @param iValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(S32 iValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_INT).append(iValue);

    return 0;
}

/**
 * 字段解码
 * @param piValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(S32* piValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    S32 iValue;

    if (NULL == piValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U32(iValue, pszValue);

    *piValue = iValue;

    return 0;
}

/**
 * 整数unsigned int字段编码
 * @param dwValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(U32 dwValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_UINT).append(dwValue);

    return 0;
}

/**
 * 字段解码
 * @param pdwValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(U32* pdwValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    U32 dwValue;

    if (NULL == pdwValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U32(dwValue, pszValue);

    *pdwValue = dwValue;

    return 0;
}

/**
 * 整数long long字段编码
 * @param llValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(S64 llValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_LONG).append(llValue);

    return 0;
}

/**
 * 字段解码
 * @param pllValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(S64* pllValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    S64 llValue;

    if (NULL == pllValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U64(llValue, pszValue);

    *pllValue = llValue;

    return 0;
}

/**
 * 整数unsigned long long字段编码
 * @param ullValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(U64 ullValue, MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_ULONG).append(ullValue);

    return 0;
}

/**
 * 字段解码
 * @param pullValue 要解码的字段的值
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(U64* pullValue, const char* szBuf, int iBufLen)
{
    const char* pszValue;
    U64 ullValue;

    if (NULL == pullValue || NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;

    pszValue = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U64(ullValue, pszValue);

    *pullValue = ullValue;

    return 0;
}

/**
 * 整数byte字段编码
 * @param chValue 字段的值
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
int MField::encode(const char* szValue, MByteArray& baBuf, U16 nTag)
{
    U32 dwValLen;

    if (NULL == szValue) return M_ERROR_INPUT_PARAM_NULL;

    dwValLen = (U32)strlen(szValue);

    baBuf.append(nTag).append((U8)M_FIELD_TYPE_STRING);
    // 字符串长度
    baBuf.append(dwValLen);
    baBuf.append(szValue, dwValLen);

    return 0;
}

/**
 * 字段解码
 * @param pszValue 要解码的字段
 * @param dwBufSize 字段的最大长度
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MField::decode(char* pszValue, U32 dwBufSize, const char* szBuf, int iBufLen)
{
    U32 dwValueLen;
    const char* pszBuf;

    if (NULL == pszValue || NULL == szBuf || iBufLen <= 0) return M_ERROR_INPUT_PARAM_NULL;

    pszBuf = szBuf + sizeof(U16) + sizeof(U8);

    M_CHAR_TO_U32(dwValueLen, pszBuf);

    if (dwValueLen >= dwBufSize) return M_ERROR_DECODE_BUFSIZE_SHORT;

    memcpy(pszValue, pszBuf, dwValueLen);
    *(pszValue + dwValueLen) = 0;

    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param chValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, S8 chValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d(0x%x)", chValue, chValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param chValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, S8 chValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d", chValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param bValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, U8 bValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u(0x%x)", bValue, bValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param bValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, U8 bValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u", bValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param shValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, S16 shValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d(0x%x)", shValue, shValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param shValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, S16 shValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d", shValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param nValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, U16 nValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u(0x%x)", nValue, nValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param nValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, U16 nValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u", nValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param iValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, S32 iValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d(0x%x)", iValue, iValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param iValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, S32 iValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%d", iValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param dwValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, U32 dwValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u(0x%x)", dwValue, dwValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param dwValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, U32 dwValue, const string& sPrefix)
{
    char szValue[32];
    SNPRINTF(szValue, sizeof(szValue), "%u", dwValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param llValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, S64 llValue, const string& sPrefix)
{
    char szValue[64];
    SNPRINTF(szValue, sizeof(szValue), "%lld(0x%llx)", llValue, llValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param llValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, S64 llValue, const string& sPrefix)
{
    char szValue[64];
    SNPRINTF(szValue, sizeof(szValue), "%lld", llValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param ullValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, U64 ullValue, const string& sPrefix)
{
    char szValue[64];
    SNPRINTF(szValue, sizeof(szValue), "%llu(0x%llx)", ullValue, ullValue);

    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param ullValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, U64 ullValue, const string& sPrefix)
{
    char szValue[64];
    SNPRINTF(szValue, sizeof(szValue), "%llu", ullValue);

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param szValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::format(MByteArray& baBuf, const string& sFieldName, const char* szValue, const string& sPrefix)
{
    if (NULL == szValue) return;
    baBuf.append(sPrefix).append(sFieldName).append(" = ").append(szValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param szValue 字段的值
 * @param sPrefix 格式化字符串的前缀
 */
void MField::toXml(MByteArray& baBuf, const string& sFieldName, const char* szValue, const string& sPrefix)
{
    if (NULL == szValue) return;
    baBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(szValue).
        append("</").append(sFieldName).append(">\n");
}

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int MField::getLengthByType(U8 bType, const char* szBuf, int iBufLen)
{
    int iMinLen = sizeof(U16) + sizeof(U8);
    
    switch (bType)
    {
        case M_FIELD_TYPE_BYTE:
            return iMinLen + sizeof(S8);
        case M_FIELD_TYPE_SHORT:
            return iMinLen + sizeof(S16);
        case M_FIELD_TYPE_INT:
            return iMinLen + sizeof(S32);
        case M_FIELD_TYPE_LONG:
            return iMinLen + sizeof(S64);
        case M_FIELD_TYPE_UBYTE:
            return iMinLen + sizeof(U8);
        case M_FIELD_TYPE_USHORT:
            return iMinLen + sizeof(U16);
        case M_FIELD_TYPE_UINT:
            return iMinLen + sizeof(U32);
        case M_FIELD_TYPE_ULONG:
            return iMinLen + sizeof(U64);
        case M_FIELD_TYPE_STRING:
        case M_FIELD_TYPE_BYTES:
        case M_FIELD_TYPE_TLV:
        case M_FIELD_TYPE_ARRAY:
        {
            if (NULL != szBuf && iBufLen >= iMinLen + (int)sizeof(U32))
            {
                U32 nLen;
                const char* pszBuf = szBuf + iMinLen;
                M_CHAR_TO_U32(nLen, pszBuf);
                return iMinLen + sizeof(U32) + nLen;
            }
            return M_ERROR_DECODE_BUFSIZE_SHORT;
        }
        default:
            return M_ERROR_DECODE_INVALID_MSG;
    }
    //return iMinLen;
}

/**
 * 从消息中读取一个字节，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的字节
 */
U8 MField::readByte(const char* szBuf)
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
U16 MField::readShort(const char* szBuf)
{
    U16 bRet;
    
    M_CHAR_TO_U16(bRet, szBuf);
    
    return bRet;
}

/**
 * 从消息中读取一个int，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U32 MField::readInt(const char* szBuf)
{
    U32 bRet;

    M_CHAR_TO_U32(bRet, szBuf);

    return bRet;
}

