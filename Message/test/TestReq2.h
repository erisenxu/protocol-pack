
/*
 * @(#) TestReq2.h Created by feimao message creator
 */

#ifndef TEST_REQ2_H
#define TEST_REQ2_H

#include "field/MFieldInc.h"
#include "TestReq.h"

/**
 * 测试用消息
 */
class M_DLLIMPORT TestReq2 : public MCompositeField
{
private:
	TestReq* m_pstTestReq;               // 请求信息1
	MArrayField<TestReq>* m_pstReqInfo;  // 请求信息
	MArrayField<MUIntField>* m_pstTypes; // 类型列表
	MStringField* m_pstGID;              // GID

public:
	/**
	 * 构造函数
	 */
	TestReq2(U16 nTag = 0, const string& name = string("TestReq2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * 析构函数
	 */
	virtual ~TestReq2();

	/**
	 * Get Function: 请求信息1
	 */
	TestReq* getTestReq() {return m_pstTestReq;}

	/**
	 * Get Function: 请求信息
	 */
	MArrayField<TestReq>* getReqInfo() {return m_pstReqInfo;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MUIntField>* getTypes() {return m_pstTypes;}

	/**
	 * Get Function: GID
	 */
	MStringField* getGID() {return m_pstGID;}

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

