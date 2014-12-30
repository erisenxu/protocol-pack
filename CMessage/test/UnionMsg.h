
/*
 * @(#) UnionMsg.h Created by @itfriday message creator
 */

#ifndef UNION_MSG_H
#define UNION_MSG_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"
#include "TestMsg2.h"

/**
 * Union Message
 */
struct tagUnionMsg
{
	FIELD stField;
	SHORTFIELD stSelection;    /* Just added for simulate union selection */
	TESTMSG stTestMsg;   /* Test Message */
	TESTMSG2 stTestMsg2; /* Test Message2 */
};

typedef struct tagUnionMsg  UNIONMSG;
typedef struct tagUnionMsg* LPUNIONMSG;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stUnionMsgFieldInfo;

#endif
