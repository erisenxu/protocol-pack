
package com.itfriday.test;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

public class Test {

    public static void main(String[] args) {
        System.out.println("Hello world!");
    }

    private void ppTest() throws ToolException {
        CsMsgResponse stMsgResponse = new CsMsgResponse();
        stMsgResponse.setCmd((short)MsgMacro.CS_MSG_GET_FRIEND_LIST);
        stMsgResponse.setEno((short) 0);

        stMsgResponse.getRespData().setSelector((short) com.itfriday.clinic.pp.MsgMacro.CS_MSG_GET_FRIEND_LIST);
        stMsgResponse.getRespData().getGetFriends().setFriendNumber((byte)2);
        stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setGID(0x12345678l);
        stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setFriendName("ErisenXu");
        stMsgResponse.getRespData().getGetFriends().getFriendInfo(0).setFriendImage("http://www.qq.com/erisenxu.jpg");

        stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setGID(0x78563412l);
        stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setFriendName("xy");
        stMsgResponse.getRespData().getGetFriends().getFriendInfo(1).setFriendImage("http://www.qq.com/xy.jpg");

        stMsgResponse.getRespData().getGetFriends().setTypeNumber((byte)3);
        stMsgResponse.getRespData().getGetFriends().setTypes(0, 0x345678);
        stMsgResponse.getRespData().getGetFriends().setTypes(1, 0x896754);
        stMsgResponse.getRespData().getGetFriends().setTypes(2, 0x2233445566778899l);

        StringBuilder stBa1 = new StringBuilder();

        /* ��ʽ�� */
        stMsgResponse.format(stBa1, "CsMsgResponse", "");
        System.out.print(stBa1.toString());

        //printf("%s", stBa1.toString());

        /* ת��Ϊxml */
        stBa1.delete(0, stBa1.length());
        stMsgResponse.toXml(stBa1, "CsMsgResponse", "");

        System.out.print(stBa1.toString());

        /* ��Ϣ���� */
        stBa1.delete(0, stBa1.length());

        ByteArray ba = new ByteArray();
        stMsgResponse.encode(ba, (short)1);

        System.out.print(ByteArray.bytesToPrintable(ba.getAllocBytes(), 0, ba.length(), 16));

        /* ������Ϣ */
        CsMsgResponse stMsgResp = new CsMsgResponse();
        stMsgResp.decode(ba.getAllocBytes(), 0);

        /* ��ʽ�������������Ϣ */
        stBa1.delete(0, stBa1.length());
        stMsgResp.format(stBa1, "CSMsgResponse", "");

        System.out.print(stBa1.toString());
    }
}