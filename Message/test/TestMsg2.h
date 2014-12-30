
/*
 * @(#) TestMsg2.h Created by @itfriday message creator
 */

#ifndef TEST_MSG2_H
#define TEST_MSG2_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "TestMsg.h"

/**
 * Just a Test Message object
 */
class M_DLLIMPORT TestMsg2 : public MCompositeField
{
private:
	MArrayField<TestMsg, 4> m_stTestMsg;   // 金币
	MArrayField<MIntField, 4> m_stIntField; // 类型列表

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestMsg2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: 金币
	 */
	MArrayField<TestMsg, 4>* getTestMsg() {return &m_stTestMsg;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MIntField, 4>* getIntField() {return &m_stIntField;}

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

