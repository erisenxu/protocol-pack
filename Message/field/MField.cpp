/*
 * @(#) MField.cpp Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#include "MField.h"

#include "comm/MBaseFuncDef.h"
#include "comm/MErrorCode.h"

/**
 * 构造函数
 */
MField::MField(U16 nTag, U8 bType, const string& sName, MField* pParent, U16 nVer)
    : m_nTag(nTag),
      m_nVer(nVer),
      m_bType(bType),
      m_sName(sName),
      m_pParent(pParent)
{
}

/**
 * 拷贝构造函数
 */
MField::MField(const MField& stField)
    : m_nTag(stField.m_nTag),
      m_bType(stField.m_bType),
      m_sName(stField.m_sName),
      m_pParent(stField.m_pParent)
{
    //
}

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
 * @param 成功返回0，失败返回错误码
 */
int MField::encode(MByteArray& baBuf, U16 /*nVer*/)
{
    baBuf.append(m_nTag);
    baBuf.append(m_bType);
    
    return 0;
}

/**
 * 取某个类型字段的长度
 * @param bType 字段类型
 * @param szBuf 要解析的协议，里面可能包含长度字段
 * @param iBufLen 协议的长度
 * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
 */
int MField::getLengthByType(U8 bType, const char* szBuf, int iBufLen)
{
    int iMinLen = sizeof(U16) + sizeof(U8);
    
    switch (bType)
    {
        case M_FIELD_TYPE_BYTE:
            return iMinLen + sizeof(U8);
        case M_FIELD_TYPE_SHORT:
            return iMinLen + sizeof(U16);
        case M_FIELD_TYPE_INT:
            return iMinLen + sizeof(U32);
        case M_FIELD_TYPE_LONG:
            return iMinLen + sizeof(U64);
        case M_FIELD_TYPE_STRING:
        case M_FIELD_TYPE_TLV:
        case M_FIELD_TYPE_ARRAY:
        default:
        {
            if (NULL != szBuf && iBufLen >= iMinLen + (int)sizeof(U32))
            {
                U32 nLen;
                const char* pszBuf = szBuf + iMinLen;
                M_CHAR_TO_U32(nLen, pszBuf);
                return iMinLen + sizeof(U32) + nLen;
            }
            return M_ERROR_DECODE_BUFSIZE_SHORT;
        }
    }
    //return iMinLen;
}

/**
 * 从消息中读取一个字节，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的字节
 */
U8 MField::readByte(const char* szBuf)
{
    U8 bRet;
    
    M_CHAR_TO_U8(bRet, szBuf);
    
    return bRet;
}

/**
 * 从消息中读取一个short，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U16 MField::readShort(const char* szBuf)
{
    U16 bRet;
    
    M_CHAR_TO_U16(bRet, szBuf);
    
    return bRet;
}

/**
 * 从消息中读取一个int，不检查长度
 * @param szBuf 消息字段
 * @return 返回读取的short
 */
U32 MField::readInt(const char* szBuf)
{
    U32 bRet;

    M_CHAR_TO_U32(bRet, szBuf);

    return bRet;
}

