
/*
 * @(#) TestUnion.c Created by @itfriday message creator
 */

#include "TestUnion.h"
#include "comm/BaseFuncDef.h"
#include "comm/ErrorCode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void construct_test_union_field(LPFIELD pstField);

static void init_test_union_field(LPFIELD pstField);

static int test_union_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer);

static int test_union_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static int test_union_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer);

static LPFIELD test_union_get_sub_field(LPFIELD pstField, U16 nTag);

static LPFIELD test_union_get_sub_field_by_name(LPFIELD pstField, const char* szName);

static LPFIELD test_union_get_sub_field_by_selection(LPFIELD pstField);

FIELDINFO g_stTestUnionFieldInfo =
{
	(U8)FIELD_TYPE_TLV,									/* type */
	construct_test_union_field,					/* construct */
	init_test_union_field,						/* init */
	test_union_field_encode,					/* encode */
	composite_field_decode,								/* decode */
	test_union_field_format,					/* format */
	test_union_field_to_xml,					/* toXml */
	test_union_get_sub_field,					/* getSubField */
	test_union_get_sub_field_by_name,			/* getSubFieldByName */
	NULL												/* setValue */
};

void construct_test_union_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	construct_short_field(&((LPTESTUNION)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1));
	construct_int_field(&((LPTESTUNION)pstField)->stMoney, M_NAME("Money"), M_TAG(2), M_PARENT(pstField), M_VERSION(1));
	init_field_struct((LPFIELD)(&((LPTESTUNION)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(3), M_PARENT(pstField), M_VERSION(1));
	construct_int_field(&((LPTESTUNION)pstField)->stGold, M_NAME("Gold"), M_TAG(4), M_PARENT(pstField), M_VERSION(1));
	construct_string_field(&((LPTESTUNION)pstField)->stDesc, M_NAME("Desc"), M_TAG(5), M_PARENT(pstField), M_VERSION(1),
		(char*)&((LPTESTUNION)pstField)->szDesc, 1);
	construct_array_field(&((LPTESTUNION)pstField)->stArrIntField, &g_stIntFieldInfo, M_NAME("IntField"), M_TAG(6), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTUNION)pstField)->astIntField, &((LPTESTUNION)pstField)->nIntFieldNum, sizeof(((LPTESTUNION)pstField)->astIntField[0]), 4);
}

void init_test_union_field(LPFIELD pstField)
{
	if (NULL == pstField) return;
	init_short_field(&((LPTESTUNION)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));
	init_int_field(&((LPTESTUNION)pstField)->stMoney, M_NAME("Money"), M_TAG(2), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0x123456));
	init_field((LPFIELD)(&((LPTESTUNION)pstField)->stTestMsg), &g_stTestMsgFieldInfo, M_NAME("TestMsg"), M_TAG(3), M_PARENT(pstField), M_VERSION(1));
	init_int_field(&((LPTESTUNION)pstField)->stGold, M_NAME("Gold"), M_TAG(4), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0x789012));
	init_string_field(&((LPTESTUNION)pstField)->stDesc, M_NAME("Desc"), M_TAG(5), M_PARENT(pstField), M_VERSION(1),
		(char*)&((LPTESTUNION)pstField)->szDesc, 1);
	init_array_field(&((LPTESTUNION)pstField)->stArrIntField, &g_stIntFieldInfo, M_NAME("IntField"), M_TAG(6), M_PARENT(pstField), M_VERSION(1),
		(char*)((LPTESTUNION)pstField)->astIntField, &((LPTESTUNION)pstField)->nIntFieldNum, sizeof(((LPTESTUNION)pstField)->astIntField[0]), 4);
}

