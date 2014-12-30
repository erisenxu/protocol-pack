#!/usr/bin/env python
#coding:utf-8
#=================================================================
# @ Author : Erisenxu @ Innovate Center
# @ Desc : 文件模版
# @ FileName : htemplate.py
# @ Date : 2014-03-29
# @ ModifyHistory :
# @ Remark :
#==================================================================

#
# C++头文件模版
#
CPPHTEMPLATE = '''
/*
 * @(#) $ClassName.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_H
#define ${ClassMacro}_H

#include "field/MFieldInc.h"${MacroInclude}
$Includes
/**
 * $ClassDesc
 */
class M_DLLIMPORT $ClassName : public MCompositeField
{
private:
$AttrDefine
public:
	/**
	 * 显式构造函数
	 */
	virtual void construct(U16 nTag = 0, const string& sName = string("$ClassName"), MField* pParent = NULL, U16 nVer = 0);
$FuncDefine
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

''';

#
# C头文件模版-字段模版
#
CHTEMPLATE = '''
/*
 * @(#) $ClassName.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_H
#define ${ClassMacro}_H

#include "field/FieldInc.h"${MacroInclude}
$Includes
/**
 * $ClassDesc
 */
struct tag${ClassName}
{
	FIELD stField;$AttrDefine
};

typedef struct tag${ClassName}  ${UpperClassName};
typedef struct tag${ClassName}* LP${UpperClassName};

/**
 * 字段信息定义
 */
extern FIELDINFO g_st${ClassName}FieldInfo;

#endif
''';

#
# C头文件模版-消息模版
#
CMSGHTEMPLATE = '''
/*
 * @(#) $ClassName.h Created by @itfriday message creator
 */

#ifndef ${ClassMacro}_H
#define ${ClassMacro}_H

#include "field/FieldInc.h"${MacroInclude}
$Includes
/**
 * $ClassDesc
 */
union tag${ClassName}
{
	$AttrDefine
};

typedef union tag${ClassName}  ${UpperClassName};
typedef union tag${ClassName}* LP${UpperClassName};

/**
 * The message object
 */
struct tagMsg${ClassName}
{
	U32 dwSequence;						/* The message sequence */
	U16 nMsgVer;						/* The message version */
	U16 nMsgType;						/* The message type */
	/* you can add your own field as needed, suce as ZipFlag, EncryptFlag, etc. */
	${UpperClassName} st${ClassName};	/* The message data */
};

typedef union tagMsg${ClassName}  MSG${UpperClassName};
typedef union tagMsg${ClassName}* LPMSG${UpperClassName};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * The message encode
 */
int msg_encode_${LowerClassMarco}(LPMSG${UpperClassName} pstMsgObj, LPBYTEARRAY pstByteArray);

/**
 * The message decode
 */
int msg_decode_${LowerClassMarco}(LPMSG${UpperClassName} pstMsgObj, const char* szBuf, int iBufLen);

#ifdef __cplusplus
}
#endif

#endif
''';

