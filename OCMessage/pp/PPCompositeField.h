/**
 * @(#) PPCompositeField.h Created on 2016-09-11
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

#import "PPField.h"

@interface PPCompositeField : NSObject <PPField>

/**
 * 通过标签查询子字段
 * @param tag 子字段的标签
 * @return 返回tag对应的子字段，若没有子字段，返回null
 */
- (id<PPField>) getSubField:(UInt16)tag ;

/**
 * 取某个类型字段的长度
 * @param type 字段类型
 * @param buff 要解析的协议，里面可能包含长度字段
 * @param start 协议的起始
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
+ (SInt32) getLengthByType:(UInt8)type data:(NSData *)buff start:(int)start ;

@end
