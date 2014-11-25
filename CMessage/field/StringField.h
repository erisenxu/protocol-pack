/*
 * @(#) StringField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef STRING_FIELD_H
#define STRING_FIELD_H

#include "Field.h"

/**
 * 字符串或字节数组类型字段对象
 */
struct tagStringField
{
    FIELD stField;
    BYTEARRAY stByteArray;
};

typedef struct tagStringField  STRINGFIELD;
typedef struct tagStringField* LPSTRINGFIELD;

/**
 * 字符串或字节数组字段信息定义
 */
extern FIELDINFO g_stStringFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstStringField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_string_field(LPSTRINGFIELD pstStringField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer,
                            char* szBuf, U16 nBufSize);

/**
 * 字段初始化
 * @param pstStringField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_string_field(LPSTRINGFIELD pstStringField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer,
                       char* szBuf, U16 nBufSize);

#ifdef __cplusplus
}
#endif

#endif /* defined(STRING_FIELD_H) */
