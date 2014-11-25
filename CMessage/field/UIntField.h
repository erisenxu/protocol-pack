/*
 * @(#) UIntField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef UINT_FIELD_H
#define UINT_FIELD_H

#include "Field.h"

/**
 * UInt类型字段对象
 */
struct tagUIntField
{
    FIELD stField;
    U32 dwValue;
};

typedef struct tagUIntField  UINTFIELD;
typedef struct tagUIntField* LPUINTFIELD;

/**
 * UInt字段信息定义
 */
extern FIELDINFO g_stUIntFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstUIntField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_uint_field(LPUINTFIELD pstUIntField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstUIntField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_uint_field(LPUINTFIELD pstUIntField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, U32 dwDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(UINT_FIELD_H) */
