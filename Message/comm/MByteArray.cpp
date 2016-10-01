/**
 * @(#) MByteArray.cpp 字节数组对象，一般用于消息编码解码
 *
 * Copyright (c) 2010-2016 Erisen Xu (@itfriday)
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
 *
 * @author Erisen Xu
 * @version 1.0
 * @history 2010-12-19 ErisenXu 创建文件
 */

#include "MByteArray.h"
#include "MBaseFuncDef.h"

#include <stdlib.h>
#include <string.h>

/**
 * 构造函数
 * @param nSize 数组预分配大小
 */
MByteArray::MByteArray(int nSize)
    : m_nLen(0)
{
    m_nSize = nSize <= 0 ? 32 : nSize;
    m_szData = (char*)MAlloc(m_nSize);
}

/**
 * 构造函数
 * @param szValue 添加到数组的字符串，字符串需以'\0'结尾
 */
MByteArray::MByteArray(const char* szValue)
{
    m_nLen = szValue ? (int)strlen(szValue) : 0;
    m_nSize = m_nLen + 32;
    m_szData = (char*)MAlloc(m_nSize);
    if (m_nLen > 0) memcpy(m_szData, szValue, m_nLen);
}

/**
 * 构造函数
 * @param szValue 添加到数组的byte字符串
 * @param nLen 字符长度
 */
MByteArray::MByteArray(const char* szValue, int nLen)
{
    m_nLen = nLen;
    m_nSize = m_nLen + 32;
    m_szData = (char*)MAlloc(m_nSize);
    if (m_nLen > 0) memcpy(m_szData, szValue, m_nLen);
}

/**
 * 拷贝构造函数
 */
MByteArray::MByteArray(const MByteArray& baValue)
{
    m_nLen = baValue.m_nLen;
    m_nSize = m_nLen + 32;
    m_szData = (char*)MAlloc(m_nSize);
    if (m_nLen > 0) memcpy(m_szData, baValue.getData(), m_nLen);
}

/**
 * 析构函数
 */
MByteArray::~MByteArray()
{
    MFree(m_szData, m_nSize);
}

/**
 * 将字符添加到数组
 * @param nVal 要添加到数组的字符
 */
MByteArray& MByteArray::append(U8 nVal)
{
    char* s_ptr;

    expand(1);

    s_ptr = m_szData + m_nLen;

    M_U8_TO_CHAR(s_ptr, nVal);

    m_nLen++;

    return *this;
}

/**
 * 将整数添加到数组
 * @param nVal 要添加到数组的整数
 */
MByteArray& MByteArray::append(U16 nVal)
{
    char* s_ptr;

    expand(2);

    s_ptr = m_szData + m_nLen;

    M_U16_TO_CHAR(s_ptr, nVal);

    m_nLen += 2;

    return *this;
}

/**
 * 将整数添加到数组
 * @param nVal 要添加到数组的整数
 */
MByteArray& MByteArray::append(U32 nVal)
{
    char* s_ptr;

    expand(4);

    s_ptr = m_szData + m_nLen;

    M_U32_TO_CHAR(s_ptr, nVal);

    m_nLen += 4;

    return *this;
}

/**
 * 将整数添加到数组
 * @param ulVal 要添加到数组的整数
 */
MByteArray& MByteArray::append(U64 ulVal)
{
    char* s_ptr;

    expand(8);

    s_ptr = m_szData + m_nLen;

    M_U64_TO_CHAR(s_ptr, ulVal);

    m_nLen += 8;

    return *this;
}

/**
 * 将字符串添加到数组，字符串需以'\0'结尾
 * @param szVal 要添加到数组的字符串
 */
//MByteArray& MByteArray::Append(const char* szVal)
//{
//    // 如果字符串为空，直接返回
//    if (!szVal || !(*szVal))
//    {
//        return *this;
//    }
//    char* s_ptr;
//    int nLen = (int)strlen(szVal);
//
//    Expand(nLen);
//
//    s_ptr = m_szData + m_nLen;
//
//    memcpy(s_ptr, szVal, nLen);
//
//    m_nLen += nLen;
//
//    return *this;
//}

/**
 * 将字符串添加到数组
 * @param szVal 要添加到数组的字符串
 * @param nLen 字符串长度
 */
MByteArray& MByteArray::append(const char* szVal, int nLen)
{
    // 如果字符串为空，直接返回
    if (nLen <= 0)
    {
        return *this;
    }
    char* s_ptr;

    expand(nLen);

    s_ptr = m_szData + m_nLen;

    memcpy(s_ptr, szVal, nLen);

    m_nLen += nLen;

    return *this;
}

/**
 * 扩充缓冲区大小
 * @param nSize 需要增加的缓冲区大小
 */
void MByteArray::expand(int nSize)
{
    if (nSize <= 0)
    {
        return;
    }

    if (m_nLen + nSize < m_nSize) return;

    int nNewSize = m_nSize + nSize;
    char* szTmp = m_szData;

    // 重新分配内存，并复制数据
    m_szData = (char*)MAlloc(nNewSize);
    memcpy(m_szData, szTmp, m_nLen);

    // 释放原来的数据的内存
    MFree(szTmp, m_nSize);

    m_nSize = nNewSize;
}

/**
 * 清空所有数据
 */
void MByteArray::clear()
{
    m_nLen = 0;
}

/**
 * 返回字符串
 * @return 返回字符串
 */
const char* MByteArray::toString()
{
    if (*(m_szData + m_nLen))
    {
        expand(1);
        *(m_szData + m_nLen) = 0;
    }
    return m_szData;
}

