#!/usr/bin/python
# -*- coding: utf-8 -*-

from MsgGenerator import *;

from string import Template;
import os;

import config;
import ctemplate;

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
		return ftype.upper();

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstUpper(name);

#
# 取编码解码函数名称
#
def getCodecName(ftype):
	if (config.M_C_CODEC_MAP.has_key(ftype)):
		return config.M_C_CODEC_MAP[ftype];
	else:
		return getClassMacro(ftype).lower();

#
# 取编码解码函数名称
#
def getFieldType(ftype):
	if (config.M_C_FIELD_TYPE_MAP.has_key(ftype)):
		return config.M_C_FIELD_TYPE_MAP[ftype];
	else:
		return 'FIELD_TYPE_TLV';

#
# 取类型属性定义长度
#
def getStructAttrDefLen(fi):
	maxWidth = 0;
	if (fi.type == 'array'):
		attrDef = '%s %s%s[%s];'%(getNamePrefix(fi.type), getStructName(fi.subtype), getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	elif (fi.type == 'string'):
		attrDef = 'char %s%s[%s];'%(getNamePrefix(fi.type), getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	elif (config.M_C_TYPE_MAP.has_key(fi.type)):
		attrDef = '%s %s%s;'%(getStructName(fi.type), getNamePrefix(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	else:
		attrDef = '%s %s%s;'%(getStructName(fi.type), getNamePrefix(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	return maxWidth;

class CMsgGenerator(MsgGenerator):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile=''):
		MsgGenerator.__init__(self, structInfo, macroFile);
		self.attributes = '';
		self.includes = '';
		self.inclClass = [];
		self.unionTagDecode = '';
		self.subFieldDecode = '';
		self.fieldEncode = '';
		self.formats = '';
		self.toXmls = '';
		self.setValueByName = '';
		self.buildFieldByName = '';
		self.getFieldByName = '';
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
			unionEncodeEnd = '';
			unionGetValue = '';

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionTab = '\t';
				self.fieldEncode += '\n\tcase %s:'%(fi.tag);
				self.formats += '\n\tcase %s:'%(fi.tag);
				self.toXmls += '\n\tcase %s:'%(fi.tag);
				unionEncodeEnd = '\n\t\tbreak;';
				unionGetValue = 'pst%s->nSelector = %s;\n\t\t'%(className, fi.tag);

			ifPrefix = '\n\n\tif (!strncmp(szSubFieldName, "%s", sizeof("%s")))\n\t{'%(fi.name, fi.name);
			elifPrefix = '\n\t}\n\telse if (!strncmp(szSubFieldName, "%s", sizeof("%s")))\n\t{'%(fi.name, fi.name);
			if (self.setValueByName != ''):
				setValuePrefix = elifPrefix;
			else:
				setValuePrefix = ifPrefix;

			if (self.getFieldByName != ''):
				getFieldPrefix = elifPrefix;
			else:
				getFieldPrefix = ifPrefix;

			if (self.buildFieldByName != ''):
				buildFieldPrefix = elifPrefix;
			else:
				buildFieldPrefix = ifPrefix;

			# 处理属性列表
			if (fi.type == 'array'):
				attrDef = '%s%s %s%s[%s];'%(unionTab, getStructName(fi.subtype), getNamePrefix(fi.type), getAttrName(fi.name), fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s */'%(attrDef, fi.desc);
				if (config.M_C_TYPE_MAP.has_key(fi.subtype) == False and fi.subtype not in self.inclClass):
					self.inclClass.append(fi.subtype);
				# 处理decode
				self.subFieldDecode += '\n\tcase %s:\n\t\treturn %s_field_decode(pst%s->%s%s, sizeof(%s), %s, szBuf, iBufLen, %s_field_decode);'%(fi.tag, getCodecName(fi.type),
					className, getNamePrefix(fi.type), getAttrName(fi.name), getStructName(fi.subtype), fi.count, getCodecName(fi.subtype));
				# 处理encode
				arrRefer = self.structInfo.getFieldByName(fi.refer);
				if (fi.refer == '' or fi.refer == None or arrRefer == None):
					raise Exception("Please give number refer for struct(%s), array field(%s)"%(self.structInfo.name, fi.name));
				self.fieldEncode += '\n\t%sCHECK_FUNC_RET(%s_field_encode(pst%s->%s%s, sizeof(%s), pst%s->%s%s, %s, pstByteArray, %s_field_encode), iRet);%s'%(unionTab, getCodecName(fi.type), className, getNamePrefix(fi.type),
					getAttrName(fi.name), getStructName(fi.subtype), className, getNamePrefix(arrRefer.type), getAttrName(arrRefer.name), fi.tag, getCodecName(fi.subtype), unionEncodeEnd);
				# 处理format
				self.formats += '\n\t%sCHECK_FUNC_RET(%s_field_format("%s", pst%s->%s%s, sizeof(%s), pst%s->%s%s, pstByteArray, szSubPrefix, %s_field_format), iRet);%s'%(unionTab, getCodecName(fi.type),
					fi.name, className, getNamePrefix(fi.type), getAttrName(fi.name), getStructName(fi.subtype), className, getNamePrefix(arrRefer.type), getAttrName(arrRefer.name), getCodecName(fi.subtype),
					unionEncodeEnd);
				# 处理toXml
				self.toXmls += '\n\t%sCHECK_FUNC_RET(%s_field_to_xml("%s", pst%s->%s%s, sizeof(%s), pst%s->%s%s, pstByteArray, szSubPrefix, %s_field_to_xml), iRet);%s'%(unionTab, getCodecName(fi.type),
					fi.name, className, getNamePrefix(fi.type), getAttrName(fi.name), getStructName(fi.subtype), className, getNamePrefix(arrRefer.type), getAttrName(arrRefer.name), getCodecName(fi.subtype),
					unionEncodeEnd);
				# 处理setfieldvalue
				if (config.M_C_VALUE_MAP.has_key(fi.subtype)):
					self.setValueByName += '%s\n\t\tif (nIdx < %s) pst%s->%s%s[nIdx] = %s(szValue);'%(setValuePrefix, fi.count, className, getNamePrefix(fi.type), getAttrName(fi.name), config.M_C_VALUE_MAP[fi.subtype]);
					self.buildFieldByName += '%s\n\t\tpstSubFieldInfo->bFieldType = FIELD_TYPE_ARRAY;\n\t\tpstSubFieldInfo->getSubFieldByName = NULL;\n\t\tpstSubFieldInfo->setSubFieldValueByName = NULL;\n\t\tpstSubFieldInfo->buildSubFieldInfoByName = NULL;\n\t\tSTRNCPY(pstSubFieldInfo->szFieldName, sizeof(pstSubFieldInfo->szFieldName),\n\t\t\t"%s", sizeof(pstSubFieldInfo->szFieldName));'%(
						buildFieldPrefix, fi.name);
				else:
					self.buildFieldByName += '%s\n\t\tpstSubFieldInfo->bFieldType = FIELD_TYPE_ARRAY;\n\t\tpstSubFieldInfo->getSubFieldByName = %s_get_sub_field_by_name;\n\t\tpstSubFieldInfo->setSubFieldValueByName = %s_set_sub_field_value_by_name;\n\t\tpstSubFieldInfo->buildSubFieldInfoByName = %s_build_sub_field_info_by_name;\n\t\tSTRNCPY(pstSubFieldInfo->szFieldName, sizeof(pstSubFieldInfo->szFieldName),\n\t\t\t"%s", sizeof(pstSubFieldInfo->szFieldName));'%(
						buildFieldPrefix, getCodecName(fi.subtype), getCodecName(fi.subtype), getCodecName(fi.subtype), fi.name);
				self.getFieldByName += '%s\n\t\t%sif (nIdx < %s) return &pst%s->%s%s[nIdx];'%(getFieldPrefix, unionGetValue, fi.count, className, getNamePrefix(fi.type), getAttrName(fi.name));
				pass;
			elif (fi.type == 'string'):
				attrDef = '%schar %s%s[%s];'%(unionTab, getNamePrefix(fi.type), getAttrName(fi.name), fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s */'%(attrDef, fi.desc);
				# 处理decode
				self.subFieldDecode += '\n\tcase %s:\n\t\treturn %s_field_decode(pst%s->%s%s, %s, szBuf, iBufLen);'%(fi.tag, getCodecName(fi.type), className, getNamePrefix(fi.type), getAttrName(fi.name), fi.count);
				# 处理encode
				self.fieldEncode += '\n\t%sCHECK_FUNC_RET(%s_field_encode(pst%s->%s%s, %s, pstByteArray), iRet);%s'%(unionTab, getCodecName(fi.type), className, getNamePrefix(fi.type),
					getAttrName(fi.name), fi.tag, unionEncodeEnd);
				# 处理format
				self.formats += '\n\t%sCHECK_FUNC_RET(%s_field_format("%s", pst%s->%s%s, pstByteArray, szSubPrefix), iRet);%s'%(unionTab, getCodecName(fi.type), fi.name, className, getNamePrefix(fi.type),
					getAttrName(fi.name), unionEncodeEnd);
				# 处理toXml
				self.toXmls += '\n\t%sCHECK_FUNC_RET(%s_field_to_xml("%s", pst%s->%s%s, pstByteArray, szSubPrefix), iRet);%s'%(unionTab, getCodecName(fi.type), fi.name, className, getNamePrefix(fi.type),
					getAttrName(fi.name), unionEncodeEnd);
				# 处理setfieldvalue
				attrName = 'pst%s->%s%s'%(className, getNamePrefix(fi.type), getAttrName(fi.name));
				self.setValueByName += '%s\n\t\tSTRNCPY(%s, sizeof(%s), szValue, sizeof(%s));'%(setValuePrefix, attrName, attrName, attrName);
				self.buildFieldByName += '%s\n\t\tpstSubFieldInfo->bFieldType = FIELD_TYPE_STRING;\n\t\tpstSubFieldInfo->getSubFieldByName = NULL;\n\t\tpstSubFieldInfo->setSubFieldValueByName = NULL;\n\t\tpstSubFieldInfo->buildSubFieldInfoByName = NULL;\n\t\tSTRNCPY(pstSubFieldInfo->szFieldName, sizeof(pstSubFieldInfo->szFieldName),\n\t\t\t"%s", sizeof(pstSubFieldInfo->szFieldName));'%(
					buildFieldPrefix, fi.name);
				self.getFieldByName += '%s\n\t\t%sreturn %s;'%(getFieldPrefix, unionGetValue, attrName);
				pass;
			else:
				attrDef = '%s%s %s%s;'%(unionTab, getStructName(fi.type), getNamePrefix(fi.type), getAttrName(fi.name));
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s */'%(attrDef, fi.desc);
				if (config.M_C_TYPE_MAP.has_key(fi.type) == False and fi.type not in self.inclClass):
					self.inclClass.append(fi.type);
				# 处理decode
				self.subFieldDecode += '\n\tcase %s:\n\t\treturn %s_field_decode(&pst%s->%s%s, szBuf, iBufLen);'%(fi.tag, getCodecName(fi.type), className, getNamePrefix(fi.type), getAttrName(fi.name));
				# 处理encode
				self.fieldEncode += '\n\t%sCHECK_FUNC_RET(%s_field_encode(&pst%s->%s%s, %s, pstByteArray), iRet);%s'%(unionTab, getCodecName(fi.type), className, getNamePrefix(fi.type),
					getAttrName(fi.name), fi.tag, unionEncodeEnd);
				# 处理format
				self.formats += '\n\t%sCHECK_FUNC_RET(%s_field_format("%s", &pst%s->%s%s, pstByteArray, szSubPrefix), iRet);%s'%(unionTab, getCodecName(fi.type), fi.name, className, getNamePrefix(fi.type),
					getAttrName(fi.name), unionEncodeEnd);
				# 处理toXml
				self.toXmls += '\n\t%sCHECK_FUNC_RET(%s_field_to_xml("%s", &pst%s->%s%s, pstByteArray, szSubPrefix), iRet);%s'%(unionTab, getCodecName(fi.type), fi.name, className, getNamePrefix(fi.type),
					getAttrName(fi.name), unionEncodeEnd);
				# 处理setfieldvalue
				if (config.M_C_VALUE_MAP.has_key(fi.type)):
					self.setValueByName += '%s\n\t\tpst%s->%s%s = %s(szValue);'%(setValuePrefix, className, getNamePrefix(fi.type), getAttrName(fi.name), config.M_C_VALUE_MAP[fi.type]);
					self.buildFieldByName += '%s\n\t\tpstSubFieldInfo->bFieldType = %s;\n\t\tpstSubFieldInfo->getSubFieldByName = NULL;\n\t\tpstSubFieldInfo->setSubFieldValueByName = NULL;\n\t\tpstSubFieldInfo->buildSubFieldInfoByName = NULL;\n\t\tSTRNCPY(pstSubFieldInfo->szFieldName, sizeof(pstSubFieldInfo->szFieldName),\n\t\t\t"%s", sizeof(pstSubFieldInfo->szFieldName));'%(
						buildFieldPrefix, getFieldType(fi.type), fi.name);
				else:
					self.buildFieldByName += '%s\n\t\tpstSubFieldInfo->bFieldType = FIELD_TYPE_TLV;\n\t\tpstSubFieldInfo->getSubFieldByName = %s_get_sub_field_by_name;\n\t\tpstSubFieldInfo->setSubFieldValueByName = %s_set_sub_field_value_by_name;\n\t\tpstSubFieldInfo->buildSubFieldInfoByName = %s_build_sub_field_info_by_name;\n\t\tSTRNCPY(pstSubFieldInfo->szFieldName, sizeof(pstSubFieldInfo->szFieldName),\n\t\t\t"%s", sizeof(pstSubFieldInfo->szFieldName));'%(
						buildFieldPrefix, getCodecName(fi.type), getCodecName(fi.type), getCodecName(fi.type), fi.name);
				self.getFieldByName += '%s\n\t\t%sreturn &pst%s->%s%s;'%(getFieldPrefix, unionGetValue, className, getNamePrefix(fi.type), getAttrName(fi.name));
				pass;

		if (self.setValueByName != ''):
			self.setValueByName += '\n\t}';

		if (self.getFieldByName != ''):
			self.getFieldByName += '\n\t}';

		if (self.buildFieldByName != ''):
			self.buildFieldByName += '\n\t}';

		# 处理union
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			self.attributes = '\n\tU16 nSelector;\n\tunion\n\t{%s\n\t};'%(self.attributes);
			self.unionTagDecode = '\n\tpst%s->nSelector = nTag;\n'%(className);
			self.fieldEncode = '\n\tswitch (pst%s->nSelector)\n\t{%s\n\tdefault:\n\t\tbreak;\n\t}'%(className, self.fieldEncode);
			self.formats = '\n\tswitch (pst%s->nSelector)\n\t{%s\n\tdefault:\n\t\tbreak;\n\t}'%(className, self.formats);
			self.toXmls = '\n\tswitch (pst%s->nSelector)\n\t{%s\n\tdefault:\n\t\tbreak;\n\t}'%(className, self.toXmls);

		# 处理includes
		for incl in self.inclClass:
			self.includes += '#include "%s.h"\n'%(getAttrName(incl));
		if (self.includes == ''):
			self.includes += '#include "field/Field.h"\n#include "%s.h"\n'%(self.macroFile);

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

		templ = Template(ctemplate.HTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, LClassName=classMacro.lower(), UClassName=className.upper(), FieldDesc=self.structInfo.name,
			ClassMacro=classMacro, ClassDesc=self.structInfo.desc, AttrDefine=self.attributes, Includes=self.includes).encode('utf-8'));
		destFile.close();

	#
	# 生成实现文件
	#
	def generateAppFile(self, outDir, marcroFile):
		className = getClassName(self.structInfo.name);
		classMacro = getClassMacro(self.structInfo.name);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.c'%(outDir, className), 'w');

		templ = Template(ctemplate.CTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, LClassName=classMacro.lower(), UClassName=className.upper(), FieldDesc=self.structInfo.name,
			UnionTagDecode=self.unionTagDecode, SubFieldDecode=self.subFieldDecode, FieldEncode=self.fieldEncode, Formats=self.formats, ToXmls=self.toXmls,
			SetValueByName=self.setValueByName, BuildFieldByName=self.buildFieldByName, GetFieldByName=self.getFieldByName, FieldName=self.structInfo.name).encode('utf-8'));
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
