/*
 * @(#) UByteField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef UBYTE_FIELD_H
#define UBYTE_FIELD_H

#include "Field.h"

/**
 * Byte类型字段对象
 */
struct tagUByteField
{
    FIELD stField;
    U8 bValue;
};

typedef struct tagUByteField  UBYTETFIELD;
typedef struct tagUByteField* LPUBYTEFIELD;

/**
 * Byte字段信息定义
 */
extern FIELDINFO g_stUByteFieldInfo;

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
void construct_ubyte_field(LPUBYTEFIELD pstUByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstUByteField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_ubyte_field(LPUBYTEFIELD pstUByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, U8 bDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(UBYTE_FIELD_H) */
