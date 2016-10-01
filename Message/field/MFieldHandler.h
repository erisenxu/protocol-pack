/*
 * @(#) MFieldHandler.h Created on 2014-03-27
 *
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MFIELD_HANDLER_H
#define MFIELD_HANDLER_H

#include <comm/MBaseDef.h>

#define MAX_FIELD_INFO_LEN  1024
#define MAX_FIELD_NAME_LEN  256

/**
 * <code>MFieldHandler</code>字段XML处理。<br>
 * @version 1.0
 * @author 徐勇(Erisen Xu)
 */
class M_DLLIMPORT MFieldHandler
{
protected:
    MFieldHandler* m_pstParent;                 /* 父处理器对象 */
    char m_szFieldName[MAX_FIELD_NAME_LEN];     /* 字段的名称 */
    U64 m_ullClientData;                        /* 自定义数据，可以保存指针地址哦 */
public:
    /**
     * 构造函数
     */
    MFieldHandler();

    /**
     * 析构函数
     */
    virtual ~MFieldHandler() {}

    /**
     * 设置父处理器对象
     */
    void setParentHandler(MFieldHandler* pstHandler) {m_pstParent = pstHandler;}

    /**
     * 获取父处理器对象
     */
    MFieldHandler* getParentHandler() {return m_pstParent;}

    /**
     * 设置字段的名称
     * @param szFieldName 字段的名称
     */
    void setFieldName(const char* szFieldName);

    /**
     * 获取字段的名称
     * @return 返回字段的名称
     */
    const char* getFieldName() {return m_szFieldName;}

    /**
     * 设置自定义数据，可以保存指针地址哦
     * @param ullData 自定义数据，可以保存指针地址哦
     */
    void setClientData(U64 ullData) {m_ullClientData = ullData;}

    /**
     * 获取设置自定义数据
     * @return 返回自定义数据
     */
    U64 getClientData() const {return m_ullClientData;}

    /**
     * 设置按字段名字设置子字段的值
     * @param szSubFieldName 字段名称
     * @param nIdx 数组字段的元素索引
     * @param szValue 字段的值
     */
    virtual void setFieldValueByName(const char* szSubFieldName, U16 nIdx, const char* szValue) = 0;

    /**
     * 通过子字段名称获取子字段处理器对象
     * @param szSubFieldName 字段名称
     * @param nIdx 数组字段的元素索引
     * @return 返回名称对应的处理器对象，若未找到，返回NULL
     */
    virtual MFieldHandler* getSubFieldHandlerByName(const char* szSubFieldName, U16 nIdx) = 0;
};

#endif /* defined(MFIELD_HANDLER_H) */
