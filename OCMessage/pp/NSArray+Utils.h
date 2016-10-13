//
//  NSArray+Utils.h
//  WeiYP
//
//  Created by APPLE on 16/4/9.
//  Copyright © 2016年 @itfriday. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray<ObjectType> (Utils)

/**
 * 获取index处的对象，若越界，返回nil
 */
- (ObjectType)objectByIndex:(NSUInteger)index;

@end
