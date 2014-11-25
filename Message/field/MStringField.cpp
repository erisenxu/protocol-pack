/*
 * @(#) MStringField.cpp Created on 2014-03-29
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "MStringField.h"

#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
MStringField::MStringField(U16 nTag, const string& sName, MField* pParent, U16 nVer, const string& sValue)
    : MField(nTag, M_FIELD_TYPE_STRING, sName, pParent, nVer),
      m_sValue(sValue)
{
    //
}

/**
 * 拷贝构造函数
 */
MStringField::MStringField(const MStringField& stField)
    : MField(stField),
      m_sValue(stField.m_sValue)
{
    //
}

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @return 成功返回0，失败返回错误码
 */
int MStringField::encode(MByteArray& baBuf, U16 nVer)
{
    M_CHECK_FIELD_VER_RET(nVer);
    
    MField::encode(baBuf, nVer);
    // 字符串长度
    baBuf.append((U16)m_sValue.size());
    baBuf.append(m_sValue);
    return 0;
}

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int MStringField::decode(const char* szBuf, int /*iBufLen*/)
{
    U16 nStrLen;
    //const char* pszValue = szBuf + sizeof(m_nTag) + sizeof(m_bType);
    M_CHAR_TO_U16(m_nTag, szBuf);
    M_CHAR_TO_U8(m_bType, szBuf);
    
    // 字符串长度
    M_CHAR_TO_U16(nStrLen, szBuf);
    
    m_sValue.clear();
    
    m_sValue.append(szBuf, nStrLen);
    //M_CHAR_TO_U32(m_iValue, szBuf);
    
    return 0;
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sPrefix 格式化字符串的前缀
 */
void MStringField::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
    M_CHECK_FIELD_VER(nVer);

    baBuf.append(sPrefix).append(m_sName).append(" = ").append(m_sValue).append("\n");
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sPrefix 格式化字符串的前缀
 */
void MStringField::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
    M_CHECK_FIELD_VER(nVer);

    baBuf.append(sPrefix).append("<").append(m_sName).append(">").append(m_sValue).
        append("</").append(m_sName).append(">\n");
}

