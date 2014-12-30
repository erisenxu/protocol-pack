
/*
 * @(#) TestReq2.h Created by @itfriday message creator
 */

#ifndef TEST_REQ2_H
#define TEST_REQ2_H

#include "field/MFieldInc.h"
#include "StarMacro.h"
#include "TestReq.h"

/**
 * 测试用消息
 */
class M_DLLIMPORT TestReq2 : public MCompositeField
{
private:
	TestReq m_stTestReq;                                // 请求信息1
	MArrayField<TestReq, MAX_TEST_INFO_NUM> m_stReqInfo; // 请求信息
	MArrayField<MUIntField, MAX_TYPE_NUM> m_stTypes;    // 类型列表
	MStringField m_stGID;                               // GID

public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("TestReq2"), MField* pParent = NULL, U16 nVer = 0);

	/**
	 * Get Function: 请求信息1
	 */
	TestReq* getTestReq() {return &m_stTestReq;}

	/**
	 * Get Function: 请求信息
	 */
	MArrayField<TestReq, MAX_TEST_INFO_NUM>* getReqInfo() {return &m_stReqInfo;}

	/**
	 * Get Function: 类型列表
	 */
	MArrayField<MUIntField, MAX_TYPE_NUM>* getTypes() {return &m_stTypes;}

	/**
	 * Get Function: GID
	 */
	MStringField* getGID() {return &m_stGID;}

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

