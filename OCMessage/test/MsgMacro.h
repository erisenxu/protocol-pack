/*
 * @(#) MsgMacro.h Created by @itfriday message creator
 */

#ifndef MSG_MACRO_H
#define MSG_MACRO_H

#define MAX_CODE_LEN                                            64		/* 鉴权码最大长度 */
#define MAX_NAME_LEN                                            64		/* 最大名字长度 */
#define MAX_URL_LEN                                             256		/* 最大URL地址长度 */
#define MAX_FRIEND_NUMBER                                       200		/* 最大好友数量 */
#define MAX_TYPE_NUMBER                                         40		/* 最大类型数量 */

/**
 * 客户端消息类型
 */
enum tagCS_MSG_TYPE_
{
	CS_MSG_LOGIN = 1,                                              /* 登录 */
	CS_MSG_GET_FRIEND_LIST = 2,                                    /* 获取好友列表 */
};

#endif
