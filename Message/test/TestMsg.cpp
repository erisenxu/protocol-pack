
/*
 * @(#) TestMsg.cpp Created by @itfriday message creator
 */

#include "TestMsg.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestMsg::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stMoney.init(M_TAG(1), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
	m_stIntField.construct(M_TAG(3), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
	m_stGold.init(M_TAG(2), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x789012));
}

/**
 * @override
 */
int TestMsg::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stMoney.encode(baBuf, nVer);
	m_stIntField.encode(baBuf, nVer);
	m_stGold.encode(baBuf, nVer);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestMsg::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stMoney.format(baBuf, sSubPrefix, nVer);
	m_stIntField.format(baBuf, sSubPrefix, nVer);
	m_stGold.format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestMsg::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stMoney.toXml(baBuf, sSubPrefix, nVer);
	m_stIntField.toXml(baBuf, sSubPrefix, nVer);
	m_stGold.toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestMsg::getSubField(U16 nTag, U8 /*chMode*/)
{
	switch (nTag)
	{
	case 1:
		return &m_stMoney;
	case 3:
		return &m_stIntField;
	case 2:
		return &m_stGold;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestMsg::getSubFieldByName(const string& sName)
{
	if (sName == "Money") return &m_stMoney;
	if (sName == "IntField") return &m_stIntField;
	if (sName == "Gold") return &m_stGold;
	return NULL;
}

