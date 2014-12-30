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

M_CLASS_TYPE_MAP = {
	'uchar': 'MUByteField',
	'char': 'MByteField',
	'ushort': 'MUShortField',
	'short': 'MShortField',
	'uint': 'MUIntField',
	'int': 'MIntField',
	'ulong': 'MULongField',
	'long': 'MLongField',
	'string': 'MStringField',
	'array': 'MArrayField'
};

M_C_TYPE_MAP = {
	'uchar': 'UBYTETFIELD',
	'char': 'BYTETFIELD',
	'ushort': 'USHORTFIELD',
	'short': 'SHORTFIELD',
	'uint': 'UINTFIELD',
	'int': 'INTFIELD',
	'ulong': 'ULONGFIELD',
	'long': 'LONGFIELD',
	'string': 'STRINGFIELD',
	'array': 'ARRAYFIELD'
};

M_C_INIT_FUNC_MAP = {
	'uchar': 'init_ubyte_field',
	'char': 'init_byte_field',
	'ushort': 'init_ushort_field',
	'short': 'init_short_field',
	'uint': 'init_uint_field',
	'int': 'init_int_field',
	'ulong': 'init_ulong_field',
	'long': 'init_long_field',
	'string': 'init_string_field',
	'array': 'init_array_field'
};

M_C_CONSTRUCT_FUNC_MAP = {
	'uchar': 'construct_ubyte_field',
	'char': 'construct_byte_field',
	'ushort': 'construct_ushort_field',
	'short': 'construct_short_field',
	'uint': 'construct_uint_field',
	'int': 'construct_int_field',
	'ulong': 'construct_ulong_field',
	'long': 'construct_long_field',
	'string': 'construct_string_field',
	'array': 'construct_array_field'
};

M_C_FIELD_INFO_MAP = {
	'uchar': 'g_stUByteFieldInfo',
	'char': 'g_stByteFieldInfo',
	'ushort': 'g_stUShortFieldInfo',
	'short': 'g_stShortFieldInfo',
	'uint': 'g_stUIntFieldInfo',
	'int': 'g_stIntFieldInfo',
	'ulong': 'g_stULongFieldInfo',
	'long': 'g_stLongFieldInfo',
	'string': 'g_stStringFieldInfo',
	'array': 'g_stArrayFieldInfo'
};
