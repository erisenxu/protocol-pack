
/*
 * @(#) TestReq.h Created by @itfriday message creator
 */

#ifndef TEST_REQ_H
#define TEST_REQ_H

#include "field/MFieldInc.h"
#include "StarMacro.h"

/**
 * 测试用消息
 */
class M_DLLIMPORT TestReq : public MCompositeField
{
private:
	MULongField m_stGID; // GID
	MIntField m_stMoney; // 游戏币
	MIntField m_stGold; // 金币

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestReq"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: GID
	 */
	MULongField* getGID() {return &m_stGID;}

	/**
	 * Get Function: 游戏币
	 */
	MIntField* getMoney() {return &m_stMoney;}

	/**
	 * Get Function: 金币
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

