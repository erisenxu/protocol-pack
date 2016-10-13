/**
 * @(#) PPArrayField.m Created on 2016-09-11
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

#import "PPArrayField.h"
#import "NSArray+Utils.h"
#import "ErrorCode.h"
#include "PPCompositeField.h"

@interface PPArrayField ()

/**
 * 字段的值
 */
@property (nonatomic, strong) PPFieldCreator fieldCreator;

/**
 * 字段的值
 */
@property (nonatomic, strong) NSMutableArray* value;

@end

@implementation PPArrayField

/**
 * 初始化函数
 */
-(instancetype)init {
    return [self initWithFieldCreator:nil];
}

/**
 * 初始化函数
 */
- (instancetype) initWithFieldCreator:(PPFieldCreator)fieldCreator {
    if (self = [super init]) {
        _value = [[NSMutableArray alloc] init];
        _fieldCreator = fieldCreator;
    }
    return self;
}

/**
 * 获取指定索引处的数组元素对象
 * @param index 指定索引
 * @return 返回指定索引处的数组元素对象
 */
- (id) getFieldByIndex:(UInt32)index {
    
    // index 只可以>=0 && <= mValue.size(),如果等于mValue.size(), 需要重新创建一个新的
    if (index > [_value count]) return nil;
    
    if (index < [_value count]) return [_value objectAtIndex:index];
    
    if (_fieldCreator) {
        id o = _fieldCreator();
        [_value addObject:o];
        return o;
    }
    
    return nil;
}

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
    UInt8 type = FIELD_TYPE_ARRAY;
    [buff appendBytes:&type length:sizeof(type)];

    // 先将数组长度设置为0
    UInt32 len = 0;
    [buff appendBytes:&len length:sizeof(len)];
    
    // 记录下当前数组长度
    UInt32 iArrOldLen = (UInt32)[buff length];
    
    // 对数组进行编码
    // 数组数量
    UInt16 count = [_value count];
    UInt16 num = CFSwapInt16BigToHost(count);
    [buff appendBytes:&num length:sizeof(num)];

    // 数组子字段
    for (short i = 0; i < count; i++) {
        [[_value objectByIndex:i] encode:buff tag:tag];
    }
    
    // 修正数组长度
    UInt32 iArrAddLen = (UInt32)[buff length] - iArrOldLen;
    iArrAddLen = CFSwapInt32BigToHost(iArrAddLen);
    [buff replaceBytesInRange:NSMakeRange(iArrOldLen - 4, sizeof(iArrOldLen))
                    withBytes:&iArrAddLen length:sizeof(iArrOldLen)];
    
    return 0;
}

/**
 * 字段解码
 * @param buff 要解码的协议消息
 * @param start 字段在协议消息中的起始位置
 * @return 成功返回0，失败返回错误码
 */
- (int) decode:(NSData *)buff start:(int)start {
    UInt32 iHdrLen = sizeof(UInt16) + sizeof(UInt8) + sizeof(UInt32);
    UInt32 iStart = start + iHdrLen;
    UInt32 bufLen = (UInt32)[buff length];
    
    // 剩余字节长度
    int iLeftLen = bufLen - iStart;
    
    // 数组长度
    UInt16 nArrayNum = 0;
    [buff getBytes:&nArrayNum range:NSMakeRange(iStart, sizeof(nArrayNum))];
    nArrayNum = CFSwapInt16HostToBig(nArrayNum);

    iLeftLen -= 2;
    iStart += 2;
    
    // 数组元素类型长度检查
    if (bufLen < iStart + 3) {
        return ERROR_DECODE_BUFSIZE_SHORT;
    }
    
    // 数组元素类型
    UInt8 bType = 0;
    [buff getBytes:&bType range:NSMakeRange(iStart + 2, sizeof(bType))];
    
    // 清空数据
    [_value removeAllObjects];
    
    // 解析子字段
    for (UInt16 i = 0; i < nArrayNum; i++) {
        // 通过类型获得数据长度
        int iMsgLen = [PPCompositeField getLengthByType:bType data:buff start:iStart];
        if (iLeftLen < iMsgLen || iMsgLen < 0) {
            return ERROR_DECODE_BUFSIZE_SHORT;
        }
        [[self getFieldByIndex:i] decode:buff start:iStart];
        iStart += iMsgLen;
        iLeftLen -= iMsgLen;
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
    UInt16 count = [_value count];
    for (short i = 0; i < count; i++) {
        [[_value objectByIndex:i] format:buff fieldName:fieldName suffix:suffix];
    }
}

/**
 * 字段格式化为xml形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) toXml:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix {
    UInt16 count = [_value count];
    for (short i = 0; i < count; i++) {
        [[_value objectByIndex:i] toXml:buff fieldName:fieldName suffix:suffix];
    }
}

@end
