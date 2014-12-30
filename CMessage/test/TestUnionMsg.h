
/*
 * @(#) TestUnionMsg.h Created by @itfriday message creator
 */

#ifndef TEST_UNION_MSG_H
#define TEST_UNION_MSG_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "UnionMsg.h"

/**
 * a union object
 */
struct tagTestUnionMsg
{
	FIELD stField;
	UINTFIELD stSequence;  /* 原因 */
	USHORTFIELD stVersion; /* 原因 */
	UNIONMSG stUnionMsg;   /* Test Message2 */
};

typedef struct tagTestUnionMsg  TESTUNIONMSG;
typedef struct tagTestUnionMsg* LPTESTUNIONMSG;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestUnionMsgFieldInfo;

#endif
