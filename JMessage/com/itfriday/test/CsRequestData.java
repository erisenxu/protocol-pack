/*
 * @(#) CsRequestData.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 客户端响应协议消息结构体
 */
public class CsRequestData extends PPCompositeField implements PPUnionField {
    /**
     * Union字段标识
     */
    protected short mSelector = 0;

    /**
     * 客户端登录请求
     */
    protected LoginRequest mLogin;

    /**
     * 获取好友列表请求
     */
    protected PPByteField mGetFriends;

    @Override
    public void setSelector(short selector) {
        mSelector = selector;
    }

    /**
     * 客户端登录请求
     */
    public LoginRequest getLogin() {
        if (mLogin == null) mLogin  = new LoginRequest();
        return mLogin;
    }

    /**
     * 获取好友列表请求
     */
    public void setGetFriends(byte value) {
        if (mGetFriends == null) mGetFriends  = new PPByteField();
        mGetFriends.setValue(value);
    }

    /**
     * 获取好友列表请求
     */
    public byte getGetFriends() {
        if (mGetFriends == null) mGetFriends  = new PPByteField();
        return mGetFriends.getValue();
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段
        switch (mSelector) {
        case MsgMacro.CS_MSG_LOGIN:
            mLogin.encode(baBuf, (short)MsgMacro.CS_MSG_LOGIN);
            break;
        case MsgMacro.CS_MSG_GET_FRIEND_LIST:
            mGetFriends.encode(baBuf, (short)MsgMacro.CS_MSG_GET_FRIEND_LIST);
            break;
        default:
            break;
        }

        // 这个必须放后面，因为append有可能那个将baBuf的Data的地址改变
        int nAddLen = baBuf.length() - iOldLen;
        byte[] byLen = ByteArray.intToBytes(nAddLen);
        for (int i = iOldLen - 4, j = 0; i < baBuf.length() && j < byLen.length; i++, j++) {
            baBuf.set(i, byLen[j]);
        }
    }

    @Override
    public void format(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";
        sbBuf.append(sPrefix).append("[").append(sFieldName).append("]\n");
        switch (mSelector) {
        case MsgMacro.CS_MSG_LOGIN:
            mLogin.format(sbBuf, "Login", sSubPrefix);
            break;
        case MsgMacro.CS_MSG_GET_FRIEND_LIST:
            mGetFriends.format(sbBuf, "GetFriends", sSubPrefix);
            break;
        default:
            break;
        }
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        switch (mSelector) {
        case MsgMacro.CS_MSG_LOGIN:
            mLogin.toXml(sbBuf, "Login", sSubPrefix);
            break;
        case MsgMacro.CS_MSG_GET_FRIEND_LIST:
            mGetFriends.toXml(sbBuf, "GetFriends", sSubPrefix);
            break;
        default:
            break;
        }
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case MsgMacro.CS_MSG_LOGIN:
            mSelector = tag;
            if (mLogin == null) mLogin  = new LoginRequest();
            return mLogin;
        case MsgMacro.CS_MSG_GET_FRIEND_LIST:
            mSelector = tag;
            if (mGetFriends == null) mGetFriends  = new PPByteField();
            return mGetFriends;
        default:
            return null;
        }
    }
}
