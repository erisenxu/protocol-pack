
/*
 * @(#) TestUnion3.h Created by feimao message creator
 */

#ifndef TEST_UNION3_H
#define TEST_UNION3_H

#include "field/FieldInc.h"
#include "StartMacro.h"
#include "TestUnion2.h"

/**
 * a union object
 */
struct tagTestUnion3
{
	FIELD stField;
	INTFIELD stReason;   // 原因
	TESTUNION2 stUnion2; // Test message
	INTFIELD stReason2;  // 原因
};

typedef struct tagTestUnion3  TESTUNION3;
typedef struct tagTestUnion3* LPTESTUNION3;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestUnion3FieldInfo;

#endif
