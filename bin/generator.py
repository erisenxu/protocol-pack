#!/usr/bin/python
# -*- coding: utf-8 -*-

from xml.sax import make_parser;
from xml.sax.handler import ContentHandler;
from string import Template;
import os;

import config;
import htemplate;
import ctemplate;

#
# 结构体类型
#
STRUCT_INFO_TYPE_STRUCT = 0;	# Struct类型
STRUCT_INFO_TYPE_UNION = 1;		# Union类型
STRUCT_INFO_TYPE_MSG = 2;		# Message类型(Deprecated)

#
# Union转换的类型
#
UNION_GENERATE_TYPE_UNION = 0;	# 将Union转换为Union (仅c、c++支持)
UNION_GENERATE_TYPE_STRUCT = 1;	# 使用Struct实现Union

#
# 首字母大小
#
def firstUpper(name):
	return name[:1].capitalize() + name[1:];

#
# 取头文件宏
#
def getClassMacro(name):
	cm = '';
	for ch in name:
		if (ch.isupper() == True):
			if (cm != ''):
				cm = cm + "_";
		cm = cm + ch;
	cm = cm.upper();
	return cm;

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstUpper(name);

#
# 取默认值
#
def getDefaultValue(type, value):
	if (type == 'uchar' or type == 'char' or
		type == 'ushort' or type == 'short' or
		type == 'uint' or type == 'int' or
		type == 'ulong' or type == 'long'):
		if (value == ''):
			return ', M_DEFAULT(0)';
		return ', M_DEFAULT(%s)'%value;
	if (type == 'string'):
		return ', M_DEFAULT("%s")'%value;
	return '';

#
# 取初始化函数名称
#
def getCppInitFuncName(type):
	if (type == 'uchar' or type == 'char' or
		type == 'ushort' or type == 'short' or
		type == 'uint' or type == 'int' or
		type == 'ulong' or type == 'long' or
		type == 'string'):
		return 'init';
	return 'construct';

#
# 取类型对应的消息名(C++语言)
#
def getClassName(fieldInfo):

	if (fieldInfo.type == 'array'):
		fi = FieldInfo();
		fi.type = fieldInfo.subtype;
		return 'MArrayField<%s, %s>'%(getClassName(fi), fieldInfo.count);
	elif (config.M_CLASS_TYPE_MAP.has_key(fieldInfo.type)):
		return config.M_CLASS_TYPE_MAP[fieldInfo.type];
	else:
		return firstUpper(fieldInfo.type);

#
# 取类型对应的结构名(C语言)
#
def getStructName(ftype):
	if (config.M_C_TYPE_MAP.has_key(ftype)):
		return config.M_C_TYPE_MAP[ftype];
	else:
		return ftype.upper();

#
# 取初始化函数名(C语言)
#
def getInitFuncName(ftype):
	if (config.M_C_INIT_FUNC_MAP.has_key(ftype)):
		return config.M_C_INIT_FUNC_MAP[ftype];
	else:
		return "init_field";

#
# 取构造函数名(C语言)
#
def getStructFuncName(ftype):
	if (config.M_C_CONSTRUCT_FUNC_MAP.has_key(ftype)):
		return config.M_C_CONSTRUCT_FUNC_MAP[ftype];
	else:
		return "init_field_struct";

#
# 取结构信息定义名(C语言)
def getStructFieldInfo(ftype, fname):
	if (config.M_C_FIELD_INFO_MAP.has_key(ftype)):
		return config.M_C_FIELD_INFO_MAP[ftype];
	else:
		return "g_st%sFieldInfo"%fname;

