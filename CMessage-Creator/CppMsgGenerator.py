#!/usr/bin/python
# -*- coding: utf-8 -*-

from MsgGenerator import *;

from string import Template;
import os;

import cpptemplate;
import config;

#
# 取类型对应名称前缀
#
def getNamePrefix(ftype):
	if (config.M_C_NAME_PREFIX_MAP.has_key(ftype)):
		return config.M_C_NAME_PREFIX_MAP[ftype];
	else:
		return 'st';

#
# 取类型对应的结构名(C语言)
#
def getStructName(ftype):
	if (config.M_C_TYPE_MAP.has_key(ftype)):
		return config.M_C_TYPE_MAP[ftype];
	else:
		return ftype;

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstUpper(name);

#
# 取类型属性定义长度
#
def getStructAttrDefLen(fi):
	maxWidth = 0;
	if (fi.type == 'array'):
		attrDef = '%s m_a%s%s[%s];'%(getStructName(fi.subtype), getNamePrefix(fi.subtype), getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	elif (fi.type == 'string'):
		attrDef = '%s m_%s%s[%s];'%(getStructName(fi.type), getNamePrefix(fi.type), getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	else:
		attrDef = '%s m_%s%s;'%(getStructName(fi.type), getNamePrefix(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	return maxWidth;

class CppMsgGenerator(MsgGenerator):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile=''):
		MsgGenerator.__init__(self, structInfo, macroFile);
		self.attributes = '';
		self.attrGetSetDefine = '';
		self.includes = '';
		self.inclClass = [];
		self.fieldEncode = '';
		self.formats = '';
		self.toXmls = '';
		self.getSubField = '';
		self.getFieldByName = '';
		self.getSubFieldSelector = '';
		self.decodeSubFieldSeletor = '';
		self.decodeSubField = '';
		# for handler
		self.hdrIncludes = '';
		self.hdrAttrDefine = '';
		self.setValueByName = '';
		self.getHdrByName = '';
		self.constructorFunc = '';
		self.handleStructInfo();

	#
	# 处理结构体
	#
	def handleStructInfo(self):
		if (self.structInfo == None):
			return;
		maxWidth = 0;
		for fi in self.structInfo.fields:
			width = getStructAttrDefLen(fi);
			if (width > maxWidth):
				maxWidth = width;

		className = getClassName(self.structInfo.name)

		for fi in self.structInfo.fields:
			if (fi.tag == '' or fi.tag == None):
				#otag = int(fi.tag);
				raise Exception("Please give tag for struct(%s), field(%s)"%(self.structInfo.name, fi.name));

			unionTab = '';
			unionEncodeStart = '';
			unionEncodeEnd = '';
			unionGetValue = '';

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionTab = '    ';
				unionEncodeStart = '\n    case %s:'%(fi.tag);
				unionEncodeEnd = '\n        break;';
				# GetFieldByName
				if (config.M_C_TYPE_MAP.has_key(fi.type) == False):
					self.getFieldByName += '\n    if (sName == "%s")\n    {\n        m_nSelector = %s;\n        return &m_st%s;\n    }'%(fi.name, fi.tag, getAttrName(fi.name));

			ifPrefix = '\n\n    if (!strncmp(szSubFieldName, "%s", sizeof("%s")))\n    {'%(fi.name, fi.name);
			elifPrefix = '\n    }\n    else if (!strncmp(szSubFieldName, "%s", sizeof("%s")))\n    {'%(fi.name, fi.name);
			if (self.setValueByName != ''):
				setValuePrefix = elifPrefix;
			else:
				setValuePrefix = ifPrefix;

			# 处理属性列表
			if (fi.type == 'array'):
				attrDef = '%s%s m_a%s%s[%s];'%(unionTab, getStructName(fi.subtype), getNamePrefix(fi.subtype), getAttrName(fi.name), fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n    %s%s */'%(attrDef, fi.desc);

				arrRefer = self.structInfo.getFieldByName(fi.refer);
				if (fi.refer == '' or fi.refer == None or arrRefer == None):
					raise Exception("Please give number refer for struct(%s), array field(%s)"%(self.structInfo.name, fi.name));
				arrReferName = '%s%s'%(getNamePrefix(arrRefer.type), getAttrName(arrRefer.name));

				if (config.M_C_TYPE_MAP.has_key(fi.subtype)):
					attrName = '%s%s'%(getNamePrefix(fi.subtype), getAttrName(fi.name));
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    %s get%s(U16 nIndex) {return nIndex < %s ? m_a%s[nIndex] : m_a%s[%s - 1];}\n'%(fi.desc,
						getStructName(fi.subtype), getAttrName(fi.name), fi.count, attrName, attrName, fi.count);
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    void set%s(U16 nIndex, %s %s) {if (nIndex < %s) m_a%s[nIndex] = %s;}\n'%(fi.desc,
						getAttrName(fi.name), getStructName(fi.subtype), attrName, fi.count, attrName, attrName);
					# Encode
					self.fieldEncode += '%s\n    %sM_ARRAY_ENCODE(baBuf, %s, m_%s, m_a%s);%s'%(unionEncodeStart, unionTab, fi.tag, arrReferName, attrName, unionEncodeEnd);
					# Format
					self.formats += '%s\n    %sM_ARRAY_FORMAT(baBuf, "%s", m_%s, m_a%s, sSubPrefix);%s'%(unionEncodeStart, unionTab, fi.name, arrReferName, attrName, unionEncodeEnd);
					# ToXml
					self.toXmls += '%s\n    %sM_ARRAY_TOXML(baBuf, "%s", m_%s, m_a%s, sSubPrefix);%s'%(unionEncodeStart, unionTab, fi.name, arrReferName, attrName, unionEncodeEnd);
					# Decode
					self.decodeSubField += '\n    case %s:\n        M_ARRAY_DECODE(szBuf, iBufLen, %s, m_a%s);'%(fi.tag, fi.count, attrName);
					# Handler
					if (config.M_C_VALUE_MAP.has_key(fi.subtype)):
						self.setValueByName += '%s\n        m_pst%s->set%s(nIdx, %s(szValue));'%(setValuePrefix, className,
							getAttrName(fi.name), config.M_C_VALUE_MAP[fi.subtype]);
					self.getHdrByName += '%s\n        return this;\n    }'%(ifPrefix);
				else:
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    %s& get%s(U16 nIndex) {return nIndex < %s ? m_ast%s[nIndex] : m_ast%s[%s - 1];}\n'%(fi.desc,
						getStructName(fi.subtype), getAttrName(fi.name), fi.count, getAttrName(fi.name), getAttrName(fi.name), fi.count);
					# Encode
					self.fieldEncode += '%s\n    %sM_ARRAY_FIELD_ENCODE(baBuf, %s, m_%s, get%s);%s'%(unionEncodeStart, unionTab, fi.tag, arrReferName, getAttrName(fi.name), unionEncodeEnd);
					# Format
					self.formats += '%s\n    %sM_ARRAY_FIELD_FORMAT(baBuf, "%s", m_%s, get%s, sSubPrefix);%s'%(unionEncodeStart, unionTab, fi.name, arrReferName, getAttrName(fi.name), unionEncodeEnd);
					# ToXml
					self.toXmls += '%s\n    %sM_ARRAY_FIELD_TOXML(baBuf, "%s", m_%s, get%s, sSubPrefix);%s'%(unionEncodeStart, unionTab, fi.name, arrReferName, getAttrName(fi.name), unionEncodeEnd);
					# Decode
					self.decodeSubField += '\n    case %s:\n        M_ARRAY_FIELD_DECODE(szBuf, iBufLen, %s, get%s);'%(fi.tag, fi.count, getAttrName(fi.name));
					# for handler
					self.hdrAttrDefine += '\n    %sHandler m_st%sHdr;'%(getStructName(fi.subtype), getAttrName(fi.name));
					self.getHdrByName += '%s\n        m_st%sHdr.set%s(&m_pst%s->get%s(nIdx));\n        return &m_st%sHdr;\n    }'%(ifPrefix,
						getAttrName(fi.name), getClassName(fi.subtype), className, getAttrName(fi.name), getAttrName(fi.name));
					self.constructorFunc += '\n    m_st%sHdr.setParentHandler(this);'%(getAttrName(fi.name));
				if (config.M_C_TYPE_MAP.has_key(fi.subtype) == False and fi.subtype not in self.inclClass):
					self.inclClass.append(fi.subtype);
				pass;
			elif (fi.type == 'string'):
				attrName = '%s%s'%(getNamePrefix(fi.type), getAttrName(fi.name));
				attrDef = '%s%s m_%s[%s];'%(unionTab, getStructName(fi.type), attrName, fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n    %s%s */'%(attrDef, fi.desc);
				# get and set
				self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    const %s* get%s() {return m_%s;}\n'%(fi.desc,
					getStructName(fi.type), getAttrName(fi.name), attrName);
				self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    void set%s(const %s* %s) {STRCPY(m_%s, %s, %s);}\n'%(fi.desc,
					getAttrName(fi.name), getStructName(fi.type), attrName, attrName, attrName, fi.count);
				# Encode
				self.fieldEncode += '%s\n    %sMField::encode(m_%s, baBuf, %s);%s'%(unionEncodeStart,
					unionTab, attrName, fi.tag, unionEncodeEnd);
				# Format
				self.formats += '%s\n    %sMField::format(baBuf, "%s", m_%s, sSubPrefix);%s'%(unionEncodeStart,
					unionTab, fi.name, attrName, unionEncodeEnd);
				# ToXml
				self.toXmls += '%s\n    %sMField::toXml(baBuf, "%s", m_%s, sSubPrefix);%s'%(unionEncodeStart,
					unionTab, fi.name, attrName, unionEncodeEnd);
				# Decode
				self.decodeSubField += '\n    case %s:\n        return MField::decode(m_%s, %s, szBuf, iBufLen);'%(fi.tag, attrName, fi.count);
				# Handler
				self.getHdrByName += '%s\n        return this;\n    }'%(ifPrefix);
				self.setValueByName += '%s\n        m_pst%s->set%s(szValue);'%(setValuePrefix, className, getAttrName(fi.name));
			else:
				attrName = '%s%s'%(getNamePrefix(fi.type), getAttrName(fi.name));
				attrDef = '%s%s m_%s;'%(unionTab, getStructName(fi.type), attrName);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n    %s%s */'%(attrDef, fi.desc);
				if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
					unionSel = '\n        m_pst%s->setSelector(%s);'%(className, fi.tag);
				else:
					unionSel = '';
				# get and set
				if (config.M_C_TYPE_MAP.has_key(fi.type)):
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    %s get%s() {return m_%s;}\n'%(fi.desc,
						getStructName(fi.type), getAttrName(fi.name), attrName);
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    void set%s(%s %s) {m_%s = %s;}\n'%(fi.desc,
						getAttrName(fi.name), getStructName(fi.type), attrName, attrName, attrName);
					# Encode
					self.fieldEncode += '%s\n    %sMField::encode(m_%s, baBuf, %s);%s'%(unionEncodeStart,
						unionTab, attrName, fi.tag, unionEncodeEnd);
					# Format
					self.formats += '%s\n    %sMField::format(baBuf, "%s", m_%s, sSubPrefix);%s'%(unionEncodeStart,
						unionTab, fi.name, attrName, unionEncodeEnd);
					# ToXml
					self.toXmls += '%s\n    %sMField::toXml(baBuf, "%s", m_%s, sSubPrefix);%s'%(unionEncodeStart,
						unionTab, fi.name, attrName, unionEncodeEnd);
					# Decode
					self.decodeSubField += '\n    case %s:\n        return MField::decode(&m_%s, szBuf, iBufLen);'%(fi.tag, attrName);
					# Handler
					self.getHdrByName += '%s%s\n        return this;\n    }'%(ifPrefix, unionSel);
					if (config.M_C_VALUE_MAP.has_key(fi.type)):
						self.setValueByName += '%s\n        m_pst%s->set%s(%s(szValue));'%(setValuePrefix, className,
							getAttrName(fi.name), config.M_C_VALUE_MAP[fi.type]);
				else:
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    %s& get%s() {return m_%s;}\n'%(fi.desc,
						getStructName(fi.type), getAttrName(fi.name), attrName);
					# Encode
					self.fieldEncode += '%s\n    %sm_st%s.encode(baBuf, %s);%s'%(unionEncodeStart,
						unionTab, getAttrName(fi.name), fi.tag, unionEncodeEnd);
					# Format
					self.formats += '%s\n    %sm_%s.format(baBuf, "%s", sSubPrefix);%s'%(unionEncodeStart,
						unionTab, attrName, fi.name, unionEncodeEnd);
					# ToXml
					self.toXmls += '%s\n    %sm_%s.toXml(baBuf, "%s", sSubPrefix);%s'%(unionEncodeStart,
						unionTab, attrName, fi.name, unionEncodeEnd);
					# decode
					self.decodeSubField += '\n    case %s:\n        return m_st%s.decode(szBuf, iBufLen);'%(fi.tag, getAttrName(fi.name));
					self.getSubField += '\n    case %s:\n        return &m_st%s;'%(fi.tag, getAttrName(fi.name));
					self.getFieldByName += '\n    if (sName == "%s") return &m_st%s;'%(fi.name, getAttrName(fi.name));
					# for handler
					self.hdrAttrDefine += '\n    %sHandler m_st%sHdr;'%(getStructName(fi.type), getAttrName(fi.name));
					self.getHdrByName += '%s%s\n        m_st%sHdr.set%s(&m_pst%s->get%s());\n        return &m_st%sHdr;\n    }'%(ifPrefix, unionSel,
						getAttrName(fi.name), getClassName(fi.type), className, getAttrName(fi.name), getAttrName(fi.name));
					self.constructorFunc += '\n    m_st%sHdr.setParentHandler(this);'%(getAttrName(fi.name));
				if (config.M_C_TYPE_MAP.has_key(fi.type) == False and fi.type not in self.inclClass):
					self.inclClass.append(fi.type);
				pass;

		if (self.setValueByName != ''):
			self.setValueByName += '\n    }';

		# 处理union
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			self.getSubFieldSelector = '\n    m_nSelector = nTag;'
			self.decodeSubFieldSeletor = '\n\n    m_nSelector = nTag;';
			self.attributes = '\n    U16 m_nSelector;\n    union\n    {%s\n    };'%(self.attributes);
			self.fieldEncode = '\n    switch (m_nSelector)\n    {%s\n    default:\n        break;\n    }'%(self.fieldEncode);
			self.formats = '\n    switch (m_nSelector)\n    {%s\n    default:\n        break;\n    }'%(self.formats);
			self.toXmls = '\n    switch (m_nSelector)\n    {%s\n    default:\n        break;\n    }'%(self.toXmls);
			self.attrGetSetDefine = u'\n    /**\n     * 设置Union字段标识\n     */\n    void setSelector(U16 nSelector) {m_nSelector = nSelector;}\n%s'%(self.attrGetSetDefine);

		# 处理includes
		for incl in self.inclClass:
			self.includes += '#include "%s.h"\n'%(getAttrName(incl));
			self.hdrIncludes += '#include "%sHandler.h"\n'%(getAttrName(incl));
		if (self.includes == ''):
			self.includes += '#include "field/MField.h"\n#include "%s.h"\n'%(self.macroFile);
			self.hdrIncludes += '#include "field/MFieldHandler.h"\n';

	#
	# 生成头文件
	#
	def generateHeaderFile(self, outDir):
		className = getClassName(self.structInfo.name);
		classMacro = getClassMacro(self.structInfo.name);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.h'%(outDir, className), 'w');

		templ = Template(cpptemplate.HTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, AttrGetSetDefine=self.attrGetSetDefine,
			ClassMacro=classMacro, ClassDesc=self.structInfo.desc, AttrDefine=self.attributes, Includes=self.includes).encode('utf-8'));
		destFile.close();
		# 生成handler
		self.generateHandlerHeaderFile(outDir);

	#
	# 生成实现文件
	#
	def generateAppFile(self, outDir, marcroFile):
		className = getClassName(self.structInfo.name);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.cpp'%(outDir, className), 'w');

		templ = Template(cpptemplate.CPPTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, FieldDesc=self.structInfo.name, GetSubFieldSelector=self.getSubFieldSelector,
			FieldEncode=self.fieldEncode, Formats=self.formats, ToXmls=self.toXmls, GetSubField=self.getSubField,
			GetFieldByName=self.getFieldByName, FieldName=self.structInfo.name, DecodeSubFieldSeletor=self.decodeSubFieldSeletor,
			DecodeSubField=self.decodeSubField).encode('utf-8'));
		destFile.close();
		# 生成handler
		self.generateHandlerAppFile(outDir, marcroFile);

	#
	# 生成handler的头文件
	#
	def generateHandlerHeaderFile(self, outDir):
		className = getClassName(self.structInfo.name);
		classMacro = getClassMacro(self.structInfo.name);
		outDir = '%s/handler'%(outDir);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%sHandler.h'%(outDir, className), 'w');

		templ = Template(cpptemplate.HDR_HTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, ClassMacro=classMacro, ClassDesc=self.structInfo.desc,
			HdrIncludes=self.hdrIncludes, HdrAttrDefine=self.hdrAttrDefine).encode('utf-8'));
		destFile.close();

	#
	# 生成handler的实现文件
	#
	def generateHandlerAppFile(self, outDir, marcroFile):
		className = getClassName(self.structInfo.name);
		outDir = '%s/handler'%(outDir);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%sHandler.cpp'%(outDir, className), 'w');

		templ = Template(cpptemplate.HDR_CPPTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, SetValueByName=self.setValueByName,
			GetHdrByName=self.getHdrByName, ConstructorFunc=self.constructorFunc).encode('utf-8'));
		destFile.close();

