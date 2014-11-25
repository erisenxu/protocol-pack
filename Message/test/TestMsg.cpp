
/*
 * @(#) TestMsg.cpp Created by feimao message creator
 */

#include "TestMsg.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestMsg::TestMsg(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstMoney = new MIntField(M_TAG(1), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
	m_pstIntField = new MArrayField<MIntField>(M_TAG(3), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
	m_pstGold = new MIntField(M_TAG(2), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x789012));
}

/**
 * 析构函数
 */
TestMsg::~TestMsg()
{
	delete m_pstMoney;
	delete m_pstIntField;
	delete m_pstGold;
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

	m_pstMoney->encode(baBuf, nVer);
	m_pstIntField->encode(baBuf, nVer);
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
void TestMsg::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_pstMoney->format(baBuf, sSubPrefix, nVer);
	m_pstIntField->format(baBuf, sSubPrefix, nVer);
	m_pstGold->format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestMsg::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstMoney->toXml(baBuf, sSubPrefix, nVer);
	m_pstIntField->toXml(baBuf, sSubPrefix, nVer);
	m_pstGold->toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestMsg::getSubField(U16 nTag)
{
	switch (nTag)
	{
	case 1:
		return m_pstMoney;
	case 3:
		return m_pstIntField;
	case 2:
		return m_pstGold;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestMsg::getSubFieldByName(const string& sName)
{
	if (sName == "Money") return m_pstMoney;
	if (sName == "IntField") return m_pstIntField;
	if (sName == "Gold") return m_pstGold;
	return NULL;
}

