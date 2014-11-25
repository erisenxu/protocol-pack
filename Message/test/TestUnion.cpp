
/*
 * @(#) TestUnion.cpp Created by feimao message creator
 */

#include "TestUnion.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestUnion::TestUnion(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstSelection = new MShortField(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(30));
	m_pstMoney = new MIntField(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
	m_pstTestMsg = new TestMsg(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
	m_pstGold = new MIntField(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x789012));
}

/**
 * 析构函数
 */
TestUnion::~TestUnion()
{
	delete m_pstSelection;
	delete m_pstMoney;
	delete m_pstTestMsg;
	delete m_pstGold;
}

/**
 * @override
 */
int TestUnion::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_pstSelection->encode(baBuf, nVer);
	switch (m_pstSelection->getValue())
	{
	case 2:
		m_pstMoney->encode(baBuf, nVer);
		break;
	case 3:
		m_pstTestMsg->encode(baBuf, nVer);
		break;
	case 4:
		m_pstGold->encode(baBuf, nVer);
		break;
	}

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestUnion::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_pstSelection->format(baBuf, sSubPrefix, nVer);
	switch (m_pstSelection->getValue())
	{
	case 2:
		m_pstMoney->format(baBuf, sSubPrefix, nVer);
		break;
	case 3:
		m_pstTestMsg->format(baBuf, sSubPrefix, nVer);
		break;
	case 4:
		m_pstGold->format(baBuf, sSubPrefix, nVer);
		break;
	}
}

/**
 * @override
 */
void TestUnion::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstSelection->toXml(baBuf, sSubPrefix, nVer);
	switch (m_pstSelection->getValue())
	{
	case 2:
		m_pstMoney->toXml(baBuf, sSubPrefix, nVer);
		break;
	case 3:
		m_pstTestMsg->toXml(baBuf, sSubPrefix, nVer);
		break;
	case 4:
		m_pstGold->toXml(baBuf, sSubPrefix, nVer);
		break;
	}
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestUnion::getSubField(U16 nTag)
{
	if (0xFFFF == nTag) return m_pstSelection;

	switch (m_pstSelection->getValue())
	{
	case 2:
		return m_pstMoney;
	case 3:
		return m_pstTestMsg;
	case 4:
		return m_pstGold;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestUnion::getSubFieldByName(const string& sName)
{
	if (sName == "Selection") return m_pstSelection;
	if (sName == "Money") return m_pstMoney;
	if (sName == "TestMsg") return m_pstTestMsg;
	if (sName == "Gold") return m_pstGold;
	return NULL;
}

