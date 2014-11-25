
/*
 * @(#) TestMsg2.cpp Created by feimao message creator
 */

#include "TestMsg2.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_test_msg2_field(LPFIELD pstField);

static void init_test_msg2_field(LPFIELD pstField);

static int test_msg2_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int test_msg2_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int test_msg2_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD test_msg2_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD test_msg2_get_sub_field_by_name(LPFIELD pstField, const char* szName);

FIELDINFO g_stTestMsg2FieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_test_msg2_field,					/* construct */
	init_test_msg2_field,						/* init */
	test_msg2_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	test_msg2_field_format,					/* format */
	test_msg2_field_to_xml,					/* toXml */
	test_msg2_get_sub_field,					/* getSubField */
	test_msg2_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_test_msg2_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	construct_array_field(&((LPTESTMSG2)pstField)->stArrTestMsg, &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(1), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTMSG2)pstField)->astTestMsg, &((LPTESTMSG2)pstField)->nTestMsgNum, sizeof(((LPTESTMSG2)pstField)->astTestMsg[0]), 4);
	construct_array_field(&((LPTESTMSG2)pstField)->stArrIntField, &g_stIntFieldInfo, M_NAME("IntField"), M_TAG(2), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTMSG2)pstField)->astIntField, &((LPTESTMSG2)pstField)->nIntFieldNum, sizeof(((LPTESTMSG2)pstField)->astIntField[0]), 4);
}

void init_test_msg2_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	init_array_field(&((LPTESTMSG2)pstField)->stArrTestMsg, &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(1), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTMSG2)pstField)->astTestMsg, &((LPTESTMSG2)pstField)->nTestMsgNum, sizeof(((LPTESTMSG2)pstField)->astTestMsg[0]), 4);
	init_array_field(&((LPTESTMSG2)pstField)->stArrIntField, &g_stIntFieldInfo, M_NAME("IntField"), M_TAG(2), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTMSG2)pstField)->astIntField, &((LPTESTMSG2)pstField)->nIntFieldNum, sizeof(((LPTESTMSG2)pstField)->astIntField[0]), 4);
}

int test_msg2_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
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

	CHECK_FUNC_RET(field_encode((char*)&((LPTESTMSG2)pstField)->stArrTestMsg, pstByteArray, nVer), iRet);
	CHECK_FUNC_RET(field_encode((char*)&((LPTESTMSG2)pstField)->stArrIntField, pstByteArray, nVer), iRet);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int test_msg2_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_format((char*)&((LPTESTMSG2)pstField)->stArrTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_format((char*)&((LPTESTMSG2)pstField)->stArrIntField, pstByteArray, szSubPrefix, nVer), iRet);

	return 0;
}

int test_msg2_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTMSG2)pstField)->stArrTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTMSG2)pstField)->stArrIntField, pstByteArray, szSubPrefix, nVer), iRet);

	snprintf(szValue, sizeof(szValue), "%s</%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD test_msg2_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{
	case 1:
		return (LPFIELD)(&((LPTESTMSG2)pstField)->stArrTestMsg);
	case 2:
		return (LPFIELD)(&((LPTESTMSG2)pstField)->stArrIntField);
	default:
		return NULL;
	}

	return NULL;
}

LPFIELD test_msg2_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{
	if (0 == strncmp(szName, "TestMsg", sizeof("TestMsg"))) return (LPFIELD)(&((LPTESTMSG2)pstField)->stArrTestMsg);
	if (0 == strncmp(szName, "IntField", sizeof("IntField"))) return (LPFIELD)(&((LPTESTMSG2)pstField)->stArrIntField);
	return NULL;
}

