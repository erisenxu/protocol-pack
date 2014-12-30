
/*
 * @(#) TestUnion.h Created by @itfriday message creator
 */

#ifndef TEST_UNION_H
#define TEST_UNION_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"

/**
 * a union object
 */
struct tagTestUnion
{
	FIELD stField;
	SHORTFIELD stSelection;    /* Just added for simulate union selection */
	INTFIELD stMoney;         /* 金币 */
	TESTMSG stTestMsg;        /* Test message */
	INTFIELD stGold;          /* 钻石 */

	char szDesc[1];           /* 描述 */
	STRINGFIELD stDesc;       /* 描述(String Struct Info) */

	U16 nIntFieldNum;         /* 类型列表(Array Number) */
	INTFIELD astIntField[4];  /* 类型列表(Array Number) */
	ARRAYFIELD stArrIntField; /* 类型列表(Array Struct Info) */
};

typedef struct tagTestUnion  TESTUNION;
typedef struct tagTestUnion* LPTESTUNION;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestUnionFieldInfo;

#endif
