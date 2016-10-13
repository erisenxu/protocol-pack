/*
 * @(#) FriendInfoList.m Created by @itfriday message creator
 */

#import "FriendInfoList.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface FriendInfoList ()
/**
 * 好友数量
 */
@property (nonatomic, strong) PPUByteField *mFriendNumber;

/**
 * 好友列表
 */
@property (nonatomic, strong) PPArrayField *mFriendInfo;

/**
 * 类型数量
 */
@property (nonatomic, strong) PPUByteField *mTypeNumber;

/**
 * 类型列表
 */
@property (nonatomic, strong) PPArrayField *mTypes;

@end

@implementation FriendInfoList

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mFriendNumber  = [[PPUByteField alloc] init];
        _mFriendInfo  = [[PPArrayField alloc] initWithFieldCreator:^id<PPField> {
            return [[FriendInfo alloc] init];
        }];
        _mTypeNumber  = [[PPUByteField alloc] init];
        _mTypes  = [[PPArrayField alloc] initWithFieldCreator:^id<PPField> {
            return [[PPULongField alloc] init];
        }];
    }
    return self;
}


/**
 * 好友数量
 */
- (void) setFriendNumber:(UInt8)value {
    _mFriendNumber.value = value;
}

/**
 * 好友数量
 */
- (UInt8) getFriendNumber {
    return _mFriendNumber.value;
}

/**
 * 好友列表
 */
- (FriendInfo *) getFriendInfo:(UInt32)index {
    return [_mFriendInfo getFieldByIndex:index];
}

/**
 * 类型数量
 */
- (void) setTypeNumber:(UInt8)value {
    _mTypeNumber.value = value;
}

/**
 * 类型数量
 */
- (UInt8) getTypeNumber {
    return _mTypeNumber.value;
}

/**
 * 类型列表
 */
- (void) setTypes:(UInt32)index value:(UInt64)value {
    [(PPULongField *)[_mTypes getFieldByIndex:index] setValue:value];
}

/**
 * 类型列表
 */
- (UInt64) getTypes:(UInt32)index {
    return [(PPULongField *)[_mTypes getFieldByIndex:index] value];
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
    [_mFriendNumber encode:buff tag:1];
    [_mFriendInfo encode:buff tag:2];
    [_mTypeNumber encode:buff tag:3];
    [_mTypes encode:buff tag:4];

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
    [_mFriendNumber format:buff fieldName:@"FriendNumber" suffix:sSubPrefix];
    [_mFriendInfo format:buff fieldName:@"FriendInfo" suffix:sSubPrefix];
    [_mTypeNumber format:buff fieldName:@"TypeNumber" suffix:sSubPrefix];
    [_mTypes format:buff fieldName:@"Types" suffix:sSubPrefix];
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
    [_mFriendNumber toXml:buff fieldName:@"FriendNumber" suffix:sSubPrefix];
    [_mFriendInfo toXml:buff fieldName:@"FriendInfo" suffix:sSubPrefix];
    [_mTypeNumber toXml:buff fieldName:@"TypeNumber" suffix:sSubPrefix];
    [_mTypes toXml:buff fieldName:@"Types" suffix:sSubPrefix];
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
        return _mFriendNumber;
    case 2:
        return _mFriendInfo;
    case 3:
        return _mTypeNumber;
    case 4:
        return _mTypes;
    default:
        return nil;
    }
}

@end
