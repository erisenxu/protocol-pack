/*
 * @(#) MsgBase.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MSG_BASE_H
#define MSG_BASE_H

#include "Field.h"

struct tagMsgBase
{
    //FIELD stField;
    U16 nCmdID;         /* 消息命令号 */
    U16 nVer;           /* 协议版本 */
    /*U8 bZip; 是否加密或压缩？可以放在连接层来处理。
     *U8 bEncrypt;*/
    /* 消息数据区，或者这里可以用一个union替代 */
    LPFIELD pstField;
};

struct tagMsgResponse
{
    U16 nCmdID;         /* 消息命令号 */
    U16 nVer;           /* 协议版本 */
    U16 nStatus;        /* 返回码 */
    /*U8 bZip; 是否加密或压缩？可以放在连接层来处理。
     *U8 bEncrypt;*/
    /* 消息数据区，或者这里可以用一个union替代 */
    LPFIELD pstField;
};

/**
 * 注意：在实现时，可以对message实现一个encode、decode的函数，然后pstField的encode和decode采用FIELD的那套来实现
 */

#endif
