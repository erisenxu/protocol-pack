/*
 * @(#) MBaseFuncDef.h Created on 2014-03-27
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

#ifndef MBASE_FUNC_DEF_H
#define MBASE_FUNC_DEF_H

#include <stdio.h>

#define MAlloc(nSize)           malloc(nSize)
#define MFree(szBuf, nSize)     free(szBuf)

/**
 * 从缓冲区中读取4个字节数据到指定变量中
 * @param nValue 存放读取的数据的变量，类型：U64
 * @param pszBuf 源缓冲区指针变量，类型：char*
 */
#define M_CHAR_TO_U64(nValue, pszBuf) \
    nValue = ((U64)(*pszBuf++ & 0xFF) << 56); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 48); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 40); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 32); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 24); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 16); \
    nValue |= ((U64)(*pszBuf++ & 0xFF) << 8); \
    nValue |= (*pszBuf++ & 0xFF)

/**
 * 从缓冲区中读取4个字节数据到指定变量中
 * @param nValue 存放读取的数据的变量，类型：U32
 * @param pszBuf 源缓冲区指针变量，类型：char*
 */
#define M_CHAR_TO_U32(nValue, pszBuf) \
    nValue = ((*pszBuf++ & 0xFF) << 24); \
    nValue |= ((*pszBuf++ & 0xFF) << 16); \
    nValue |= ((*pszBuf++ & 0xFF) << 8); \
    nValue |= (*pszBuf++ & 0xFF)

/**
 * 从缓冲区中读取2个字节数据到指定变量中
 * @param nValue 存放读取的数据的变量，类型：U16
 * @param pszBuf 源缓冲区指针变量，类型：char*
 */
#define M_CHAR_TO_U16(nValue, pszBuf) \
    nValue = ((*pszBuf++ & 0xFF) << 8); \
    nValue |= (*pszBuf++ & 0xFF)

/**
 * 从缓冲区中读取1个字节数据到指定变量中
 * @param bValue 存放读取的数据的变量，类型：U8
 * @param pszBuf 源缓冲区指针变量，类型：char*
 */
#define M_CHAR_TO_U8(bValue, pszBuf) \
    bValue = (U8)(*pszBuf++)

/**
 * 写1个字节数据到缓冲区中
 * @param pszBuf 目标缓冲区指针变量，类型：char*
 * @param bValue 存放读取的数据的变量，类型：U8
 */
#define M_U8_TO_CHAR(pszBuf, bValue) \
    *pszBuf++ = (U8)(bValue)

/**
 * 写2个字节数据到缓冲区中
 * @param pszBuf 目标缓冲区指针变量，类型：char*
 * @param nValue 存放读取的数据的变量，类型：U16
 */
#define M_U16_TO_CHAR(pszBuf, nValue) \
    *pszBuf++ = (U8)(((nValue) >> 8) & 0xFF); \
    *pszBuf++ = (U8)((nValue) & 0xFF)

/**
 * 写4个字节数据到缓冲区中
 * @param pszBuf 目标缓冲区指针变量，类型：char*
 * @param dwValue 存放读取的数据的变量，类型：U32
 */
#define M_U32_TO_CHAR(pszBuf, dwValue) \
    *pszBuf++ = (U8)(((dwValue) >> 24) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 16) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 8) & 0xFF); \
    *pszBuf++ = (U8)((dwValue) & 0xFF)

/**
 * 写4个字节数据到缓冲区中
 * @param pszBuf 目标缓冲区指针变量，类型：char*
 * @param dwValue 存放读取的数据的变量，类型：U64
 */
#define M_U64_TO_CHAR(pszBuf, dwValue) \
    *pszBuf++ = (U8)(((dwValue) >> 56) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 48) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 40) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 32) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 24) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 16) & 0xFF); \
    *pszBuf++ = (U8)(((dwValue) >> 8) & 0xFF); \
    *pszBuf++ = (U8)((dwValue) & 0xFF)

#endif
