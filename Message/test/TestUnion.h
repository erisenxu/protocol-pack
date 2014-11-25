
/*
 * @(#) TestUnion.h Created by feimao message creator
 */

#ifndef TEST_UNION_H
#define TEST_UNION_H

#include "field/MFieldInc.h"
#include "TestMsg.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnion : public MCompositeField
{
private:
	MShortField* m_pstSelection;    // Just added for simulate union selection
	MIntField* m_pstMoney; // 金币
	TestMsg* m_pstTestMsg; // Test message
	MIntField* m_pstGold;  // 钻石

public:
	/**
	 * 构造函数
	 */
	TestUnion(U16 nTag = 0, const string& name = string("TestUnion"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestUnion();

	/**
	 * Get Function: Selection
	 */
	MShortField* getSelection() {return m_pstSelection;}

	/**
	 * Get Function: 金币
	 */
	MIntField* getMoney() {return m_pstMoney;}

	/**
	 * Get Function: Test message
	 */
	TestMsg* getTestMsg() {return m_pstTestMsg;}

	/**
	 * Get Function: 钻石
	 */
	MIntField* getGold() {return m_pstGold;}

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
	virtual MField* getSubField(U16 nTag);

	/**
	 * @override
	 */
	virtual MField* getSubFieldByName(const string& sName);
};

#endif

