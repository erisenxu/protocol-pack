
/*
 * @(#) TestIdipMsg.c Created by @itfriday message creator
 */

#include "TestIdipMsg.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_test_idip_msg_field(LPFIELD pstField);

static void init_test_idip_msg_field(LPFIELD pstField);

static int test_idip_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int test_idip_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int test_idip_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD test_idip_msg_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD test_idip_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName);

FIELDINFO g_stTestIdipMsgFieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_test_idip_msg_field,					/* construct */
	init_test_idip_msg_field,						/* init */
	test_idip_msg_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	test_idip_msg_field_format,					/* format */
	test_idip_msg_field_to_xml,					/* toXml */
	test_idip_msg_get_sub_field,					/* getSubField */
	test_idip_msg_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_test_idip_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	construct_uint_field(&((LPTESTIDIPMSG)pstField)->stSequence, M_NAME("Sequence"), M_TAG(1), M_PARENT(pstField), M_VERSION(1));
	construct_ushort_field(&((LPTESTIDIPMSG)pstField)->stVersion, M_NAME("Version"), M_TAG(2), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPTESTIDIPMSG)pstField)->stIdipMsg), &g_stIdipMsgFieldInfo, M_NAME("IdipMsg"), M_TAG(3), M_PARENT(pstField), M_VERSION(1));
}

void init_test_idip_msg_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	init_uint_field(&((LPTESTIDIPMSG)pstField)->stSequence, M_NAME("Sequence"), M_TAG(1), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));
	init_ushort_field(&((LPTESTIDIPMSG)pstField)->stVersion, M_NAME("Version"), M_TAG(2), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));
	init_field((LPFIELD)(&((LPTESTIDIPMSG)pstField)->stIdipMsg), &g_stIdipMsgFieldInfo, M_NAME("IdipMsg"), M_TAG(3), M_PARENT(pstField), M_VERSION(1));
}

int test_idip_msg_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
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

	CHECK_FUNC_RET(field_encode((char*)&((LPTESTIDIPMSG)pstField)->stSequence, pstByteArray, nVer), iRet);
	CHECK_FUNC_RET(field_encode((char*)&((LPTESTIDIPMSG)pstField)->stVersion, pstByteArray, nVer), iRet);
	CHECK_FUNC_RET(field_encode((char*)&((LPTESTIDIPMSG)pstField)->stIdipMsg, pstByteArray, nVer), iRet);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int test_idip_msg_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_format((char*)&((LPTESTIDIPMSG)pstField)->stSequence, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_format((char*)&((LPTESTIDIPMSG)pstField)->stVersion, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_format((char*)&((LPTESTIDIPMSG)pstField)->stIdipMsg, pstByteArray, szSubPrefix, nVer), iRet);

	return 0;
}

int test_idip_msg_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTIDIPMSG)pstField)->stSequence, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTIDIPMSG)pstField)->stVersion, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTIDIPMSG)pstField)->stIdipMsg, pstByteArray, szSubPrefix, nVer), iRet);

	snprintf(szValue, sizeof(szValue), "%s</%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD test_idip_msg_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{
	case 1:
		return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stSequence);
	case 2:
		return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stVersion);
	case 3:
		return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stIdipMsg);
	default:
		return NULL;
	}

	return NULL;
}

LPFIELD test_idip_msg_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{
	if (0 == strncmp(szName, "Sequence", sizeof("Sequence"))) return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stSequence);
	if (0 == strncmp(szName, "Version", sizeof("Version"))) return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stVersion);
	if (0 == strncmp(szName, "IdipMsg", sizeof("IdipMsg"))) return (LPFIELD)(&((LPTESTIDIPMSG)pstField)->stIdipMsg);
	return NULL;
}

