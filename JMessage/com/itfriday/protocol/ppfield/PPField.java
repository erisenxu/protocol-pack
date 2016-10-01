package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public interface PPField {

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
