
/*
 * @(#) TestMsg2.cpp Created by feimao message creator
 */

#include "TestMsg2.h"
#include "comm/MBaseFuncDef.h"

/**
 * 构造函数
 */
TestMsg2::TestMsg2(U16 nTag, const string& name, MField* pParent, U16 nVer)
	: MCompositeField(nTag, name, pParent, nVer)
{
	m_pstTestMsg = new MArrayField<TestMsg>(M_TAG(1), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
	m_pstIntField = new MArrayField<MIntField>(M_TAG(2), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
}

/**
 * 析构函数
 */
TestMsg2::~TestMsg2()
{
	delete m_pstTestMsg;
	delete m_pstIntField;
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

	m_pstTestMsg->encode(baBuf, nVer);
	m_pstIntField->encode(baBuf, nVer);

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
	m_pstTestMsg->format(baBuf, sSubPrefix, nVer);
	m_pstIntField->format(baBuf, sSubPrefix, nVer);
}

/**
 * @override
 */
void TestMsg2::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_pstTestMsg->toXml(baBuf, sSubPrefix, nVer);
	m_pstIntField->toXml(baBuf, sSubPrefix, nVer);
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestMsg2::getSubField(U16 nTag)
{
	switch (nTag)
	{
	case 1:
		return m_pstTestMsg;
	case 2:
		return m_pstIntField;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestMsg2::getSubFieldByName(const string& sName)
{
	if (sName == "TestMsg") return m_pstTestMsg;
	if (sName == "IntField") return m_pstIntField;
	return NULL;
}

