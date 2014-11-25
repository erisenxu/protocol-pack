
/*
 * @(#) TestUnion3.cpp Created by feimao message creator
 */

#include "TestUnion3.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestUnion3::TestUnion3(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstReason = new MIntField(M_TAG(1), M_NAME("Reason"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
	m_pstUnion2 = new TestUnion2(M_TAG(2), M_NAME("Union2"), M_PARENT(this), M_VERSION(1));
	m_pstReason2 = new MIntField(M_TAG(3), M_NAME("Reason2"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
}

/**
 * 析构函数
 */
TestUnion3::~TestUnion3()
{
	delete m_pstReason;
	delete m_pstUnion2;
	delete m_pstReason2;
}

/**
 * @override
 */
int TestUnion3::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_pstReason->encode(baBuf, nVer);
	m_pstUnion2->encode(baBuf, nVer);
	m_pstReason2->encode(baBuf, nVer);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestUnion3::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_pstReason->format(baBuf, sSubPrefix, nVer);
	m_pstUnion2->format(baBuf, sSubPrefix, nVer);
	m_pstReason2->format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestUnion3::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstReason->toXml(baBuf, sSubPrefix, nVer);
	m_pstUnion2->toXml(baBuf, sSubPrefix, nVer);
	m_pstReason2->toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestUnion3::getSubField(U16 nTag)
{
	switch (nTag)
	{
	case 1:
		return m_pstReason;
	case 2:
		return m_pstUnion2;
	case 3:
		return m_pstReason2;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestUnion3::getSubFieldByName(const string& sName)
{
	if (sName == "Reason") return m_pstReason;
	if (sName == "Union2") return m_pstUnion2;
	if (sName == "Reason2") return m_pstReason2;
	return NULL;
}

