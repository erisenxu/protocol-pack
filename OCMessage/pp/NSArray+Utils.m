//
//  NSArray+Utils.m
//  WeiYP
//
//  Created by APPLE on 16/4/9.
//  Copyright © 2016年 @itfriday. All rights reserved.
//

#import "NSArray+Utils.h"

@implementation NSArray (Utils)

/**
 * 获取index处的对象，若越界，返回nil
 */
- (id)objectByIndex:(NSUInteger)index {
    return index >= [self count] ? nil : [self objectAtIndex:index];
}

@end
