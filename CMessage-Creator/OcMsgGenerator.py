#!/usr/bin/python
# -*- coding: utf-8 -*-

from MsgGenerator import *;

from string import Template;
import os;

import octemplate;

M_OC_TYPE_MAP = {
	'uchar': 'UInt8',
	'char': 'SInt8',
	'ushort': 'UInt16',
	'short': 'SInt16',
	'uint': 'UInt32',
	'int': 'SInt32',
	'ulong': 'UInt64',
	'long': 'SInt64',
	'string': 'NSString *'
};

M_OC_FIELD_MAP = {
	'uchar': 'PPUByteField',
	'char': 'PPByteField',
	'ushort': 'PPUShortField',
	'short': 'PPShortField',
	'uint': 'PPUIntField',
	'int': 'PPIntField',
	'ulong': 'PPULongField',
	'long': 'PPLongField',
	'string': 'PPStringField'
};

#
# 取类型对应的类型名
#
def getTypeName(ftype):
	if (M_OC_TYPE_MAP.has_key(ftype)):
		return M_OC_TYPE_MAP[ftype];
	else:
		return '%s *'%(ftype);

#
# 取类型对应的结构名
#
def getStructName(ftype):
	if (M_OC_FIELD_MAP.has_key(ftype)):
		return M_OC_FIELD_MAP[ftype];
	else:
		return ftype;

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstUpper(name);

