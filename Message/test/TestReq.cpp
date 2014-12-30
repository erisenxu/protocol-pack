
/*
 * @(#) TestReq.cpp Created by @itfriday message creator
 */

#include "TestReq.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestReq::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stGID.init(M_TAG(1), M_NAME("GID"), M_PARENT(this), M_VERSION(1), M_DEFAULT(10));
	m_stMoney.init(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(20));
	m_stGold.init(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(30));
}

/**
 * @override
 */
int TestReq::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stGID.encode(baBuf, nVer);
	m_stMoney.encode(baBuf, nVer);
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
void TestReq::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stGID.format(baBuf, sSubPrefix, nVer);
	m_stMoney.format(baBuf, sSubPrefix, nVer);
	m_stGold.format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestReq::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stGID.toXml(baBuf, sSubPrefix, nVer);
	m_stMoney.toXml(baBuf, sSubPrefix, nVer);
	m_stGold.toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestReq::getSubField(U16 nTag, U8 /*chMode*/)
{
	switch (nTag)
	{
	case 1:
		return &m_stGID;
	case 2:
		return &m_stMoney;
	case 3:
		return &m_stGold;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestReq::getSubFieldByName(const string& sName)
{
	if (sName == "GID") return &m_stGID;
	if (sName == "Money") return &m_stMoney;
	if (sName == "Gold") return &m_stGold;
	return NULL;
}

