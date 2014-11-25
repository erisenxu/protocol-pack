/*
 * @(#) ArrayField.c Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "ArrayField.h"

#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
static int array_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
static int array_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen);

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int array_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
static int array_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

/**
 * Array字段信息定义
 */
FIELDINFO g_stArrayFieldInfo =
{
    (U8)FIELD_TYPE_ARRAY,  /* type */
    NULL,                  /* construct */
    NULL,                  /* init */
    array_field_encode,    /* encode */
    array_field_decode,    /* decode */
    array_field_format,    /* format */
    array_field_to_xml,    /* toXml */
    NULL,                  /* getSubField */
    NULL,                  /* getSubFieldByName */
    NULL                   /* setValue */
};

/**
 * 字段结构体初始化
 * @param pstArrField 要初始化的字段
 * @param pstSubFieldInfo 数组元素字段信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void construct_array_field(LPARRAYFIELD pstArrField, LPFIELDINFO pstSubFieldInfo, const char* szName,
                           U16 nTag, LPFIELD pstParent, U16 nVer, char* pstSubField, U16* pnFieldNum, U16 nSize, U32 dwMaxNum)
{
    if (NULL == pstArrField || NULL == pstSubFieldInfo || NULL == pstSubField || NULL == pnFieldNum) return;

    init_field((LPFIELD)pstArrField, &g_stArrayFieldInfo, szName, nTag, pstParent, nVer);

    pstArrField->pnNum = pnFieldNum;
    pstArrField->nSize = nSize;
    pstArrField->pstSubField = pstSubField;
    pstArrField->pstSubFieldInfo = pstSubFieldInfo;
    pstArrField->dwMaxNum = dwMaxNum;
}

/**
 * 字段初始化
 * @param pstArrField 要初始化的字段
 * @param pstSubFieldInfo 数组元素字段信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_array_field(LPARRAYFIELD pstArrField, LPFIELDINFO pstSubFieldInfo, const char* szName,
                      U16 nTag, LPFIELD pstParent, U16 nVer, char* pstSubField, U16* pnFieldNum, U16 nSize, U32 dwMaxNum)
{
    construct_array_field(pstArrField, pstSubFieldInfo, szName, nTag, pstParent, nVer, pstSubField, pnFieldNum, nSize, dwMaxNum);

    if (NULL == pnFieldNum) return;

    *pnFieldNum = (U16)0;
}

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int array_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
    LPARRAYFIELD pstArrField;
    LPFIELD pstSubField;
    int iOldLen;
    U32 nAddLen;
    char* pszMsg;
    int i;
    int iRet;

    if (NULL == pstField || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    // 编码Tag及Type
    CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstField->nTag), iRet);
    CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, pstField->pstFieldInfo->bType), iRet);

    // 先将数组长度设置为0
    CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, (U32)0), iRet);

    // 记录下当前数组长度
    iOldLen = pstByteArray->dwLen;

    // 对数组进行编码
    pstArrField = (LPARRAYFIELD)pstField;

    // 数组数量
    CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, (U16)(*((LPARRAYFIELD)pstField)->pnNum)), iRet);

    // 数组子字段
    for (i = 0; i < *((LPARRAYFIELD)pstField)->pnNum; i++)
    {
        pstSubField = (LPFIELD)((char*)(((LPARRAYFIELD)pstField)->pstSubField + ((LPARRAYFIELD)pstField)->nSize * i));

        init_field_struct(pstSubField, pstArrField->pstSubFieldInfo, pstArrField->stField.szName, i + 1, pstField, pstArrField->stField.nVer);

        CHECK_FUNC_RET(field_encode((char*)pstSubField, pstByteArray, nVer), iRet);
    }

    // 修正数组长度
    // 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
    nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
    pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

    M_U32_TO_CHAR(pszMsg, nAddLen);

    return 0;
}

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int array_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen)
{
    LPARRAYFIELD pstArrField;
    int iHdrLen;
    const char* pszArray;
    U16 nArrayNum = 0;
    int iLeftLen;
    int iRet = -1;
    LPFIELD pstSubField = NULL;
    int iMsgLen = 0;
    U16 i;

    if (NULL == pstField || NULL == szBuf || NULL == pstField->pstFieldInfo) return ERROR_INPUT_PARAM_NULL;

    iHdrLen = sizeof(pstField->nTag) + sizeof(pstField->pstFieldInfo->bType) + sizeof(U32);
    pszArray = szBuf + iHdrLen;
    iLeftLen = iBufLen - iHdrLen;

    pstArrField = (LPARRAYFIELD)pstField;
    *pstArrField->pnNum = 0;

    /* 数组长度 */
    M_CHAR_TO_U16(nArrayNum, pszArray);
    iLeftLen -= sizeof(nArrayNum);

    /* 数组长度超过了最大值的处理 */
    if (nArrayNum > pstArrField->dwMaxNum) return ERROR_DECODE_ARRAY_LONG;

    /* 解析子字段 */
    for (i = 0; i < nArrayNum; i++)
    {
        pstSubField = (LPFIELD)((char*)(pstArrField->pstSubField + pstArrField->nSize * i));

        /* 初始化一下子字段 */
        init_field(pstSubField, pstArrField->pstSubFieldInfo, pstArrField->stField.szName,
                   pstArrField->stField.nTag, pstField, pstArrField->stField.nVer);

        /* 在初始化后，取下子字段的类型，并通过类型获得数据长度 */
        iMsgLen = get_length_by_type(pstSubField->pstFieldInfo->bType, pszArray, iLeftLen);

        if (iLeftLen < iMsgLen)
        {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }

        iRet = field_decode(pstSubField, pszArray, iLeftLen);

        if (iRet != 0) return iRet;

        pszArray += iMsgLen;
        iLeftLen -= iMsgLen;
        *pstArrField->pnNum = *pstArrField->pnNum + 1;
    }

    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int array_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    char szValue[MAX_FIELD_INFO_LEN];
    LPFIELD pstSubField;
    LPARRAYFIELD pstArrField;
    int i;
    int iRet;

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    /* 长度 */
    snprintf(szValue, sizeof(szValue), "%s[%s]\n%sNum=%d\n", szPrefix, pstField->szName,
         szPrefix, *((LPARRAYFIELD)pstField)->pnNum);
    CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

    pstArrField = (LPARRAYFIELD)pstField;
    /* 子字段 */
    for (i = 0; i < *((LPARRAYFIELD)pstField)->pnNum; i++)
    {
        pstSubField = (LPFIELD)((char*)(((LPARRAYFIELD)pstField)->pstSubField + ((LPARRAYFIELD)pstField)->nSize * i));

        init_field_struct(pstSubField, pstArrField->pstSubFieldInfo, pstArrField->stField.szName, i + 1, pstField, pstArrField->stField.nVer);

        CHECK_FUNC_RET(field_format(pstSubField, pstByteArray, szPrefix, nVer), iRet);
    }

    return 0;
}

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int array_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    /*char szSubPrefix[MAX_FIELD_INFO_LEN];*/
    LPFIELD pstSubField;
    LPARRAYFIELD pstArrField;
    int i;
    int iRet;

    if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

    CHECK_FIELD_VER_RET(pstField, nVer);

    /*snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);*/

    /* 子字段 */
    pstArrField = (LPARRAYFIELD)pstField;
    /* 子字段 */
    for (i = 0; i < *((LPARRAYFIELD)pstField)->pnNum; i++)
    {
        pstSubField = (LPFIELD)((char*)(((LPARRAYFIELD)pstField)->pstSubField + ((LPARRAYFIELD)pstField)->nSize * i));

        init_field_struct(pstSubField, pstArrField->pstSubFieldInfo, pstArrField->stField.szName, i + 1, pstField, pstArrField->stField.nVer);

        CHECK_FUNC_RET(field_toxml(pstSubField, pstByteArray, szPrefix, nVer), iRet);
    }

    return 0;
}

/**
 * 数组字段新增子字段
 * @param pstArrField 数组字段
 * @return 返回新增的子字段对象，如果增加不成功，返回NULL
 */
LPFIELD array_field_append_sub_field(LPARRAYFIELD pstArrField)
{
    LPFIELD pstSubField;

    if (NULL == pstArrField) return NULL;

    /* 数组长度超过最大数量 */
    if (*pstArrField->pnNum >= pstArrField->dwMaxNum) return NULL;

    pstSubField = (LPFIELD)((char*)(pstArrField->pstSubField + pstArrField->nSize * (*pstArrField->pnNum)));

    /* 初始化一下子字段 */
    init_field(pstSubField, pstArrField->pstSubFieldInfo, pstArrField->stField.szName,
               pstArrField->stField.nTag, (LPFIELD)pstArrField, pstArrField->stField.nVer);

    *pstArrField->pnNum = *pstArrField->pnNum + 1;

    return pstSubField;
}

