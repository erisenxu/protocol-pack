/*
 * @(#) CsMsgRequest.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"
#import "CsRequestData.h"

@interface CsMsgRequest : PPCompositeField

/**
 * 玩家GID
 */
- (void) setGID:(UInt64)value ;

/**
 * 玩家GID
 */
- (UInt64) getGID ;

/**
 * 消息命令字
 */
- (void) setCmd:(SInt16)value ;

/**
 * 消息命令字
 */
- (SInt16) getCmd ;

/**
 * 消息结构体
 */
- (CsRequestData *) getReqData ;

@end
