
/*
 * @(#) TestUnionMsg.h Created by @itfriday message creator
 */

#ifndef TEST_UNION_MSG_H
#define TEST_UNION_MSG_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "UnionMsg.h"

/**
 * a union object
 */
class M_DLLIMPORT TestUnionMsg : public MCompositeField
{
private:
	MUIntField m_stSequence; // 原因
	MUShortField m_stVersion; // 原因
	UnionMsg m_stUnionMsg;   // Test Message2

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestUnionMsg"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: 原因
	 */
	MUIntField* getSequence() {return &m_stSequence;}

	/**
	 * Get Function: 原因
	 */
	MUShortField* getVersion() {return &m_stVersion;}

	/**
	 * Get Function: Test Message2
	 */
	UnionMsg* getUnionMsg() {return &m_stUnionMsg;}

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

