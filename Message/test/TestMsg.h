
/*
 * @(#) TestMsg.h Created by @itfriday message creator
 */

#ifndef TEST_MSG_H
#define TEST_MSG_H

#include "field/MFieldInc.h"
#include "StarMacro.h"

/**
 * Just a Test Message object
 */
class M_DLLIMPORT TestMsg : public MCompositeField
{
private:
	MIntField m_stMoney;                   // 金币
	MArrayField<MIntField, 4> m_stIntField; // 类型列表
	MIntField m_stGold;                    // 钻石

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestMsg"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: 金币
	 */
	MIntField* getMoney() {return &m_stMoney;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MIntField, 4>* getIntField() {return &m_stIntField;}

	/**
	 * Get Function: 钻石
	 */
	MIntField* getGold() {return &m_stGold;}

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

