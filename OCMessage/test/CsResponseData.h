/*
 * @(#) CsResponseData.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"
#import "LoginResponse.h"
#import "FriendInfoList.h"

@interface CsResponseData : PPCompositeField

/**
 * Union字段标识
 */
@property (nonatomic, assign) UInt16 selector;

/**
 * 登录响应
 */
- (LoginResponse *) getLogin ;

/**
 * 获取好友列表响应
 */
- (FriendInfoList *) getGetFriends ;

@end
