/*
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

import java.util.ArrayList;

/**
 * Created by erisenxu on 2016/9/3.
 */
public class PPArrayField<E extends PPField> implements PPField {

    /**
     * 字段的值
     */
    protected ArrayList<E> mValue = new ArrayList<>();

    /**
     * 创建数组元素的对象
     */
    protected PPFieldCreator<E> mFieldCreator;

    /**
     * 构造函数
     */
    public PPArrayField(PPFieldCreator<E> fieldCreator) {
        this.mFieldCreator = fieldCreator;
    }

    /**
     * 获取指定索引处的数组元素对象
     * @param index 指定索引
     * @return 返回指定索引处的数组元素对象
     * @throws ToolException 失败抛出ToolException异常
     */
    public E getFieldByIndex(int index) throws ToolException {
        // index 只可以>=0 && <= mValue.size(),如果等于mValue.size(), 需要重新创建一个新的
        if (index < 0 || index > mValue.size()) {
            throw new ToolException("getFieldByIndex error, the index " + index + " is invalid");
        }

        if (index < mValue.size()) return mValue.get(index);

        if (mFieldCreator == null) {
            throw new ToolException("getFieldByIndex error, field to create subfield, cause the field creator is null");
        }

        E f = mFieldCreator.create();
        mValue.add(f);

        return f;
    }

    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        /* 编码Tag及Type */
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_ARRAY);
        /* 先将数组长度设置为0 */
        baBuf.append(0);
        /* 记录下当前数组长度 */
        int iArrOldLen = baBuf.length();
        /* 对数组进行编码 */
        /* 数组数量 */
        baBuf.append((short)mValue.size());
        /* 数组子字段 */
        for (short i = 0; i < (short)mValue.size(); i++) {
            mValue.get(i).encode(baBuf, tag);
        }
        /* 修正数组长度 */
        /* 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变 */
        int nArrAddLen = baBuf.length() - iArrOldLen;
        byte[] byLen = ByteArray.intToBytes(nArrAddLen);
        for (int i = iArrOldLen - 4, j = 0; i < baBuf.length() && j < byLen.length; i++, j++) {
            baBuf.set(i, byLen[j]);
        }
    }

    @Override
    public void decode(byte[] szBuf, int iStart) throws ToolException {

        int iHdrLen = 7; // sizeof(Tag) + sizeof(Type) + sizeof(Len)
        iStart += iHdrLen;

        // 剩余字节长度
        int iLeftLen = szBuf.length - iStart;

        /* 数组长度 */
        short nArrayNum = ByteArray.bytesToShort(szBuf, iStart);
        iLeftLen -= 2;
        iStart += 2;

        /* 数组元素类型长度检查 */
        if (szBuf.length < iStart + 3) {
            throw new ToolException("Array field decode error, the message buffer is too short");
        }

        /* 数组元素类型 */
        byte bType = szBuf[iStart + 2];

        /* 清空数据 */
        mValue.clear();

        /* 解析子字段 */
        for (short i = 0; i < nArrayNum; i++) {
            /* 通过类型获得数据长度 */
            int iMsgLen = PPCompositeField.getLengthByType(bType, szBuf, iStart, szBuf.length);
            if (iLeftLen < iMsgLen || iMsgLen < 0) {
                throw new ToolException("Array field decode error, the message buffer is too short");
            }
            //E f = mFieldCreator.create();
            //f.decode(szBuf, iStart);
            getFieldByIndex(i).decode(szBuf, iStart);
            iStart += iMsgLen;
            iLeftLen -= iMsgLen;
        }
    }

    @Override
    public void format(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        /* 数组子字段 */
        for (short i = 0; i < mValue.size(); i++) {
            mValue.get(i).format(sbBuf, sFieldName, sPrefix);
        }
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        /* 数组子字段 */
        for (short i = 0; i < mValue.size(); i++) {
            mValue.get(i).toXml(sbBuf, sFieldName, sPrefix);
        }
    }

    @Override
    public void setValue(String value) {
        //
    }
}
