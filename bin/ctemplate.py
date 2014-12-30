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

CPPTEMPLATE = '''
/*
 * @(#) $ClassName.cpp Created by @itfriday message creator
 */

#include "$ClassName.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void $ClassName::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);$Init
}

/**
 * @override
 */
int $ClassName::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();
$Encodes

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void $ClassName::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\\n");$Formats
}

/**
 * @override
 */
void $ClassName::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\\n");$ToXmls
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\\n");
}

/**
 * @override
 */
MField* $ClassName::getSubField(U16 nTag, U8 $GetFieldMode)
{$GetSubFields
}

/**
 * @override
 */
MField* $ClassName::getSubFieldByName(const string& sName)
{$GetSubFieldByNames
	return NULL;
}

''';

#
# C文件模版-字段模版
#
CTEMPLATE = '''
/*
 * @(#) ${ClassName}.c Created by @itfriday message creator
 */

#include "${ClassName}.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_${LowerClassMarco}_field(LPFIELD pstField);

static void init_${LowerClassMarco}_field(LPFIELD pstField);

static int ${LowerClassMarco}_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int ${LowerClassMarco}_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int ${LowerClassMarco}_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD ${LowerClassMarco}_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD ${LowerClassMarco}_get_sub_field_by_name(LPFIELD pstField, const char* szName);
${GetSubFieldBySelection}
FIELDINFO g_st${ClassName}FieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_${LowerClassMarco}_field,					/* construct */
	init_${LowerClassMarco}_field,						/* init */
	${LowerClassMarco}_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	${LowerClassMarco}_field_format,					/* format */
	${LowerClassMarco}_field_to_xml,					/* toXml */
	${LowerClassMarco}_get_sub_field,					/* getSubField */
	${LowerClassMarco}_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_${LowerClassMarco}_field(LPFIELD pstField)
{
	if (NULL == pstField) return;$Constructs
}

void init_${LowerClassMarco}_field(LPFIELD pstField)
{
	if (NULL == pstField) return;$Init
}

int ${LowerClassMarco}_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
{
	int iRet;
	int iOldLen;
	U32 nAddLen;
	char* pszMsg;

	if (NULL == pstField || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	// 编码Tag及Type
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstField->nTag), iRet);
	CHECK_FUNC_RET(bytearray_append_u8(pstByteArray, pstField->pstFieldInfo->bType), iRet);

	// 先将数组长度设置为0
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, (U32)0), iRet);

	// 记录下当前数组长度
	iOldLen = pstByteArray->dwLen;
$Encodes

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int ${LowerClassMarco}_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
$Formats

	return 0;
}

int ${LowerClassMarco}_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);
$ToXmls

	snprintf(szValue, sizeof(szValue), "%s</%s>\\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD ${LowerClassMarco}_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{$GetSubFields
	}

	return NULL;
}
${GetSubFieldBySelectionFunc}
LPFIELD ${LowerClassMarco}_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{$GetSubFieldByNames
	return NULL;
}

''';

#
# C文件模版-消息模版
#
CMSGTEMPLATE = '''
/*
 * @(#) ${ClassName}.c Created by @itfriday message creator
 */

#include "${ClassName}.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

int msg_encode_${LowerClassMarco}(LPMSG${UpperClassName} pstMsgObj, LPBYTEARRAY pstByteArray)
{
	int iRet;
	char* pszMsg;

	if (NULL == pstMsgObj || NULL == pstByteArray) return ERROR_INPUT_PARAM_NULL;

	// 先将数组长度设置为0
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, (U32)0), iRet);

	// 编码Sequence及Version，如果不需要Sequence和Version字段，可以将这两个字段删除
	CHECK_FUNC_RET(bytearray_append_u32(pstByteArray, pstMsgObj->dwSequence), iRet);
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstMsgObj->nMsgVer), iRet);
	CHECK_FUNC_RET(bytearray_append_u16(pstByteArray, pstMsgObj->nMsgType), iRet);
	// (注)如果有其他的字段，可以在这里编码

	// 根据消息类型，编码消息
	switch (pstMsgObj->nMsgType)
	{$EncodeMsgFields
	default:
		break;
	}

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	pszMsg = pstByteArray->pszData;

	M_U32_TO_CHAR(pszMsg, pstByteArray->dwLen);

	return 0;
}

/**
 * The message decode
 */
int msg_decode_${LowerClassMarco}(LPMSG${UpperClassName} pstMsgObj, const char* szBuf, int iBufLen)
{
	const char* pszBuf;
	int iHeadLen;
	U16 nTag;

	if (NULL == pstMsgObj || NULL == szBuf || iBufLen <= 0) return ERROR_INPUT_PARAM_NULL;

	// 消息头部，包含消息总长度、Sequence、Version、Message Type
	// (注)如果消息头部包含其他字段，需在这里加上头部长度
	iHeadLen = sizeof(U32) + sizeof(pstMsgObj->dwSequence) + sizeof(pstMsgObj->nMsgVer) +
		sizeof(pstMsgObj->nMsgType);

	if (iBufLen < iHeadLen) return ERROR_DECODE_BUFSIZE_SHORT;

	pszBuf = szBuf + sizeof(U32);

	// 解码Sequence、Version、Message Type
	M_CHAR_TO_U32(pstMsgObj->dwSequence, pszBuf);
	M_CHAR_TO_U16(pstMsgObj->nMsgVer, pszBuf);
	M_CHAR_TO_U16(pstMsgObj->nMsgType, pszBuf);
	// (注)如果消息头部包含其他字段，可以在这里解码

	// 根据消息类型，解码消息
	switch (pstMsgObj->nMsgType)
	{$DecodeMsgFields
	default:
		break;
	}

	return 0;
}
''';
