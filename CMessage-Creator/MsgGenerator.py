#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# 结构体类型
#
STRUCT_INFO_TYPE_STRUCT = 0;	# Struct类型
STRUCT_INFO_TYPE_UNION = 1;		# Union类型
STRUCT_INFO_TYPE_MSG = 2;		# Message类型(Deprecated)

#
# 首字母大写
#
def firstUpper(name):
	return name[:1].capitalize() + name[1:];

#
# 首首字母小写
#
def firstLower(name):
	return name[:1].lower() + name[1:];

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
# 根据名字获得类名
#
def getClassName(name):
	className = '';
	state = 0;
	num = len(name);
	for i in range(0, num):
		if (state == 0):
			if (name[i] == '_' or name[i] == '-'):
				state = 1;
			else:
				if (i == 0):
					className += name[i].capitalize();
				else:
					className += name[i];
		elif (state == 1):
			if (name[i] == '_' or name[i] == '-'):
				pass;
			else:
				className += name[i].capitalize();
				state = 0;
	return className;

#
# 属性字段信息
#
class FieldInfo(object):

	def __init__(self, name='', type='', default='', desc='', subtype='', value='', tag='', count='', refer=''):
		self.name = name;
		self.type = type;
		self.subtype = subtype;
		self.default = default;
		self.desc = desc;
		self.value = value;
		self.tag = tag;
		self.count = count;
		self.refer = refer;

#
# 结构体信息
#
class StructInfo(object):

	def __init__(self, name='', desc='', type='', macros=[], enums=[]):
		self.name = name;
		self.desc = desc;
		self.type = type;
		self.macros = macros;
		self.enums = enums;
		self.fields = [];

	def addField(self, fieldInfo):
		self.fields.append(fieldInfo);

	def hasMacro(self, name):
		for ma in self.macros:
			if (ma.name == name):
				return True;
		for en in self.enums:
			for fi in en.fields:
				if (fi.name == name):
					return True;
		return False;

	#
	# 按名称查找子字段
	#
	def getFieldByName(self, name):
		for fi in self.fields:
			if (fi.name == name):
				return fi;
		return None;

class MsgGenerator(object):

	#
	# 构造函数
	#
	def __init__(self, structInfo=None, macroFile=''):
		self.structInfo = structInfo;
		self.macroFile = macroFile;

	#
	# 处理结构体
	#
	def handleStructInfo(self):
		pass;

	#
	# 生成头文件
	#
	def generateHeaderFile(self, outputDir):
		pass;

	#
	# 生成实现文件
	#
	def generateAppFile(self, outputDir, marcroFile):
		pass;