#
# 取类型属性定义长度
#
def getStructAttrDefLen(fi):
	maxWidth = 0;
	if (fi.type == 'array'):
		attrDef = 'U16 n%sNum;'%(getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;

		attrDef = '%s ast%s[%s];'%(getStructName(fi.subtype), getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;

		attrDef = '%s stArr%s;'%(getStructName(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	elif (fi.type == 'string'):
		attrDef = 'char sz%s[%s];'%(getAttrName(fi.name), fi.count);
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;

		attrDef = '%s st%s;'%(getStructName(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	else:
		attrDef = '%s st%s;'%(getStructName(fi.type), getAttrName(fi.name));
		width = len(attrDef);
		if (maxWidth < width):
			maxWidth = width;
	return maxWidth;

#
# 参数信息
#
class Argument(object):

	def __init__(self, unionType=UNION_GENERATE_TYPE_UNION):
		self.unionType = unionType;

#
# 属性字段信息
#
class FieldInfo(object):

	def __init__(self, name='', type='', tag='', version='1', default='', desc='', subtype='', count='1', value=''):
		self.name = name;
		self.type = type;
		self.tag = tag;
		self.version = version;
		self.subtype = subtype;
		self.default = default;
		self.desc = desc;
		self.count = count;
		self.value = value;

#
# 结构体信息
#
class StructInfo(object):

	def __init__(self, name='', id='', version='', desc='', type=0):
		self.name = name;
		self.id = id;
		self.version = version;
		self.desc = desc;
		self.fields = [];
		self.type = type;

	def addField(self, fieldInfo):
		self.fields.append(fieldInfo);

class HeaderGenerator(object):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, language='cpp', argument=Argument()):
		self.structInfo = structInfo;
		self.attributes = '';
		self.attrFunc = '';
		self.encodes = '';
		self.formats = '';
		self.toXmls = '';
		self.inits = '';
		self.getfields = '';
		self.getfieldsBySelection = '';
		self.getfieldsBySelectionFunc = '';
		self.decodeMsgFields = '';
		self.encodeMsgFields = '';
		self.getfieldByNames = '';
		self.releases = '';
		self.includes = '';
		self.fieldNames = [];
		self.language = language;
		self.constructs = '';
		self.argument = argument;
		if (self.language == 'cpp'):
			self.handleStructInfoForCPP();
		elif (self.language == 'c'):
			self.handleStructInfoForC();

	#
	# 更新include域
	#
	def updateIncludeFieldNames(self, fieldInfo):
		if (fieldInfo.type == 'array'):
			fi = FieldInfo();
			fi.type = fieldInfo.subtype;
			self.updateIncludeFieldNames(fi);
		elif (config.M_CLASS_TYPE_MAP.has_key(fieldInfo.type)):
			return;
		else:
			fieldName = firstUpper(fieldInfo.type);
			try:
				self.fieldNames.index(fieldName);
			except ValueError, ve:
				self.fieldNames.append(fieldName);

	#
	# 生成include
	#
	def generateFieldInclude(self):
		for fn in self.fieldNames:
			self.includes += '#include "%s.h"\n'%fn;

	#
	# 处理数据获取信息 (C语言)
	#
	def handleStructInfoForC(self):
		if (self.structInfo == None):
			return;
		maxWidth = 0;
		for fi in self.structInfo.fields:
			width = getStructAttrDefLen(fi);
			if (width > maxWidth):
				maxWidth = width;

		otag = 0;
		for fi in self.structInfo.fields:
			if (fi.tag == '' or fi.tag == None):
				#otag = int(fi.tag);
				raise Exception("Please give tag for struct(%s), field(%s)"%(self.structInfo.name, fi.name));
			#else:
			#	#otag = otag + 1;
			otag = fi.tag;
			className = getStructName(fi.type);

			unionTab = '';
			unionStructStart = '';
			unionStructEnd = '';

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION and self.argument.unionType == UNION_GENERATE_TYPE_UNION):
				unionTab = '\t';

			if (fi.type == 'array'):
				if (self.structInfo.type == STRUCT_INFO_TYPE_UNION and self.argument.unionType == UNION_GENERATE_TYPE_UNION):
					unionTab = '\t\t';
					unionStructStart = '\tstruct\n\t\t{\n\t';
					unionStructEnd = '\n\t\t};';
				attrName = "stArr%s"%getAttrName(fi.name);
				attrDef = '%s%sU16 n%sNum;'%(unionStructStart, unionTab, getAttrName(fi.name));
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\n\t%s%s(Array Number) */'%(attrDef, fi.desc);

				attrDef = '%s%s ast%s[%s];'%(unionTab, getStructName(fi.subtype), getAttrName(fi.name), fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s(Array Number) */'%(attrDef, fi.desc);

				attrDef = '%s%s stArr%s;'%(unionTab, className, getAttrName(fi.name));
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s(Array Struct Info) */%s'%(attrDef, fi.desc, unionStructEnd);

				# init function
				initString = '(&((LP%s)pstField)->stArr%s, &%s, M_NAME("%s"), M_TAG(%s), M_PARENT(pstField), M_VERSION(%s),\n\t\t(char*)((LP%s)pstField)->ast%s, &((LP%s)pstField)->n%sNum, sizeof(((LP%s)pstField)->ast%s[0]), %s);'%(
					self.structInfo.name.upper(), getAttrName(fi.name), getStructFieldInfo(fi.subtype, firstUpper(fi.subtype)),
					fi.name, otag, fi.version, self.structInfo.name.upper(), getAttrName(fi.name),
					self.structInfo.name.upper(), getAttrName(fi.name), self.structInfo.name.upper(), getAttrName(fi.name), fi.count);
				self.inits += '\n\t%s%s'%(getInitFuncName(fi.type), initString);
				self.constructs += '\n\t%s%s'%(getStructFuncName(fi.type), initString);
			elif (fi.type == 'string'):
				if (self.structInfo.type == STRUCT_INFO_TYPE_UNION and self.argument.unionType == UNION_GENERATE_TYPE_UNION):
					unionTab = '\t\t';
					unionStructStart = '\tstruct\n\t\t{\n\t';
					unionStructEnd = '\n\t\t};';
				attrName = "st%s"%getAttrName(fi.name);
				attrDef = '%s%schar sz%s[%s];'%(unionStructStart, unionTab, getAttrName(fi.name), fi.count);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\n\t%s%s */'%(attrDef, fi.desc);

				attrDef = '%s%s st%s;'%(unionTab, className, getAttrName(fi.name));
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s(String Struct Info) */%s'%(attrDef, fi.desc, unionStructEnd);

				# init function
				initString = '(&((LP%s)pstField)->st%s, M_NAME("%s"), M_TAG(%s), M_PARENT(pstField), M_VERSION(%s),\n\t\t(char*)&((LP%s)pstField)->sz%s, %s);'%(
					self.structInfo.name.upper(), getAttrName(fi.name),
					fi.name, otag, fi.version, self.structInfo.name.upper(), getAttrName(fi.name), fi.count);
				self.inits += '\n\t%s%s'%(getInitFuncName(fi.type), initString);
				self.constructs += '\n\t%s%s'%(getStructFuncName(fi.type), initString);
			else:
				attrName = "st%s"%getAttrName(fi.name);
				attrDef = '%s%s %s;'%(unionTab, className, attrName);
				attrDef = '{0:{width}} /* '.format(attrDef, width=maxWidth);
				self.attributes += '\n\t%s%s */'%(attrDef, fi.desc);

				# init function
				if (config.M_C_INIT_FUNC_MAP.has_key(fi.type)):
					initString = '(&((LP%s)pstField)->st%s, M_NAME("%s"), M_TAG(%s), M_PARENT(pstField), M_VERSION(%s)'%(
						self.structInfo.name.upper(), getAttrName(fi.name), fi.name, otag, fi.version);
					self.inits += '\n\t%s%s%s);'%(getInitFuncName(fi.type), initString, getDefaultValue(fi.type, fi.default));
					self.constructs += '\n\t%s%s);'%(getStructFuncName(fi.type), initString);
				else:
					initString = '((LPFIELD)(&((LP%s)pstField)->st%s), &%s, M_NAME("%s"), M_TAG(%s), M_PARENT(pstField), M_VERSION(%s));'%(
						self.structInfo.name.upper(), getAttrName(fi.name), getStructFieldInfo(fi.type, firstUpper(fi.type)), fi.name, otag, fi.version);
					self.inits += '\n\t%s%s'%(getInitFuncName(fi.type), initString);
					self.constructs += '\n\t%s%s'%(getStructFuncName(fi.type), initString);

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionInfo = '\n\tcase %s:\n\t\t'%(otag);
				unionEnd = '\n\t\tbreak;';
			else:
				unionInfo = '\n\t';
				unionEnd = '';
			if (self.structInfo.type == STRUCT_INFO_TYPE_MSG):
				self.encodeMsgFields += '\n\tcase %s:\n\t\tCHECK_FUNC_RET(field_encode(&pstMsgObj->st%s.%s, pstByteArray, pstMsgObj->nMsgVer), iRet);\n\t\tbreak;'%(otag, firstUpper(self.structInfo.name), attrName);
				self.decodeMsgFields += '\n\tcase %s:\n\t\tinit_field(&pstMsgObj->st%s.%s, &%s, "%s", %s, %s);\n\t\treturn field_decode(&pstMsgObj->st%s.%s, pszBuf, iBufLen - iHeadLen);'%(otag, firstUpper(self.structInfo.name), attrName, getStructFieldInfo(fi.type, firstUpper(fi.type)), fi.name, otag, fi.version, firstUpper(self.structInfo.name), attrName);

			self.encodes += '%sCHECK_FUNC_RET(field_encode((char*)&((LP%s)pstField)->%s, pstByteArray, nVer), iRet);%s'%(unionInfo, self.structInfo.name.upper(), attrName, unionEnd);
			self.formats += '%sCHECK_FUNC_RET(field_format((char*)&((LP%s)pstField)->%s, pstByteArray, szSubPrefix, nVer), iRet);%s'%(unionInfo, self.structInfo.name.upper(), attrName, unionEnd);
			self.toXmls += '%sCHECK_FUNC_RET(field_toxml((char*)&((LP%s)pstField)->%s, pstByteArray, szSubPrefix, nVer), iRet);%s'%(unionInfo, self.structInfo.name.upper(), attrName, unionEnd);
			#self.inits += '\n\t%s = new %s(M_TAG(%s), M_NAME("%s"), M_VERSION(%s)%s);'%(attrName, className, otag, fi.name, fi.version, getDefaultValue(fi.type, fi.default));
			self.getfields += '\n\tcase %s:\n\t\treturn (LPFIELD)(&((LP%s)pstField)->%s);'%(otag, self.structInfo.name.upper(), attrName);
			self.getfieldByNames += '\n\tif (0 == strncmp(szName, "%s", sizeof("%s"))) return (LPFIELD)(&((LP%s)pstField)->%s);'%(fi.name, fi.name, self.structInfo.name.upper(), attrName);
			self.updateIncludeFieldNames(fi);
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			classMacroName = getClassMacro(self.structInfo.name).lower();
			unionInfo = '\n\tswitch (((LP%s)pstField)->stSelection.nValue)\n\t{'%(self.structInfo.name.upper());
			if (self.argument.unionType == UNION_GENERATE_TYPE_UNION):
				unionStart = '\n\tunion\n\t{';
				unionEnd = '\n\t};';
			else:
				unionStart = '';
				unionEnd = '';
			self.encodes = '\n\tCHECK_FUNC_RET(field_encode((char*)&((LP%s)pstField)->stSelection, pstByteArray, nVer), iRet);%s%s\n\t}'%(self.structInfo.name.upper(), unionInfo, self.encodes);
			self.formats = '\n\tCHECK_FUNC_RET(field_format((char*)&((LP%s)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);%s%s\n\t}'%(self.structInfo.name.upper(), unionInfo, self.formats);
			self.toXmls = '\n\tCHECK_FUNC_RET(field_toxml((char*)&((LP%s)pstField)->stSelection, pstByteArray, szSubPrefix, nVer), iRet);%s%s\n\t}'%(self.structInfo.name.upper(), unionInfo, self.toXmls);
			self.constructs = '\n\tconstruct_short_field(&((LP%s)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1));%s'%(self.structInfo.name.upper(), self.constructs);
			self.inits = '\n\tinit_short_field(&((LP%s)pstField)->stSelection, M_NAME("Selection"), M_TAG(0xFFFF), M_PARENT(pstField), M_VERSION(1), M_DEFAULT(0));%s'%(self.structInfo.name.upper(), self.inits);
			self.getfieldByNames = '\n\tif (0 == strncmp(szName, "Selection", sizeof("Selection"))) return (LPFIELD)(&((LP%s)pstField)->stSelection);%s'%(self.structInfo.name.upper(), self.getfieldByNames);
			self.attributes = '\n\tSHORTFIELD stSelection;    /* Just added for simulate union selection */%s%s%s'%(unionStart, self.attributes, unionEnd);
			self.getfieldsBySelection = '\nstatic LPFIELD %s_get_sub_field_by_selection(LPFIELD pstField);\n'%(classMacroName);
			self.getfieldsBySelectionFunc = '\nLPFIELD %s_get_sub_field_by_selection(LPFIELD pstField)\n{\n\tif (NULL == pstField) return NULL;\n%s%s\n\t}\n\treturn NULL;\n}\n'%(classMacroName, unionInfo, self.getfields);
			self.getfields = '\n\tcase 0xFFFF:\n\t\treturn (LPFIELD)(&((LP%s)pstField)->stSelection);\n\tdefault:\n\t\treturn %s_get_sub_field_by_selection(pstField);'%(self.structInfo.name.upper(), classMacroName);
		else:
			self.getfields += '\n\tdefault:\n\t\treturn NULL;';
		self.generateFieldInclude();

	#
	# 处理数据获取信息 (C++语言)
	#
	def handleStructInfoForCPP(self):
		if (self.structInfo == None):
			return;
		maxWidth = 0;
		for fi in self.structInfo.fields:
			className = getClassName(fi);
			attrName = "st%s"%getAttrName(fi.name);
			attrDef = '%s* %s;'%(className, attrName);
			width = len(attrDef);
			if (width > maxWidth):
				maxWidth = width;

		otag = 0;
		for fi in self.structInfo.fields:
			if (fi.tag == '' or fi.tag == None):
				#otag = int(fi.tag);
				raise Exception("Please give tag for struct(%s), field(%s)"%(self.structInfo.name, fi.name));
			#else:
			#	otag = otag + 1;
			otag = fi.tag;
			className = getClassName(fi);
			attrName = "m_st%s"%getAttrName(fi.name);
			attrDef = '%s %s;'%(className, attrName);

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionInfo = '\n\tcase %s:\n\t\t'%(otag);
				unionEnd = '\n\t\tbreak;';
				attrDef = '\t%s'%(attrDef);
			else:
				unionInfo = '\n\t';
				unionEnd = '';

			attrDef = '{0:{width}} // '.format(attrDef, width=maxWidth);

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				self.inits = '%s.construct(M_TAG(%s), M_NAME("%s"), M_PARENT(this), M_VERSION(%s));'%(attrName, otag, fi.name, fi.version);
				self.getfieldByNames += '\n\tif (sName == "%s")\n\t{\n\t\t%s\n\t\treturn &%s;\n\t}'%(fi.name, self.inits, attrName);
				unionInfo = '%s%s\n\t\t'%(unionInfo, self.inits);
				getFieldInfo = '%s.%s(M_TAG(%s), M_NAME("%s"), M_PARENT(this), M_VERSION(%s)%s);\n\t\t'%(attrName, getCppInitFuncName(fi.type), otag, fi.name, fi.version, getDefaultValue(fi.type, fi.default));
				if ('construct' != getCppInitFuncName(fi.type)):
					getFieldInfo = 'if (M_GET_SUB_FIELD_MODE_DECODE == chMode)\n\t\t{\n\t\t\t%s}\n\t\telse\n\t\t{\n\t\t\t%s\n\t\t}\n\t\t'%(getFieldInfo, self.inits);
			else:
				self.inits += '\n\t%s.%s(M_TAG(%s), M_NAME("%s"), M_PARENT(this), M_VERSION(%s)%s);'%(attrName, getCppInitFuncName(fi.type), otag, fi.name, fi.version, getDefaultValue(fi.type, fi.default));
				getFieldInfo = '';
				self.getfieldByNames += '\n\tif (sName == "%s") return &%s;'%(fi.name, attrName);
			self.attributes += '\t%s%s\n'%(attrDef, fi.desc);
			self.attrFunc += '\n\t/**\n\t * Get Function: %s\n\t */\n\t%s* get%s() {return &%s;}\n'%(fi.desc, className, firstUpper(fi.name), attrName);
			self.encodes += '%s%s.encode(baBuf, nVer);%s'%(unionInfo, attrName, unionEnd);
			self.formats += '%s%s.format(baBuf, sSubPrefix, nVer);%s'%(unionInfo, attrName, unionEnd);
			self.toXmls += '%s%s.toXml(baBuf, sSubPrefix, nVer);%s'%(unionInfo, attrName, unionEnd);
			#self.releases += '\n\tdelete %s;'%(attrName);
			self.getfields += '\n\tcase %s:\n\t\t%sreturn &%s;'%(otag, getFieldInfo, attrName);
			self.updateIncludeFieldNames(fi);

		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			classMacroName = getClassMacro(self.structInfo.name).lower();
			unionInfo = '\n\tswitch (m_stSelection.getValue())\n\t{';
			self.encodes = '\n\tm_stSelection.encode(baBuf, nVer);%s%s\n\t}'%(unionInfo, self.encodes);
			self.formats = '\n\tm_stSelection.format(baBuf, sSubPrefix, nVer);%s%s\n\t}'%(unionInfo, self.formats);
			self.toXmls = '\n\tm_stSelection.toXml(baBuf, sSubPrefix, nVer);%s%s\n\t}'%(unionInfo, self.toXmls);
			self.inits = '\n\tm_stSelection.init(M_TAG(3), M_NAME("Gold"), M_PARENT(this), M_VERSION(1), M_DEFAULT(0));'#%(self.inits);
			self.getfieldByNames = '\n\tif (sName == "Selection") return &m_stSelection;%s'%(self.getfieldByNames);
			self.attributes = '\tMShortField m_stSelection;    // Just added for simulate union selection\n\tunion\n\t{\n%s\t};'%(self.attributes);
			#self.releases = '\n\tdelete m_stSelection;%s'%(self.releases);
			self.getfields = '\n\tif (0xFFFF == nTag) return &m_stSelection;\n\n\tswitch (m_stSelection.getValue())\n\t{%s\n\tdefault:\n\t\treturn NULL;\n\t}'%(self.getfields);
			self.attrFunc = '\n\t/**\n\t * Get Function: Selection\n\t */\n\tMShortField* getSelection() {return &m_stSelection;}\n%s'%(self.attrFunc);
			self.getFieldMode = 'chMode';
		else:
			self.getfields = '\n\tswitch (nTag)\n\t{%s\n\tdefault:\n\t\treturn NULL;\n\t}'%(self.getfields);
			self.getFieldMode = '/*chMode*/';

		self.generateFieldInclude();

	#
	# 生成头文件
	#
	def generateHeaderFile(self, outdir, macroFile=''):
		try:
			os.makedirs(outdir);
		except:
			pass;
		destFile = open('%s/%s.h'%(outdir, firstUpper(self.structInfo.name)), 'w');
		if (macroFile != ''):
			macroInclude = '\n#include "%s.h"'%macroFile
		else:
			macroInclude = '';

		if (self.language == 'cpp'):
			templ = Template(htemplate.CPPHTEMPLATE.decode('utf-8'));
			destFile.write(templ.safe_substitute(ClassName=firstUpper(self.structInfo.name), MacroInclude=macroInclude,
				ClassDesc=self.structInfo.desc, ClassMacro=getClassMacro(self.structInfo.name),
				AttrDefine=self.attributes, FuncDefine=self.attrFunc, Includes=self.includes).encode('utf-8'));
		elif (self.language == 'c'):
			if (self.structInfo.type == STRUCT_INFO_TYPE_MSG):
				templ = Template(htemplate.CMSGHTEMPLATE.decode('utf-8'));
			else:
				templ = Template(htemplate.CHTEMPLATE.decode('utf-8'));
			destFile.write(templ.safe_substitute(ClassName=firstUpper(self.structInfo.name), MacroInclude=macroInclude,
				ClassDesc=self.structInfo.desc, ClassMacro=getClassMacro(self.structInfo.name),LowerClassMarco=getClassMacro(self.structInfo.name).lower(),
				AttrDefine=self.attributes, UpperClassName=self.structInfo.name.upper(), Includes=self.includes).encode('utf-8'));
		destFile.close();

	#
	# 生成cpp文件
	#
	def generateCppFile(self, outdir):
		try:
			os.makedirs(outdir);
		except:
			pass;
		destFile = open('%s/%s.%s'%(outdir, firstUpper(self.structInfo.name), self.language), 'w');

		if (self.language == 'cpp'):
			templ = Template(ctemplate.CPPTEMPLATE.decode('utf-8'));
			destFile.write(templ.safe_substitute(ClassName=firstUpper(self.structInfo.name), GetFieldMode=self.getFieldMode,
				Init=self.inits, Release=self.releases, Encodes = self.encodes, Formats=self.formats, ToXmls=self.toXmls,
				GetSubFields=self.getfields, GetSubFieldByNames=self.getfieldByNames).encode('utf-8'));
		elif (self.language == 'c'):
			if (self.structInfo.type == STRUCT_INFO_TYPE_MSG):
				templ = Template(ctemplate.CMSGTEMPLATE.decode('utf-8'));
			else:
				templ = Template(ctemplate.CTEMPLATE.decode('utf-8'));
			destFile.write(templ.safe_substitute(ClassName=firstUpper(self.structInfo.name),UpperClassName=self.structInfo.name.upper(),
				Init=self.inits, Constructs=self.constructs, Encodes=self.encodes, Formats=self.formats, ToXmls=self.toXmls, DecodeMsgFields=self.decodeMsgFields,
				GetSubFieldBySelection=self.getfieldsBySelection, GetSubFieldBySelectionFunc=self.getfieldsBySelectionFunc, EncodeMsgFields=self.encodeMsgFields,
				GetSubFields=self.getfields, GetSubFieldByNames=self.getfieldByNames, LowerClassMarco=getClassMacro(self.structInfo.name).lower()).encode('utf-8'));
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
	destFile.write('/*\n * @(#) %s.h Created by feimao message creator\n */\n'%fileName);
	destFile.write('\n#ifndef %s_H\n#define %s_H\n\n'%(getClassMacro(fileName), getClassMacro(fileName)));

	macroString = '';
	for fi in macros:
		attrDef = '#define %s'%(fi.name);
		attrDef = '{0:{width}}'.format(attrDef, width=64);
		macroString += '%s%s\t/* %s */\n'%(attrDef, fi.value, fi.desc);

	destFile.write(macroString.encode('utf-8'));

	for si in enums:
		destFile.write(generateEnumDefine(si).encode('utf-8'));

	destFile.write('\n#endif\n');

	destFile.close();

#
# 消息配置文件读取与处理
#
class MsgCreatorHandler(ContentHandler):

	def __init__(self, enums=[], macros=[], messages=[], macroFile='', outputDir='./', lanaguage='cpp', argument=Argument()):
		self.curStructInfo = None;
		self.enums = enums;
		self.macros = macros;
		self.macroFile = macroFile;
		self.outputDir = outputDir;
		self.lanaguage = lanaguage;
		self.messages = messages;
		self.argument = argument;
		pass;

	def startDocument(self):
		pass;

	def startElement(self, name, attrs):
		if (name == 'struct' or name == 'enum' or name=='union' or name=='message'):
			if (name == 'union'):
				siType = STRUCT_INFO_TYPE_UNION;
			elif (name == 'message'):
				siType = STRUCT_INFO_TYPE_MSG;
			else:
				siType = STRUCT_INFO_TYPE_STRUCT;
			self.curStructInfo = StructInfo(name=attrs.get('name', ''), id=attrs.get('id', ''), version=attrs.get('version', '1'), desc=attrs.get('desc', ''), type=siType);
		elif (name == 'field'):
			fieldInfo = FieldInfo(name=attrs.get('name', ''), value=attrs.get('value', ''), type=attrs.get('type', ''), tag=attrs.get('tag', ''), version=attrs.get('version', '1'), default=attrs.get('default', ''), desc=attrs.get('desc', ''), subtype=attrs.get('subtype', '1'), count=attrs.get('count', '1'));
			if (self.curStructInfo != None):
				self.curStructInfo.addField(fieldInfo);
			pass;
		elif (name == 'macro'):
			fieldInfo = FieldInfo(name=attrs.get('name', ''), value=attrs.get('value', ''), desc=attrs.get('desc', ''))
			if (self.curStructInfo != None):
				self.curStructInfo.addField(fieldInfo);
			else:
				self.macros.append(fieldInfo);

	def characters(self, ch):
		pass;

	def endElement(self, name):
		if (name == 'struct' or name=='union' or name=='message'):
			g = HeaderGenerator(self.curStructInfo, language=self.lanaguage, argument=self.argument);
			g.generateHeaderFile(self.outputDir, self.macroFile);
			g.generateCppFile(self.outputDir);

			if (self.curStructInfo != None and self.curStructInfo.id != ''):
				self.messages.append(self.curStructInfo);

			self.curStructInfo = None;
		elif (name == 'enum'):
			self.enums.append(self.curStructInfo);
			self.curStructInfo = None;
		pass;

	def endDocument(self):
		pass;

#
# 指定路径下查找.xml文件，并生成字段定义文件
# @param xmlSrcPath 协议定义文件查找路径
# @param macroFileName 宏定义文件名
# @param outputDir 输出路径
# @param language 输出的语言类型，当前支持c、cpp
# @param unionType
#
def genernateFieldFile(xmlSrcPath, macroFileName, outputDir, language, unionType=UNION_GENERATE_TYPE_UNION):
	enums = [];
	macros = [];
	messages = [];
	argument = Argument(unionType);

	parser = make_parser();
	parser.setContentHandler(MsgCreatorHandler(enums, macros, messages, macroFileName, outputDir, language, argument));

	for root, dirs, files in os.walk(xmlSrcPath):
		for name in files:
			if (name.endswith('.xml')):
				parser.parse(open(os.path.join(root, name)));

	# 生成macro文件
	generateMacroFile(outputDir, macroFileName, enums, macros);
	# 生成消息create文件

def usage():
	print '''
Description: @itfriday protocol-pack message generator.
Version: 1.0.0.0
Usage: python generator.py [-?] [-h] [-s DIRECTORY] [-d DIRECTORY]
                           [-l {c, cpp}] [-m FILE_NAME] [-u {union, struct}]

optional arguments:
  -?, -h, --help\tShow this help information
  -s DIRECTORY, --srcpath DIRECTORY
\t\t\tSet protocol define file search directory
  -l {c, cpp}, --language {c, cpp}\t
\t\t\tMajor programming language you want to use, should be
\t\t\t[c|cpp]
  -d DIRECTORY, --directory DIRECTORY
\t\t\tSet generate project directory for project
  -m FILE_NAME
\t\t\tSet generate macro file name

Example:
  python generator.py --help
  python generator.py -s . -d ../test -l cpp -m StarMacro'''

#-u {union, struct}, --uniontype {union, struct}
#\t\t\tSet c/c++ type for union struct

import getopt;
import sys;

if __name__ == '__main__':
	xmlSrcPath = '.';
	macroFileName = 'StarMacro';
	outputDir = '.';
	language = 'c';
	unionType = UNION_GENERATE_TYPE_STRUCT;

	try:
		opts, args = getopt.getopt(sys.argv[1:], 's:m:d:l:h?u:', ['help','language', 'directory', 'srcpath', 'uniontype']);
	except getopt.GetoptError, ex:
		print ex;
		usage();
		sys.exit(-1);

	for opt, arg in opts:
		if opt in ('-h', '--help', '-?'):
			usage();
			sys.exit();
		elif opt in ('-s', '--srcpath'):
			xmlSrcPath = arg;
		elif opt in ('-d', '--directory'):
			outputDir = arg;
		elif opt in ('-l', '--language'):
			language = arg;
		elif opt == '-m':
			macroFileName = arg;
		elif opt in ('-u', '--uniontype'):
			if (arg == 'struct'):
				unionType = UNION_GENERATE_TYPE_STRUCT;

	genernateFieldFile(xmlSrcPath, macroFileName, outputDir, language, unionType);

	#genernateFieldFile('.', 'StartMacro', '../../CMessage/test', 'c');
	#genernateFieldFile('.', 'StartMacro', '../test', 'cpp');
	#genernateFieldFile('../../PopLevelEditor/protocol', 'PopMacro', '../../CMessage/test', 'c');
	#genernateFieldFile('../../PopLevelEditor/protocol', 'PopMacro', '../../PopLevelEditor/protocol', 'cpp');
	#genernateFieldFile('../../FConnector/conf', 'ConfigMacro', '../../FConnector/Config', 'c');
	#genernateFieldFile(r'E:\Xu\QT\ResConvert\project', 'ConfigMacro', r'E:\Xu\QT\ResConvert\project', 'cpp');