#
# generate enum define
#
def generateEnumDefine(si):
	enumDef = '\n/**\n * %s\n */\nenum tag%s\n{\n'%(si.desc, si.name);

	for fi in si.fields:
		attrDef = '\t%s = %s,'%(fi.name, fi.value);
		attrDef = '{0:{width}}'.format(attrDef, width=64);
		enumDef += '%s/* %s */\n'%(attrDef, fi.desc);

	return '%s};\n'%enumDef;

#
# generate macro file
#
def generateMacroFile(outdir, fileName, enums, macros):
	try:
		os.makedirs(outdir);
	except:
		pass;
	destFile = open('%s/%s.h'%(outdir, fileName), 'w');
	destFile.write('/*\n * @(#) %s.h Created by @itfriday message creator\n */\n'%fileName);
	destFile.write('\n#ifndef %s_H\n#define %s_H\n\n'%(getClassMacro(fileName), getClassMacro(fileName)));

	macroString = '';
	for fi in macros:
		attrDef = '#define %s'%(fi.name);
		attrDef = '{0:{width}}'.format(attrDef, width=64);
		macroString += '%s%s\t\t/* %s */\n'%(attrDef, fi.value, fi.desc);

	destFile.write(macroString.encode('utf-8'));

	for si in enums:
		destFile.write(generateEnumDefine(si).encode('utf-8'));

	destFile.write('\n#endif\n');

	destFile.close();
