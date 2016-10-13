/*
 * @(#) CsMsgResponse.h Created by @itfriday message creator
 */

#import "PPCompositeField.h"
#import "CsResponseData.h"

@interface CsMsgResponse : PPCompositeField

/**
 * 响应码
 */
- (void) setEno:(SInt16)value ;

/**
 * 响应码
 */
- (SInt16) getEno ;

/**
 * 命令字
 */
- (void) setCmd:(SInt16)value ;

/**
 * 命令字
 */
- (SInt16) getCmd ;

/**
 * 消息结构体
 */
- (CsResponseData *) getRespData ;

@end
