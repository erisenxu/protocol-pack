
/*
 * @(#) TestMsg.h Created by feimao message creator
 */

#ifndef TEST_MSG_H
#define TEST_MSG_H

#include "field/MFieldInc.h"

/**
 * Just a Test Message object
 */
class M_DLLIMPORT TestMsg : public MCompositeField
{
private:
	MIntField* m_pstMoney;                 // 金币
	MArrayField<MIntField>* m_pstIntField; // 类型列表
	MIntField* m_pstGold;                  // 钻石

public:
	/**
	 * 构造函数
	 */
	TestMsg(U16 nTag = 0, const string& name = string("TestMsg"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestMsg();

	/**
	 * Get Function: 金币
	 */
	MIntField* getMoney() {return m_pstMoney;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MIntField>* getIntField() {return m_pstIntField;}

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

