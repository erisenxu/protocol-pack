
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "test/CsMsgResponse.h"

int main()
{
    CSMSGRESPONSE stMsgResponse;
    stMsgResponse.shCmd = CS_MSG_GET_FRIEND_LIST;
    stMsgResponse.shEno = 0;

    stMsgResponse.stRespData.nSelector = CS_MSG_GET_FRIEND_LIST;
    stMsgResponse.stRespData.stGetFriends.bFriendNumber = 2;

    stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].ullGID = 0x12345678l;
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].szFriendName, "ErisenXu");
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].szFriendImage, "http://www.qq.com/erisenxu.jpg");

    stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].ullGID = 0x78563412l;
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].szFriendName, "xy");
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].szFriendImage, "http://www.qq.com/xy.jpg");

    stMsgResponse.stRespData.stGetFriends.bTypeNumber = 3;
    stMsgResponse.stRespData.stGetFriends.astTypes[0] = 0x345678;
    stMsgResponse.stRespData.stGetFriends.astTypes[1] = 0x896754;
    stMsgResponse.stRespData.stGetFriends.astTypes[2] = 0x2233445566778899l;

    char szMsg1[1024];
    BYTEARRAY stBa1;
    INIT_BYTE_ARRAY(stBa1, szMsg1, sizeof(szMsg1));

    /* 格式化 */
    cs_msg_response_field_format("CSMsgResponse", &stMsgResponse, &stBa1, "");
    bytearray_append_u8(&stBa1, (U8)0);

    printf("%s", stBa1.pszData);

    /* 转换为xml */
    bytearray_clear(&stBa1);
    cs_msg_response_field_to_xml("CSMsgResponse", &stMsgResponse, &stBa1, "");
    bytearray_append_u8(&stBa1, (U8)0);

    printf("%s", stBa1.pszData);

    /* 消息编码 */
    bytearray_clear(&stBa1);
    cs_msg_response_field_encode(&stMsgResponse, 1, &stBa1);

    char szOut2[8192];
    BYTEARRAY stBuf2;
    INIT_BYTE_ARRAY(stBuf2, szOut2, sizeof(szOut2));

    bytes_to_printable(&stBuf2, stBa1.pszData, stBa1.dwLen, 0, -1, 16);

    printf("%s\n", stBuf2.pszData);

    /* 解码消息 */
    CSMSGRESPONSE stMsgResp;
    memset(&stMsgResp, sizeof(stMsgResp), 0);
    cs_msg_response_field_decode(&stMsgResp, stBa1.pszData, stBa1.dwLen);

    /* 格式化输出解码后的消息 */
    bytearray_clear(&stBuf2);
    cs_msg_response_field_format("CSMsgResponse", &stMsgResp, &stBuf2, "");
    bytearray_append_u8(&stBuf2, (U8)0);

    printf("%s", stBuf2.pszData);

    return 0;
}

