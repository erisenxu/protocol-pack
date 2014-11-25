/*
 * @(#) MArrayField.h Created on 2014-09-07
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MARRAY_FIELD_H
#define MARRAY_FIELD_H

#include "MField.h"
#include "comm/MBaseFuncDef.h"

#include <vector>

/**
 * <code>MArrayField.h</code>数组字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */

template <typename T> class MArrayField : public MField
{
protected:
    vector<MField*> m_oSubFields;
public:
    /**
     * 构造函数
     */
    MArrayField(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0) : MField(nTag, M_FIELD_TYPE_ARRAY, sName, pParent, nVer) {}
    
    /**
     * 拷贝构造函数
     */
    MArrayField(const MArrayField& stField) : MField(stField) {
        for (auto mf : stField.m_oSubFields) {
            m_oSubFields.push_back(new T(*mf));
        }
    }
    
    /**
     * 析构函数
     */
    virtual ~MArrayField() {
        removeAllFields();
    }
    
    /**
     * 添加子字段
     */
    void addSubField(MField* pstField) {
        if (NULL == pstField) return;

        for (auto mf : m_oSubFields) {
            if (pstField == mf) return;
        }

        m_oSubFields.push_back(pstField);
        pstField->setFieldName(getFieldName());
        pstField->setParent(this);
    }

    /**
     * 新增一个子字段
     */
    virtual MField* appendSubField() {
        MField* pstField = new T(m_oSubFields.size() + 1, getFieldName());

        m_oSubFields.push_back(pstField);
        pstField->setParent(this);

        return pstField;
    }
    
    /**
     * 删除子字段
     */
    void removeSubField(MField* pstField) {
        std::vector<MField*>::iterator iter;

        for (iter = m_oSubFields.begin(); iter != m_oSubFields.end(); iter++) {
            if (*iter == pstField) {
                //delete *iter;
                m_oSubFields.erase(iter);
                break;
            }
        }
    }
    
    /**
     * 删除所有字段
     */
    void removeAllFields() {
        for (auto mf : m_oSubFields) {
            delete mf;
        }
        m_oSubFields.clear();
    }

    /**
     * 获得所有子字段列表
     * @return 返回子字段列表
     */
    const vector<MField*>& getSubFields() {
        return m_oSubFields;
    }

    /**
     * 通过字段标签查找字段
     * @param nTag 字段标签
     * @return 返回与字段标签对应的字段对象
     */
    virtual MField* getSubField(U16 nTag) {
        for (auto mf : m_oSubFields) {
            if (mf->getTag() == nTag) return mf;
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
        baBuf.append((U16)m_oSubFields.size());

        // 数组子字段
        for (auto mf : m_oSubFields) {
            mf->encode(baBuf, nVer);
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
        U16 nArrayNum = 0;
        int iLeftLen = iBufLen - iHdrLen;
        int iRet = -1;
        MField* pstField = NULL;
        int iMsgLen = 0;

        removeAllFields();

        // 数组长度
        M_CHAR_TO_U16(nArrayNum, pszArray);
        iLeftLen -= sizeof(nArrayNum);

        // 解析子字段
        for (U16 i = 1; i <= nArrayNum; i++) {
            pstField = new T(i, getFieldName());

            m_oSubFields.push_back(pstField);
            pstField->setParent(this);

            iMsgLen = MField::getLengthByType(pstField->getType(), pszArray, iLeftLen);

            iRet = pstField->decode(pszArray, iLeftLen);

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
        snprintf(szValue, sizeof(szValue), "%d", m_oSubFields.size());

        // 长度
        string sSubPrefix = sPrefix + "    ";
        baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n").
            append(sSubPrefix).append("Num = ").append(szValue).append("\n");

        // 子字段
        for (auto mf : m_oSubFields) {
            mf->format(baBuf, sSubPrefix, nVer);
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
        for (auto mf : m_oSubFields) {
            mf->toXml(baBuf, sPrefix, nVer);
        }
    }
};

#endif
