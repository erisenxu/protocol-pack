
/*
 * @(#) IdipMsg.cpp Created by @itfriday message creator
 */

#include "IdipMsg.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void IdipMsg::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stSelection.init(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0));
}

/**
 * @override
 */
int IdipMsg::encode(MByteArray& baBuf, U16 nVer)
{
	M_CHECK_FIELD_VER_RET(nVer);

	MField::encode(baBuf, nVer);
	baBuf.append((U32)0);

	int iOldLen = baBuf.getLength();

	m_stSelection.encode(baBuf, nVer);
	switch (m_stSelection.getValue())
	{
	case TEST_MSG:
		m_stTestMsg.construct(M_TAG(TEST_MSG), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.encode(baBuf, nVer);
		break;
	case TEST_MSG_2:
		m_stTestMsg2.construct(M_TAG(TEST_MSG_2), M_NAME("TestMsg2"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg2.encode(baBuf, nVer);
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
void IdipMsg::format(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("[").append(getFieldName()).append("]\n");
	m_stSelection.format(baBuf, sSubPrefix, nVer);
	switch (m_stSelection.getValue())
	{
	case TEST_MSG:
		m_stTestMsg.construct(M_TAG(TEST_MSG), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.format(baBuf, sSubPrefix, nVer);
		break;
	case TEST_MSG_2:
		m_stTestMsg2.construct(M_TAG(TEST_MSG_2), M_NAME("TestMsg2"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg2.format(baBuf, sSubPrefix, nVer);
		break;
	}
}

/**
 * @override
 */
void IdipMsg::toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer)
{
	string sSubPrefix = sPrefix + "    ";
	M_CHECK_FIELD_VER(nVer);

	baBuf.append(sPrefix).append("<").append(getFieldName()).append(">\n");
	m_stSelection.toXml(baBuf, sSubPrefix, nVer);
	switch (m_stSelection.getValue())
	{
	case TEST_MSG:
		m_stTestMsg.construct(M_TAG(TEST_MSG), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.toXml(baBuf, sSubPrefix, nVer);
		break;
	case TEST_MSG_2:
		m_stTestMsg2.construct(M_TAG(TEST_MSG_2), M_NAME("TestMsg2"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg2.toXml(baBuf, sSubPrefix, nVer);
		break;
	}
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* IdipMsg::getSubField(U16 nTag, U8 chMode)
{
	if (0xFFFF == nTag) return &m_stSelection;

	switch (m_stSelection.getValue())
	{
	case TEST_MSG:
		m_stTestMsg.construct(M_TAG(TEST_MSG), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg;
	case TEST_MSG_2:
		m_stTestMsg2.construct(M_TAG(TEST_MSG_2), M_NAME("TestMsg2"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg2;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* IdipMsg::getSubFieldByName(const string& sName)
{
	if (sName == "Selection") return &m_stSelection;
	if (sName == "TestMsg")
	{
		m_stTestMsg.construct(M_TAG(TEST_MSG), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg;
	}
	if (sName == "TestMsg2")
	{
		m_stTestMsg2.construct(M_TAG(TEST_MSG_2), M_NAME("TestMsg2"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg2;
	}
	return NULL;
}

