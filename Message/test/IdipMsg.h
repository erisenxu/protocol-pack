
/*
 * @(#) IdipMsg.h Created by @itfriday message creator
 */

#ifndef IDIP_MSG_H
#define IDIP_MSG_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"
#include "TestMsg2.h"

/**
 * IDIP Message
 */
class M_DLLIMPORT IdipMsg : public MCompositeField
{
private:
	MShortField m_stSelection;    // Just added for simulate union selection
	union
	{
		TestMsg m_stTestMsg; // Test Message
		TestMsg2 m_stTestMsg2; // Test Message2
	};
public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("IdipMsg"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: Selection
	 */
	MShortField* getSelection() {return &m_stSelection;}

	/**
	 * Get Function: Test Message
	 */
	TestMsg* getTestMsg() {return &m_stTestMsg;}

	/**
	 * Get Function: Test Message2
	 */
	TestMsg2* getTestMsg2() {return &m_stTestMsg2;}

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

