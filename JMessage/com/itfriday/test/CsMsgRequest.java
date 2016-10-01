/*
 * @(#) CsMsgRequest.java Created by @itfriday message creator
 */

package com.itfriday.test;

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * 客户端请求协议
 */
public class CsMsgRequest extends PPCompositeField {
    /**
     * 玩家GID
     */
    protected PPULongField mGID = new PPULongField();

    /**
     * 消息命令字
     */
    protected PPShortField mCmd = new PPShortField();

    /**
     * 消息结构体
     */
    protected CsRequestData mReqData = new CsRequestData();

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
     * 消息命令字
     */
    public void setCmd(short value) {
        mCmd.setValue(value);
    }

    /**
     * 消息命令字
     */
    public short getCmd() {
        return mCmd.getValue();
    }

    /**
     * 消息结构体
     */
    public CsRequestData getReqData() {
        return mReqData;
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
        mCmd.encode(baBuf, (short)2);
        mReqData.encode(baBuf, (short)3);

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
        mCmd.format(sbBuf, "Cmd", sSubPrefix);
        mReqData.format(sbBuf, "ReqData", sSubPrefix);
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\n");
        mGID.toXml(sbBuf, "GID", sSubPrefix);
        mCmd.toXml(sbBuf, "Cmd", sSubPrefix);
        mReqData.toXml(sbBuf, "ReqData", sSubPrefix);
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {
        case 1:
            return mGID;
        case 2:
            return mCmd;
        case 3:
            return mReqData;
        default:
            return null;
        }
    }
}
