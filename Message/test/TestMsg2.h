
/*
 * @(#) TestMsg2.h Created by feimao message creator
 */

#ifndef TEST_MSG2_H
#define TEST_MSG2_H

#include "field/MFieldInc.h"
#include "TestMsg.h"

/**
 * Just a Test Message object
 */
class M_DLLIMPORT TestMsg2 : public MCompositeField
{
private:
	MArrayField<TestMsg>* m_pstTestMsg;    // 金币
	MArrayField<MIntField>* m_pstIntField; // 类型列表

public:
	/**
	 * 构造函数
	 */
	TestMsg2(U16 nTag = 0, const string& name = string("TestMsg2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestMsg2();

	/**
	 * Get Function: 金币
	 */
	MArrayField<TestMsg>* getTestMsg() {return m_pstTestMsg;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MIntField>* getIntField() {return m_pstIntField;}

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

