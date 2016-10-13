/*
 * @(#) FriendInfoList.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"
#import "FriendInfo.h"

@interface FriendInfoList : PPCompositeField

/**
 * 好友数量
 */
- (void) setFriendNumber:(UInt8)value ;

/**
 * 好友数量
 */
- (UInt8) getFriendNumber ;

/**
 * 好友列表
 */
- (FriendInfo *) getFriendInfo:(UInt32)index ;

/**
 * 类型数量
 */
- (void) setTypeNumber:(UInt8)value ;

/**
 * 类型数量
 */
- (UInt8) getTypeNumber ;

/**
 * 类型列表
 */
- (void) setTypes:(UInt32)index value:(UInt64)value ;

/**
 * 类型列表
 */
- (UInt64) getTypes:(UInt32)index ;

@end
