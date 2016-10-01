/*
 * @(#) LoginRequest.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 登录请求
 */
public class LoginRequest extends PPCompositeField {
    /**
     * 登录鉴权码
     */
    protected PPStringField mCode = new PPStringField();

    /**
     * 系统类型：0 - iOS，1 - Android
     */
    protected PPIntField mOsType = new PPIntField();

    /**
     * 登录鉴权码
     */
    public void setCode(String value) {
        mCode.setValue(value);
    }

    /**
     * 登录鉴权码
     */
    public String getCode() {
        return mCode.getValue();
    }

    /**
     * 系统类型：0 - iOS，1 - Android
     */
    public void setOsType(int value) {
        mOsType.setValue(value);
    }

    /**
     * 系统类型：0 - iOS，1 - Android
     */
    public int getOsType() {
        return mOsType.getValue();
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段
        mCode.encode(baBuf, (short)1);
        mOsType.encode(baBuf, (short)2);

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
        mCode.format(sbBuf, "Code", sSubPrefix);
        mOsType.format(sbBuf, "OsType", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mCode.toXml(sbBuf, "Code", sSubPrefix);
        mOsType.toXml(sbBuf, "OsType", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mCode;
        case 2:
            return mOsType;
        default:
            return null;
        }
    }
}
