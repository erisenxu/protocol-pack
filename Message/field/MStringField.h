/*
 * @(#) MStringField.h Created on 2014-03-29
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MSTRING_FIELD_H
#define MSTRING_FIELD_H

#include "MField.h"

/**
 * <code>MStringField</code>字符串字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MStringField: public MField
{
protected:
    string m_sValue;   // 整数值
public:
    /**
     * 构造函数
     */
    MStringField(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0, const string& sValue = "");
    
    /**
     * 拷贝构造函数
     */
    MStringField(const MStringField& stField);
    
    /**
     * 析构函数
     */
    virtual ~MStringField() {}
    
    /**
     * 设置字段值
     * @param sValue 字段的值
     */
    virtual void setValue(const string& sValue) {m_sValue = sValue;}
    
    /**
     * 取字段的值
     * @return 返回字段的值
     */
    const string& getValue() const {return m_sValue;}
    
    /**
     * 取字段的值
     * @return 返回字段的值
     */
    string getValue() {return m_sValue;}

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
};

#endif /* defined(MSTRING_FIELD_H) */
