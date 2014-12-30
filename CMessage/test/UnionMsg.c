
/*
 * @(#) UnionMsg.c Created by @itfriday message creator
 */

#include "UnionMsg.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_union_msg_field(LPFIELD pstField);

static void init_union_msg_field(LPFIELD pstField);

static int union_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int union_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int union_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD union_msg_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD union_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName);

static LPFIELD union_msg_get_sub_field_by_selection(LPFIELD pstField);

FIELDINFO g_stUnionMsgFieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_union_msg_field,					/* construct */
	init_union_msg_field,						/* init */
	union_msg_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	union_msg_field_format,					/* format */
	union_msg_field_to_xml,					/* toXml */
	union_msg_get_sub_field,					/* getSubField */
	union_msg_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_union_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	construct_short_field(&((LPUNIONMSG)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(TEST_MSG), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg2), &g_stTestMsg2FieldInfo, M_NAME("TestMsg2"), M_TAG(TEST_MSG_2), M_PARENT(pstField), M_VERSION(1));
}

void init_union_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	init_short_field(&((LPUNIONMSG)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));
	init_field((LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(TEST_MSG), M_PARENT(pstField), M_VERSION(1));
	init_field((LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg2), &g_stTestMsg2FieldInfo, M_NAME("TestMsg2"), M_TAG(TEST_MSG_2), M_PARENT(pstField), M_VERSION(1));
}

int union_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
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

	CHECK_FUNC_RET(field_encode((char*)&((LPUNIONMSG)pstField)->stSelection, pstByteArray, nVer), iRet);
	switch (((LPUNIONMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_encode((char*)&((LPUNIONMSG)pstField)->stTestMsg, pstByteArray, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_encode((char*)&((LPUNIONMSG)pstField)->stTestMsg2, pstByteArray, nVer), iRet);
		break;
	}

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int union_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_format((char*)&((LPUNIONMSG)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPUNIONMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_format((char*)&((LPUNIONMSG)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_format((char*)&((LPUNIONMSG)pstField)->stTestMsg2, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	return 0;
}

int union_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_toxml((char*)&((LPUNIONMSG)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPUNIONMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_toxml((char*)&((LPUNIONMSG)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_toxml((char*)&((LPUNIONMSG)pstField)->stTestMsg2, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	snprintf(szValue, sizeof(szValue), "%s</%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD union_msg_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{
	case 0xFFFF:
		return (LPFIELD)(&((LPUNIONMSG)pstField)->stSelection);
	default:
		return union_msg_get_sub_field_by_selection(pstField);
	}

	return NULL;
}

LPFIELD union_msg_get_sub_field_by_selection(LPFIELD pstField)
{
	if (NULL == pstField) return NULL;

	switch (((LPUNIONMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		return (LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg);
	case TEST_MSG_2:
		return (LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg2);
	}
	return NULL;
}

LPFIELD union_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{
	if (0 == strncmp(szName, "Selection", sizeof("Selection"))) return (LPFIELD)(&((LPUNIONMSG)pstField)->stSelection);
	if (0 == strncmp(szName, "TestMsg", sizeof("TestMsg"))) return (LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg);
	if (0 == strncmp(szName, "TestMsg2", sizeof("TestMsg2"))) return (LPFIELD)(&((LPUNIONMSG)pstField)->stTestMsg2);
	return NULL;
}

