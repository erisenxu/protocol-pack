
/*
 * @(#) TestUnion2.h Created by feimao message creator
 */

#ifndef TEST_UNION2_H
#define TEST_UNION2_H

#include "field/MFieldInc.h"
#include "TestUnion.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnion2 : public MCompositeField
{
private:
	MIntField* m_pstReason; // 原因
	TestUnion* m_pstUnion;  // Test message

public:
	/**
	 * 构造函数
	 */
	TestUnion2(U16 nTag = 0, const string& name = string("TestUnion2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestUnion2();

	/**
	 * Get Function: 原因
	 */
	MIntField* getReason() {return m_pstReason;}

	/**
	 * Get Function: Test message
	 */
	TestUnion* getUnion() {return m_pstUnion;}

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

