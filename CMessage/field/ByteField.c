/*
 * @(#) ByteField.c Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "ByteField.h"

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
static int byte_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
static int byte_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int byte_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int byte_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
static void byte_field_set_value(LPFIELD pstField, const char* szValue);

/**
 * Byte字段信息定义
 */
FIELDINFO g_stByteFieldInfo =
{
    (U8)FIELD_TYPE_BYTE,    /* type */
    NULL,                   /* construct */
    NULL,                   /* init */
    byte_field_encode,      /* encode */
    byte_field_decode,      /* decode */
    byte_field_format,      /* format */
    byte_field_to_xml,      /* toXml */
    NULL,                   /* getSubField */
    NULL,                   /* getSubFieldByName */
    byte_field_set_value    /* setValue */
};

/**
 * 字段初始化
 * @param pstByteField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_byte_field(LPBYTEFIELD pstByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer)
{
    if (NULL == pstByteField) return;

    init_field((LPFIELD)pstByteField, &g_stByteFieldInfo, szName, nTag, pstParent, nVer);
}

/**
 * 字段初始化
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_byte_field(LPBYTEFIELD pstByteField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer, S8 chDefault)
{
    if (NULL == pstByteField) return;

    construct_byte_field(pstByteField, szName, nTag, pstParent, nVer);

    pstByteField->chValue = chDefault;
}

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int byte_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
    int iRet;

    if (NULL == pstField || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstField->nTag), iRet);
    CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, pstField->pstFieldInfo->bType), iRet);
    CHECK_FUNC_RET(bytearray_append_s8(pstByteArray, ((LPBYTEFIELD)pstField)->chValue), iRet);

    return 0;
}

/**
 * 字段解码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int byte_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen)
{
    S8 chValue;
    const char* pszBuf;

    if (NULL == pstField || NULL == szBuf || NULL == pstField->pstFieldInfo || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

    pszBuf = szBuf + sizeof(pstField->nTag) + sizeof(pstField->pstFieldInfo->bType);

    M_CHAR_TO_U8(chValue, pszBuf);

    ((LPBYTEFIELD)pstField)->chValue = chValue;

    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int byte_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    snprintf(szValue, sizeof(szValue), "%s%s=%d(0x%x)\n", szPrefix, pstField->szName,
         ((LPBYTEFIELD)pstField)->chValue, ((LPBYTEFIELD)pstField)->chValue);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int byte_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    snprintf(szValue, sizeof(szValue), "%s<%s>%d</%s>\n", szPrefix, pstField->szName,
        ((LPBYTEFIELD)pstField)->chValue, pstField->szName);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
void byte_field_set_value(LPFIELD pstField, const char* szValue)
{
    if (NULL == pstField) return;

    if (NULL == szValue)
    {
        ((LPBYTEFIELD)pstField)->chValue = 0;
    }
    else
    {
        ((LPBYTEFIELD)pstField)->chValue = (S8)atoi(szValue);
    }
}

