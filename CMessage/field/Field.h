/*
 * @(#) Field.h Created on 2014-03-27
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

/**
 * 检查字段版本，若高于指定版本，则返回0
 */
#define CHECK_FIELD_VER_RET(pstField, nVer) \
    if (nVer != 0 && pstField->nVer > nVer) return 0

/**
 * 检查字段版本，若高于指定版本，则返回
 */
#define CHECK_FIELD_VER(pstField, nVer) \
    if (nVer != 0 && pstField->nVer > nVer) return

#define M_TAG(nTag)         nTag
#define M_NAME(name)        name
#define M_VERSION(nVer)     nVer
#define M_DEFAULT(value)    value
#define M_PARENT(parent)    parent

#define MAX_FIELD_NAME_LEN  64
#define MAX_FIELD_INFO_LEN  256

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

typedef struct tagFieldInfo     FIELDINFO;
typedef struct tagFieldInfo*    LPFIELDINFO;

typedef struct tagField     FIELD;
typedef struct tagField*    LPFIELD;

/**
 * 对字段结构体初始化(不设置初始值)(用于一些复合字段的子字段初始化)
 * @param pstField 要初始化的字段
 */
typedef void (*LPFUNCFIELDSTRUCT)(LPFIELD pstField);

/**
 * 字段初始化(用于一些复合字段的子字段初始化)
 * @param pstField 要初始化的字段
 */
typedef void (*LPFUNCFIELDINIT)(LPFIELD pstField);

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
typedef int (*LPFUNCFIELDENCODE)(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
typedef int (*LPFUNCFIELDDECODE)(LPFIELD pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
typedef int (*LPFUNCFIELDFORMAT)(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
typedef int (*LPFUNCFIELDTOXML)(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 通过字段标签查找字段
 * @param nTag 字段标签
 * @return 返回与字段标签对应的字段对象
 */
typedef LPFIELD (*LPFUNCFIELDGETSUBFIELD)(LPFIELD pstField, U16 nTag);

/**
 * 通过字段名字查找字段
 * @param szName 字段名字
 * @return 返回与字段名字对应的字段对象
 */
typedef LPFIELD (*LPFUNCFIELDGETSUBFIELDBYNAME)(LPFIELD pstField, const char* szName);

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
typedef void (*LPFUNCFIELDSETVALUE)(LPFIELD pstField, const char* szValue);

/**
 * 字段信息
 */
struct tagFieldInfo
{
    U8 bType;                                       /* 字段数据类型，见FIELD_TYPE_*系列 */
    LPFUNCFIELDSTRUCT construct;                    /* 初始化复合字段的子字段(仅初始化信息不设置初始值) */
    LPFUNCFIELDINIT init;                           /* 初始化复合字段的子字段(初始化信息并设置初始值) */
    LPFUNCFIELDENCODE encode;                       /* 字段编码 */
    LPFUNCFIELDDECODE decode;                       /* 字段解码 */
    LPFUNCFIELDFORMAT format;                       /* 字段格式化 */
    LPFUNCFIELDTOXML toXml;                         /* 字段输出成xml格式 */
    LPFUNCFIELDGETSUBFIELD getSubField;             /* 通过字段标签查找字段 */
    LPFUNCFIELDGETSUBFIELDBYNAME getSubFieldByName; /* 通过字段名字查找字段 */
    LPFUNCFIELDSETVALUE setValue;                   /* 设置字段的值 */
};

/**
 * 字段对象
 */
struct tagField
{
    LPFIELDINFO pstFieldInfo;           /* 字段信息对象 */
    LPFIELD pstParent;                  /* 字段的父字段 */
    char szName[MAX_FIELD_NAME_LEN];    /* 字段名字 */
    U16 nTag;                           /* 字段标签，表明它是什么字段 */
    U16 nVer;                           /* 字段引入版本。注：字段版本其实可以不用，因本协议可以向下、向上兼容。*/
                                        /* 但是可以将高版本的字段在低版本的协议中裁剪掉，以减少包的大小及提升打包解包时间 */
};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段结构初始化
 * @param pstField 要初始化的字段
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param pstParent 字段的父字段
 * @param nVer 字段引人版本号
 */
void init_field_struct(LPFIELD pstField, LPFIELDINFO pstFieldInfo, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstField 要初始化的字段
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_field(LPFIELD pstField, LPFIELDINFO pstFieldInfo, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int get_length_by_type(U8 bType, const char* szBuf, int iBufLen);

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int field_encode(void* pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int field_decode(void* pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int field_format(void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int field_toxml(void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 复合字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int composite_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen);

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
 * @return 返回读取的short
 */
U32 read_int(const char* szBuf);

#ifdef __cplusplus
}
#endif

#endif /* defined(FIELD_H) */
