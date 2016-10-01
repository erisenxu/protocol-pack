package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPShortField implements PPField {

    /**
     * 字段的值
     */
    protected short mValue = 0;

    /**
     * 构造函数
     */
    public PPShortField() {
        this((short)0);
    }

    /**
     * 构造函数
     * @param value 字段的值
     */
    public PPShortField(short value) {
        this.mValue = value;
    }

    /**
     * 设置字段值
     * @param value 字段的值
     */
    public void setValue(short value) {
        this.mValue = value;
    }

    /**
     * 取字段的值
     * @return 返回字段的值
     */
    public short getValue() {
        return mValue;
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_SHORT).append(mValue);
    }

    @Override
    public void decode(byte[] szBuf, int iStart) throws ToolException {
        // 3 = sizeof(mTag) + sizeof(mFieldType)
        mValue = ByteArray.bytesToShort(szBuf, iStart + 3);
    }

    @Override
    public void format(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        sbBuf.append(sPrefix).append(sFieldName).append(" = ").append(mValue).append("\n");
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">").append(mValue).
                append("</").append(sFieldName).append(">\n");
    }

    @Override
    public void setValue(String value) {
        try {
            mValue = Short.parseShort(value);
        } catch (Exception e) {
            mValue = 0;
        }
    }
}
