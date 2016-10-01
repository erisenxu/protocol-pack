#!/usr/bin/env python
#coding:utf-8
#=================================================================
# @ Author : Erisenxu @ Innovate Center
# @ Desc : 文件模版
# @ FileName : ctemplate.py
# @ Date : 2014-03-29
# @ ModifyHistory :
# @ Remark :
#==================================================================

#
# H文件模版-字段模版
#
HTEMPLATE = '''/*
 * @(#) ${ClassName}.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_H
#define ${ClassMacro}_H
 
${Includes}
/**
 * $ClassDesc
 */
struct tag${ClassName}
{$AttrDefine
};

typedef struct tag${ClassName}  ${UClassName};
typedef struct tag${ClassName}* LP${UClassName};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * ${ClassName}字段编码
 * @param pstField 要编码的字段
 * @param nTag 字段的Tag值
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_encode(void* pstField, U16 nTag, LPBYTEARRAY pstByteArray);

/**
 * ${ClassName}字段的子字段解码
 * @param pstField 要解码的字段
 * @param szBuf 解码读取的字节流
 * @param iBufLen 解码读取的字节流长度
 * @param nTag 子字段的Tag值
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_sub_field_decode(void* pstField, const char* szBuf, int iBufLen, U16 nTag);

/**
 * ${ClassName}字段解码
 * @param pstField 要解码的字段
 * @param szBuf 解码读取的字节流
 * @param iBufLen 解码读取的字节流长度
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_decode(void* pstField, const char* szBuf, int iBufLen);

/**
 * ${ClassName}字段格式化
 * @param szFieldName 字段的名字
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @param szPrefix 格式化前缀字符，一般为对其空格
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_format(const char* szFieldName, void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * ${ClassName}字段转换为xml格式
 * @param szFieldName 字段的名字
 * @param pstField 要转换的字段
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @param szPrefix 格式化前缀字符，一般为对其空格
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_to_xml(const char* szFieldName, void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix);

/**
 * 设置按字段名字设置子字段的值
 * @param pstField 给定字段对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @param szValue 字段的值
 */
void ${LClassName}_set_sub_field_value_by_name(void* pstField, const char* szSubFieldName, U16 nIdx, const char* szValue);

/**
 * 按字段名字获取子字段对象
 * @param pstField 给定字段对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @return 返回子字段名称对应的子字段对象
 */
void* ${LClassName}_get_sub_field_by_name(void* pstField, const char* szSubFieldName, U16 nIdx);

/**
 * 构建子字段信息对象
 * @param pstSubFieldInfo 要构建的子字段信息对象
 * @param szSubFieldName 子字段的名称
 */
void ${LClassName}_build_sub_field_info_by_name(LPFIELDINFO pstSubFieldInfo, const char* szSubFieldName);

/**
 * 构建字段信息对象
 * @param pstFieldInfo 要构建的字段信息对象
 */
void ${LClassName}_build_field_info(LPFIELDINFO pstFieldInfo);

#ifdef __cplusplus
}
#endif

#endif
''';

