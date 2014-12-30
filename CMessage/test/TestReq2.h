
/*
 * @(#) TestReq2.h Created by @itfriday message creator
 */

#ifndef TEST_REQ2_H
#define TEST_REQ2_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "TestReq.h"

/**
 * 测试用消息
 */
struct tagTestReq2
{
	FIELD stField;
	TESTREQ stTestReq;                     /* 请求信息1 */

	U16 nReqInfoNum;                       /* 请求信息(Array Number) */
	TESTREQ astReqInfo[MAX_TEST_INFO_NUM]; /* 请求信息(Array Number) */
	ARRAYFIELD stArrReqInfo;               /* 请求信息(Array Struct Info) */

	U16 nTypesNum;                         /* 类型列表(Array Number) */
	UINTFIELD astTypes[MAX_TYPE_NUM];      /* 类型列表(Array Number) */
	ARRAYFIELD stArrTypes;                 /* 类型列表(Array Struct Info) */

	char szGID[MAX_GID_NUM];               /* GID */
	STRINGFIELD stGID;                     /* GID(String Struct Info) */
};

typedef struct tagTestReq2  TESTREQ2;
typedef struct tagTestReq2* LPTESTREQ2;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestReq2FieldInfo;

#endif
