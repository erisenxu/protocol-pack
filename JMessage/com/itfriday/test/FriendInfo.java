/*
 * @(#) FriendInfo.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 好友信息
 */
public class FriendInfo extends PPCompositeField {
    /**
     * 好友GID
     */
    protected PPULongField mGID = new PPULongField();

    /**
     * 好友名称
     */
    protected PPStringField mFriendName = new PPStringField();

    /**
     * 好友头像URL地址
     */
    protected PPStringField mFriendImage = new PPStringField();

    /**
     * 好友GID
     */
    public void setGID(long value) {
        mGID.setValue(value);
    }

    /**
     * 好友GID
     */
    public long getGID() {
        return mGID.getValue();
    }

    /**
     * 好友名称
     */
    public void setFriendName(String value) {
        mFriendName.setValue(value);
    }

    /**
     * 好友名称
     */
    public String getFriendName() {
        return mFriendName.getValue();
    }

    /**
     * 好友头像URL地址
     */
    public void setFriendImage(String value) {
        mFriendImage.setValue(value);
    }

    /**
     * 好友头像URL地址
     */
    public String getFriendImage() {
        return mFriendImage.getValue();
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
        mFriendName.encode(baBuf, (short)3);
        mFriendImage.encode(baBuf, (short)4);

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
        mFriendName.format(sbBuf, "FriendName", sSubPrefix);
        mFriendImage.format(sbBuf, "FriendImage", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mGID.toXml(sbBuf, "GID", sSubPrefix);
        mFriendName.toXml(sbBuf, "FriendName", sSubPrefix);
        mFriendImage.toXml(sbBuf, "FriendImage", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mGID;
        case 3:
            return mFriendName;
        case 4:
            return mFriendImage;
        default:
            return null;
        }
    }
}
