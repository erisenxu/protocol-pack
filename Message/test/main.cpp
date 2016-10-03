
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "test/CsMsgResponse.h"

int main()
{
    /* 对象结构体申明及赋值 */
    CsMsgResponse stMsgResponse;

    stMsgResponse.setCmd(CS_MSG_GET_FRIEND_LIST);
    stMsgResponse.setEno(0);

    stMsgResponse.getRespData().setSelector(CS_MSG_GET_FRIEND_LIST);

    /* 数组字段 */
    stMsgResponse.getRespData().getGetFriends().setFriendNumber(2);
    stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setGID(0x12345678l);
    stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setFriendName("ErisenXu");
    stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setFriendImage("http://www.qq.com/erisenxu.jpg");

    stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setGID(0x78563412l);
    stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setFriendName("xy");
    stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setFriendImage("http://www.qq.com/xy.jpg");

    stMsgResponse.getRespData().getGetFriends().setTypeNumber(3);
    stMsgResponse.getRespData().getGetFriends().setTypes(0, 0x345678);
    stMsgResponse.getRespData().getGetFriends().setTypes(1, 0x896754);
    stMsgResponse.getRespData().getGetFriends().setTypes(2, 0x2233445566778899l);

    MByteArray stBa1(1024);

    /* 格式化 */
    stMsgResponse.format(stBa1, "CsMsgResponse", "");

    printf("%s", stBa1.toString());

    /* 转换为xml */
    stBa1.clear();
    stMsgResponse.toXml(stBa1, "CsMsgResponse", "");

    printf("%s", stBa1.toString());

    /* 消息编码成二进制 */
    stBa1.clear();
    stMsgResponse.encode(stBa1, 1);

    MByteArray stBuf2(1024);

    MByteArray::bytesToPrintable(stBuf2, stBa1.getData(), stBa1.getLength(), 0, -1, 16);

    printf("%s\n", stBuf2.toString());

    /* 将二进制数据解码为消息对象 */
    CsMsgResponse stMsgResp;
    stMsgResp.decode(stBa1.getData(), stBa1.getLength());

    /* 格式化输出解码后的消息 */
    stBuf2.clear();
    stMsgResp.format(stBuf2, "CSMsgResponse", "");

    printf("%s", stBuf2.toString());

    return 0;
}

