
/*
 * @(#) TestUnion2.h Created by @itfriday message creator
 */

#ifndef TEST_UNION2_H
#define TEST_UNION2_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "TestUnion.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnion2 : public MCompositeField
{
private:
	MIntField m_stReason; // 原因
	TestUnion m_stUnion; // Test message

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestUnion2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: 原因
	 */
	MIntField* getReason() {return &m_stReason;}

	/**
	 * Get Function: Test message
	 */
	TestUnion* getUnion() {return &m_stUnion;}

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

