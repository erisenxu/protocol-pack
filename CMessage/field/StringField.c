/*
 * @(#) StringField.c Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "StringField.h"

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
static int string_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
static int string_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int string_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int string_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
static void string_field_set_value(LPFIELD pstField, const char* szValue);

/**
 * Int字段信息定义
 */
FIELDINFO g_stStringFieldInfo =
{
    (U8)FIELD_TYPE_STRING,  /* type */
    NULL,                   /* construct */
    NULL,                   /* init */
    string_field_encode,    /* encode */
    string_field_decode,    /* decode */
    string_field_format,    /* format */
    string_field_to_xml,    /* toXml */
    NULL,                   /* getSubField */
    NULL,                   /* getSubFieldByName */
    string_field_set_value  /* setValue */
};

/**
 * 字段初始化
 * @param pstStringField 要初始化的字段
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_string_field(LPSTRINGFIELD pstStringField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer,
                            char* szBuf, U16 nBufSize)
{
    if (NULL == pstStringField) return;

    init_field((LPFIELD)pstStringField, &g_stStringFieldInfo, szName, nTag, pstParent, nVer);

    pstStringField->stByteArray.dwSize = nBufSize;
    pstStringField->stByteArray.pszData = szBuf;
}

/**
 * 字段初始化
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_string_field(LPSTRINGFIELD pstStringField, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer,
                       char* szBuf, U16 nBufSize)
{
    if (NULL == pstStringField) return;

    construct_string_field(pstStringField, szName, nTag, pstParent, nVer, szBuf, nBufSize);

    pstStringField->stByteArray.dwLen = 0;
    //bytearray_append_string(&pstStringField->stByteArray, szDefault, nDefLen);
}

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int string_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
    int iRet;

    if (NULL == pstField || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstField->nTag), iRet);
    CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, pstField->pstFieldInfo->bType), iRet);

    // 字符串长度
    CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, ((LPSTRINGFIELD)pstField)->stByteArray.dwLen), iRet);
    CHECK_FUNC_RET(bytearray_append_string(pstByteArray, ((LPSTRINGFIELD)pstField)->stByteArray.pszData,
                                           ((LPSTRINGFIELD)pstField)->stByteArray.dwLen), iRet);

    return 0;
}

/**
 * 字段解码
 * @param pstField 要编码的字段
 * @param pstInitField 已初始化的字段，提供编码函数
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int string_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen)
{
    U32 nLen;
    int iRet;
    const char* pszBuf;

    if (NULL == pstField || NULL == szBuf || NULL == pstField->pstFieldInfo || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

    pszBuf = szBuf + sizeof(pstField->nTag) + sizeof(pstField->pstFieldInfo->bType);

    M_CHAR_TO_U32(nLen, pszBuf);

    ((LPSTRINGFIELD)pstField)->stByteArray.dwLen = 0;

    CHECK_FUNC_RET(bytearray_append_string(&(((LPSTRINGFIELD)pstField)->stByteArray), pszBuf, nLen), iRet);

    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int string_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];
    const char* szStr;

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    szStr = byte_array_to_string(&((LPSTRINGFIELD)pstField)->stByteArray);

    snprintf(szValue, sizeof(szValue), "%s%s=%s\n", szPrefix, pstField->szName,
         szStr == NULL ? "" : szStr);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int string_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];
    const char* szStr;

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    szStr = byte_array_to_string(&((LPSTRINGFIELD)pstField)->stByteArray);

    snprintf(szValue, sizeof(szValue), "%s<%s>%s</%s>\n", szPrefix, pstField->szName,
        szStr == NULL ? "" : szStr, pstField->szName);

    return bytearray_append_string(pstByteArray, szValue, strlen(szValue));
}

/**
 * 设置字段的值
 * @param szValue 字段的值
 */
void string_field_set_value(LPFIELD pstField, const char* szValue)
{
    if (NULL == pstField) return;

    bytearray_clear(&((LPSTRINGFIELD)pstField)->stByteArray);

    if (NULL != szValue)
    {
        bytearray_append_string(&((LPSTRINGFIELD)pstField)->stByteArray, szValue, strlen(szValue));
    }
}

