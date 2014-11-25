/*
 * @(#) UByteField.c Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "UByteField.h"

#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
static int ubyte_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
static int ubyte_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen);


/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int ubyte_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int ubyte_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
static void ubyte_field_set_value(LPFIELD pstField, const char* szValue);

/**
 * Byte字段信息定义
 */
FIELDINFO g_stUByteFieldInfo =
{
    (U8)FIELD_TYPE_BYTE,    /* type */
    NULL,                   /* construct */
    NULL,                   /* init */
    ubyte_field_encode,     /* encode */
    ubyte_field_decode,     /* decode */
    ubyte_field_format,     /* format */
    ubyte_field_to_xml,     /* toXml */
    NULL,                   /* getSubField */
    NULL,                   /* getSubFieldByName */
    ubyte_field_set_value   /* setValue */
};

/**
 * 字段初始化
 * @param pstUByteField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_ubyte_field(LPUBYTEFIELD pstUByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer)
{
    if (NULL == pstUByteField) return;

    init_field((LPFIELD)pstUByteField, &g_stUByteFieldInfo, szName, nTag, pstParent, nVer);
}

/**
 * 字段初始化
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_ubyte_field(LPUBYTEFIELD pstUByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, U8 bDefault)
{
    if (NULL == pstUByteField) return;

    construct_ubyte_field(pstUByteField, szName, nTag, pstParent, nVer);

    pstUByteField->bValue = bDefault;
}

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int ubyte_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
    int iRet;

    if (NULL == pstField || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstField->nTag), iRet);
    CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, pstField->pstFieldInfo->bType), iRet);
    CHECK_FUNC_RET(bytearray_append_s8(pstByteArray, ((LPUBYTEFIELD)pstField)->bValue), iRet);

    return 0;
}

/**
 * 字段解码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int ubyte_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen)
{
    U8 bValue;
    const char* pszBuf;

    if (NULL == pstField || NULL == szBuf || NULL == pstField->pstFieldInfo || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

    pszBuf = szBuf + sizeof(pstField->nTag) + sizeof(pstField->pstFieldInfo->bType);

    M_CHAR_TO_U8(bValue, pszBuf);

    ((LPUBYTEFIELD)pstField)->bValue = bValue;

    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int ubyte_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    snprintf(szValue, sizeof(szValue), "%s%s=%u(0x%x)\n", szPrefix, pstField->szName,
         ((LPUBYTEFIELD)pstField)->bValue, ((LPUBYTEFIELD)pstField)->bValue);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int ubyte_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    snprintf(szValue, sizeof(szValue), "%s<%s>%u</%s>\n", szPrefix, pstField->szName,
        ((LPUBYTEFIELD)pstField)->bValue, pstField->szName);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
void ubyte_field_set_value(LPFIELD pstField, const char* szValue)
{
    if (NULL == pstField) return;

    if (NULL == szValue)
    {
        ((LPUBYTEFIELD)pstField)->bValue = 0;
    }
    else
    {
        ((LPUBYTEFIELD)pstField)->bValue = (U8)atoi(szValue);
    }
}

