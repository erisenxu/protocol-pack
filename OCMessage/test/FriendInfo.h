/*
 * @(#) FriendInfo.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"

@interface FriendInfo : PPCompositeField

/**
 * 好友GID
 */
- (void) setGID:(UInt64)value ;

/**
 * 好友GID
 */
- (UInt64) getGID ;

/**
 * 好友名称
 */
- (void) setFriendName:(NSString *)value ;

/**
 * 好友名称
 */
- (NSString *) getFriendName ;

/**
 * 好友头像URL地址
 */
- (void) setFriendImage:(NSString *)value ;

/**
 * 好友头像URL地址
 */
- (NSString *) getFriendImage ;

@end
