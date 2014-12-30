
/*
 * @(#) IdipMsg.h Created by @itfriday message creator
 */

#ifndef IDIP_MSG_H
#define IDIP_MSG_H

#include "field/FieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"
#include "TestMsg2.h"

/**
 * IDIP Message
 */
struct tagIdipMsg
{
	FIELD stField;
	SHORTFIELD stSelection;    /* Just added for simulate union selection */
	TESTMSG stTestMsg;   /* Test Message */
	TESTMSG2 stTestMsg2; /* Test Message2 */
};

typedef struct tagIdipMsg  IDIPMSG;
typedef struct tagIdipMsg* LPIDIPMSG;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stIdipMsgFieldInfo;

#endif
