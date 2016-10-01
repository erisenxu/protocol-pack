package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPByteField implements PPField {

    /**
     * 字段的值
     */
    protected byte mValue = 0;

    /**
     * 构造函数
     */
    public PPByteField() {
        this((byte)0);
    }

    /**
     * 构造函数
     * @param value 字段的值
     */
    public PPByteField(byte value) {
        this.mValue = value;
    }

    /**
     * 设置字段值
     * @param value 字段的值
     */
    public void setValue(byte value) {
        this.mValue = value;
    }

    /**
     * 取字段的值
     * @return 返回字段的值
     */
    public byte getValue() {
        return mValue;
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_BYTE).append(mValue);
    }

    @Override
    public void decode(byte[] szBuf, int iStart) throws ToolException {
        // 3 = sizeof(mTag) + sizeof(mFieldType)
        if (szBuf.length < iStart + 4) {
            throw new ToolException(
                    "byte decode: the length of the bytes is less than " +
                            (iStart + 4));
        }

        mValue = szBuf[iStart + 3];
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
            mValue = Byte.parseByte(value);
        } catch (Exception e) {
            mValue = 0;
        }
    }
}
