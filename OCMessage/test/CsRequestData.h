/*
 * @(#) CsRequestData.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"
#import "LoginRequest.h"

@interface CsRequestData : PPCompositeField

/**
 * Union字段标识
 */
@property (nonatomic, assign) UInt16 selector;

/**
 * 客户端登录请求
 */
- (LoginRequest *) getLogin ;

/**
 * 获取好友列表请求
 */
- (void) setGetFriends:(SInt8)value ;

/**
 * 获取好友列表请求
 */
- (SInt8) getGetFriends ;

@end
