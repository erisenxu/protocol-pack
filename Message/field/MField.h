/*
 * @(#) MField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MFIELD_H
#define MFIELD_H

#include "comm/MByteArray.h"
#include <stdlib.h>

/**
 * 检查字段版本，若高于指定版本，则返回0
 */
#define M_CHECK_FIELD_VER_RET(nVer) \
    if (nVer != 0 && m_nVer > nVer) return 0

/**
 * 检查字段版本，若高于指定版本，则返回0
 */
#define M_CHECK_FIELD_VER(nVer) \
    if (nVer != 0 && m_nVer > nVer) return

#define M_TAG(nTag)         nTag
#define M_NAME(name)        name
#define M_VERSION(nVer)     nVer
#define M_DEFAULT(value)    value
#define M_PARENT(value)     value

/**
 * <code>MField</code>协议字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MField
{
public:
    enum MFieldDataType
    {
        M_FIELD_TYPE_INVALID = 0, // 不合法(未初始化)的字段类型
        M_FIELD_TYPE_BYTE = 1,    // S8，占1个字节
        M_FIELD_TYPE_UBYTE = 2,   // U8，占1个字节
        M_FIELD_TYPE_SHORT = 3,   // S16，占2个字节
        M_FIELD_TYPE_USHORT = 4,  // U16，占2个字节
        M_FIELD_TYPE_INT = 5,     // S32，占4个字节
        M_FIELD_TYPE_UINT = 6,    // U32，占4个字节
        M_FIELD_TYPE_LONG = 7,    // S64，占8个字节
        M_FIELD_TYPE_ULONG = 8,   // U64，占8个字节
        M_FIELD_TYPE_STRING = 9,  // 字符串，特殊的TLV字段
        M_FIELD_TYPE_BYTES = 10,  // 字节数组，特殊的TLV字段
        M_FIELD_TYPE_TLV = 11,    // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
        M_FIELD_TYPE_ARRAY = 12   // 数组
    };
    enum MGetSubFieldMode
    {
        M_GET_SUB_FIELD_MODE_NORMAL = 0,    // 一般获取子字段
        M_GET_SUB_FIELD_MODE_DECODE = 1     // 解码消息时，获取子字段
    };
protected:
    U16 m_nTag;         // 字段标签，表明它是什么字段
    U16 m_nVer;         // 字段引入版本。注：字段版本其实可以不用，因本协议可以向下、向上兼容。
                        // 但是可以将高版本的字段在低版本的协议中裁剪掉，以减少包的大小及提升打包解包时间
    U8 m_bType;         // 字段数据类型，见M_FIELD_TYPE_*系列
    string m_sName;     // 字段名字
    MField* m_pParent;  // 父字段对象
public:
    /**
     * 显式构造函数
     */
    virtual void construct(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0);

    /**
     * 设置字段标签
     * @param nTag 字段标签
     */
    void setTag(U16 nTag) {m_nTag = nTag;}

    /**
     * 取字段标签
     * @return 返回字段标签
     */
    U16 getTag() const {return m_nTag;}

    /**
     * 设置字段类型
     * @param bType 字段类型
     */
    void setType(U8 bType) {m_bType = bType;}

    /**
     * 取字段类型
     * @return 返回字段类型
     */
    U8 getType() const {return m_bType;}

    /**
     * 设置字段名字
     * @param sName 字段名字
     */
    void setFieldName(const string& sName) {m_sName = sName;}

    /**
     * 取字段名字
     * @return 返回字段名字
     */
    string getFieldName() {return m_sName;}

    /**
     * 取字段名字
     * @return 返回字段名字
     */
    const string& getFieldName() const {return m_sName;}

    /**
     * 设置父字段对象
     * @param pParent 父字段对象
     */
    void setParent(MField* pParent) {m_pParent = pParent;}

    /**
     * 取父字段对象
     * @return 返回父字段对象
     */
    MField* getParent() const {return m_pParent;}

    /**
     * 字段编码
     * @param baBuf 保存字段编码后的协议信息
     * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
     * @param 成功返回0，失败返回错误码
     */
    virtual int encode(MByteArray& baBuf, U16 nVer);

    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     */
    virtual int decode(const char* /*szBuf*/, int /*iBufLen*/) {return 0;}
    
    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void format(MByteArray& /*baBuf*/, const string& /*sPrefix*/, U16 /*nVer*/) {}

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void toXml(MByteArray& /*baBuf*/, const string& /*sPrefix*/, U16 /*nVer*/) {}

    /**
     * 通过字段标签查找字段
     * @param nTag 字段标签
     * @param chMode 获取字段标签时的用途或场景，见GET_SUB_FIELD_MODE_*
     * @return 返回与字段标签对应的字段对象
     */
    virtual MField* getSubField(U16 /*nTag*/, U8 /*chMode*/) {return NULL;}

    /**
     * 通过字段名查找字段
     * @param sName 字段名
     * @return 返回与字段名对应的字段对象
     */
    virtual MField* getSubFieldByName(const string& /*sName*/) {return NULL;}

    /**
     * 新增一个子字段
     * @param 返回新增的子字段
     */
    virtual MField* appendSubField() {return NULL;}

    /**
     * 设置字段的值
     */
    virtual void setValue(const string& /*sValue*/) {}

    /**
     * 取某个类型字段的长度
     * @param bType 字段类型
     * @param szBuf 要解析的协议，里面可能包含长度字段
     * @param iBufLen 协议的长度
     * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
     */
    static int getLengthByType(U8 bType, const char* szBuf, int iBufLen);

protected:    
    /**
     * 从消息中读取一个字节，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的字节
     */
    static U8 readByte(const char* szBuf);

    /**
     * 从消息中读取一个short，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的short
     */
    static U16 readShort(const char* szBuf);

    /**
     * 从消息中读取一个int，不检查长度
     * @param szBuf 消息字段
     * @return 返回读取的short
     */
    static U32 readInt(const char* szBuf);

    /**
     * 显式构造函数
     */
    void constructField(U16 nTag = 0, U8 bType = M_FIELD_TYPE_INT, const string& sName = "", MField* pParent = NULL, U16 nVer = 0);
};

#endif /* defined(MFIELD_H) */
