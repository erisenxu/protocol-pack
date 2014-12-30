
/*
 * @(#) TestIdipMsg.h Created by @itfriday message creator
 */

#ifndef TEST_IDIP_MSG_H
#define TEST_IDIP_MSG_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "IdipMsg.h"

/**
 * a union object
 */
class M_DLLIMPORT TestIdipMsg : public MCompositeField
{
private:
	MUIntField m_stSequence; // 原因
	MUShortField m_stVersion; // 原因
	IdipMsg m_stIdipMsg;     // Test Message2

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestIdipMsg"), MField* pParent = NULL, U16 nVer = 0);

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
	IdipMsg* getIdipMsg() {return &m_stIdipMsg;}

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

