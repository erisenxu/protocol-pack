/*
 * @(#) MErrorCode.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MERROR_CODE_H
#define MERROR_CODE_H

/* 普通错误码-1~-1000 */
#define M_ERROR_INPUT_PARAM_NULL          -1        // 输入参数不合法，为NULL

/* 编解码错误码-1001~-1100 */
#define M_ERROR_ENCODE_BUFSIZE_SHORT      -1001     // 消息编码时缓存太小
#define M_ERROR_DECODE_BUFSIZE_SHORT      -1002     // 消息解码时缓存太小
#define M_ERROR_DECODE_ARRAY_LONG         -1003     // 解码数组时，数组字段太长

#endif
