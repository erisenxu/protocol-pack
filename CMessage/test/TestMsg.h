
/*
 * @(#) TestMsg.h Created by feimao message creator
 */

#ifndef TEST_MSG_H
#define TEST_MSG_H

#include "field/FieldInc.h"
#include "StartMacro.h"

/**
 * Just a Test Message object
 */
struct tagTestMsg
{
	FIELD stField;
	INTFIELD stMoney;         // 金币

	U16 nIntFieldNum;         // 类型列表(Array Number)
	INTFIELD astIntField[4];  // 类型列表(Array Number)
	ARRAYFIELD stArrIntField; // 类型列表(Array Struct Info)
	INTFIELD stGold;          // 钻石
};

typedef struct tagTestMsg  TESTMSG;
typedef struct tagTestMsg* LPTESTMSG;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestMsgFieldInfo;

#endif
