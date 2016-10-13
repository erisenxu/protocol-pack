/*
 * @(#) LoginResponse.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"

@interface LoginResponse : PPCompositeField

/**
 * 玩家GID
 */
- (void) setGID:(UInt64)value ;

/**
 * 玩家GID
 */
- (UInt64) getGID ;

/**
 * 用户VIP类型
 */
- (void) setUserType:(SInt8)value ;

/**
 * 用户VIP类型
 */
- (SInt8) getUserType ;

/**
 * 用户名称
 */
- (void) setUserName:(NSString *)value ;

/**
 * 用户名称
 */
- (NSString *) getUserName ;

/**
 * 用户头像URL地址
 */
- (void) setUserImage:(NSString *)value ;

/**
 * 用户头像URL地址
 */
- (NSString *) getUserImage ;

@end
