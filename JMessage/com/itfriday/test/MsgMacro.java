/*
 * @(#) MsgMacro.java Created by @itfriday message creator
 */

package com.itfriday.test;

public interface MsgMacro {
    int MAX_CODE_LEN = 64;                                      // 鉴权码最大长度
    int MAX_NAME_LEN = 64;                                      // 最大名字长度
    int MAX_URL_LEN = 256;                                      // 最大URL地址长度
    int MAX_FRIEND_NUMBER = 200;                                // 最大好友数量
    int MAX_TYPE_NUMBER = 40;                                   // 最大类型数量
    int CS_MSG_LOGIN = 1;                                       // 登录
    int CS_MSG_GET_FRIEND_LIST = 2;                             // 获取好友列表
}
