#!/usr/bin/python
# -*- coding: utf-8 -*-

from MsgGenerator import *;

from string import Template;
import os;

import jstemplate;

M_JAVA_FIELD_MAP = {
	'uchar': 'PPField.PPUByteField',
	'char': 'PPField.PPByteField',
	'ushort': 'PPField.PPUShortField',
	'short': 'PPField.PPShortField',
	'uint': 'PPField.PPUIntField',
	'int': 'PPField.PPIntField',
	'ulong': 'PPField.PPULongField',
	'long': 'PPField.PPLongField',
	'string': 'PPField.PPStringField',
	'bytes': 'PPField.PPBytesField'
};

#
# 取类型对应的结构名
#
def getStructName(ftype):
	if (M_JAVA_FIELD_MAP.has_key(ftype)):
		return M_JAVA_FIELD_MAP[ftype];
	else:
		return 'pp.%s'%(ftype);

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstLower(name);

#
# 取函数名称
#
def getAttrFuncName(name):
	return '%s'%firstUpper(name);

class JsMsgGenerator(MsgGenerator):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile=''):
		MsgGenerator.__init__(self, structInfo, macroFile);
		self.attributes = '';
		self.attrGetSetDefine = '';
		self.fieldEncode = '';
		self.toJson = '';
		self.fromJson = '';
		self.getSubField = '';
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
			if (self.structInfo.hasMacro(fi.tag)):
				otag = 'pp.%s'%(fi.tag);

			unionTab = '';
			unionEncodeStart = '';
			unionEncodeEnd = '';
			unionAttrNew = '';
			unionAttrGetSet = '';
			unionGetSubField = '';
			unionAttrIf = '';

			if (fi.type == 'array'):
				attrNew = ' = new PPField.PPArrayField(%s, o.%s)'%(getStructName(fi.subtype), getAttrName(fi.name));
				attrNewUnion = ' = new PPField.PPArrayField(%s)'%(getStructName(fi.subtype));
			else:
				attrNew = ' = new %s(o.%s)'%(getStructName(fi.type), getAttrName(fi.name));
				attrNewUnion = ' = new %s()'%(getStructName(fi.type));

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionTab = '\t';
				unionEncodeStart = '\n\t\tcase %s:'%(otag);
				unionEncodeEnd = '\n\t\t\tbreak;';
				unionAttrGetSet = '\n\t\tif (this.%s === undefined) this.%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNewUnion);
				unionGetSubField = '\n\t\t\tthis.selector = tag;\n\t\t\tif (this.%s === undefined) this.%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNewUnion);
				unionAttrIf = 'if (o.%s) {'%(getAttrName(fi.name));
				unionAttrNew = '%s;this.selector = %s;}'%(attrNew, otag);
				# ToJson
				self.toJson += '%s\n\t\t\treturn {%s:this.%s.toJson()};'%(unionEncodeStart, getAttrName(fi.name), getAttrName(fi.name));
				# FromJson
				self.fromJson += '\n\t\tif (o.%s) {this.%s === undefined ? this.%s %s : this.%s.fromJson(o.%s);this.selector = %s;}'%(getAttrName(fi.name), getAttrName(fi.name), getAttrName(fi.name), attrNew, getAttrName(fi.name), getAttrName(fi.name), otag);
			else:
				unionAttrNew = '%s;'%(attrNew);
				# ToJson
				if (self.toJson != ''):
					self.toJson += ',';
				self.toJson += '%s:this.%s.toJson()'%(getAttrName(fi.name), getAttrName(fi.name));
				# FromJson
				self.fromJson += '\n\t\tthis.%s.fromJson(o.%s);'%(getAttrName(fi.name), getAttrName(fi.name));

			# Encode
			self.fieldEncode += '%s\n%s\t\tthis.%s.encode(baBuf, %s);%s'%(unionEncodeStart, unionTab, getAttrName(fi.name), otag, unionEncodeEnd);
			# GetSubField
			self.getSubField += '\n\t\tcase %s:%s\n\t\t\treturn this.%s;'%(otag, unionGetSubField, getAttrName(fi.name));

			# 处理属性列表
			if (fi.type == 'array'):
				# Attributes
				self.attributes += '\n\t\t%sthis.%s%s'%(unionAttrIf, getAttrName(fi.name), unionAttrNew);
				# get and set
				if (M_JAVA_FIELD_MAP.has_key(fi.subtype)):
					returnValue = 'return this.%s.getFieldByIndex(index).value;'%(getAttrName(fi.name));
					self.attrGetSetDefine += '\n    \n    %s.prototype.set%s = function(index, value) {%s\n        this.%s.getFieldByIndex(index).value = value;\n    };'%(getClassName(self.structInfo.name),
						getAttrFuncName(fi.name), unionAttrGetSet, getAttrName(fi.name));
				else:
					returnValue = 'return this.%s.getFieldByIndex(index);'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n    %s.prototype.get%s = function(index) {%s\n        %s\n    };'%(getClassName(self.structInfo.name),
					getAttrFuncName(fi.name), unionAttrGetSet, returnValue);
			else:
				# Attributes
				self.attributes += '\n\t\t%sthis.%s%s'%(unionAttrIf, getAttrName(fi.name), unionAttrNew);
				# get and set
				if (M_JAVA_FIELD_MAP.has_key(fi.type)):
					returnValue = 'return this.%s.value;'%(getAttrName(fi.name));
					self.attrGetSetDefine += '\n\t%s.prototype.set%s = function(value) {%s\n\t\tthis.%s.value = value;\n\t};'%(getClassName(self.structInfo.name),
						getAttrFuncName(fi.name), unionAttrGetSet, getAttrName(fi.name));
				else:
					returnValue = 'return this.%s;'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n\t%s.prototype.get%s = function() {%s\n\t\t%s\n\t};'%(getClassName(self.structInfo.name),
					getAttrFuncName(fi.name), unionAttrGetSet, returnValue);
				pass;

		# 处理union
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			self.attributes = '\n\t\tthis.selector = 0;%s'%(self.attributes);
			self.fieldEncode = '\n\t\tswitch (this.selector) {%s\n\t\tdefault:\n\t\t\tbreak;\n\t\t}'%(self.fieldEncode);
			self.toJson = '\n\t\tswitch (this.selector) {%s\n\t\tdefault:\n\t\t\treturn {};\n\t\t}'%(self.toJson);
		else:
			self.toJson = '\n\t\treturn {%s};'%(self.toJson);

	#
	# 生成头文件
	#
	def generateHeaderFile(self, outDir):
		return '';

	#
	# 生成实现文件
	#
	def generateAppFile(self, outDir, marcroFile):
		className = getClassName(self.structInfo.name);

		templ = Template(jstemplate.JC_TEMPLATE.decode('utf-8'));
		return templ.safe_substitute(ClassName=className, AttrDefine=self.attributes,
			AttrSetGet=self.attrGetSetDefine, FieldEncode=self.fieldEncode, FieldFromJson=self.fromJson,
			FieldToJson=self.toJson, GetSubField=self.getSubField).encode('utf-8');

#
# generate enum define
#
def generateEnumDefine(si):
	enumDef = '';

	for fi in si.fields:
		enumDef += 'pp.%s = %s;\n'%(fi.name, fi.value);

	return enumDef;

#
# generate macro file
#
def generateMacroDefine(enums, macros):

	macroString = '';
	for fi in macros:
		macroString += 'pp.%s = %s;\n'%(fi.name, fi.value);

	for si in enums:
		macroString += generateEnumDefine(si);

	return macroString;

#
# generate macro file
#
def generateMsgDefineFile(outdir, fileName, msgDefines, enums, macros):
	outdir = '%s'%(outdir);
	try:
		os.makedirs(outdir);
	except:
		pass;
	destFile = open('%s/%s.js'%(outdir, fileName), 'w');
	templ = Template(jstemplate.JSTEMPLATE.decode('utf-8'));

	destFile.write(templ.safe_substitute(ppMarcoDefine=generateMacroDefine(enums, macros), ppMsgDefine=msgDefines).encode('utf-8'));

	destFile.close();
