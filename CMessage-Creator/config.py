#!/usr/bin/env python
#coding:utf-8
#=================================================================
# @ Author : Erisenxu @ Innovate Center
# @ Desc : 配置信息
# @ FileName : MsgConfig.py
# @ Date : 2014-03-29
# @ ModifyHistory :
# @ Remark :
#==================================================================

M_C_NAME_PREFIX_MAP = {
	'uchar': 'b',
	'char': 'ch',
	'ushort': 'n',
	'short': 'sh',
	'uint': 'dw',
	'int': 'i',
	'ulong': 'ull',
	'long': 'll',
	'string': 'sz',
	'array': 'ast'
};

M_C_TYPE_MAP = {
	'uchar': 'U8',
	'char': 'S8',
	'ushort': 'U16',
	'short': 'S16',
	'uint': 'U32',
	'int': 'S32',
	'ulong': 'U64',
	'long': 'S64',
	'string': 'char'
};

M_C_CODEC_MAP = {
	'uchar': 'ubyte',
	'char': 'byte',
	'ushort': 'ushort',
	'short': 'short',
	'uint': 'uint',
	'int': 'int',
	'ulong': 'ulong',
	'long': 'long',
	'string': 'string',
	'array': 'array'
};

M_C_VALUE_MAP = {
	'uchar': '(U8)atoi',
	'char': '(S8)atoi',
	'ushort': '(U16)atoi',
	'short': '(S16)atoi',
	'uint': '(U32)atoi',
	'int': '(S32)atoi',
	'ulong': '(U64)atoll',
	'long': '(S64)atoll'
};

M_C_FIELD_TYPE_MAP = {
	'uchar': 'FIELD_TYPE_UBYTE',
	'char': 'FIELD_TYPE_BYTE',
	'ushort': 'FIELD_TYPE_USHORT',
	'short': 'FIELD_TYPE_SHORT',
	'uint': 'FIELD_TYPE_UINT',
	'int': 'FIELD_TYPE_INT',
	'ulong': 'FIELD_TYPE_ULONG',
	'long': 'FIELD_TYPE_LONG'
};