class OcMsgGenerator(MsgGenerator):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile=''):
		MsgGenerator.__init__(self, structInfo, macroFile);
		self.attrSetGetDef = '';
		self.attributes = '';
		self.attrGetSetDefine = '';
		self.fieldEncode = '';
		self.formats = '';
		self.toXmls = '';
		self.getSubField = '';
		self.includes = '';
		self.inclClass = [];
		self.inits = '';
		self.selector = '';
		self.handleStructInfo();

	#
	# 处理结构体
	#
	def handleStructInfo(self):
		if (self.structInfo == None):
			return;

		className = getClassName(self.structInfo.name)

		for fi in self.structInfo.fields:
			if (fi.tag == '' or fi.tag == None):
				raise Exception("Please give tag for struct(%s), field(%s)"%(self.structInfo.name, fi.name));

			otag = fi.tag;
			#if (self.structInfo.hasMacro(fi.tag)):
			#	otag = '%s.%s'%(self.macroFile, fi.tag);

			unionTab = '';
			unionEncodeStart = '';
			unionEncodeEnd = '';
			unionAttrNew = '';
			unionAttrGetSet = '';
			unionGetSubField = '';

			if (fi.type == 'array'):
				attrNew = ' = [[PPArrayField alloc] initWithFieldCreator:^id<PPField> {\n            return [[%s alloc] init];\n        }]'%(getStructName(fi.subtype));
			else:
				attrNew = ' = [[%s alloc] init]'%(getStructName(fi.type));

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionTab = '    ';
				unionEncodeStart = '\n    case %s:'%(otag);
				unionEncodeEnd = '\n        break;';
				unionAttrGetSet = '\n    if (_m%s == nil) _m%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNew);
				unionGetSubField = '\n        _selector = tag;\n        if (_m%s == nil) _m%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNew);
			else:
				unionAttrNew = attrNew;

			# Encode
			self.fieldEncode += '%s\n    %s[_m%s encode:buff tag:%s];%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), otag, unionEncodeEnd);
			# Format
			self.formats += '%s\n    %s[_m%s format:buff fieldName:@"%s" suffix:sSubPrefix];%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), fi.name, unionEncodeEnd);
			# ToXml
			self.toXmls += '%s\n    %s[_m%s toXml:buff fieldName:@"%s" suffix:sSubPrefix];%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), fi.name, unionEncodeEnd);
			# GetSubField
			self.getSubField += '\n    case %s:%s\n        return _m%s;'%(otag, unionGetSubField, getAttrName(fi.name));

			# 处理属性列表
			if (fi.type == 'array'):
				# inits
				self.inits += '\n        _m%s %s;'%(getAttrName(fi.name), attrNew);
				# Attributes
				self.attributes += '\n/**\n * %s\n */\n@property (nonatomic, strong) PPArrayField *m%s;\n'%(fi.desc, getAttrName(fi.name));
				# get and set
				if (M_OC_TYPE_MAP.has_key(fi.subtype)):
					returnValue = 'return [(%s *)[_m%s getFieldByIndex:index] value];'%(getStructName(fi.subtype), getAttrName(fi.name));
					self.attrGetSetDefine += '\n/**\n * %s\n */\n- (void) set%s:(UInt32)index value:(%s)value {%s\n    [(%s *)[_m%s getFieldByIndex:index] setValue:value];\n}\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.subtype), unionAttrGetSet, getStructName(fi.subtype), getAttrName(fi.name));
					self.attrSetGetDef += '\n/**\n * %s\n */\n- (void) set%s:(UInt32)index value:(%s)value ;\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.subtype));
				else:
					returnValue = 'return [_m%s getFieldByIndex:index];'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n/**\n * %s\n */\n- (%s) get%s:(UInt32)index {%s\n    %s\n}\n'%(fi.desc, getTypeName(fi.subtype),
					getAttrName(fi.name), unionAttrGetSet, returnValue);
				# imports
				if (M_OC_TYPE_MAP.has_key(fi.subtype) == False and fi.subtype not in self.inclClass):
					self.inclClass.append(fi.subtype);
				# Set and get define
				self.attrSetGetDef += '\n/**\n * %s\n */\n- (%s) get%s:(UInt32)index ;\n'%(fi.desc, getTypeName(fi.subtype), getAttrName(fi.name));
			else:
				# inits
				self.inits += '\n        _m%s %s;'%(getAttrName(fi.name), attrNew);
				# Attributes
				self.attributes += '\n/**\n * %s\n */\n@property (nonatomic, strong) %s *m%s;\n'%(fi.desc, getStructName(fi.type), getAttrName(fi.name));
				# get and set
				if (M_OC_TYPE_MAP.has_key(fi.type)):
					returnValue = 'return _m%s.value;'%(getAttrName(fi.name));
					self.attrGetSetDefine += '\n/**\n * %s\n */\n- (void) set%s:(%s)value {%s\n    _m%s.value = value;\n}\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.type), unionAttrGetSet, getAttrName(fi.name));
					self.attrSetGetDef += '\n/**\n * %s\n */\n- (void) set%s:(%s)value ;\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.type));
				else:
					returnValue = 'return _m%s;'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n/**\n * %s\n */\n- (%s) get%s {%s\n    %s\n}\n'%(fi.desc, getTypeName(fi.type),
					getAttrName(fi.name), unionAttrGetSet, returnValue);
				# Set and get define
				self.attrSetGetDef += '\n/**\n * %s\n */\n- (%s) get%s ;\n'%(fi.desc, getTypeName(fi.type), getAttrName(fi.name));
				# imports
				if (M_OC_TYPE_MAP.has_key(fi.type) == False and fi.type not in self.inclClass):
					self.inclClass.append(fi.type);
				pass;

		# 处理union
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			self.selector = u'\n/**\n * Union字段标识\n */\n@property (nonatomic, assign) UInt16 selector;\n';
			self.fieldEncode = '\n    switch (_selector) {%s\n    default:\n        break;\n    }'%(self.fieldEncode);
			self.formats = '\n    switch (_selector) {%s\n    default:\n        break;\n    }'%(self.formats);
			self.toXmls = '\n    switch (_selector) {%s\n    default:\n        break;\n    }'%(self.toXmls);

		# 处理includes
		for incl in self.inclClass:
			self.includes += '\n#import "%s.h"'%(getAttrName(incl));

	#
	# 生成头文件
	#
	def generateHeaderFile(self, outDir):
		className = getClassName(self.structInfo.name);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.h'%(outDir, className), 'w');

		templ = Template(octemplate.OC_H_TEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, AttrSetGetDef=self.attrSetGetDef, Imports=self.includes,
			Selector=self.selector).encode('utf-8'));
		destFile.close();
		return ''

	#
	# 生成实现文件
	#
	def generateAppFile(self, outDir, marcroFile):
		className = getClassName(self.structInfo.name);
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.m'%(outDir, className), 'w');

		templ = Template(octemplate.OC_M_TEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, ClassDesc=self.structInfo.desc, AttrDefine=self.attributes,
			AttrSetGet=self.attrGetSetDefine, FieldEncode=self.fieldEncode, Formats=self.formats, ToXmls=self.toXmls,
			GetSubField=self.getSubField, MsgMacro=marcroFile, Inits=self.inits).encode('utf-8'));
		destFile.close();
		return ''

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
