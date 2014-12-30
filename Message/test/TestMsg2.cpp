
/*
 * @(#) TestMsg2.cpp Created by @itfriday message creator
 */

#include "TestMsg2.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestMsg2::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stTestMsg.construct(M_TAG(1), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
	m_stIntField.construct(M_TAG(2), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
}

/**
 * @override
 */
int TestMsg2::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stTestMsg.encode(baBuf, nVer);
	m_stIntField.encode(baBuf, nVer);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestMsg2::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stTestMsg.format(baBuf, sSubPrefix, nVer);
	m_stIntField.format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestMsg2::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stTestMsg.toXml(baBuf, sSubPrefix, nVer);
	m_stIntField.toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestMsg2::getSubField(U16 nTag, U8 /*chMode*/)
{
	switch (nTag)
	{
	case 1:
		return &m_stTestMsg;
	case 2:
		return &m_stIntField;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestMsg2::getSubFieldByName(const string& sName)
{
	if (sName == "TestMsg") return &m_stTestMsg;
	if (sName == "IntField") return &m_stIntField;
	return NULL;
}

