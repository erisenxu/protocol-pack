/*
 * @(#) ArrayField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef ARRAY_FIELD_H
#define ARRAY_FIELD_H

#include "Field.h"

/**
 * 数组类型字段对象
 */
struct tagArrayField
{
    FIELD stField;
    U16 nSize;                      /* 数组元素大小 */
    U16* pnNum;                     /* 数组数量 */
    U32 dwMaxNum;                   /* 数组最大数量 */
    char* pstSubField;              /* 数组元素指针 */
    LPFIELDINFO pstSubFieldInfo;    /* 子字段数据信息。若bType字段类型为数组，则需要指定数组子类型 */
};

typedef struct tagArrayField  ARRAYFIELD;
typedef struct tagArrayField* LPARRAYFIELD;

/**
 * Array字段信息定义
 */
extern FIELDINFO g_stArrayFieldInfo;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 字段结构体初始化
 * @param pstArrField 要初始化的字段
 * @param pstSubFieldInfo 数组元素字段信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_array_field(LPARRAYFIELD pstArrField, LPFIELDINFO pstSubFieldInfo, const char* szName,
                           U16 nTag, LPFIELD pstParent, U16 nVer, char* pstSubField, U16* pnFieldNum, U16 nSize, U32 dwMaxNum);

/**
 * 字段初始化
 * @param pstArrField 要初始化的字段
 * @param pstSubFieldInfo 数组元素字段信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_array_field(LPARRAYFIELD pstArrField, LPFIELDINFO pstSubFieldInfo, const char* szName,
                      U16 nTag, LPFIELD pstParent, U16 nVer, char* pstSubField, U16* pnFieldNum, U16 nSize, U32 dwMaxNum);

/**
 * 数组字段新增子字段
 * @param pstArrField 数组字段
 * @return 返回新增的子字段对象，如果增加不成功，返回NULL
 */
LPFIELD array_field_append_sub_field(LPARRAYFIELD pstArrField);

#ifdef __cplusplus
}
#endif

#endif /* defined(INT_FIELD_H) */
