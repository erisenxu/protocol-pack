//
//  ErrCode.h
//  common
//
//  Created by erisenxu on 16/7/1.
//  Copyright © 2016年 @itfriday. All rights reserved.
//

#ifndef ERR_CODE_H
#define ERR_CODE_H

#define RET_SUCCESS                 0
#define RET_ERR_UNKNOWN             -1          // 未知错误
#define RET_ERR_PACK_ERR            -2          // 服务器打包格式不正确
#define ERROR_INPUT_PARAM_NULL      -3          // 输入参数不对

/* 编解码错误码-1001~-1100 */
#define ERROR_ENCODE_BUFSIZE_SHORT                  -1001   /* 消息编码时缓存太小 */
#define ERROR_DECODE_BUFSIZE_SHORT                  -1002   /* 消息解码时缓存太小 */
#define ERROR_APPEND_BUFSIZE_SHORT                  -1003   /* 向数组中扩展字符时，数组长度太小 */
#define ERROR_ARRAY_SUB_FIELD_INFO_NULL             -1004   /* 数组字段的子字段信息为NULL */
#define ERROR_DECODE_ARRAY_LONG                     -1005   /* 数组解码时，数组个数太大 */
#define ERROR_DECODE_INVALID_MSG                    -1006   /* 消息解码到不合法的协议 */
#define ERROR_ENCODE_INVALID_MSG                    -1007   /* 消息编码到不合法的协议 */

#endif /* ERR_CODE_H */
