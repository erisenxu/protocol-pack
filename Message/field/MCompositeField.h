/*
 * @(#) MCompositeField.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2054 Erisen Xu(徐勇) All Rights Reserved
 */

#ifndef MCOMPOSITE_FIELD_H
#define MCOMPOSITE_FIELD_H

#include "MField.h"

/**
 * <code>MCompositeField</code>组合协议字段类。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MCompositeField : public MField
{
public:
    /**
     * 显式构造函数
     */
    virtual void construct(U16 nTag = 0, const string& sName = "", MField* pParent = NULL, U16 nVer = 0);

    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     */
    virtual int decode(const char* szBuf, int iBufLen);
};

#endif