#
# C文件模版-字段模版
#
CTEMPLATE = '''/*
 * @(#) ${ClassName}.c Created by @itfriday message creator
 */

#include "${ClassName}.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * ${ClassName}字段编码
 * @param pstField 要编码的字段
 * @param nTag 字段的Tag值
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_encode(void* pstField, U16 nTag, LPBYTEARRAY pstByteArray)
{
	int iRet;
	int iOldLen;
	U32 nAddLen;
	char* pszMsg;
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	/* 编码Tag及Type */
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, FIELD_TYPE_TLV), iRet);

	/* 先将数组长度设置为0 */
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, (U32)0), iRet);

	/* 记录下当前数组长度 */
	iOldLen = pstByteArray->dwLen;
${FieldEncode}

	/* 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变 */
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * ${ClassName}字段的子字段解码
 * @param pstField 要解码的字段
 * @param szBuf 解码读取的字节流
 * @param iBufLen 解码读取的字节流长度
 * @param nTag 子字段的Tag值
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_sub_field_decode(void* pstField, const char* szBuf, int iBufLen, U16 nTag)
{
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == szBuf) return ERROR_INPUT_PARAM_NULL;
${UnionTagDecode}
	/* 解码子字段 */
	switch (nTag)
	{${SubFieldDecode}
	default:
		break;
	}

	return 0;
}

/**
 * ${ClassName}字段解码
 * @param pstField 要解码的字段
 * @param szBuf 解码读取的字节流
 * @param iBufLen 解码读取的字节流长度
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_decode(void* pstField, const char* szBuf, int iBufLen)
{
	return composite_field_decode(pstField, szBuf, iBufLen, ${LClassName}_sub_field_decode);
}

/**
 * ${ClassName}字段格式化
 * @param szFieldName 字段的名字
 * @param pstField 要格式化的字段
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @param szPrefix 格式化前缀字符，一般为对其空格
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_format(const char* szFieldName, void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	SNPRINTF(szValue, sizeof(szValue), "%s[%s]\\n", szPrefix, szFieldName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
${Formats}

	return 0;
}

/**
 * ${ClassName}字段转换为xml格式
 * @param szFieldName 字段的名字
 * @param pstField 要转换的字段
 * @param pstByteArray 保存编码字节流的缓存区数组
 * @param szPrefix 格式化前缀字符，一般为对其空格
 * @return 成功返回0，失败返回错误码
 */
int ${LClassName}_field_to_xml(const char* szFieldName, void* pstField, LPBYTEARRAY pstByteArray, const char* szPrefix)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == szFieldName || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	SNPRINTF(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	SNPRINTF(szValue, sizeof(szValue), "%s<%s>\\n", szPrefix, szFieldName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
${ToXmls}

	SNPRINTF(szValue, sizeof(szValue), "%s</%s>\\n", szPrefix, szFieldName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

/**
 * 设置按字段名字设置子字段的值
 * @param pstField 给定字段对象
 * @param szSubFieldName 子字段名称
 * @param nIdx 数组字段的元素索引
 * @param szValue 字段的值
 */
void ${LClassName}_set_sub_field_value_by_name(void* pstField, const char* szSubFieldName, U16 nIdx, const char* szValue)
{
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == szSubFieldName || NULL == szValue) return;${SetValueByName}
}

/**
 * 按字段名字获取子字段对象
 * @param pstField 给定字段对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @return 返回子字段名称对应的子字段对象
 */
void* ${LClassName}_get_sub_field_by_name(void* pstField, const char* szSubFieldName, U16 nIdx)
{
	LP${UClassName} pst${ClassName} = (LP${UClassName})pstField;

	if (NULL == pst${ClassName} || NULL == szSubFieldName) return NULL;${GetFieldByName}

	return NULL;
}

/**
 * 构建子字段信息对象
 * @param pstSubFieldInfo 要构建的子字段信息对象
 * @param szSubFieldName 子字段的名称
 */
void ${LClassName}_build_sub_field_info_by_name(LPFIELDINFO pstSubFieldInfo, const char* szSubFieldName)
{
	if (NULL == pstSubFieldInfo || NULL == szSubFieldName) return;${BuildFieldByName}
}

/**
 * 构建字段信息对象
 * @param pstFieldInfo 要构建的字段信息对象
 */
void ${LClassName}_build_field_info(LPFIELDINFO pstFieldInfo)
{
	if (NULL == pstFieldInfo) return;

	pstFieldInfo->iMemIndex = -1;
	pstFieldInfo->pstParent = NULL;
	pstFieldInfo->pstExtData = NULL;
	pstFieldInfo->bFieldType = FIELD_TYPE_TLV;
	STRNCPY(pstFieldInfo->szFieldName, sizeof(pstFieldInfo->szFieldName), "${FieldName}", sizeof(pstFieldInfo->szFieldName));
	pstFieldInfo->setSubFieldValueByName = ${LClassName}_set_sub_field_value_by_name;
	pstFieldInfo->getSubFieldByName = ${LClassName}_get_sub_field_by_name;
	pstFieldInfo->buildSubFieldInfoByName = ${LClassName}_build_sub_field_info_by_name;
}

''';
