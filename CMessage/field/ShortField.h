/*
 * @(#) ShortField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef SHORT_FIELD_H
#define SHORT_FIELD_H

#include "Field.h"

/**
 * Short类型字段对象
 */
struct tagShortField
{
    FIELD stField;
    S16 nValue;
};

typedef struct tagShortField  SHORTFIELD;
typedef struct tagShortField* LPSHORTFIELD;

/**
 * Short字段信息定义
 */
extern FIELDINFO g_stShortFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段初始化
 * @param pstShortField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_short_field(LPSHORTFIELD pstShortField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer);

/**
 * 字段初始化
 * @param pstShortField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_short_field(LPSHORTFIELD pstShortField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, S16 nDefault);

#ifdef __cplusplus
}
#endif

#endif /* defined(SHORT_FIELD_H) */
