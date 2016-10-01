package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPUByteField extends PPByteField {
    /**
     * 构造函数
     */
    public PPUByteField() {
        this((byte)0);
    }

    /**
     * 构造函数
     * @param value 字段的值
     */
    public PPUByteField(byte value) {
        super(value);
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_UBYTE).append(mValue);
    }
}
