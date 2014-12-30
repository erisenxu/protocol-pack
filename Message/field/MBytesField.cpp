/*
 * @(#) MBytesField.cpp Created on 2014-03-29
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "MBytesField.h"

#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void MBytesField::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
    constructField(nTag, M_FIELD_TYPE_BYTES, sName, pParent, nVer);
}

/**
 * 设置字段值
 * @param szValue 字段的值
 */
void MBytesField::setValue(const char* szValue, int iLen)
{
    if (NULL == szValue) return;
    
    m_baValue.clear();
    
    m_baValue.append(szValue, iLen);
}

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @return 成功返回0，失败返回错误码
 */
int MBytesField::encode(MByteArray& baBuf, U16 nVer)
{
    M_CHECK_FIELD_VER_RET(nVer);
    
    MField::encode(baBuf, nVer);
    
    // 字符串长度
    baBuf.append((U16)m_baValue.getLength());
    baBuf.append(m_baValue.getData(), m_baValue.getLength());
    return 0;
}

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MBytesField::decode(const char* szBuf, int /*iBufLen*/)
{
    U16 nBytesLen;
    //const char* pszValue = szBuf + sizeof(m_nTag) + sizeof(m_bType);
    M_CHAR_TO_U16(m_nTag, szBuf);
    M_CHAR_TO_U8(m_bType, szBuf);
    
    // 字符串长度
    M_CHAR_TO_U16(nBytesLen, szBuf);
    
    m_baValue.clear();
    
    m_baValue.append(szBuf, nBytesLen);
    //M_CHAR_TO_U32(m_iValue, szBuf);
    
    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sPrefix 格式化字符串的前缀
 */
void MBytesField::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
    M_CHECK_FIELD_VER(nVer);

    if (m_baValue.getLength() > 0)
    {
        // 16进制
        MByteArray baHex(m_baValue.getLength());
        MByteArray::bytesToHexStr(baHex, m_baValue.getData(), m_baValue.getLength());
        // 字符串
        MByteArray baStr(m_baValue.getLength());
        MByteArray::bytesToStr(baStr, m_baValue.getData(), m_baValue.getLength());

        baBuf.append(sPrefix).append(m_sName).append(" = 0x").append(baHex.getData(), baHex.getLength()).
            append("(").append(baStr.getData(), baStr.getLength()).append(")\n");
    }
    else
    {
        baBuf.append(sPrefix).append(m_sName).append(" =\n");
    }
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sPrefix 格式化字符串的前缀
 */
void MBytesField::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
    M_CHECK_FIELD_VER(nVer);

    if (m_baValue.getLength() > 0)
    {
        // 16进制
        MByteArray baHex(m_baValue.getLength());
        MByteArray::bytesToHexStr(baHex, m_baValue.getData(), m_baValue.getLength());

        baBuf.append(sPrefix).append("<").append(m_sName).append(">").append(baHex.getData(), baHex.getLength()).
            append("</").append(m_sName).append(">\n");

    }
    else
    {
        baBuf.append(sPrefix).append("<").append(m_sName).append("></").append(m_sName).append(">\n");
    }
}

/**
 * 设置字段的值
 * @param sValue 16进制的值，如果是要设置字符串，请使用setValue(const char* szValue, int iLen)这个函数
 */
void MBytesField::setValue(const string& sValue)
{
    MByteArray baBuf;
    MByteArray::hexStrToBytes(baBuf, sValue.c_str());

    setValue(baBuf.getData(), baBuf.getLength());
}

