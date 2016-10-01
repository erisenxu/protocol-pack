package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPStringField implements PPField {

    /**
     * 字段的值
     */
    protected String mValue = "";

    /**
     * 构造函数
     */
    public PPStringField() {
        this("");
    }

    /**
     * 构造函数
     * @param value 字段的值
     */
    public PPStringField(String value) {
        this.mValue = value;
    }

    @Override
    public void setValue(String value) {
        this.mValue = value;
    }

    /**
     * 取字段的值
     * @return 返回字段的值
     */
    public String getValue() {
        return mValue;
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        byte[] b = mValue.getBytes();
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_STRING).append(b.length).append(b);
    }

    @Override
    public void decode(byte[] szBuf, int iStart) throws ToolException {
        // 3 = sizeof(mTag) + sizeof(mFieldType)
        int start = iStart + 3;
        int len = ByteArray.bytesToInt(szBuf, start);

        start += 4;

        if (szBuf.length < start + len) {
            throw new ToolException(
                    "byte decode: the length of the bytes is less than " +
                            (start + len));
        }

        mValue = new String(szBuf, start, len);
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
}
