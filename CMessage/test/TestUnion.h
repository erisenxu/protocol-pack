
/*
 * @(#) TestUnion.h Created by feimao message creator
 */

#ifndef TEST_UNION_H
#define TEST_UNION_H

#include "field/FieldInc.h"
#include "StartMacro.h"
#include "TestMsg.h"

/**
 * a union object
 */
struct tagTestUnion
{
	FIELD stField;
	SHORTFIELD stSelection;    // Just added for simulate union selection
	INTFIELD stMoney;  // 金币
	TESTMSG stTestMsg; // Test message
	INTFIELD stGold;   // 钻石
};

typedef struct tagTestUnion  TESTUNION;
typedef struct tagTestUnion* LPTESTUNION;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestUnionFieldInfo;

#endif
