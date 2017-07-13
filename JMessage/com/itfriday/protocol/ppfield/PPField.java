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

import java.io.Serializable;

/**
 * Created by erisenxu on 2016/9/3.
 */
public interface PPField extends Serializable {

    /**
     * 消息不全，没有长度字段
     */
    int MESSAGE_LENGTH_NOT_PRESENT = -1;

    /**
     * 消息类型不对
     */
    int MESSAGE_LENGTH_TYPE_INVALID = -2;

    /**
     * 字段编码
     *
     * @param baBuf 保存字段编码后的协议信息
     * @param tag   字段的标签
     * @throws ToolException 失败抛出ToolException异常
     */
    void encode(ByteArray baBuf, short tag) throws ToolException;

    /**
     * 字段解码
     *
     * @param szBuf  要解析的协议
     * @param iStart 协议的起始位置
     * @throws ToolException 失败抛出ToolException异常
     */
    void decode(byte[] szBuf, int iStart) throws ToolException;

    /**
     * 将字段格式化成可读形式
     *
     * @param sbBuf      保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param sPrefix    格式化字符串的前缀
     */
    void format(StringBuilder sbBuf, String sFieldName, String sPrefix);

    /**
     * 将字段格式化成XML形式
     *
     * @param sbBuf      保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param sPrefix    格式化字符串的前缀
     */
    void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix);

    /**
     * 设置字段的值
     *
     * @param value 字段的值
     */
    void setValue(String value);
}
