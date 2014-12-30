/*
 * @(#) MArrayField.h Created on 2014-09-07
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MARRAY_FIELD_H
#define MARRAY_FIELD_H

#include "MField.h"
#include "comm/MBaseFuncDef.h"
#include "comm/MErrorCode.h"

#include <vector>

/**
 * <code>MArrayField.h</code>数组字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */

template <typename T, size_t MAX_ARRAY_NUM> class MArrayField : public MField
{
protected:
    U16 m_nArrNum;
    T m_oSubFields[MAX_ARRAY_NUM];
public:
    /**
     * 显式构造函数
     */
    virtual void construct(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0) {
        constructField(nTag, M_FIELD_TYPE_ARRAY, sName, pParent, nVer);
        m_nArrNum = 0;
    }

    /**
     * 新增一个子字段
     */
    virtual MField* appendSubField() {

        MField* pstField;

        if (m_nArrNum >= MAX_ARRAY_NUM) return NULL;
        
        pstField = &m_oSubFields[m_nArrNum];
        m_nArrNum++;

        pstField->construct(m_nArrNum, getFieldName(), this, m_nVer);

        return pstField;
    }

    /**
     * 删除所有字段
     */
    void removeAllFields() {
        m_nArrNum = 0;
    }

    /**
     * 取数组字段数量
     * @return 返回数组字段数量
     */
    U16 getFieldNumber() const {
        return m_nArrNum;
    }

    /**
     * 获得所有子字段列表
     * @return 返回子字段列表
     */
    T* getSubFieldByIndex(U16 nIndex) {
        if (nIndex >= m_nArrNum) return NULL;
        return &m_oSubFields[nIndex];
    }

    /**
     * 通过字段标签查找字段
     * @param nTag 字段标签
     * @param chMode 获取字段标签时的用途或场景，见GET_SUB_FIELD_MODE_*
     * @return 返回与字段标签对应的字段对象
     */
    virtual MField* getSubField(U16 nTag, U8 /*chMode*/) {
        for (U16 i = 0; i < m_nArrNum; i++) {
            if (m_oSubFields[i].getTag() == nTag) return &m_oSubFields[i];
        }
        return NULL;
    }

    /**
     * 字段编码
     * @param baBuf 保存字段编码后的协议信息
     * @param nVer 编码消息的版本，版本比这个高的字段将被裁剪掉不编码在消息中
     * @return 成功返回0，失败返回错误码
     */
    virtual int encode(MByteArray& baBuf, U16 nVer) {

        M_CHECK_FIELD_VER_RET(nVer);

        // 编码Tag及Type
        MField::encode(baBuf, nVer);

        // 先将数组长度设置为0
        baBuf.append((U32)0);

        // 记录下当前数组长度
        int iOldLen = baBuf.getLength();

        // 对数组进行编码
        // 数组数量
        baBuf.append((U16)m_nArrNum);

        // 数组子字段
        for (U16 i = 0; i < m_nArrNum; i++) {
            m_oSubFields[i].encode(baBuf, nVer);
        }

        // 修正数组长度
        // 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
        U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
        char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

        M_U32_TO_CHAR(pszMsg, nAddLen);

        return 0;
    }

    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    virtual int decode(const char* szBuf, int iBufLen) {

        int iHdrLen = sizeof(m_nTag) + sizeof(m_bType) + sizeof(U32);
        const char* pszArray = szBuf + iHdrLen;
        int iLeftLen = iBufLen - iHdrLen;
        int iRet = -1;
        int iMsgLen = 0;
        MField* pstSubField;

        removeAllFields();

        // 数组长度
        M_CHAR_TO_U16(m_nArrNum, pszArray);
        iLeftLen -= sizeof(m_nArrNum);

        // 数组长度超过了最大值的处理
        if (m_nArrNum > MAX_ARRAY_NUM) return M_ERROR_DECODE_ARRAY_LONG;

        // 解析子字段
        for (U16 i = 0; i < m_nArrNum; i++) {
            pstSubField = &m_oSubFields[i];
            pstSubField->construct(i, getFieldName(), this, m_nVer);

            iMsgLen = MField::getLengthByType(pstSubField->getType(), pszArray, iLeftLen);

            iRet = m_oSubFields[i].decode(pszArray, iLeftLen);

            if (iRet != 0) return iRet;

            pszArray += iMsgLen;
            iLeftLen -= iMsgLen;
        }

        return 0;
    }

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void format(MByteArray& baBuf, const string& sPrefix, U16 nVer) {

        M_CHECK_FIELD_VER(nVer);

        char szValue[32];
        snprintf(szValue, sizeof(szValue), "%u", m_nArrNum);

        // 长度
        string sSubPrefix = sPrefix + "    ";
        baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n").
            append(sSubPrefix).append("Num = ").append(szValue).append("\n");

        // 子字段
        for (U16 i = 0; i < m_nArrNum; i++) {
            m_oSubFields[i].format(baBuf, sSubPrefix, nVer);
        }
    }

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sPrefix 格式化字符串的前缀
     */
    virtual void toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer) {
        M_CHECK_FIELD_VER(nVer);
        // 子字段
        //string sSubPrefix = sPrefix + "";
        for (U16 i = 0; i < m_nArrNum; i++) {
            m_oSubFields[i].toXml(baBuf, sPrefix, nVer);
        }
    }
};

#endif
