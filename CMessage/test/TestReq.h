
/*
 * @(#) TestReq.h Created by feimao message creator
 */

#ifndef TEST_REQ_H
#define TEST_REQ_H

#include "field/FieldInc.h"
#include "StartMacro.h"

/**
 * 测试用消息
 */
struct tagTestReq
{
	FIELD stField;
	ULONGFIELD stGID; // GID
	INTFIELD stMoney; // 金币
	INTFIELD stGold;  // 钻石
};

typedef struct tagTestReq  TESTREQ;
typedef struct tagTestReq* LPTESTREQ;

/**
 * 字段信息定义
 */
extern FIELDINFO g_stTestReqFieldInfo;

#endif
