/**
 * @(#) PPCompositeField.m Created on 2016-09-11
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

#import "PPCompositeField.h"
#import "ErrorCode.h"

@implementation PPCompositeField

/**
 * 字段解码
 * @param buff 要解码的协议消息
 * @param start 字段在协议消息中的起始位置
 * @return 成功返回0，失败返回错误码
 */
- (int)decode:(NSData *)buff start:(int)start {
    
    if (!buff || start < 0) {
        return ERROR_INPUT_PARAM_NULL;
    }
    
    UInt32 iMinLen = sizeof(UInt16) + sizeof(UInt8);    // 字段最小长度
    id<PPField> pstSubField = nil;
    
    UInt16 nTag = 0;
    UInt8 bType = 0;
    int iLeftLen;
    int iFieldLen;
    UInt32 len = (UInt32)[buff length];

    // 起始位置
    start += iMinLen;
    
    if (len < start + 4) {
        return ERROR_DECODE_BUFSIZE_SHORT;
    }
    
    // 求字段长度
    [buff getBytes:&iLeftLen range:NSMakeRange(start, sizeof(iLeftLen))];
    iLeftLen = CFSwapInt32HostToBig(iLeftLen);
    start += 4;
    
    while (iLeftLen > 0) {
        
        // 解析Tag和Type
        if (len < start + iMinLen) {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }
        
        // Tag和类型
        [buff getBytes:&nTag range:NSMakeRange(start, sizeof(nTag))];
        nTag = CFSwapInt16HostToBig(nTag);
        
        // 类型
        [buff getBytes:&bType range:NSMakeRange(start + 2, sizeof(bType))];
        
        // 消息长度
        iFieldLen = [PPCompositeField getLengthByType:bType data:buff start:start];
        if (iFieldLen < 0 || len < start + iFieldLen) {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }
        
        // 取消息对象
        pstSubField = [self getSubField:nTag];
        
        // 对认识的字段进行解码，不认识的字段直接丢弃
        if (pstSubField) {
            [pstSubField decode:buff start:start];
        }
        // 不认识的字段，直接丢弃 (兼容旧版本)
        start += iFieldLen;
        iLeftLen -= iFieldLen;
    }
    
    return 0;
}

/**
 * 通过标签查询子字段
 * @param tag 子字段的标签
 * @return 返回tag对应的子字段，若没有子字段，返回null
 */
- (id<PPField>) getSubField:(UInt16)tag {
    return nil;
}

/**
 * 取某个类型字段的长度
 * @param type 字段类型
 * @param buff 要解析的协议，里面可能包含长度字段
 * @param start 协议的起始
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
+ (SInt32) getLengthByType:(UInt8)type data:(NSData *)buff start:(int)start {
    int iMinLen = sizeof(UInt16) + sizeof(UInt8);
    
    switch (type) {
        case FIELD_TYPE_BYTE:
        case FIELD_TYPE_UBYTE:
            return iMinLen + sizeof(UInt8);
        case FIELD_TYPE_SHORT:
        case FIELD_TYPE_USHORT:
            return iMinLen + sizeof(UInt16);
        case FIELD_TYPE_INT:
        case FIELD_TYPE_UINT:
            return iMinLen + sizeof(UInt32);
        case FIELD_TYPE_LONG:
        case FIELD_TYPE_ULONG:
            return iMinLen + sizeof(UInt64);
        case FIELD_TYPE_STRING:
        case FIELD_TYPE_BYTES:
        case FIELD_TYPE_TLV:
        case FIELD_TYPE_ARRAY: {
            if (buff && [buff length] >= start + iMinLen + sizeof(UInt32)) {
                int nLen = 0;
                [buff getBytes:&nLen range:NSMakeRange(start + iMinLen, sizeof(UInt32))];
                nLen = CFSwapInt32HostToBig(nLen);
                return iMinLen + 4 + nLen;
            }
            return -1;
        }
        default:
            return -2;
    }
}

@end
