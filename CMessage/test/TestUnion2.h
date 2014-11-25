
/*
 * @(#) TestUnion2.h Created by feimao message creator
 */

#ifndef TEST_UNION2_H
#define TEST_UNION2_H

#include "field/FieldInc.h"
#include "StartMacro.h"
#include "TestUnion.h"

/**
 * a union object
 */
struct tagTestUnion2
{
	FIELD stField;
	INTFIELD stReason; // 原因
	TESTUNION stUnion; // Test message
};

typedef struct tagTestUnion2  TESTUNION2;
typedef struct tagTestUnion2* LPTESTUNION2;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestUnion2FieldInfo;

#endif
