/*
 * @(#) CsRequestData.m Created by @itfriday message creator
 */

#import "CsRequestData.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface CsRequestData ()
/**
 * 客户端登录请求
 */
@property (nonatomic, strong) LoginRequest *mLogin;

/**
 * 获取好友列表请求
 */
@property (nonatomic, strong) PPByteField *mGetFriends;

@end

@implementation CsRequestData

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mLogin  = [[LoginRequest alloc] init];
        _mGetFriends  = [[PPByteField alloc] init];
    }
    return self;
}


/**
 * 客户端登录请求
 */
- (LoginRequest *) getLogin {
    if (_mLogin == nil) _mLogin  = [[LoginRequest alloc] init];
    return _mLogin;
}

/**
 * 获取好友列表请求
 */
- (void) setGetFriends:(SInt8)value {
    if (_mGetFriends == nil) _mGetFriends  = [[PPByteField alloc] init];
    _mGetFriends.value = value;
}

/**
 * 获取好友列表请求
 */
- (SInt8) getGetFriends {
    if (_mGetFriends == nil) _mGetFriends  = [[PPByteField alloc] init];
    return _mGetFriends.value;
}

/**
 * 字段编码
 * @param buff 保存字段编码后的协议信息
 * @param tag 字段的tag
 * @return 成功返回0，失败返回错误码
 */
- (int) encode:(NSMutableData *)buff tag:(UInt16)tag {
    // 编码TAG
    UInt16 ntag = CFSwapInt16BigToHost(tag);
    [buff appendBytes:&ntag length:sizeof(ntag)];
    // 编码Type
    UInt8 type = FIELD_TYPE_TLV;
    [buff appendBytes:&type length:sizeof(type)];

    // 先将长度设置为0
    UInt32 len = 0;
    [buff appendBytes:&len length:sizeof(len)];

    // 记录下当前数组长度
    UInt32 iArrOldLen = (UInt32)[buff length];

    // 编码子字段
    switch (_selector) {
    case CS_MSG_LOGIN:
        [_mLogin encode:buff tag:CS_MSG_LOGIN];
        break;
    case CS_MSG_GET_FRIEND_LIST:
        [_mGetFriends encode:buff tag:CS_MSG_GET_FRIEND_LIST];
        break;
    default:
        break;
    }

    // 修正数组长度
    UInt32 iArrAddLen = (UInt32)[buff length] - iArrOldLen;
    iArrAddLen = CFSwapInt32BigToHost(iArrAddLen);
    [buff replaceBytesInRange:NSMakeRange(iArrOldLen - 4, sizeof(iArrOldLen))
                    withBytes:&iArrAddLen length:sizeof(iArrOldLen)];
    return 0;
}

/**
 * 字段格式化为可读形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) format:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix {
    NSString* sSubPrefix = [NSString stringWithFormat:@"%@    ", suffix];
    [buff appendFormat:@"%@[%@]\n", suffix, fieldName];
    switch (_selector) {
    case CS_MSG_LOGIN:
        [_mLogin format:buff fieldName:@"Login" suffix:sSubPrefix];
        break;
    case CS_MSG_GET_FRIEND_LIST:
        [_mGetFriends format:buff fieldName:@"GetFriends" suffix:sSubPrefix];
        break;
    default:
        break;
    }
}

/**
 * 字段格式化为xml形式
 * @param buff 保存格式化的字符串
 * @param fieldName 字段的名字
 * @param suffix 格式化前缀
 */
- (void) toXml:(NSMutableString *)buff fieldName:(NSString *)fieldName suffix:(NSString *)suffix {
    NSString* sSubPrefix = [NSString stringWithFormat:@"%@    ", suffix];

    [buff appendFormat:@"%@<%@>\n", suffix, fieldName];
    switch (_selector) {
    case CS_MSG_LOGIN:
        [_mLogin toXml:buff fieldName:@"Login" suffix:sSubPrefix];
        break;
    case CS_MSG_GET_FRIEND_LIST:
        [_mGetFriends toXml:buff fieldName:@"GetFriends" suffix:sSubPrefix];
        break;
    default:
        break;
    }
    [buff appendFormat:@"%@</%@>\n", suffix, fieldName];
}

/**
 * 通过标签查询子字段
 * @param tag 子字段的标签
 * @return 返回tag对应的子字段，若没有子字段，返回null
 */
- (id<PPField>) getSubField:(UInt16)tag {
    switch (tag) {
    case CS_MSG_LOGIN:
        _selector = tag;
        if (_mLogin == nil) _mLogin  = [[LoginRequest alloc] init];
        return _mLogin;
    case CS_MSG_GET_FRIEND_LIST:
        _selector = tag;
        if (_mGetFriends == nil) _mGetFriends  = [[PPByteField alloc] init];
        return _mGetFriends;
    default:
        return nil;
    }
}

@end
