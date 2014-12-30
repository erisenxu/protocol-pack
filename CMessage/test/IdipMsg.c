
/*
 * @(#) IdipMsg.c Created by @itfriday message creator
 */

#include "IdipMsg.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_idip_msg_field(LPFIELD pstField);

static void init_idip_msg_field(LPFIELD pstField);

static int idip_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int idip_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int idip_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD idip_msg_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD idip_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName);

static LPFIELD idip_msg_get_sub_field_by_selection(LPFIELD pstField);

FIELDINFO g_stIdipMsgFieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_idip_msg_field,					/* construct */
	init_idip_msg_field,						/* init */
	idip_msg_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	idip_msg_field_format,					/* format */
	idip_msg_field_to_xml,					/* toXml */
	idip_msg_get_sub_field,					/* getSubField */
	idip_msg_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_idip_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	construct_short_field(&((LPIDIPMSG)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(TEST_MSG), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg2), &g_stTestMsg2FieldInfo, M_NAME("TestMsg2"), M_TAG(TEST_MSG_2), M_PARENT(pstField), M_VERSION(1));
}

void init_idip_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	init_short_field(&((LPIDIPMSG)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));
	init_field((LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(TEST_MSG), M_PARENT(pstField), M_VERSION(1));
	init_field((LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg2), &g_stTestMsg2FieldInfo, M_NAME("TestMsg2"), M_TAG(TEST_MSG_2), M_PARENT(pstField), M_VERSION(1));
}

int idip_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
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

	CHECK_FUNC_RET(field_encode((char*)&((LPIDIPMSG)pstField)->stSelection, pstByteArray, nVer), iRet);
	switch (((LPIDIPMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_encode((char*)&((LPIDIPMSG)pstField)->stTestMsg, pstByteArray, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_encode((char*)&((LPIDIPMSG)pstField)->stTestMsg2, pstByteArray, nVer), iRet);
		break;
	}

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int idip_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_format((char*)&((LPIDIPMSG)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPIDIPMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_format((char*)&((LPIDIPMSG)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_format((char*)&((LPIDIPMSG)pstField)->stTestMsg2, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	return 0;
}

int idip_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_toxml((char*)&((LPIDIPMSG)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPIDIPMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		CHECK_FUNC_RET(field_toxml((char*)&((LPIDIPMSG)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case TEST_MSG_2:
		CHECK_FUNC_RET(field_toxml((char*)&((LPIDIPMSG)pstField)->stTestMsg2, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	snprintf(szValue, sizeof(szValue), "%s</%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD idip_msg_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{
	case 0xFFFF:
		return (LPFIELD)(&((LPIDIPMSG)pstField)->stSelection);
	default:
		return idip_msg_get_sub_field_by_selection(pstField);
	}

	return NULL;
}

LPFIELD idip_msg_get_sub_field_by_selection(LPFIELD pstField)
{
	if (NULL == pstField) return NULL;

	switch (((LPIDIPMSG)pstField)->stSelection.nValue)
	{
	case TEST_MSG:
		return (LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg);
	case TEST_MSG_2:
		return (LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg2);
	}
	return NULL;
}

LPFIELD idip_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{
	if (0 == strncmp(szName, "Selection", sizeof("Selection"))) return (LPFIELD)(&((LPIDIPMSG)pstField)->stSelection);
	if (0 == strncmp(szName, "TestMsg", sizeof("TestMsg"))) return (LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg);
	if (0 == strncmp(szName, "TestMsg2", sizeof("TestMsg2"))) return (LPFIELD)(&((LPIDIPMSG)pstField)->stTestMsg2);
	return NULL;
}

