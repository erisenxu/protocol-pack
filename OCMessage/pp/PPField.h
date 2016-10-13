/**
 * @(#) PPField.h Created on 2016-09-11
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

#import <Foundation/Foundation.h>

#define FIELD_TYPE_BYTE         1   // S8，占1个字节
#define FIELD_TYPE_UBYTE        2   // U8，占1个字节
#define FIELD_TYPE_SHORT        3   // S16，占2个字节
#define FIELD_TYPE_USHORT       4   // U16，占2个字节
#define FIELD_TYPE_INT          5   // S32，占4个字节
#define FIELD_TYPE_UINT         6   // U32，占4个字节
#define FIELD_TYPE_LONG         7   // S64，占8个字节
#define FIELD_TYPE_ULONG        8   // U64，占8个字节
#define FIELD_TYPE_STRING       9   // 字符串，特殊的TLV字段
#define FIELD_TYPE_BYTES        10  // 字节数组，特殊的TLV字段
#define FIELD_TYPE_TLV          11  // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
#define FIELD_TYPE_ARRAY        12  // 数组

@protocol PPField <NSObject>

//@required
@optional

/**
 * 字段编码
 * @param buff 保存字段编码后的协议信息
 * @param tag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
- (int) encode:(NSMutableData *)buff tag:(UInt16)tag ;

/**
 * 字段解码
 * @param buff 要解码的协议消息
 * @param start 字段在协议消息中的起始位置
 * @return 成功返回0，失败返回错误码
 */
- (int) decode:(NSData *)buff start:(int)start ;

/**
 * 字段格式化为可读形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) format:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix ;

/**
 * 字段格式化为xml形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) toXml:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix ;

@end
