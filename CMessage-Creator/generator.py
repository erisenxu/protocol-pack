#!/usr/bin/python
# -*- coding: utf-8 -*-

from xml.sax import make_parser;
from xml.sax.handler import ContentHandler;

import os;

from MsgGenerator import *;
import CMsgGenerator;
import CppMsgGenerator;
import JavaMsgGenerator;
import OcMsgGenerator;

#
# 消息配置文件读取与处理
#
class MsgCreatorHandler(ContentHandler):

	def __init__(self, enums=[], macros=[], macroFile='', outputDir='./', language='c', packageName=''):
		self.curStructInfo = None;
		self.enums = enums;
		self.macros = macros;
		self.macroFile = macroFile;
		self.outputDir = outputDir;
		self.language = language;
		self.packageName = packageName;
		pass;

	def startDocument(self):
		pass;

	def startElement(self, name, attrs):
		if (name == 'struct' or name=='message' or name=='union' or name=='enum'):
			if (name == 'message'):
				siType = STRUCT_INFO_TYPE_MSG;
			elif (name == 'union'):
				siType = STRUCT_INFO_TYPE_UNION;
			else:
				siType = STRUCT_INFO_TYPE_STRUCT;
			self.curStructInfo = StructInfo(name=attrs.get('name', ''), desc=attrs.get('desc', ''), type=siType, macros=self.macros, enums=self.enums);
		elif (name == 'field'):
			fieldInfo = FieldInfo(name=attrs.get('name', ''), value=attrs.get('value', ''), type=attrs.get('type', ''), tag=attrs.get('tag', ''),
				default=attrs.get('default', ''), desc=attrs.get('desc', ''), subtype=attrs.get('subtype', '1'), count=attrs.get('count', '1'),
				refer=attrs.get('refer', ''));
			if (self.curStructInfo != None):
				self.curStructInfo.addField(fieldInfo);
			pass;
		elif (name == 'macro'):
			fieldInfo = FieldInfo(name=attrs.get('name', ''), value=attrs.get('value', ''), desc=attrs.get('desc', ''));
			if (self.curStructInfo != None):
				self.curStructInfo.addField(fieldInfo);
			else:
				self.macros.append(fieldInfo);

	def characters(self, ch):
		pass;

	def endElement(self, name):
		if (name == 'struct' or name=='message' or name=='union'):
			if (self.language == 'c'):
				g = CMsgGenerator.CMsgGenerator(self.curStructInfo, macroFile=self.macroFile);
			elif (self.language == 'cpp'):
				g = CppMsgGenerator.CppMsgGenerator(self.curStructInfo, macroFile=self.macroFile);
			elif (self.language == 'oc'):
				g = OcMsgGenerator.OcMsgGenerator(self.curStructInfo, macroFile=self.macroFile);
			elif (self.language == 'java'):
				g = JavaMsgGenerator.JavaMsgGenerator(self.curStructInfo, macroFile=self.macroFile, packageName=self.packageName);
			else:
				g = MsgGenerator(self.curStructInfo, macroFile=self.macroFile);

			g.generateHeaderFile(self.outputDir);
			g.generateAppFile(self.outputDir, self.macroFile);
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
def genernateFieldFile(xmlSrcPath, macroFileName, outputDir, language, packageName):
	enums = [];
	macros = [];

	parser = make_parser();
	parser.setContentHandler(MsgCreatorHandler(enums, macros, macroFileName, outputDir, language, packageName));

	for root, dirs, files in os.walk(xmlSrcPath):
		for name in files:
			if (name.endswith('.xml')):
				parser.parse(open(os.path.join(root, name)));

	# 生成macro文件
	if (language == 'c' or language == 'cpp'):
		CMsgGenerator.generateMacroFile(outputDir, macroFileName, enums, macros);
	elif (language == 'oc'):
		OcMsgGenerator.generateMacroFile(outputDir, macroFileName, enums, macros);
	elif (language == 'java'):
		JavaMsgGenerator.generateMacroFile(outputDir, macroFileName, enums, macros, packageName);

def usage():
	print '''
Description: message generator.
Version: 1.0.0.0
Usage: python generator.py [-?] [-h] [-s DIRECTORY] [-d DIRECTORY]
                           [-l {c, cpp, java, oc}] [-m FILE_NAME] [-p PACKAGE_NAME]

optional arguments:
  -?, -h, --help\tShow this help information
  -s DIRECTORY, --srcpath DIRECTORY
\t\t\tSet protocol define file search directory
  -l {c, cpp, java, oc}, --language {c, cpp, java, oc}\t
\t\t\tMajor programming language you want to use, should be
\t\t\t[c|cpp|java|oc]
  -d DIRECTORY, --directory DIRECTORY
\t\t\tSet generate project directory for project
  -m FILE_NAME
\t\t\tSet generate macro file name
  -p PACKAGE_NAME
\t\t\tSet package for java

Example:
  python generator.py --help
  python generator.py -s . -d ../test -l c -m StarMacro'''

import getopt;
import sys;

if __name__ == '__main__':
	xmlSrcPath = '.';
	macroFileName = 'MsgMacro';
	outputDir = '../CMessage/test';
	language = 'c';
	packageName = '';

	try:
		opts, args = getopt.getopt(sys.argv[1:], 's:m:d:l:p:h?', ['help','language', 'directory', 'srcpath']);
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
		elif opt == '-p':
			packageName = arg;

	genernateFieldFile(xmlSrcPath, macroFileName, outputDir, language, packageName);
