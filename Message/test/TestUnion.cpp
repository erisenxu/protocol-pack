
/*
 * @(#) TestUnion.cpp Created by @itfriday message creator
 */

#include "TestUnion.h"
#include "comm/MBaseFuncDef.h"

/**
 * 显式构造函数
 */
void TestUnion::construct(U16 nTag, const string& sName, MField* pParent, U16 nVer)
{
	MCompositeField::construct(nTag, sName, pParent, nVer);
	m_stSelection.init(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0));
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

	m_stSelection.encode(baBuf, nVer);
	switch (m_stSelection.getValue())
	{
	case 2:
		m_stMoney.construct(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1));
		m_stMoney.encode(baBuf, nVer);
		break;
	case 3:
		m_stTestMsg.construct(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.encode(baBuf, nVer);
		break;
	case 4:
		m_stGold.construct(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1));
		m_stGold.encode(baBuf, nVer);
		break;
	case 5:
		m_stDesc.construct(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1));
		m_stDesc.encode(baBuf, nVer);
		break;
	case 6:
		m_stIntField.construct(M_TAG(6), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
		m_stIntField.encode(baBuf, nVer);
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
	m_stSelection.format(baBuf, sSubPrefix, nVer);
	switch (m_stSelection.getValue())
	{
	case 2:
		m_stMoney.construct(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1));
		m_stMoney.format(baBuf, sSubPrefix, nVer);
		break;
	case 3:
		m_stTestMsg.construct(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.format(baBuf, sSubPrefix, nVer);
		break;
	case 4:
		m_stGold.construct(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1));
		m_stGold.format(baBuf, sSubPrefix, nVer);
		break;
	case 5:
		m_stDesc.construct(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1));
		m_stDesc.format(baBuf, sSubPrefix, nVer);
		break;
	case 6:
		m_stIntField.construct(M_TAG(6), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
		m_stIntField.format(baBuf, sSubPrefix, nVer);
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
	m_stSelection.toXml(baBuf, sSubPrefix, nVer);
	switch (m_stSelection.getValue())
	{
	case 2:
		m_stMoney.construct(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1));
		m_stMoney.toXml(baBuf, sSubPrefix, nVer);
		break;
	case 3:
		m_stTestMsg.construct(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		m_stTestMsg.toXml(baBuf, sSubPrefix, nVer);
		break;
	case 4:
		m_stGold.construct(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1));
		m_stGold.toXml(baBuf, sSubPrefix, nVer);
		break;
	case 5:
		m_stDesc.construct(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1));
		m_stDesc.toXml(baBuf, sSubPrefix, nVer);
		break;
	case 6:
		m_stIntField.construct(M_TAG(6), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
		m_stIntField.toXml(baBuf, sSubPrefix, nVer);
		break;
	}
	baBuf.append(sPrefix).append("</").append(getFieldName()).append(">\n");
}

/**
 * @override
 */
MField* TestUnion::getSubField(U16 nTag, U8 chMode)
{
	if (0xFFFF == nTag) return &m_stSelection;

	switch (m_stSelection.getValue())
	{
	case 2:
		if (M_GET_SUB_FIELD_MODE_DECODE == chMode)
		{
			m_stMoney.init(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x123456));
		}
		else
		{
			m_stMoney.construct(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1));
		}
		return &m_stMoney;
	case 3:
		m_stTestMsg.construct(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg;
	case 4:
		if (M_GET_SUB_FIELD_MODE_DECODE == chMode)
		{
			m_stGold.init(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0x789012));
		}
		else
		{
			m_stGold.construct(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1));
		}
		return &m_stGold;
	case 5:
		if (M_GET_SUB_FIELD_MODE_DECODE == chMode)
		{
			m_stDesc.init(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1), M_DEFAULT(""));
		}
		else
		{
			m_stDesc.construct(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1));
		}
		return &m_stDesc;
	case 6:
		m_stIntField.construct(M_TAG(6), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
		return &m_stIntField;
	default:
		return NULL;
	}
}

/**
 * @override
 */
MField* TestUnion::getSubFieldByName(const string& sName)
{
	if (sName == "Selection") return &m_stSelection;
	if (sName == "Money")
	{
		m_stMoney.construct(M_TAG(2), M_NAME("Money"), M_PARENT(this), M_VERSION(1));
		return &m_stMoney;
	}
	if (sName == "TestMsg")
	{
		m_stTestMsg.construct(M_TAG(3), M_NAME("TestMsg"), M_PARENT(this), M_VERSION(1));
		return &m_stTestMsg;
	}
	if (sName == "Gold")
	{
		m_stGold.construct(M_TAG(4), M_NAME("Gold"), M_PARENT(this), M_VERSION(1));
		return &m_stGold;
	}
	if (sName == "Desc")
	{
		m_stDesc.construct(M_TAG(5), M_NAME("Desc"), M_PARENT(this), M_VERSION(1));
		return &m_stDesc;
	}
	if (sName == "IntField")
	{
		m_stIntField.construct(M_TAG(6), M_NAME("IntField"), M_PARENT(this), M_VERSION(1));
		return &m_stIntField;
	}
	return NULL;
}

