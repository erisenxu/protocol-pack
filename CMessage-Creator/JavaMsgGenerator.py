#!/usr/bin/python
# -*- coding: utf-8 -*-

from MsgGenerator import *;

from string import Template;
import os;

import javatemplate;

M_JAVA_TYPE_MAP = {
	'uchar': 'byte',
	'char': 'byte',
	'ushort': 'short',
	'short': 'short',
	'uint': 'int',
	'int': 'int',
	'ulong': 'long',
	'long': 'long',
	'string': 'String',
	'bytes': 'byte[]'
};

M_JAVA_FIELD_MAP = {
	'uchar': 'PPUByteField',
	'char': 'PPByteField',
	'ushort': 'PPUShortField',
	'short': 'PPShortField',
	'uint': 'PPUIntField',
	'int': 'PPIntField',
	'ulong': 'PPULongField',
	'long': 'PPLongField',
	'string': 'PPStringField',
	'bytes': 'PPBytesField'
};

#
# 取类型对应的类型名
#
def getTypeName(ftype):
	if (M_JAVA_TYPE_MAP.has_key(ftype)):
		return M_JAVA_TYPE_MAP[ftype];
	else:
		return ftype;

#
# 取类型对应的结构名
#
def getStructName(ftype):
	if (M_JAVA_FIELD_MAP.has_key(ftype)):
		return M_JAVA_FIELD_MAP[ftype];
	else:
		return ftype;

#
# 取属性名称
#
def getAttrName(name):
	return '%s'%firstUpper(name);

