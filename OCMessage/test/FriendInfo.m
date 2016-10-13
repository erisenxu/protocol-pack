/*
 * @(#) FriendInfo.m Created by @itfriday message creator
 */

#import "FriendInfo.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface FriendInfo ()
/**
 * 好友GID
 */
@property (nonatomic, strong) PPULongField *mGID;

/**
 * 好友名称
 */
@property (nonatomic, strong) PPStringField *mFriendName;

/**
 * 好友头像URL地址
 */
@property (nonatomic, strong) PPStringField *mFriendImage;

@end

@implementation FriendInfo

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mGID  = [[PPULongField alloc] init];
        _mFriendName  = [[PPStringField alloc] init];
        _mFriendImage  = [[PPStringField alloc] init];
    }
    return self;
}


/**
 * 好友GID
 */
- (void) setGID:(UInt64)value {
    _mGID.value = value;
}

/**
 * 好友GID
 */
- (UInt64) getGID {
    return _mGID.value;
}

/**
 * 好友名称
 */
- (void) setFriendName:(NSString *)value {
    _mFriendName.value = value;
}

/**
 * 好友名称
 */
- (NSString *) getFriendName {
    return _mFriendName.value;
}

/**
 * 好友头像URL地址
 */
- (void) setFriendImage:(NSString *)value {
    _mFriendImage.value = value;
}

/**
 * 好友头像URL地址
 */
- (NSString *) getFriendImage {
    return _mFriendImage.value;
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
    [_mFriendName encode:buff tag:3];
    [_mFriendImage encode:buff tag:4];

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
    [_mFriendName format:buff fieldName:@"FriendName" suffix:sSubPrefix];
    [_mFriendImage format:buff fieldName:@"FriendImage" suffix:sSubPrefix];
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
    [_mFriendName toXml:buff fieldName:@"FriendName" suffix:sSubPrefix];
    [_mFriendImage toXml:buff fieldName:@"FriendImage" suffix:sSubPrefix];
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
    case 3:
        return _mFriendName;
    case 4:
        return _mFriendImage;
    default:
        return nil;
    }
}

@end
