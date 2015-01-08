/*
 * @(#) MsgBase.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
