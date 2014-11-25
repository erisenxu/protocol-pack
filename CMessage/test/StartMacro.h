/*
 * @(#) StartMacro.h Created by feimao message creator
 */

#ifndef START_MACRO
#define START_MACRO

#define MAX_TEST_INFO_NUM                                       20	/* 最大请求信息数量 */
#define MAX_TYPE_NUM                                            30	/* 最大类型数量 */
#define MAX_GID_NUM                                             64	/* 最大GID数量 */
#define MAX_ACTIVITY_PARAM_VALUE_NUM                            10	/* 最大活动参数值个数 */
#define MAX_ACTIVITY_PARAM_NUM                                  20	/* 最大活动参数个数 */
#define MAX_ACTIVITY_AWARD_NUM                                  20	/* 最大活动奖励个数 */
#define MAX_ONCE_GET_COMM_DATA_NUM                              100	/* 通用系统数据表数量 */
#define MAX_ACCEPT_TASK_NUM                                     20	/* 角色身上最大任务数 */
#define MAX_TASK_TYPE_NUM                                       10	/* 最大任务类型数 */

/**
 * 消息类型
 */
enum tagMSG_TYPE_
{
	MSG_TEST_REQ = 1,                                              /* 测试用消息类型1 */
	MSG_TEST_REQ2 = 2,                                             /* 测试用消息类型2 */
};

/**
 * 怪物属性类型
 */
enum tagMONSTERBUY_TYPE_
{
	MONSTERBUY_TYPE_0 = 0,                                         /* 无 */
	MONSTERBUY_TYPE_WATER = 1,                                     /* 水 */
	MONSTERBUY_TYPE_ELECTRICITY = 2,                               /* 电 */
	MONSTERBUY_TYPE_FIRE = 3,                                      /* 火 */
	MONSTERBUY_TYPE_DARK = 4,                                      /* 暗 */
	MONSTERBUY_TYPE_WIND = 5,                                      /* 风 */
	MONSTERBUY_TYPE_WATER_FIRE = 6,                                /* 水火 */
	MONSTERBUY_TYPE_WATER_ELECTRIC = 7,                            /* 水电 */
	MONSTERBUY_TYPE_WATER_DARK = 8,                                /* 水暗 */
	MONSTERBUY_TYPE_FIRE_ELECTRIC = 9,                             /* 火电 */
	MONSTERBUY_TYPE_FIRE_DARK = 10,                                /* 火暗 */
	MONSTERBUY_TYPE_DARK_ELECTRIC = 11,                            /* 暗电 */
};

/**
 * 死亡原因
 */
enum tagDIE_REASON
{
	DIE_REASON_MISSILE = 1,                                        /* 导弹击中 */
	DIE_REASON_BOSS = 2,                                           /* 被BOSS打死 */
	DIE_REASON_CRASH = 3,                                          /* 自杀机撞死 */
	DIE_REASON_OTHER = 4,                                          /* 其它原因 */
	DIE_REASON_MAP_OBSTACLE = 5,                                   /* 地图障碍物 */
};

#endif
