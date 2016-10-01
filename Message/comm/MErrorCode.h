/*
 * @(#) MErrorCode.h Created on 2014-03-27
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

#ifndef MERROR_CODE_H
#define MERROR_CODE_H

/* 普通错误码-1~-1000 */
#define M_ERROR_INPUT_PARAM_NULL          -1        // 输入参数不合法，为NULL

/* 编解码错误码-1001~-1100 */
#define M_ERROR_ENCODE_BUFSIZE_SHORT                  -1001   /* 消息编码时缓存太小 */
#define M_ERROR_DECODE_BUFSIZE_SHORT                  -1002   /* 消息解码时缓存太小 */
#define M_ERROR_APPEND_BUFSIZE_SHORT                  -1003   /* 向数组中扩展字符时，数组长度太小 */
#define M_ERROR_ARRAY_SUB_FIELD_INFO_NULL             -1004   /* 数组字段的子字段信息为NULL */
#define M_ERROR_DECODE_ARRAY_LONG                     -1005   /* 数组解码时，数组个数太大 */
#define M_ERROR_DECODE_INVALID_MSG                    -1006   /* 消息解码到不合法的协议 */

/* XML解析错误码段-1501~-1600 */
#define M_ERROR_XML_LOAD_FIELD_NULL                   -1501   /* XML-Loader的当前字段对象为NULL */
#define M_ERROR_XML_LOAD_GET_SUB_FIELD_FUNC_NULL      -1502   /* GetSubFieldByName未定义 */
#define M_ERROR_XML_LOAD_NO_SUB_FIELD                 -1503   /* 未找到给定名字的子字段 */
#define M_ERROR_XML_LOAD_PARSE                        -1504   /* 解析xml出错 */
#define M_ERROR_XML_LOAD_ERROR                        -1505   /* 解析出现致命错误 */
#define M_ERROR_XML_LOAD_FATAL_ERROR                  -1506   /* 解析出现致命错误 */
#define M_ERROR_XML_LOAD_VALUE_TOO_LONG               -1507   /* 字段的值太长 */

#endif
