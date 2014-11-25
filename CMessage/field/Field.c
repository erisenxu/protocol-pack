/*
 * @(#) Field.c Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "Field.h"

#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <string.h>

/**
 * 字段信息初始化
 */
#define INIT_FIELD_INFO() \
    if (NULL == pstField) return; \
    if (NULL == szName) \
    { \
        STRNCPY(pstField->szName, sizeof(pstField->szName), "", sizeof(pstField->szName)); \
    } \
    else \
    { \
        STRNCPY(pstField->szName, sizeof(pstField->szName), szName, sizeof(pstField->szName)); \
    } \
    pstField->nTag = nTag; \
    pstField->pstParent = pstParent; \
    pstField->nVer = nVer; \
    pstField->pstFieldInfo = pstFieldInfo

/**
 * 字段结构初始化
 * @param pstField 要初始化的字段
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 */
void init_field_struct(LPFIELD pstField, LPFIELDINFO pstFieldInfo, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer)
{
    INIT_FIELD_INFO();

    // 再对字段进行下初始化
    if (pstFieldInfo && pstFieldInfo->construct) pstFieldInfo->construct(pstField);
}

/**
 * 字段初始化
 * @param pstField 要初始化的字段
 * @param pstFieldInfo 字段描述信息
 * @param szName 字段名字
 * @param nTag 字段Tag
 * @param nVer 字段引人版本号
 * @return
 */
void init_field(LPFIELD pstField, LPFIELDINFO pstFieldInfo, const char* szName, U16 nTag, LPFIELD pstParent, U16 nVer)
{
    INIT_FIELD_INFO();

    // 再对字段进行下初始化
    if (pstFieldInfo && pstFieldInfo->init) pstFieldInfo->init(pstField);
}

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int get_length_by_type(U8 bType, const char* szBuf, int iBufLen)
{
    int iMinLen = sizeof(U16) + sizeof(U8);

    switch (bType)
    {
        case FIELD_TYPE_BYTE:
            return iMinLen + sizeof(U8);
        case FIELD_TYPE_SHORT:
            return iMinLen + sizeof(U16);
        case FIELD_TYPE_INT:
            return iMinLen + sizeof(U32);
        case FIELD_TYPE_LONG:
            return iMinLen + sizeof(U64);
        case FIELD_TYPE_STRING:
        case FIELD_TYPE_TLV:
        case FIELD_TYPE_ARRAY:
        default:
        {
            if (NULL != szBuf && iBufLen >= iMinLen + (int)sizeof(U32))
            {
                U32 nLen;
                const char* pszBuf = szBuf + iMinLen;
                M_CHAR_TO_U32(nLen, pszBuf);
                return iMinLen + sizeof(nLen) + nLen;
            }
            return ERROR_DECODE_BUFSIZE_SHORT;
        }
    }
    //return iMinLen;
}

/**
 * 字段编码
 * @param pstField 要编码的字段
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int field_encode(void* pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
    if (NULL == pstField || NULL == ((LPFIELD)pstField)->pstFieldInfo ||
        NULL == ((LPFIELD)pstField)->pstFieldInfo->encode)
    {
        return ERROR_INPUT_PARAM_NULL;
    }

    return ((LPFIELD)pstField)->pstFieldInfo->encode((LPFIELD)pstField, pstByteArray, nVer);
}

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int field_decode(void* pstField, const char* szBuf, int iBufLen)
{
    if (NULL == pstField || NULL == ((LPFIELD)pstField)->pstFieldInfo ||
        NULL == ((LPFIELD)pstField)->pstFieldInfo->decode) return ERROR_INPUT_PARAM_NULL;

    return ((LPFIELD)pstField)->pstFieldInfo->decode(((LPFIELD)pstField), szBuf, iBufLen);
}

/**
 * 将字段格式化成可读形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int field_format(void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    if (NULL == pstField || NULL == ((LPFIELD)pstField)->pstFieldInfo ||
        NULL == ((LPFIELD)pstField)->pstFieldInfo->format)
    {
        return ERROR_INPUT_PARAM_NULL;
    }

    return ((LPFIELD)pstField)->pstFieldInfo->format((LPFIELD)pstField, pstByteArray, szPrefix, nVer);
}

/**
 * 将字段格式化成XML形式
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存字段信息的缓存区
 * @param szPrefix 格式化字符串的前缀
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 */
int field_toxml(void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
    if (NULL == pstField || NULL == ((LPFIELD)pstField)->pstFieldInfo ||
        NULL == ((LPFIELD)pstField)->pstFieldInfo->toXml)
    {
        return ERROR_INPUT_PARAM_NULL;
    }

    return ((LPFIELD)pstField)->pstFieldInfo->toXml((LPFIELD)pstField, pstByteArray, szPrefix, nVer);
}

/**
 * 复合字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 */
int composite_field_decode(LPFIELD pstField, const char* szBuf, int iBufLen)
{
    int iMinLen;    // 字段最小长度
    LPFIELD pstSubField = NULL;
    U16 nTag = 0;
    U8 bType = 0;
    const char* pszBuf;
    int iLeftLen;
    int iFieldLen;
    int iRet = -1;

    if (NULL == pstField || NULL == szBuf || NULL == pstField->pstFieldInfo ||
        NULL == pstField->pstFieldInfo->getSubField) return ERROR_INPUT_PARAM_NULL;

    iMinLen = sizeof(pstField->nTag) + sizeof(pstField->pstFieldInfo->bType);    // 字段最小长度
    pszBuf = szBuf + iMinLen + sizeof(U32);
    iLeftLen = iBufLen - iMinLen - sizeof(U32);

    if (iLeftLen < 0)
    {
        return ERROR_DECODE_BUFSIZE_SHORT;
    }

    // 求字段长度
    iLeftLen = read_int(szBuf + iMinLen);

    while (iLeftLen > 0)
    {
        // 解析Tag和Type
        if (iLeftLen < iMinLen)
        {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }

        // Tag和类型
        nTag = read_short(pszBuf);
        bType = read_byte(pszBuf + sizeof(nTag));

        // 消息长度
        iFieldLen = get_length_by_type(bType, pszBuf, iLeftLen);
        if (iFieldLen == ERROR_DECODE_BUFSIZE_SHORT || iLeftLen < iFieldLen)
        {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }

        /* 取消息对象 */
        pstSubField = pstField->pstFieldInfo->getSubField(pstField, nTag);

        /* 对认识的字段进行解码，不认识的字段直接丢弃 */
        if (pstSubField)
        {
            iRet = field_decode(pstSubField, pszBuf, iLeftLen);
            if (iRet != 0) return iRet;
        }
        /* 不认识的字段，直接丢弃 (兼容旧版本) */
        pszBuf += iFieldLen;
        iLeftLen -= iFieldLen;
    }

    return 0;
}

/**
 * 从消息中读取一个字节，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的字节
 */
U8 read_byte(const char* szBuf)
{
    U8 bRet;

    M_CHAR_TO_U8(bRet, szBuf);

    return bRet;
}

/**
 * 从消息中读取一个short，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U16 read_short(const char* szBuf)
{
    U16 bRet;

    M_CHAR_TO_U16(bRet, szBuf);

    return bRet;
}

/**
 * 从消息中读取一个int，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U32 read_int(const char* szBuf)
{
    U32 bRet;

    M_CHAR_TO_U32(bRet, szBuf);

    return bRet;
}

