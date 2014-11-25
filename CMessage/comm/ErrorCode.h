/*
 * @(#) ErrorCode.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef ERROR_CODE_H
#define ERROR_CODE_H

/* 普通错误码-1~-1000 */
#define ERROR_INPUT_PARAM_NULL                      -1      /* 输入参数不合法，为NULL */

/* 编解码错误码-1001~-1100 */
#define ERROR_ENCODE_BUFSIZE_SHORT                  -1001   /* 消息编码时缓存太小 */
#define ERROR_DECODE_BUFSIZE_SHORT                  -1002   /* 消息解码时缓存太小 */
#define ERROR_APPEND_BUFSIZE_SHORT                  -1003   /* 向数组中扩展字符时，数组长度太小 */
#define ERROR_ARRAY_SUB_FIELD_INFO_NULL             -1004   /* 数组字段的子字段信息为NULL */
#define ERROR_DECODE_ARRAY_LONG                     -1005   /* 数组解码时，数组个数太大 */

/* XML解析错误码段-1501~-1600 */
#define ERROR_XML_LOAD_FIELD_NULL                   -1501   /* XML-Loader的当前字段对象为NULL */
#define ERROR_XML_LOAD_GET_SUB_FIELD_FUNC_NULL      -1502   /* GetSubFieldByName未定义 */
#define ERROR_XML_LOAD_NO_SUB_FIELD                 -1503   /* 未找到给定名字的子字段 */
#define ERROR_XML_LOAD_PARSE                        -1504   /* 解析xml出错 */
#define ERROR_XML_LOAD_ERROR                        -1505   /* 解析出现致命错误 */
#define ERROR_XML_LOAD_FATAL_ERROR                  -1506   /* 解析出现致命错误 */
#define ERROR_XML_LOAD_VALUE_TOO_LONG               -1507   /* 字段的值太长 */

#endif

