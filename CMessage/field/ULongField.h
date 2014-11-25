/*
 * @(#) ULongField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef ULONG_FIELD_H
#define ULONG_FIELD_H

#include "Field.h"

/**
 * Long类型字段对象
 */
struct tagULongField
{
    FIELD stField;
    U64 ullValue;
};

typedef struct tagULongField  ULONGFIELD;
typedef struct tagULongField* LPULONGFIELD;

/**
 * Long字段信息定义
 */
extern FIELDINFO g_stULongFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstULongField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_ulong_field(LPULONGFIELD pstULongField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstULongField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_ulong_field(LPULONGFIELD pstULongField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, U64 ullDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(LONG_FIELD_H) */
