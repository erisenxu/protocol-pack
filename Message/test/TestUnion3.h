
/*
 * @(#) TestUnion3.h Created by feimao message creator
 */

#ifndef TEST_UNION3_H
#define TEST_UNION3_H

#include "field/MFieldInc.h"
#include "TestUnion2.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnion3 : public MCompositeField
{
private:
	MIntField* m_pstReason;  // 原因
	TestUnion2* m_pstUnion2; // Test message
	MIntField* m_pstReason2; // 原因

public:
	/**
	 * 构造函数
	 */
	TestUnion3(U16 nTag = 0, const string& name = string("TestUnion3"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestUnion3();

	/**
	 * Get Function: 原因
	 */
	MIntField* getReason() {return m_pstReason;}

	/**
	 * Get Function: Test message
	 */
	TestUnion2* getUnion2() {return m_pstUnion2;}

	/**
	 * Get Function: 原因
	 */
	MIntField* getReason2() {return m_pstReason2;}

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

