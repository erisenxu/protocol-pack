/*
 * @(#) LoginResponse.m Created by @itfriday message creator
 */

#import "LoginResponse.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface LoginResponse ()
/**
 * 玩家GID
 */
@property (nonatomic, strong) PPULongField *mGID;

/**
 * 用户VIP类型
 */
@property (nonatomic, strong) PPByteField *mUserType;

/**
 * 用户名称
 */
@property (nonatomic, strong) PPStringField *mUserName;

/**
 * 用户头像URL地址
 */
@property (nonatomic, strong) PPStringField *mUserImage;

@end

@implementation LoginResponse

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mGID  = [[PPULongField alloc] init];
        _mUserType  = [[PPByteField alloc] init];
        _mUserName  = [[PPStringField alloc] init];
        _mUserImage  = [[PPStringField alloc] init];
    }
    return self;
}


/**
 * 玩家GID
 */
- (void) setGID:(UInt64)value {
    _mGID.value = value;
}

/**
 * 玩家GID
 */
- (UInt64) getGID {
    return _mGID.value;
}

/**
 * 用户VIP类型
 */
- (void) setUserType:(SInt8)value {
    _mUserType.value = value;
}

/**
 * 用户VIP类型
 */
- (SInt8) getUserType {
    return _mUserType.value;
}

/**
 * 用户名称
 */
- (void) setUserName:(NSString *)value {
    _mUserName.value = value;
}

/**
 * 用户名称
 */
- (NSString *) getUserName {
    return _mUserName.value;
}

/**
 * 用户头像URL地址
 */
- (void) setUserImage:(NSString *)value {
    _mUserImage.value = value;
}

/**
 * 用户头像URL地址
 */
- (NSString *) getUserImage {
    return _mUserImage.value;
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
    [_mGID encode:buff tag:1];
    [_mUserType encode:buff tag:2];
    [_mUserName encode:buff tag:3];
    [_mUserImage encode:buff tag:4];

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
    [_mGID format:buff fieldName:@"GID" suffix:sSubPrefix];
    [_mUserType format:buff fieldName:@"UserType" suffix:sSubPrefix];
    [_mUserName format:buff fieldName:@"UserName" suffix:sSubPrefix];
    [_mUserImage format:buff fieldName:@"UserImage" suffix:sSubPrefix];
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
    [_mGID toXml:buff fieldName:@"GID" suffix:sSubPrefix];
    [_mUserType toXml:buff fieldName:@"UserType" suffix:sSubPrefix];
    [_mUserName toXml:buff fieldName:@"UserName" suffix:sSubPrefix];
    [_mUserImage toXml:buff fieldName:@"UserImage" suffix:sSubPrefix];
    [buff appendFormat:@"%@</%@>\n", suffix, fieldName];
}

/**
 * 通过标签查询子字段
 * @param tag 子字段的标签
 * @return 返回tag对应的子字段，若没有子字段，返回null
 */
- (id<PPField>) getSubField:(UInt16)tag {
    switch (tag) {
    case 1:
        return _mGID;
    case 2:
        return _mUserType;
    case 3:
        return _mUserName;
    case 4:
        return _mUserImage;
    default:
        return nil;
    }
}

@end
