package com.itfriday.protocol.ppfield;

/**
 * Created by erisenxu on 2016/9/3.
 */
public interface PPFieldType {
    byte FIELD_TYPE_INVALID = 0; // 不合法(未初始化)的字段类型
    byte FIELD_TYPE_BYTE = 1;    // S8，占1个字节
    byte FIELD_TYPE_UBYTE = 2;   // U8，占1个字节
    byte FIELD_TYPE_SHORT = 3;   // S16，占2个字节
    byte FIELD_TYPE_USHORT = 4;  // U16，占2个字节
    byte FIELD_TYPE_INT = 5;     // S32，占4个字节
    byte FIELD_TYPE_UINT = 6;    // U32，占4个字节
    byte FIELD_TYPE_LONG = 7;    // S64，占8个字节
    byte FIELD_TYPE_ULONG = 8;   // U64，占8个字节
    byte FIELD_TYPE_STRING = 9;  // 字符串，特殊的TLV字段
    byte FIELD_TYPE_BYTES = 10;  // 字节数组，特殊的TLV字段
    byte FIELD_TYPE_TLV = 11;    // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
    byte FIELD_TYPE_ARRAY = 12;   // 数组
}
