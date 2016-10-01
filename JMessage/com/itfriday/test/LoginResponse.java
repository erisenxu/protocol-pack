/*
 * @(#) LoginResponse.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 登录响应
 */
public class LoginResponse extends PPCompositeField {
    /**
     * 玩家GID
     */
    protected PPULongField mGID = new PPULongField();

    /**
     * 用户VIP类型
     */
    protected PPByteField mUserType = new PPByteField();

    /**
     * 用户名称
     */
    protected PPStringField mUserName = new PPStringField();

    /**
     * 用户头像URL地址
     */
    protected PPStringField mUserImage = new PPStringField();

    /**
     * 玩家GID
     */
    public void setGID(long value) {
        mGID.setValue(value);
    }

    /**
     * 玩家GID
     */
    public long getGID() {
        return mGID.getValue();
    }

    /**
     * 用户VIP类型
     */
    public void setUserType(byte value) {
        mUserType.setValue(value);
    }

    /**
     * 用户VIP类型
     */
    public byte getUserType() {
        return mUserType.getValue();
    }

    /**
     * 用户名称
     */
    public void setUserName(String value) {
        mUserName.setValue(value);
    }

    /**
     * 用户名称
     */
    public String getUserName() {
        return mUserName.getValue();
    }

    /**
     * 用户头像URL地址
     */
    public void setUserImage(String value) {
        mUserImage.setValue(value);
    }

    /**
     * 用户头像URL地址
     */
    public String getUserImage() {
        return mUserImage.getValue();
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段
        mGID.encode(baBuf, (short)1);
        mUserType.encode(baBuf, (short)2);
        mUserName.encode(baBuf, (short)3);
        mUserImage.encode(baBuf, (short)4);

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
        mGID.format(sbBuf, "GID", sSubPrefix);
        mUserType.format(sbBuf, "UserType", sSubPrefix);
        mUserName.format(sbBuf, "UserName", sSubPrefix);
        mUserImage.format(sbBuf, "UserImage", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mGID.toXml(sbBuf, "GID", sSubPrefix);
        mUserType.toXml(sbBuf, "UserType", sSubPrefix);
        mUserName.toXml(sbBuf, "UserName", sSubPrefix);
        mUserImage.toXml(sbBuf, "UserImage", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mGID;
        case 2:
            return mUserType;
        case 3:
            return mUserName;
        case 4:
            return mUserImage;
        default:
            return null;
        }
    }
}
