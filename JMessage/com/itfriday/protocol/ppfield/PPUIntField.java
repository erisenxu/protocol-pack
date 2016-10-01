package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPUIntField extends PPIntField {
    /**
     * 构造函数
     */
    public PPUIntField() {
        this(0);
    }

    /**
     * 构造函数
     * @param value 字段的值
     */
    public PPUIntField(int value) {
        super(value);
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_UINT).append(mValue);
    }
}