/**
 * 将字节数组转换成供打印的十六进制字符串
 *
 * @param baBuf 用来保存数据的数组
 * @param szBytes 要打印的字节数组
 * @param nBufLen 字节数组szBytes的总长度
 * @param nOffset 要打印的数组的起始字节索引
 * @param nLength 要打印的数组中字节的总长度，若nLength=-1，则转换所有字节
 * @param nColumn 每行打印的列数
 */
void MByteArray::bytesToPrintable(MByteArray& baBuf, const char* szBytes,
                                  int nBufLen, int nOffset, int nLength, int nColumn)
{
    const char* szHexDigits = "0123456789abcdef";

    MByteArray baText(1024);
    int nEnd = nLength < 0 ? nOffset + nBufLen : nOffset + nLength;
    int nCols = 0;
    int nHalf;
    int i;
    int j;

    if (nEnd > nBufLen)
    {
        nEnd = nBufLen;
    }

    if (nColumn <= 0)
    {
        nColumn = 8;
    }

    if (nColumn%2 != 0)
    {
        nColumn++;
    }

    nHalf = nColumn/2;

    baBuf.append("0000   ");

    for (i = nOffset, j = 0; i < nEnd; i++, j++)
    {
        baBuf.append((U8)(szHexDigits[(szBytes[i] >> 4) & 0xF])).
            append((U8)(szHexDigits[szBytes[i] & 0xF])).
            append(" ");

        if (szBytes[i] >= 32 && szBytes[i] < 127)
        {
            baText.append((U8)szBytes[i]);
        }
        else
        {
            baText.append((U8)'.');
        }

        if ((j + 1)%nColumn == 0)
        {
            baBuf.append("  ").append(baText.getData(), baText.getLength()).
                append((U8)'\n');

            nCols += nColumn;
            baBuf.append((U8)(szHexDigits[(nCols >> 12) & 0xF])).
                append((U8)(szHexDigits[(nCols >> 8) & 0xF])).
                append((U8)(szHexDigits[(nCols >> 4) & 0xF])).
                append((U8)(szHexDigits[nCols & 0xF])).
                append("   ");
            // 清空baText
            baText.clear();
            continue;
        }

        if ((j + 1)%nHalf == 0)
        {
            baBuf.append((U8)' ');
            baText.append((U8)' ');
        }
    }

    // 检查baText中是否还有数据?
    if (baText.getLength() > 0)
    {
        int nNum = j%nColumn;
        int nSpaces;

        if (nNum < nHalf)
        {
            nSpaces = (nColumn - nNum)*3 + 3;
        }
        else
        {
            nSpaces = (nColumn - nNum)*3 + 2;
        }
        for (i = 0; i < nSpaces; i++)
        {
            baBuf.append((U8)' ');
        }
        baBuf.append(baText.getData(), baText.getLength());
    }

    // 最后将字节数组变成字符串
    baBuf.append((U8)0);
}

/**
 * 将字节数组转成字符串，不可见字符以.表示
 * @param baBuf 用来保存数据的数组
 * @param szBytes 要打印的字节数组
 * @param nBufLen 字节数组szBytes的总长度
 * @param nOffset 要打印的数组的起始字节索引
 * @param nLength 要打印的数组中字节的总长度，若nLength=-1，则转换所有字节
 */
void MByteArray::bytesToStr(MByteArray& baBuf, const char* szBytes,
                            int nBufLen, int nOffset, int nLength)
{
    int nEnd = nLength < 0 ? nOffset + nBufLen : nOffset + nLength;

    if (nEnd > nBufLen) nEnd = nBufLen;

    for (int i = nOffset; i < nEnd; i++)
    {
        if (szBytes[i] >= 32 && szBytes[i] < 127)
        {
            baBuf.append((U8)szBytes[i]);
        }
        else
        {
            baBuf.append((U8)'.');
        }
    }
    // 最后将字节数组变成字符串
    baBuf.append((U8)0);
}

/**
 * 将字节数组转换成十六进制字符串
 * @param baBuf 用来保存转换后的数据的数组
 * @param szBytes 被转换的字节数组
 * @param nBufLen 字节数组长度
 * @param nOffset 数组的起始字节索引
 */
void MByteArray::bytesToHexStr(MByteArray& baBuf, const char* szBytes, int nBufLen, int nOffset)
{
    if (!szBytes || nBufLen <= 0) return;

    const char* szHexDigits = "0123456789abcdef";

    for (int i = nOffset; i < nBufLen; i++)
    {
        baBuf.append((U8)szHexDigits[(szBytes[i] >> 4) & 0xF]);
        baBuf.append((U8)szHexDigits[szBytes[i] & 0xF]);
    }

    // 最后将字节数组变成字符串
    baBuf.append((U8)0);
}

/**
 * 将十六进制字符串转换成字节数组
 * @param baBuf 用来保存转换后的数据的数组
 * @param szHexStr 被转换的十六进制字符串数据
 */
void MByteArray::hexStrToBytes(MByteArray& baBuf, const char* szHexStr)
{
    if (!szHexStr || !(*szHexStr)) return;

    size_t nLen = strlen(szHexStr);
    char chHi; // 高位
    char chLo; // 低位
    const char* szBuf = szHexStr;

    if (nLen % 2 != 0)
    {
        baBuf.append((U8)hexCharToInt(*szBuf++));
    }

    while (*szBuf)
    {
        chHi = *szBuf++;
        chLo = *szBuf++;
        baBuf.append((U8)((hexCharToInt(chHi) << 4) | hexCharToInt(chLo)));
    }
}

/**
 * 将十六进制字符转换成整数
 * @param chHex 被转换的十六进制字符
 */
U8 MByteArray::hexCharToInt(char chHex)
{
    switch (chHex)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return chHex - '0';
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
        return chHex - 'a' + 10;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
        return chHex - 'A' + 10;
    default:
        return 0;
    }
}
