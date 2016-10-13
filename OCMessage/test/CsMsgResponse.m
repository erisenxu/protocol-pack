/*
 * @(#) CsMsgResponse.m Created by @itfriday message creator
 */

#import "CsMsgResponse.h"
#import "PPFieldInc.h"
#import "MsgMacro.h"

@interface CsMsgResponse ()
/**
 * 响应码
 */
@property (nonatomic, strong) PPShortField *mEno;

/**
 * 命令字
 */
@property (nonatomic, strong) PPShortField *mCmd;

/**
 * 消息结构体
 */
@property (nonatomic, strong) CsResponseData *mRespData;

@end

@implementation CsMsgResponse

/**
 * 初始化函数
 */
- (instancetype) init {
    if (self = [super init]) {
        _mEno  = [[PPShortField alloc] init];
        _mCmd  = [[PPShortField alloc] init];
        _mRespData  = [[CsResponseData alloc] init];
    }
    return self;
}


/**
 * 响应码
 */
- (void) setEno:(SInt16)value {
    _mEno.value = value;
}

/**
 * 响应码
 */
- (SInt16) getEno {
    return _mEno.value;
}

/**
 * 命令字
 */
- (void) setCmd:(SInt16)value {
    _mCmd.value = value;
}

/**
 * 命令字
 */
- (SInt16) getCmd {
    return _mCmd.value;
}

/**
 * 消息结构体
 */
- (CsResponseData *) getRespData {
    return _mRespData;
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
    [_mEno encode:buff tag:1];
    [_mCmd encode:buff tag:2];
    [_mRespData encode:buff tag:3];

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
    [_mEno format:buff fieldName:@"Eno" suffix:sSubPrefix];
    [_mCmd format:buff fieldName:@"Cmd" suffix:sSubPrefix];
    [_mRespData format:buff fieldName:@"RespData" suffix:sSubPrefix];
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
    [_mEno toXml:buff fieldName:@"Eno" suffix:sSubPrefix];
    [_mCmd toXml:buff fieldName:@"Cmd" suffix:sSubPrefix];
    [_mRespData toXml:buff fieldName:@"RespData" suffix:sSubPrefix];
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
        return _mEno;
    case 2:
        return _mCmd;
    case 3:
        return _mRespData;
    default:
        return nil;
    }
}

@end
