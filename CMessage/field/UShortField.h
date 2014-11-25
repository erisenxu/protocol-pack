/*
 * @(#) UShortField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef USHORT_FIELD_H
#define USHORT_FIELD_H

#include "Field.h"

/**
 * UShort类型字段对象
 */
struct tagUShortField
{
    FIELD stField;
    U16 nValue;
};

typedef struct tagUShortField  USHORTFIELD;
typedef struct tagUShortField* LPUSHORTFIELD;

/**
 * Short字段信息定义
 */
extern FIELDINFO g_stUShortFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstUShortField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_ushort_field(LPUSHORTFIELD pstUShortField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstUShortField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_ushort_field(LPUSHORTFIELD pstUShortField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, U16 nDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(USHORT_FIELD_H) */
