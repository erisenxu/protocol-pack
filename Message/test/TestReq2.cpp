
/*
 * @(#) TestReq2.cpp Created by feimao message creator
 */

#include "TestReq2.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestReq2::TestReq2(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstTestReq = new TestReq(M_TAG(1), M_NAME("testReq"), M_PARENT(this), M_VERSION(1));
	m_pstReqInfo = new MArrayField<TestReq>(M_TAG(2), M_NAME("reqInfo"), M_PARENT(this), M_VERSION(1));
	m_pstTypes = new MArrayField<MUIntField>(M_TAG(30), M_NAME("types"), M_PARENT(this), M_VERSION(1));
	m_pstGID = new MStringField(M_TAG(4), M_NAME("GID"), M_PARENT(this), M_VERSION(1), M_DEFAULT("0"));
}

/**
 * 析构函数
 */
TestReq2::~TestReq2()
{
	delete m_pstTestReq;
	delete m_pstReqInfo;
	delete m_pstTypes;
	delete m_pstGID;
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

	m_pstTestReq->encode(baBuf, nVer);
	m_pstReqInfo->encode(baBuf, nVer);
	m_pstTypes->encode(baBuf, nVer);
	m_pstGID->encode(baBuf, nVer);

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
	m_pstTestReq->format(baBuf, sSubPrefix, nVer);
	m_pstReqInfo->format(baBuf, sSubPrefix, nVer);
	m_pstTypes->format(baBuf, sSubPrefix, nVer);
	m_pstGID->format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestReq2::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstTestReq->toXml(baBuf, sSubPrefix, nVer);
	m_pstReqInfo->toXml(baBuf, sSubPrefix, nVer);
	m_pstTypes->toXml(baBuf, sSubPrefix, nVer);
	m_pstGID->toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestReq2::getSubField(U16 nTag)
{
	switch (nTag)
	{
	case 1:
		return m_pstTestReq;
	case 2:
		return m_pstReqInfo;
	case 30:
		return m_pstTypes;
	case 4:
		return m_pstGID;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestReq2::getSubFieldByName(const string& sName)
{
	if (sName == "testReq") return m_pstTestReq;
	if (sName == "reqInfo") return m_pstReqInfo;
	if (sName == "types") return m_pstTypes;
	if (sName == "GID") return m_pstGID;
	return NULL;
}