class JavaMsgGenerator(MsgGenerator):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile='', packageName=''):
		MsgGenerator.__init__(self, structInfo, macroFile);
		self.packageName = packageName;
		self.attributes = '';
		self.attrGetSetDefine = '';
		self.fieldEncode = '';
		self.formats = '';
		self.toXmls = '';
		self.getSubField = '';
		self.implUnion = '';
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
				otag = '%s.%s'%(self.macroFile, fi.tag);

			unionTab = '';
			unionEncodeStart = '';
			unionEncodeEnd = '';
			unionAttrNew = '';
			unionAttrGetSet = '';
			unionGetSubField = '';

			if (fi.type == 'array'):
				attrNew = ' = new PPArrayField<>(new PPFieldCreator<%s>() {\n        @Override\n        public %s create() {\n            return new %s();\n        }\n    })'%(getStructName(fi.subtype),
					getStructName(fi.subtype), getStructName(fi.subtype));
			else:
				attrNew = ' = new %s()'%(getStructName(fi.type));

			if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
				unionTab = '    ';
				unionEncodeStart = '\n        case %s:'%(otag);
				unionEncodeEnd = '\n            break;';
				unionAttrGetSet = '\n        if (m%s == null) m%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNew);
				unionGetSubField = '\n            mSelector = tag;\n            if (m%s == null) m%s %s;'%(getAttrName(fi.name), getAttrName(fi.name), attrNew);
				self.implUnion = ' implements PPUnionField';
			else:
				unionAttrNew = attrNew;

			# Encode
			self.fieldEncode += '%s\n        %sm%s.encode(baBuf, (short)%s);%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), otag, unionEncodeEnd);
			# Format
			self.formats += '%s\n        %sm%s.format(sbBuf, "%s", sSubPrefix);%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), fi.name, unionEncodeEnd);
			# ToXml
			self.toXmls += '%s\n        %sm%s.toXml(sbBuf, "%s", sSubPrefix);%s'%(unionEncodeStart,
				unionTab, getAttrName(fi.name), fi.name, unionEncodeEnd);
			# GetSubField
			self.getSubField += '\n        case %s:%s\n            return m%s;'%(otag, unionGetSubField, getAttrName(fi.name));

			# 处理属性列表
			if (fi.type == 'array'):
				# Attributes
				self.attributes += '\n    /**\n     * %s\n     */\n    protected PPArrayField<%s> m%s%s;\n'%(fi.desc, getStructName(fi.subtype), getAttrName(fi.name), unionAttrNew);    
				# get and set
				if (M_JAVA_TYPE_MAP.has_key(fi.subtype)):
					returnValue = 'return m%s.getFieldByIndex(index).getValue();'%(getAttrName(fi.name));
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    public void set%s(int index, %s value) throws ToolException {%s\n        m%s.getFieldByIndex(index).setValue(value);\n    }\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.subtype), unionAttrGetSet, getAttrName(fi.name));
				else:
					returnValue = 'return m%s.getFieldByIndex(index);'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    public %s get%s(int index) throws ToolException {%s\n        %s\n    }\n'%(fi.desc, getTypeName(fi.subtype),
					getAttrName(fi.name), unionAttrGetSet, returnValue);
			else:
				# Attributes
				self.attributes += '\n    /**\n     * %s\n     */\n    protected %s m%s%s;\n'%(fi.desc, getStructName(fi.type), getAttrName(fi.name), unionAttrNew);
				# get and set
				if (M_JAVA_TYPE_MAP.has_key(fi.type)):
					returnValue = 'return m%s.getValue();'%(getAttrName(fi.name));
					self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    public void set%s(%s value) {%s\n        m%s.setValue(value);\n    }\n'%(fi.desc,
						getAttrName(fi.name), getTypeName(fi.type), unionAttrGetSet, getAttrName(fi.name));
				else:
					returnValue = 'return m%s;'%(getAttrName(fi.name));
				self.attrGetSetDefine += '\n    /**\n     * %s\n     */\n    public %s get%s() {%s\n        %s\n    }\n'%(fi.desc, getTypeName(fi.type),
					getAttrName(fi.name), unionAttrGetSet, returnValue);
				pass;

		# 处理union
		if (self.structInfo.type == STRUCT_INFO_TYPE_UNION):
			self.attributes = u'\n    /**\n     * Union字段标识\n     */\n    protected short mSelector = 0;\n%s'%(self.attributes);
			self.fieldEncode = '\n        switch (mSelector) {%s\n        default:\n            break;\n        }'%(self.fieldEncode);
			self.formats = '\n        switch (mSelector) {%s\n        default:\n            break;\n        }'%(self.formats);
			self.toXmls = '\n        switch (mSelector) {%s\n        default:\n            break;\n        }'%(self.toXmls);
			self.attrGetSetDefine = u'\n    @Override\n    public void setSelector(short selector) {\n        mSelector = selector;\n    }\n%s'%(self.attrGetSetDefine);

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
		outDir = '%s/%s/'%(outDir, self.packageName.replace('.', '/'));
		try:
			os.makedirs(outDir);
		except:
			pass;
		destFile = open('%s/%s.java'%(outDir, className), 'w');

		templ = Template(javatemplate.JTEMPLATE.decode('utf-8'));
		destFile.write(templ.safe_substitute(ClassName=className, ClassDesc=self.structInfo.desc, AttrDefine=self.attributes,
			AttrSetGet=self.attrGetSetDefine, FieldEncode=self.fieldEncode, Formats=self.formats, ToXmls=self.toXmls,
			GetSubField=self.getSubField, PackageName=self.packageName, ImplUnion=self.implUnion).encode('utf-8'));
		destFile.close();
		return ''

# generate enum define
#
def generateEnumDefine(si):
	enumDef = '';

	for fi in si.fields:
		attrDef = '    int %s = %s;'%(fi.name, fi.value);
		attrDef = '{0:{width}}'.format(attrDef, width=64);
		enumDef += '%s// %s\n'%(attrDef, fi.desc);

	return enumDef;

#
# generate macro file
#
def generateMacroFile(outdir, fileName, enums, macros, packageName):
	outdir = '%s/%s/'%(outdir, packageName.replace('.', '/'));
	try:
		os.makedirs(outdir);
	except:
		pass;
	destFile = open('%s/%s.java'%(outdir, fileName), 'w');
	destFile.write('/*\n * @(#) %s.java Created by @itfriday message creator\n */\n'%fileName);
	destFile.write('\npackage %s;\n'%(packageName));
	destFile.write('\npublic interface %s {\n'%(fileName));

	macroString = '';
	for fi in macros:
		attrDef = '    int %s = %s;'%(fi.name, fi.value);
		attrDef = '{0:{width}}'.format(attrDef, width=64);
		macroString += '%s// %s\n'%(attrDef, fi.desc);

	destFile.write(macroString.encode('utf-8'));

	for si in enums:
		destFile.write(generateEnumDefine(si).encode('utf-8'));

	destFile.write('}\n');

	destFile.close();