int test_union_field_encode(LPFIELD pstField, LPBYTEARRAY pstByteArray, U16 nVer)
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

	CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stSelection, pstByteArray, nVer), iRet);
	switch (((LPTESTUNION)pstField)->stSelection.nValue)
	{
	case 2:
		CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stMoney, pstByteArray, nVer), iRet);
		break;
	case 3:
		CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stTestMsg, pstByteArray, nVer), iRet);
		break;
	case 4:
		CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stGold, pstByteArray, nVer), iRet);
		break;
	case 5:
		CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stDesc, pstByteArray, nVer), iRet);
		break;
	case 6:
		CHECK_FUNC_RET(field_encode((char*)&((LPTESTUNION)pstField)->stArrIntField, pstByteArray, nVer), iRet);
		break;
	}

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	nAddLen = (U32)(pstByteArray->dwLen - iOldLen);
	pszMsg = pstByteArray->pszData + (pstByteArray->dwLen - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

int test_union_field_format(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s[%s]\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPTESTUNION)pstField)->stSelection.nValue)
	{
	case 2:
		CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stMoney, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 3:
		CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 4:
		CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stGold, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 5:
		CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stDesc, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 6:
		CHECK_FUNC_RET(field_format((char*)&((LPTESTUNION)pstField)->stArrIntField, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	return 0;
}

int test_union_field_to_xml(LPFIELD pstField, LPBYTEARRAY pstByteArray, const char* szPrefix, U16 nVer)
{
	char szValue[MAX_FIELD_INFO_LEN];
	char szSubPrefix[MAX_FIELD_INFO_LEN];
	int iRet;

	if (NULL == pstField || NULL == pstByteArray || NULL == szPrefix) return ERROR_INPUT_PARAM_NULL;

	CHECK_FIELD_VER_RET(pstField, nVer);

	snprintf(szSubPrefix, sizeof(szSubPrefix), "%s    ", szPrefix);
	snprintf(szValue, sizeof(szValue), "%s<%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);
	switch (((LPTESTUNION)pstField)->stSelection.nValue)
	{
	case 2:
		CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stMoney, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 3:
		CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stTestMsg, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 4:
		CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stGold, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 5:
		CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stDesc, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	case 6:
		CHECK_FUNC_RET(field_toxml((char*)&((LPTESTUNION)pstField)->stArrIntField, pstByteArray, szSubPrefix, nVer), iRet);
		break;
	}

	snprintf(szValue, sizeof(szValue), "%s</%s>\n", szPrefix, pstField->szName);
	CHECK_FUNC_RET(bytearray_append_string(pstByteArray, szValue, strlen(szValue)), iRet);

	return 0;
}

LPFIELD test_union_get_sub_field(LPFIELD pstField, U16 nTag)
{
	if (NULL == pstField) return NULL;

	switch (nTag)
	{
	case 0xFFFF:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stSelection);
	default:
		return test_union_get_sub_field_by_selection(pstField);
	}

	return NULL;
}

LPFIELD test_union_get_sub_field_by_selection(LPFIELD pstField)
{
	if (NULL == pstField) return NULL;

	switch (((LPTESTUNION)pstField)->stSelection.nValue)
	{
	case 2:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stMoney);
	case 3:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stTestMsg);
	case 4:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stGold);
	case 5:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stDesc);
	case 6:
		return (LPFIELD)(&((LPTESTUNION)pstField)->stArrIntField);
	}
	return NULL;
}

LPFIELD test_union_get_sub_field_by_name(LPFIELD pstField, const char* szName)
{
	if (0 == strncmp(szName, "Selection", sizeof("Selection"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stSelection);
	if (0 == strncmp(szName, "Money", sizeof("Money"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stMoney);
	if (0 == strncmp(szName, "TestMsg", sizeof("TestMsg"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stTestMsg);
	if (0 == strncmp(szName, "Gold", sizeof("Gold"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stGold);
	if (0 == strncmp(szName, "Desc", sizeof("Desc"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stDesc);
	if (0 == strncmp(szName, "IntField", sizeof("IntField"))) return (LPFIELD)(&((LPTESTUNION)pstField)->stArrIntField);
	return NULL;
}

