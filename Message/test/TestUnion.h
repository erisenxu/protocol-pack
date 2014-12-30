
/*
 * @(#) TestUnion.h Created by @itfriday message creator
 */

#ifndef TEST_UNION_H
#define TEST_UNION_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnion : public MCompositeField
{
private:
	MShortField m_stSelection;    // Just added for simulate union selection
	union
	{
		MIntField m_stMoney;                  // 金币
		TestMsg m_stTestMsg;                  // Test message
		MIntField m_stGold;                   // 钻石
		MStringField m_stDesc;                // 描述
		MArrayField<MIntField, 4> m_stIntField; // 类型列表
	};
public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestUnion"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: Selection
	 */
	MShortField* getSelection() {return &m_stSelection;}

	/**
	 * Get Function: 金币
	 */
	MIntField* getMoney() {return &m_stMoney;}

	/**
	 * Get Function: Test message
	 */
	TestMsg* getTestMsg() {return &m_stTestMsg;}

	/**
	 * Get Function: 钻石
	 */
	MIntField* getGold() {return &m_stGold;}

	/**
	 * Get Function: 描述
	 */
	MStringField* getDesc() {return &m_stDesc;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MIntField, 4>* getIntField() {return &m_stIntField;}

	/**
	 * @override
	 */
	virtual int encode(MByteArray& baBuf, U16 nVer);

	/**
	 * @override
	 */
	virtual void format(MByteArray& baBuf, const string& sPrefix, U16 nVer);

	/**
	 * @override
	 */
	virtual void toXml(MByteArray& baBuf, const string& sPrefix, U16 nVer);

	/**
	 * @override
	 */
	virtual MField* getSubField(U16 nTag, U8 chMode);

	/**
	 * @override
	 */
	virtual MField* getSubFieldByName(const string& sName);
};

#endif

