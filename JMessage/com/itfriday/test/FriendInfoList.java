/*
 * @(#) FriendInfoList.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Just a Test Message object
 */
public class FriendInfoList extends PPCompositeField {
    /**
     * 好友数量
     */
    protected PPUByteField mFriendNumber = new PPUByteField();

    /**
     * 好友列表
     */
    protected PPArrayField<FriendInfo> mFriendInfo = new PPArrayField<>(new PPFieldCreator<FriendInfo>() {
        @Override
        public FriendInfo create() {
            return new FriendInfo();
        }
    });

    /**
     * 类型数量
     */
    protected PPUByteField mTypeNumber = new PPUByteField();

    /**
     * 类型列表
     */
    protected PPArrayField<PPULongField> mTypes = new PPArrayField<>(new PPFieldCreator<PPULongField>() {
        @Override
        public PPULongField create() {
            return new PPULongField();
        }
    });

    /**
     * 好友数量
     */
    public void setFriendNumber(byte value) {
        mFriendNumber.setValue(value);
    }

    /**
     * 好友数量
     */
    public byte getFriendNumber() {
        return mFriendNumber.getValue();
    }

    /**
     * 好友列表
     */
    public FriendInfo getFriendInfo(int index) throws ToolException {
        return mFriendInfo.getFieldByIndex(index);
    }

    /**
     * 类型数量
     */
    public void setTypeNumber(byte value) {
        mTypeNumber.setValue(value);
    }

    /**
     * 类型数量
     */
    public byte getTypeNumber() {
        return mTypeNumber.getValue();
    }

    /**
     * 类型列表
     */
    public void setTypes(int index, long value) throws ToolException {
        mTypes.getFieldByIndex(index).setValue(value);
    }

    /**
     * 类型列表
     */
    public long getTypes(int index) throws ToolException {
        return mTypes.getFieldByIndex(index).getValue();
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段
        mFriendNumber.encode(baBuf, (short)1);
        mFriendInfo.encode(baBuf, (short)2);
        mTypeNumber.encode(baBuf, (short)3);
        mTypes.encode(baBuf, (short)4);

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
        mFriendNumber.format(sbBuf, "FriendNumber", sSubPrefix);
        mFriendInfo.format(sbBuf, "FriendInfo", sSubPrefix);
        mTypeNumber.format(sbBuf, "TypeNumber", sSubPrefix);
        mTypes.format(sbBuf, "Types", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mFriendNumber.toXml(sbBuf, "FriendNumber", sSubPrefix);
        mFriendInfo.toXml(sbBuf, "FriendInfo", sSubPrefix);
        mTypeNumber.toXml(sbBuf, "TypeNumber", sSubPrefix);
        mTypes.toXml(sbBuf, "Types", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mFriendNumber;
        case 2:
            return mFriendInfo;
        case 3:
            return mTypeNumber;
        case 4:
            return mTypes;
        default:
            return null;
        }
    }
}
