
/*
 * @(#) TestIdipMsg.h Created by @itfriday message creator
 */

#ifndef TEST_IDIP_MSG_H
#define TEST_IDIP_MSG_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "IdipMsg.h"

/**
 * a union object
 */
struct tagTestIdipMsg
{
	FIELD stField;
	UINTFIELD stSequence;  /* 原因 */
	USHORTFIELD stVersion; /* 原因 */
	IDIPMSG stIdipMsg;     /* Test Message2 */
};

typedef struct tagTestIdipMsg  TESTIDIPMSG;
typedef struct tagTestIdipMsg* LPTESTIDIPMSG;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestIdipMsgFieldInfo;

#endif
