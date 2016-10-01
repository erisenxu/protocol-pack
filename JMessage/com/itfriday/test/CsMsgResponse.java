/*
 * @(#) CsMsgResponse.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 客户端响应协议
 */
public class CsMsgResponse extends PPCompositeField {
    /**
     * 响应码
     */
    protected PPShortField mEno = new PPShortField();

    /**
     * 命令字
     */
    protected PPShortField mCmd = new PPShortField();

    /**
     * 消息结构体
     */
    protected CsResponseData mRespData = new CsResponseData();

    /**
     * 响应码
     */
    public void setEno(short value) {
        mEno.setValue(value);
    }

    /**
     * 响应码
     */
    public short getEno() {
        return mEno.getValue();
    }

    /**
     * 命令字
     */
    public void setCmd(short value) {
        mCmd.setValue(value);
    }

    /**
     * 命令字
     */
    public short getCmd() {
        return mCmd.getValue();
    }

    /**
     * 消息结构体
     */
    public CsResponseData getRespData() {
        return mRespData;
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段
        mEno.encode(baBuf, (short)1);
        mCmd.encode(baBuf, (short)2);
        mRespData.encode(baBuf, (short)3);

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
        mEno.format(sbBuf, "Eno", sSubPrefix);
        mCmd.format(sbBuf, "Cmd", sSubPrefix);
        mRespData.format(sbBuf, "RespData", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mEno.toXml(sbBuf, "Eno", sSubPrefix);
        mCmd.toXml(sbBuf, "Cmd", sSubPrefix);
        mRespData.toXml(sbBuf, "RespData", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mEno;
        case 2:
            return mCmd;
        case 3:
            return mRespData;
        default:
            return null;
        }
    }
}
