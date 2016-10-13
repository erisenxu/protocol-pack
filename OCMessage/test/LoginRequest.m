/*
 * @(#) LoginRequest.m Created by @itfriday message creator
 */

#import "LoginRequest.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface LoginRequest ()
/**
 * 登录鉴权码
 */
@property (nonatomic, strong) PPStringField *mCode;

/**
 * 系统类型：0 - iOS，1 - Android
 */
@property (nonatomic, strong) PPIntField *mOsType;

@end

@implementation LoginRequest

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mCode  = [[PPStringField alloc] init];
        _mOsType  = [[PPIntField alloc] init];
    }
    return self;
}


/**
 * 登录鉴权码
 */
- (void) setCode:(NSString *)value {
    _mCode.value = value;
}

/**
 * 登录鉴权码
 */
- (NSString *) getCode {
    return _mCode.value;
}

/**
 * 系统类型：0 - iOS，1 - Android
 */
- (void) setOsType:(SInt32)value {
    _mOsType.value = value;
}

/**
 * 系统类型：0 - iOS，1 - Android
 */
- (SInt32) getOsType {
    return _mOsType.value;
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
    [_mCode encode:buff tag:1];
    [_mOsType encode:buff tag:2];

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
    [_mCode format:buff fieldName:@"Code" suffix:sSubPrefix];
    [_mOsType format:buff fieldName:@"OsType" suffix:sSubPrefix];
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
    [_mCode toXml:buff fieldName:@"Code" suffix:sSubPrefix];
    [_mOsType toXml:buff fieldName:@"OsType" suffix:sSubPrefix];
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
        return _mCode;
    case 2:
        return _mOsType;
    default:
        return nil;
    }
}

@end
