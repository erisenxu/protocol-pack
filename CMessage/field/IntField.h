/*
 * @(#) IntField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef INT_FIELD_H
#define INT_FIELD_H

#include "Field.h"

/**
 * Int类型字段对象
 */
struct tagIntField
{
    FIELD stField;
    S32 iValue;
};

typedef struct tagIntField  INTFIELD;
typedef struct tagIntField* LPINTFIELD;

/**
 * Int字段信息定义
 */
extern FIELDINFO g_stIntFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstIntField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_int_field(LPINTFIELD pstIntField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstIntField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_int_field(LPINTFIELD pstIntField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, S32 iDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(INT_FIELD_H) */
