/**
 * @(#) PPStringField.m Created on 2016-09-11
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

#import "PPStringField.h"

@implementation PPStringField

/**
 * 字段编码
 * @param buff 保存字段编码后的协议信息
 * @param tag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
- (int) encode:(NSMutableData *)buff tag:(UInt16)tag {
    // 编码TAG
    UInt16 ntag = CFSwapInt16BigToHost(tag);
    [buff appendBytes:&ntag length:sizeof(ntag)];
    // 编码Type
    UInt8 type = FIELD_TYPE_STRING;
    [buff appendBytes:&type length:sizeof(type)];
    // 编码长度
    NSData* pData = [_value dataUsingEncoding:NSUTF8StringEncoding];
    UInt32 len = (UInt32)[pData length];
    len = CFSwapInt32BigToHost(len);
    [buff appendBytes:&len length:sizeof(len)];
    // 编码值
    [buff appendData:pData];
    
    return 0;
}

/**
 * 字段解码
 * @param buff 要解码的协议消息
 * @param start 字段在协议消息中的起始位置
 * @return 成功返回0，失败返回错误码
 */
- (int) decode:(NSData *)buff start:(int)start {
#if CHECK_ON_DECODE
    // 为了保险，这里做一下判断，其实可以不必加这个判断的
    UInt32 minlen = sizeof(UInt16) + sizeof(UInt8) + sizeof(UInt32);
    if ([buff length] < start + minlen) {
        return ERROR_DECODE_BUFSIZE_SHORT;
    }
#endif
    
    // 获取字段长度
    UInt32 len = 0;
    UInt32 pos = start + sizeof(UInt16) + sizeof(UInt8);
    
    [buff getBytes:&len range:NSMakeRange(pos, sizeof(UInt32))];
    
    len = CFSwapInt32HostToBig(len);
    
    pos += sizeof(UInt32);
    // 获取字段的值
    if (len > 0) {
        NSData* pData = [buff subdataWithRange:NSMakeRange(pos, len)];
        _value = [[NSString alloc] initWithData:pData encoding:NSUTF8StringEncoding];
    } else {
        _value = @"";
    }
    
    return 0;
}

/**
 * 字段格式化为可读形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) format:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix {
    [buff appendFormat:@"%@%@ = %@\n", suffix, fieldName, _value];
}

/**
 * 字段格式化为xml形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) toXml:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix {
    [buff appendFormat:@"%@<%@>%@</%@>\n", suffix, fieldName, _value, fieldName];
}

@end
