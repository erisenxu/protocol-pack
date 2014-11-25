/*
 * @(#) ByteField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef BYTE_FIELD_H
#define BYTE_FIELD_H

#include "Field.h"

/**
 * Byte类型字段对象
 */
struct tagByteField
{
    FIELD stField;
    S8 chValue;
};

typedef struct tagByteField  BYTETFIELD;
typedef struct tagByteField* LPBYTEFIELD;

/**
 * Byte字段信息定义
 */
extern FIELDINFO g_stByteFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstByteField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_byte_field(LPBYTEFIELD pstByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstByteField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_byte_field(LPBYTEFIELD pstByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, S8 chDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(BYTE_FIELD_H) */
