
/*
 * @(#) TestReq.h Created by feimao message creator
 */

#ifndef TEST_REQ_H
#define TEST_REQ_H

#include "field/MFieldInc.h"

/**
 * 测试用消息
 */
class M_DLLIMPORT TestReq : public MCompositeField
{
private:
	MULongField* m_pstGID; // GID
	MIntField* m_pstMoney; // 金币
	MIntField* m_pstGold;  // 钻石

public:
	/**
	 * 构造函数
	 */
	TestReq(U16 nTag = 0, const string& name = string("TestReq"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestReq();

	/**
	 * Get Function: GID
	 */
	MULongField* getGID() {return m_pstGID;}

	/**
	 * Get Function: 金币
	 */
	MIntField* getMoney() {return m_pstMoney;}

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

