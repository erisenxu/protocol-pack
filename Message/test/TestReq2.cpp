
/*
 * @(#) TestReq2.cpp Created by @itfriday message creator
 */

#include "TestReq2.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestReq2::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stTestReq.construct(M_TAG(1), M_NAME("testReq"), M_PARENT(this), M_VERSION(1));
	m_stReqInfo.construct(M_TAG(2), M_NAME("reqInfo"), M_PARENT(this), M_VERSION(1));
	m_stTypes.construct(M_TAG(30), M_NAME("types"), M_PARENT(this), M_VERSION(1));
	m_stGID.init(M_TAG(4), M_NAME("GID"), M_PARENT(this), M_VERSION(1), M_DEFAULT("0"));
}

/**
 * @override
 */
int TestReq2::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stTestReq.encode(baBuf, nVer);
	m_stReqInfo.encode(baBuf, nVer);
	m_stTypes.encode(baBuf, nVer);
	m_stGID.encode(baBuf, nVer);

	// 这个必须放后面，因为append有可能那个将baBuf的getData的返回地址改变
	U32 nAddLen = (U32)(baBuf.getLength() - iOldLen);
	char* pszMsg = baBuf.getData() + (baBuf.getLength() - nAddLen - sizeof(U32));

	M_U32_TO_CHAR(pszMsg, nAddLen);

	return 0;
}

/**
 * @override
 */
void TestReq2::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stTestReq.format(baBuf, sSubPrefix, nVer);
	m_stReqInfo.format(baBuf, sSubPrefix, nVer);
	m_stTypes.format(baBuf, sSubPrefix, nVer);
	m_stGID.format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestReq2::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stTestReq.toXml(baBuf, sSubPrefix, nVer);
	m_stReqInfo.toXml(baBuf, sSubPrefix, nVer);
	m_stTypes.toXml(baBuf, sSubPrefix, nVer);
	m_stGID.toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestReq2::getSubField(U16 nTag, U8 /*chMode*/)
{
	switch (nTag)
	{
	case 1:
		return &m_stTestReq;
	case 2:
		return &m_stReqInfo;
	case 30:
		return &m_stTypes;
	case 4:
		return &m_stGID;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestReq2::getSubFieldByName(const string& sName)
{
	if (sName == "testReq") return &m_stTestReq;
	if (sName == "reqInfo") return &m_stReqInfo;
	if (sName == "types") return &m_stTypes;
	if (sName == "GID") return &m_stGID;
	return NULL;
}

