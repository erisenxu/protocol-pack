
/*
 * @(#) TestUnion2.cpp Created by @itfriday message creator
 */

#include "TestUnion2.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestUnion2::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stReason.init(M_TAG(1), M_NAME("Reason"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
	m_stUnion.construct(M_TAG(2), M_NAME("Union"), M_PARENT(this), M_VERSION(1));
}

/**
 * @override
 */
int TestUnion2::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stReason.encode(baBuf, nVer);
	m_stUnion.encode(baBuf, nVer);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestUnion2::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stReason.format(baBuf, sSubPrefix, nVer);
	m_stUnion.format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestUnion2::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stReason.toXml(baBuf, sSubPrefix, nVer);
	m_stUnion.toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestUnion2::getSubField(U16 nTag, U8 /*chMode*/)
{
	switch (nTag)
	{
	case 1:
		return &m_stReason;
	case 2:
		return &m_stUnion;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestUnion2::getSubFieldByName(const string& sName)
{
	if (sName == "Reason") return &m_stReason;
	if (sName == "Union") return &m_stUnion;
	return NULL;
}

