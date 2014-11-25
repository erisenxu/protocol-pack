
/*
 * @(#) TestReq.cpp Created by feimao message creator
 */

#include "TestReq.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestReq::TestReq(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstGID = new MULongField(M_TAG(1), M_NAME("GID"), M_PARENT(this), M_VERSION(1), M_DEFAULT(10));
	m_pstMoney = new MIntField(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(20));
	m_pstGold = new MIntField(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(30));
}

/**
 * 析构函数
 */
TestReq::~TestReq()
{
	delete m_pstGID;
	delete m_pstMoney;
	delete m_pstGold;
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

	m_pstGID->encode(baBuf, nVer);
	m_pstMoney->encode(baBuf, nVer);
	m_pstGold->encode(baBuf, nVer);

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
	m_pstGID->format(baBuf, sSubPrefix, nVer);
	m_pstMoney->format(baBuf, sSubPrefix, nVer);
	m_pstGold->format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestReq::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstGID->toXml(baBuf, sSubPrefix, nVer);
	m_pstMoney->toXml(baBuf, sSubPrefix, nVer);
	m_pstGold->toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestReq::getSubField(U16 nTag)
{
	switch (nTag)
	{
	case 1:
		return m_pstGID;
	case 2:
		return m_pstMoney;
	case 3:
		return m_pstGold;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestReq::getSubFieldByName(const string& sName)
{
	if (sName == "GID") return m_pstGID;
	if (sName == "Money") return m_pstMoney;
	if (sName == "Gold") return m_pstGold;
	return NULL;
}

