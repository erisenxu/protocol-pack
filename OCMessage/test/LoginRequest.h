/*
 * @(#) LoginRequest.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"

@interface LoginRequest : PPCompositeField

/**
 * 登录鉴权码
 */
- (void) setCode:(NSString *)value ;

/**
 * 登录鉴权码
 */
- (NSString *) getCode ;

/**
 * 系统类型：0 - iOS，1 - Android
 */
- (void) setOsType:(SInt32)value ;

/**
 * 系统类型：0 - iOS，1 - Android
 */
- (SInt32) getOsType ;

@end
