/*
 * @(#) MShortField.h Created on 2014-03-29
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MSHORT_FIELD_H
#define MSHORT_FIELD_H

#include "MField.h"

/**
 * <code>MShortField</code>短整数字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MShortField: public MField
{
protected:
    short m_nValue;   // 整数值
public:
    /**
     * 显式构造函数
     */
    virtual void construct(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0);
    
    /**
     * 初始化函数，会调用显式构造函数
     */
    void init(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0, short nValue = 0);

    /**
     * 设置字段值
     * @param nValue 字段的值
     */
    void setValue(short nValue) {m_nValue = nValue;}

    /**
     * 取字段的值
     * @return 返回字段的值
     */
    short getValue() const {return m_nValue;}

    /**
     * 字段编码
     * @param baBuf 保存字段编码后的协议信息
     * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
     * @return 成功返回0，失败返回错误码
     */
    virtual int encode(MByteArray& baBuf, U16 nVer);

    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    virtual int decode(const char* szBuf, int iBufLen);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void format(MByteArray& baBuf, const string& sPrefix, U16 nVer);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer);

    /**
     * 设置字段的值
     */
    virtual void setValue(const string& sValue) {setValue((short)atoi(sValue.c_str()));}
};

#endif /* defined(MSHORT_FIELD_H) */
