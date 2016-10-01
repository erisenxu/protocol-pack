#!/usr/bin/env python
#coding:utf-8
#=================================================================
# @ Author : Erisenxu @ Innovate Center
# @ Desc : 文件模版
# @ FileName : ctemplate.py
# @ Date : 2014-03-29
# @ ModifyHistory :
# @ Remark :
#==================================================================

#
# H文件模版-字段模版
#
HTEMPLATE = '''/*
 * @(#) ${ClassName}.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_H
#define ${ClassMacro}_H
 
${Includes}
/**
 * $ClassDesc
 */
class M_DLLIMPORT ${ClassName}
{
protected:${AttrDefine}

public:${AttrGetSetDefine}
    /**
     * 字段编码
     * @param baBuf 保存字段编码后的协议信息
     * @param nTag 字段标签
     * @return 成功返回0，失败返回错误码
     */
    int encode(MByteArray& baBuf, U16 nTag);

    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    int decode(const char* szBuf, int iBufLen);

    /**
     * 将字段格式化成可读形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param sPrefix 格式化字符串的前缀
     */
    void format(MByteArray& baBuf, const string& sFieldName, const string& sPrefix);

    /**
     * 将字段格式化成XML形式
     * @param baBuf 保存字段信息的缓存区
     * @param sFieldName 字段的名称
     * @param sPrefix 格式化字符串的前缀
     */
    void toXml(MByteArray& baBuf, const string& sFieldName, const string& sPrefix);

protected:
    /**
     * 字段解码
     * @param szBuf 要解析的协议
     * @param iBufLen 协议的长度
     * @return 成功返回0，失败返回错误码
     */
    int decodeSubField(const char* szBuf, int iBufLen, U16 nTag);
};

#endif
''';

#
# C文件模版-字段模版
#
CPPTEMPLATE = '''/*
 * @(#) ${ClassName}.cpp Created by @itfriday message creator
 */

#include "${ClassName}.h"
#include "comm/MErrorCode.h"

/**
 * 字段编码
 * @param baBuf 保存字段编码后的协议信息
 * @param nTag 字段标签
 * @return 成功返回0，失败返回错误码
 */
int ${ClassName}::encode(MByteArray& baBuf, U16 nTag)
{
    baBuf.append(nTag).append((U8)M_FIELD_TYPE_TLV);

    // 预留长度字段
    baBuf.append((U32)0);
    // 子字段编码前长度
    int iOldLen = baBuf.getLength();

    // 编码子字段${FieldEncode}

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
int ${ClassName}::decode(const char* szBuf, int iBufLen)
{
    M_FIELD_DECODE(szBuf, iBufLen);
}

/**
 * 将字段格式化成可读形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param sPrefix 格式化字符串的前缀
 */
void ${ClassName}::format(MByteArray& baBuf, const string& sFieldName, const string& sPrefix)
{
    string sSubPrefix = sPrefix + "    ";

    baBuf.append(sPrefix).append("[").append(sFieldName).append("]\\n");${Formats}
}

/**
 * 将字段格式化成XML形式
 * @param baBuf 保存字段信息的缓存区
 * @param sFieldName 字段的名称
 * @param sPrefix 格式化字符串的前缀
 */
void ${ClassName}::toXml(MByteArray& baBuf, const string& sFieldName, const string& sPrefix)
{
    string sSubPrefix = sPrefix + "    ";

    baBuf.append(sPrefix).append("<").append(sFieldName).append(">\\n");${ToXmls}
    baBuf.append(sPrefix).append("</").append(sFieldName).append(">\\n");
}

/**
 * 字段解码
 * @param szBuf 要解析的协议
 * @param iBufLen 协议的长度
 * @return 成功返回0，失败返回错误码
 */
int ${ClassName}::decodeSubField(const char* szBuf, int iBufLen, U16 nTag)
{
    if (NULL == szBuf) return M_ERROR_INPUT_PARAM_NULL;${DecodeSubFieldSeletor}

    switch(nTag)
    {${DecodeSubField}
    default:
        return 0;
    }
}

''';

#
# H文件模版-字段模版
#
HDR_HTEMPLATE = '''/*
 * @(#) ${ClassName}Handler.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_HANDLER_H
#define ${ClassMacro}_HANDLER_H

${HdrIncludes}#include "${ClassName}.h"

/**
 * $ClassDesc
 */
class M_DLLIMPORT ${ClassName}Handler : public MFieldHandler
{
protected:
    ${ClassName}* m_pst${ClassName};${HdrAttrDefine}
public:
    /**
     * 构造函数
     */
    ${ClassName}Handler();

    /**
     * 设置字段对象
     * @param pst${ClassName} 字段对象
     */
    void set${ClassName}(${ClassName}* pst${ClassName}) {m_pst${ClassName} = pst${ClassName};}

    /**
     * 获取字段对象
     * @return 返回字段对象
     */
    ${ClassName}* get${ClassName}() {return m_pst${ClassName};}

    /**
     * 设置按字段名字设置子字段的值
     * @param szSubFieldName 字段名称
     * @param nIdx 数组字段的元素索引
     * @param szValue 字段的值
     */
    virtual void setFieldValueByName(const char* szSubFieldName, U16 nIdx, const char* szValue);

    /**
     * 通过子字段名称获取子字段处理器对象
     * @param szSubFieldName 字段名称
     * @param nIdx 数组字段的元素索引
     * @return 返回名称对应的处理器对象，若未找到，返回NULL
     */
    virtual MFieldHandler* getSubFieldHandlerByName(const char* szSubFieldName, U16 nIdx);
};

#endif
''';

#
# C文件模版-字段模版
#
HDR_CPPTEMPLATE = '''/*
 * @(#) ${ClassName}Handler.cpp Created by @itfriday message creator
 */

#include "${ClassName}Handler.h"
#include "comm/MErrorCode.h"

/**
 * 构造函数
 */
${ClassName}Handler::${ClassName}Handler()
{
    setFieldName("${ClassName}");${ConstructorFunc}
}

/**
 * 设置按字段名字设置子字段的值
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @param szValue 字段的值
 */
void ${ClassName}Handler::setFieldValueByName(const char* szSubFieldName, U16 nIdx, const char* szValue)
{
    if (NULL == szSubFieldName || NULL == szValue || NULL == m_pst${ClassName}) return;${SetValueByName}
}

/**
 * 通过子字段名称获取子字段处理器对象
 * @param szSubFieldName 字段名称
 * @param nIdx 数组字段的元素索引
 * @return 返回名称对应的处理器对象，若未找到，返回NULL
 */
MFieldHandler* ${ClassName}Handler::getSubFieldHandlerByName(const char* szSubFieldName, U16 nIdx)
{
    if (NULL == szSubFieldName || NULL == m_pst${ClassName}) return NULL;${GetHdrByName}

    return NULL;
}

''';
