/*
 * @(#) LongField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef LONG_FIELD_H
#define LONG_FIELD_H

#include "Field.h"

/**
 * Long类型字段对象
 */
struct tagLongField
{
    FIELD stField;
    S64 llValue;
};

typedef struct tagLongField  LONGFIELD;
typedef struct tagLongField* LPLONGFIELD;

/**
 * Long字段信息定义
 */
extern FIELDINFO g_stLongFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstLongField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_long_field(LPLONGFIELD pstLongField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstLongField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_long_field(LPLONGFIELD pstLongField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, S64 llDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(LONG_FIELD_H) */
