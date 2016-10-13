//
//  main.m
//  OcMessage
//
//  Created by erisenxu on 2016/10/13.
//  Copyright © 2016年 @itfriday. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CsMsgResponse.h"
#import "MsgMacro.h"

void test() {
    CsMsgResponse* stMsgResponse = [[CsMsgResponse alloc] init];
    [stMsgResponse setCmd:CS_MSG_GET_FRIEND_LIST];
    [stMsgResponse setEno:0];
    
    [[stMsgResponse getRespData] setSelector:CS_MSG_GET_FRIEND_LIST];
    [[[stMsgResponse getRespData] getGetFriends] setFriendNumber:2];
    
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:0] setGID:0x12345678l];
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:0] setFriendName:@"ErisenXu"];
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:0] setFriendImage:@"http://www.qq.com/erisenxu.jpg"];
    
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:1] setGID:0x78563412l];
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:1] setFriendName:@"xy"];
    [[[[stMsgResponse getRespData] getGetFriends] getFriendInfo:1] setFriendImage:@"http://www.qq.com/xy.jpg"];
    
    [[[stMsgResponse getRespData] getGetFriends] setTypeNumber:3];
    [[[stMsgResponse getRespData] getGetFriends] setTypes:0 value:0x345678];
    [[[stMsgResponse getRespData] getGetFriends] setTypes:1 value:0x896754];
    [[[stMsgResponse getRespData] getGetFriends] setTypes:2 value:0x2233445566778899l];
    
    NSMutableString* stBa1 = [[NSMutableString alloc] init];
    
    /* 格式化 */
    [stMsgResponse format:stBa1 fieldName:@"CsMsgResponse" suffix:@""];
    
    NSLog(@"%@", stBa1);
    
    /* 转换为xml */
    NSMutableString* stBa2 = [[NSMutableString alloc] init];
    [stMsgResponse toXml:stBa2 fieldName:@"CsMsgResponse" suffix:@""];
    
    NSLog(@"%@", stBa2);
    
    /* 消息编码 */
    NSMutableData* pData = [[NSMutableData alloc] init];
    [stMsgResponse encode:pData tag:1];
    
    NSLog(@"%@", pData);
    
    /* 解码消息 */
    CsMsgResponse* stMsgResp = [[CsMsgResponse alloc] init];
    [stMsgResp decode:pData start:0];
    
    /* 格式化输出解码后的消息 */
    NSMutableString* stBa3 = [[NSMutableString alloc] init];
    [stMsgResp format:stBa3 fieldName:@"CsMsgResponse" suffix:@""];
    
    NSLog(@"%@", stBa3);
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        test();
        //NSLog(@"Hello, World!");
    }
    return 0;
}
