
/*
 * @(#) TestMsg2.h Created by @itfriday message creator
 */

#ifndef TEST_MSG2_H
#define TEST_MSG2_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"

/**
 * Just a Test Message object
 */
struct tagTestMsg2
{
	FIELD stField;

	U16 nTestMsgNum;          /* 金币(Array Number) */
	TESTMSG astTestMsg[4];    /* 金币(Array Number) */
	ARRAYFIELD stArrTestMsg;  /* 金币(Array Struct Info) */

	U16 nIntFieldNum;         /* 类型列表(Array Number) */
	INTFIELD astIntField[4];  /* 类型列表(Array Number) */
	ARRAYFIELD stArrIntField; /* 类型列表(Array Struct Info) */
};

typedef struct tagTestMsg2  TESTMSG2;
typedef struct tagTestMsg2* LPTESTMSG2;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestMsg2FieldInfo;

#endif
