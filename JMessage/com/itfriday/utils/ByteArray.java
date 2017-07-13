/**
 * @(#) ByteArray.java Created on 2016-01-16
 *
 * Copyright (c) 2014-2016 Erisen Xu (@itfriday)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package com.itfriday.utils;

import java.util.ArrayList;

/**
 * The class <code>ByteArray</code> is used to store bytes
 * 注意ByteArray使用网络字节序保存bytes，网络字节序一般和Big Endian
 * (即Most significant byte first)是等价的
 *
 * @author erisenxu
 * @version 1.0
 */
public class ByteArray {

    /*
     * 保存byte数组的buffer
     */
    protected byte[] _data;

    /*
     * 字符数组分配的长度
     */
    protected int _alloc;

    /*
     * 字符数组当前长度
     */
    protected int _size;

    /*
     * The length of byte
     */
    protected final static int BYTE_LENGTH = Byte.SIZE/8;

    /**
     * Constructs a new ByteArray with 0 as its size
     */
    public ByteArray() {
        this(0);
    }

    /**
     * Constructs a new ByteArray with the specified size as its size
     * @param size The specified size
     */
    public ByteArray(int size) {
        _size = 0;
        _alloc = alloc(size, BYTE_LENGTH);
        _data = new byte[_alloc];
    }

    /**
     * Constructs a new ByteArray with the specified byte as its first byte in
     * the byte array
     * @param b The specified byte
     */
    public ByteArray(byte b) {
        this(1);
        _data[0] = b;
        _size = 1;
    }

    /**
     * Constructs a new ByteArray with the specified byte array as its contents
     * @param ba The specified byte array
     */
    public ByteArray(byte[] ba) {
        this(ba.length);
        System.arraycopy(ba, 0, _data, 0, ba.length);
        _size = ba.length;
    }

    /**
     * Constructs a new ByteArray with the specified byte array as its contents
     * @param ba The specified byte array
     */
    public ByteArray(byte[] ba, int length) {
        this(length);
        System.arraycopy(ba, 0, _data, 0, length);
        _size = length;
    }

    /**
     * Constructs a new ByteArray from another byte array
     * @param ba The specified byte array
     */
    public ByteArray(ByteArray ba) {
        this(ba.length());
        System.arraycopy(ba._data, 0, _data, 0, ba.length());
        _size = ba.length();
    }

    /**
     * Gets the size of this ByteArray
     * @return Returns the size of this ByteArray
     */
    public int length() {
        return _size;
    }

    /**
     * Sets value for the specified position
     * @param pos The specified position of the byte to be set
     * @param by The byte value
     * @throws throws ToolException if the position pos is invalid
     */
    public void set(int pos, byte by) throws ToolException {

        if (pos < 0 || pos >= _size) {
            throw new ToolException("[ByteArray::set]: Invalid array index :" +
                    pos);
        }

        _data[pos] = by;
    }

    /**
     * Gets the byte of the specified position
     * @param pos The specified position of the byte to be get
     * @return Returns the byte of the specified position
     * @throws throws ToolException if the position pos is invalid
     */
    public byte get(int pos) throws ToolException {

        if (pos < 0 || pos >= _size) {
            throw new ToolException("[ByteArray::get]: Invalid array index :" +
                    pos);
        }

        return _data[pos];
    }

    /**
     * 取ByteArray中保存的byte数组
     * @return 返回ByteArray中保存的byte数组
     */
    public byte[] get() {

        byte[] bytes = new byte[_size];

        System.arraycopy(_data, 0, bytes, 0, _size);

        return bytes;
    }

    /**
     * 取ByteArray中分配使用的Byte数组，该数组长度是内存分配时的长度，比使用length函数取得的
     * 长度要长。要使用实际的数组长度，请使用length函数配合本函数使用
     * @return 返回ByteArray中分配使用的Byte数组
     */
    public byte[] getAllocBytes() {
        return _data;
    }

    /**
     * Appends a byte to this ByteArray
     * @param b The byte to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(byte b) {

        int tLen = _size + 1;

        if (tLen >= _alloc) {
            _alloc = alloc(tLen, BYTE_LENGTH);

            // Memory Allocator for the byte
            byte[] ptr = new byte[_alloc];

            // Copy the old data to string
            System.arraycopy(_data, 0, ptr, 0, _size);
            _data = ptr;

        }

        _data[_size] = b;
        _size = tLen;

        return this;
    }

    /**
     * Appends a byte array to this ByteArray
     * @param ba The byte to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(byte[] ba) {
        return append(ba, 0, ba.length);
    }

    /**
     * Appends a byte array to this ByteArray
     * @param ba The byte to be appended
     * @param start the starting index of the byte to be appended.
     * @param len the length of the bytes to be appended.
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(byte[] ba, int start, int len) {

        int tLen = _size + len;

        if (tLen >= _alloc) {
            _alloc = alloc(tLen, BYTE_LENGTH);

            // Memory Allocator for the byte
            byte[] ptr = new byte[_alloc];

            // Copy the old data to string
            System.arraycopy(_data, 0, ptr, 0, _size);
            _data = ptr;

        }

        // Copy the new data to byte array
        System.arraycopy(ba, start, _data, _size, len);
        _size = tLen;

        return this;
    }

    /**
     * Appends a ByteArray to this ByteArray
     * @param baVal The String value to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(ByteArray baVal) {
        return append(baVal._data, 0, baVal._size);
    }

    /**
     * Appends String value to this ByteArray
     * @param sVal The String value to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(String sVal) {
        return append(sVal.getBytes());
    }

    /**
     * Tests whether the byte array is start with the given String
     *
     * @param start The begin index of the byte array
     * @param sVal The string to be tested
     * @return Return true if the byte array is begin with the given String
     */
    public boolean startsWith(int start, String sVal) {

        byte[] bVal = sVal.getBytes();

        if (start + bVal.length > _size) {
            return false;
        }

        for (int i = start, j = 0; j < bVal.length; j++, i++) {
            if (_data[i] != bVal[j]) {
                return false;
            }
        }

        return true;
    }

    /**
     * Appends a short value to this ByteArray
     * @param iVal The short value to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(short iVal) {
        return append(shortToBytes(iVal));
    }

    /**
     * Appends a Character to this ByteArray
     * @param ch The Character to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(char ch) {
        return append(charToBytes(ch));
    }

    /**
     * 将一个字符添加到ByteArray中，该字符可能占用一个字节，也可能占用两个字节。若是中文字符，
     * 则占用2个字节，西文字符占用一个
     * @param ch The Character to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray appendChar(char ch) {
        return append(Character.toString(ch));
    }

    /**
     * Appends an integer to this ByteArray
     * @param iVal The integer to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(int iVal) {

        return append(intToBytes(iVal));
    }

    /**
     * Appends a long value to this ByteArray
     * @param lVal The long value to be appended
     * @return Returns the reference of this ByteArray
     */
    public ByteArray append(long lVal) {

        return append(longToBytes(lVal));
    }

    /**
     * Removes the bytes in a sub byte array of this byte array.
     * The sub byte array begins at the specified <code>start</code> and extends to
     * the byte at index <code>end - 1</code> or to the end of the
     * sequence if no such byte exists. If
     * <code>start</code> is equal to <code>end</code>, no changes are made.
     *
     * @param      start  The beginning index, inclusive.
     * @param      end    The ending index, exclusive.
     * @return     The reference of this object.
     * @throws     StringIndexOutOfBoundsException  if <code>start</code>
     *             is negative, greater than <code>length()</code>, or
     *		   greater than <code>end</code>.
     */
    public ByteArray delete(int start, int end) {

        if (start < 0) {
            throw new StringIndexOutOfBoundsException(start);
        }

        if (end > _size) {
            end = _size;
        }

        if (start > end) {
            throw new StringIndexOutOfBoundsException();
        }

        int len = end - start;
        if (len > 0) {
            System.arraycopy(_data, start + len, _data, start, _size - end);
            _size -= len;
        }

        return this;
    }

    /**
     * Removes all bytes from the byte array
     * @return Returns the reference of this byte array
     */
    public ByteArray clear() {
        _size = 0;
        return this;
    }

    /**
     * Tests whether this ByteArray is equal to the given object
     * @return Returns true if this ByteArray is equal to the given object, or
     *         will return false
     */
    public boolean equals(Object o) {

        if (o == this) return true;

        if (o == null) return false;

        if (o instanceof ByteArray) {
            ByteArray ba = (ByteArray)o;

            if (ba._size != _size) return false;

            for (int i = 0; i < _size; i++) {
                if (ba._data[i] != _data[i]) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    /**
     * Parses from a string object to a byte array.
     * The string is formatted as HEX string like
     * 04 05 78 8e
     * @param s The string to be parsed
     * @return Returns the ByteArray parsed from the string
     */
    public final static ByteArray parse(String s) {

        byte[] tmp = new byte[3];
        int cur = 0;
        ByteArray ba = new ByteArray(s.length()/2);

        for (int i = 0; i < s.length(); i++) {

            if (!Character.isWhitespace(s.charAt(i))) {
                tmp[cur++] = (byte)Character.digit(s.charAt(i), 16);
                if (cur >= 2) {
                    ba.append((byte)((tmp[0] << 4) | tmp[1]));
                    cur = 0;
                    //memset(tmp, 0, sizeof(tmp));
                }
            } else if (cur > 0) {
                ba.append((byte)((tmp[0] << 4) | tmp[1]));
                cur = 0;
                //memset(tmp, 0, sizeof(tmp));
            }
        }

        return ba;
    }

    /**
     * 计算要分配的内存长度
     * @param alloc 期望分配的最小内存
     * @param extra 数据类型长度，例如对byte是1，对char是2
     * @return 返回实际应该分配的内存长度
     */
    protected final static int alloc(int alloc, int extra) {
        final int page = 1 << 12;
        int nalloc;

        alloc += extra;
        if (alloc < 1<<6) {
            nalloc = (1<<3) + ((alloc >>3) << 3);
        } else  {
            nalloc = (alloc < page) ? 1<<3 : page;
            while (nalloc < alloc)
                nalloc *= 2;
        }
        return nalloc - extra;
    }

    /**
     * 将byte数组转换成character值
     *
     * @param bytes 要转换的byte数组
     * @return 返回转换的character值
     */
    public final static short bytesToShort(byte[] bytes) throws ToolException {

        return bytesToShort(bytes, 0);
    }

    /**
     * 将byte数组转换成character值
     *
     * @param bytes 要转换的byte数组
     * @param start the starting index of the byte to be appended.
     * @return 返回转换的character值
     */
    public final static short bytesToShort(byte[] bytes, int start) throws ToolException {

        if (bytes.length < start + 2) {
            throw new ToolException(
                    "bytesToShort error: the length of the bytes is less than " +
                            (start + 2));
        }

        short value;

        value = (short)((bytes[start++] & 0xFF) << 8);
        value |= (bytes[start++]) & 0xFF;

        return value;
    }

    /**
     * 将short值转换成byte数组
     *
     * @param sVal short类型的值
     * @return 返回转换的byte数组
     */
    public final static byte[] shortToBytes(short sVal) {

        //byte[] ba = new byte[Short.SIZE/8];
        byte[] ba = new byte[2];

        ba[0] = (byte)((sVal >> 8) & 0xFF);
        ba[1] = (byte)(sVal & 0xFF);

        return ba;
    }

    /**
     * 将byte数组转换成character值
     *
     * @param bytes 要转换的byte数组
     * @return 返回转换的character值
     */
    public final static char bytesToChar(byte[] bytes) throws ToolException {

        return bytesToChar(bytes, 0);
    }

    /**
     * 将byte数组转换成character值
     *
     * @param bytes 要转换的byte数组
     * @param start the starting index of the byte to be appended.
     * @return 返回转换的character值
     */
    public final static char bytesToChar(byte[] bytes, int start) throws ToolException {

        if (bytes.length < start + 2) {
            throw new ToolException(
                    "bytesToChar error: the length of the bytes is less than " + (start + 2));
        }

        char value;

        value = (char)((bytes[start++] & 0xFF) << 8);
        value |= (bytes[start++]) & 0xFF;

        return value;
    }

    /**
     * 将character值转换成byte数组
     *
     * @param ch character类型的值
     * @return 返回转换的byte数组
     */
    public final static byte[] charToBytes(char ch) {

        //byte[] ba = new byte[Character.SIZE/8];
        byte[] ba = new byte[2];

        ba[0] = (byte)((ch >> 8) & 0xFF);
        ba[1] = (byte)(ch & 0xFF);

        return ba;
    }

    /**
     * 将byte数组转换成int值
     *
     * @param bytes 要转换的byte数组
     * @return 返回转换的int值
     */
    public final static int bytesToInt(byte[] bytes) throws ToolException {

        return bytesToInt(bytes, 0);
    }

    /**
     * 将byte数组转换成int值
     *
     * @param bytes 要转换的byte数组
     * @param start the starting index of the byte to be appended.
     * @return 返回转换的int值
     */
    public final static int bytesToInt(byte[] bytes, int start) throws ToolException {

        if (bytes.length < start + 4) {
            throw new ToolException(
                    "bytesToInt error: the length of the bytes is less than " +
                            (start + 4));
        }

        int value;

        value = (bytes[start++] & 0xFF) << 24;
        value |= ((bytes[start++] & 0xFF) << 16);
        value |= ((bytes[start++] & 0xFF) << 8);
        value |= (bytes[start++]) & 0xFF;

        return value;
    }

    /**
     * 将byte数组转换成int值,注意此处的int是指三个字节长度的，将再此对这种情况做特殊处理
     *
     * @param bytes 要转换的byte数组
     * @param start the starting index of the byte to be appended.
     * @param len int类型的长度，要小于等于4
     * @return 返回转换的int值
     */
    public final static int bytesToInt(byte[] bytes, int start, int len) throws ToolException {

        if (bytes.length < start + len) {
            throw new ToolException(
                    "bytesToInt error: the length of the bytes is less than " +
                            (start + len));
        }

        int value;
        int length = len - 1;

        value = ((bytes[start++] & 0xFF) << length * 8);

        for (int i = length - 1; i >= 0; i--) {
            value |= ((bytes[start++] & 0xFF) << i * 8);
        }

        return value;
    }

    /**
     * 将int值转换成byte数组
     *
     * @param iVal int类型的值
     * @return 返回转换的byte数组
     */
    public final static byte[] intToBytes(int iVal) {

        //byte[] ba = new byte[Integer.SIZE/8];

        byte[] ba = new byte[4];

        ba[0] = (byte)((iVal >> 24) & 0xFF);
        ba[1] = (byte)((iVal >> 16) & 0xFF);
        ba[2] = (byte)((iVal >> 8) & 0xFF);
        ba[3] = (byte)(iVal & 0xFF);

        return ba;
    }

    /**
     * 将int值转换成byte数组，此处的int为三个字节长度
     *
     * @param iVal int 类型的值
     * @param len 将被转化的 int 类型的长度，此处为特殊处理，因为在某些情况下，也可能将三个
     *  字节的数声明为 int 型
     * @return 返回转换的byte数组
     */
    public final static byte[] intToBytes(int iVal, int len) {

        byte[] ba = new byte[len];

        for (int i = 0, j = len - 1; i < len && j >= 0; i++, j--) {
            ba[i] = (byte)((iVal >> (8 * j)) & 0xFF);
        }

        return ba;
    }

    /**
     * 将byte数组转换成long值
     *
     * @param bytes 要转换的byte数组
     * @return 返回转换的long值
     */
    public final static long bytesToLong(byte[] bytes) throws ToolException {

        return bytesToLong(bytes, 0);
    }

    /**
     * 将byte数组转换成long值
     *
     * @param bytes 要转换的byte数组
     * @param start the starting index of the byte to be appended.
     * @return 返回转换的long值
     */
    public final static long bytesToLong(byte[] bytes, int start) throws ToolException {

        if (bytes.length < start + 8) {
            throw new ToolException(
                    "bytesToLong error: the length of the bytes is less than " +
                            (start + 8));
        }

        long value;

        value = ((long)bytes[start++] & 0xFF) << 56;
        value |= ((long)(bytes[start++] & 0xFF) << 48);
        value |= ((long)(bytes[start++] & 0xFF) << 40);
        value |= ((long)(bytes[start++] & 0xFF) << 32);
        value |= ((long)(bytes[start++] & 0xFF) << 24);
        value |= ((long)(bytes[start++] & 0xFF) << 16);
        value |= ((long)(bytes[start++] & 0xFF) << 8);
        value |= ((long)bytes[start++]) & 0xFF;

        return value;
    }

    /**
     * 将long值转换成byte数组
     *
     * @param lVal long类型的值
     * @return 返回转换的byte数组
     */
    public final static byte[] longToBytes(long lVal) {

        //byte[] ba = new byte[Long.SIZE/8];
        byte[] ba = new byte[8];

        ba[0] = (byte)((lVal >> 56) & 0xFF);
        ba[1] = (byte)((lVal >> 48) & 0xFF);
        ba[2] = (byte)((lVal >> 40) & 0xFF);
        ba[3] = (byte)((lVal >> 32) & 0xFF);
        ba[4] = (byte)((lVal >> 24) & 0xFF);
        ba[5] = (byte)((lVal >> 16) & 0xFF);
        ba[6] = (byte)((lVal >> 8) & 0xFF);
        ba[7] = (byte)(lVal & 0xFF);

        return ba;
    }

    /**
     * Tests whether the byte array is start with the given String
     *
     * @param bytes The byte array
     * @param start The begin index of the byte array
     * @param length The total length of the byte array
     * @param sVal The string to be tested
     * @return Return true if the byte array is begin with the given String
     */
    public static boolean startsWith(byte[] bytes, int start, int length, String sVal) {

        byte[] bVal = sVal.getBytes();

        if (start + bVal.length > length) {
            return false;
        }

        for (int i = start, j = 0; j < bVal.length; j++, i++) {
            if (bytes[i] != bVal[j]) {
                return false;
            }
        }

        return true;
    }

    /**
     * Returns the index within this string of the first occurrence of the
     * specified substring, starting at the specified index.
     *
     * @param bytes The byte array
     * @param start The begin index of the byte array
     * @param length The total length of the byte array
     * @param subbytes The sub bytes for which to search
     * @return The index within this bytes of the first occurrence of the
     *         specified sub bytes, starting at the specified index. If
     *         no such value of sub bytes exists, then -1 is returned
     */
    public static int indexOf(byte[] bytes, int start, int length, byte[] subbytes) {

        int idx = -1;

        if (start + subbytes.length > length) {
            return idx;
        }

        if (subbytes.length == 0) return 0;

        int j = 0;
        int i = start;
        byte curByte = subbytes[j++];

        for (i = start; i < length; i++) {
            if (curByte != bytes[i]) {
                idx = -1;
                j = 0;
                curByte = subbytes[j++];
                continue;
            }

            if (idx == -1) {
                idx = i;
            }
            if (j >= subbytes.length) {
                break;
            }
            curByte = subbytes[j++];
        }

        if (i == length && j != subbytes.length - 1) {
            return -1;
        }

        return idx;
    }

    /**
     * 将byte数组按照分割符号by分割，并返回分割后的byte数组列表
     * @param bytes 要分割的数组
     * @param start 数组的起始位置
     * @param length 数组的总长度
     * @param by 分割符号
     * @return 返回分割后的byte数组列表
     */
    public static ArrayList<byte[]> split(byte[] bytes, int start,
                                          int length, byte by) {

        ArrayList<byte[]> result = new ArrayList<byte[]>();
        ByteArray baTmp = new ByteArray();

        for (int i = start; i < length; i++) {
            byte curBy = bytes[i];

            if (curBy == by) {
                result.add(baTmp.get());
                baTmp.clear();
                continue;
            }

            baTmp.append(curBy);
        }

        if (baTmp.length() > 0) {
            result.add(baTmp.get());
        }

        return result;
    }

    /**
     * 将byte数组按照分割符号by分割，并返回分割后的字符串列表
     * @param bytes 要分割的数组
     * @param start 数组的起始位置
     * @param length 数组的总长度
     * @param by 分割符号
     * @return 返回分割后的字符串列表
     */
    public static ArrayList<String> split2String(byte[] bytes, int start,
                                                 int length, byte by) {

        ArrayList<String> result = new ArrayList<String>();
        ByteArray baTmp = new ByteArray();

        for (int i = start; i < length; i++) {
            byte curBy = bytes[i];

            if (curBy == by) {
                result.add(baTmp.toString());
                baTmp.clear();
                continue;
            }

            baTmp.append(curBy);
        }

        if (baTmp.length() > 0) {
            result.add(baTmp.toString());
        }

        return result;
    }

    /**
     * 将byte数组按照分割符号by分割，并返回分割后的字符串列表
     * @param bytes 要分割的数组
     * @param start 数组的起始位置
     * @param length 数组的总长度
     * @param by 分割符号
     * @param ignoreTail 是否忽略结尾的分割符
     * @return 返回分割后的字符串列表
     */
    public static ArrayList<String> split2String(byte[] bytes, int start,
                                                 int length, byte by, boolean ignoreTail) {

        ArrayList<String> result = new ArrayList<String>();
        ByteArray baTmp = new ByteArray();

        for (int i = start; i < length; i++) {
            byte curBy = bytes[i];

            if (curBy == by) {
                result.add(baTmp.toString());
                baTmp.clear();
                continue;
            }

            baTmp.append(curBy);
        }

        if (baTmp.length() > 0 || !ignoreTail) {
            result.add(baTmp.toString());
        }

        return result;
    }

    /*
     * (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    public String toString() {
        return new String(_data, 0, _size);
    }

    /**
     * 将byte数组转换成供打印的十六进制字符串
     *
     * @param bytes 要打印的byte数组
     */
    public static String bytesToPrintable(byte[] bytes) {
        return bytesToPrintable(bytes, 16);
    }

    /**
     * 将byte数组转换成供打印的十六进制字符串
     *
     * @param bytes 要打印的byte数组
     * @param column 每行打印的列数
     */
    public static String bytesToPrintable(byte[] bytes, int column) {
        return bytesToPrintable(bytes, 0, bytes.length, column);
    }

    /**
     * 将byte数组转换成供打印的十六进制字符串
     *
     * @param bytes 要打印的byte数组
     * @param offset 要打印的数组的起始字节索引
     * @param length 要打印的数组中字节的总长度
     */
    public static String bytesToPrintable(byte[] bytes, int offset,
                                          int length) {
        return bytesToPrintable(bytes, offset, length, 16);
    }

    /**
     * 将byte数组转换成供打印的十六进制字符串
     *
     * @param bytes 要打印的byte数组
     * @param offset 要打印的数组的起始字节索引
     * @param length 要打印的数组中字节的总长度
     * @param column 每行打印的列数
     */
    public static String bytesToPrintable(byte[] bytes, int offset,
                                          int length, int column) {

        char hexDigits[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'a', 'b', 'c', 'd', 'e', 'f'
        };
        StringBuffer ss = new StringBuffer();
        StringBuffer sText = new StringBuffer();
        int end = offset + length;
        int cols = 0;
        int half;
        int i;
        int j;

        if (end > bytes.length) {
            end = bytes.length;
        }

        if (column <= 0) {
            column = 8;
        }

        if (column%2 != 0) {
            column++;
        }

        half = column/2;

        ss.append("0000   ");

        for (i = offset, j = 0; i < end; i++, j++) {
            ss.append(hexDigits[(bytes[i] >> 4) & 0xF]);
            ss.append(hexDigits[bytes[i] & 0xF]);
            ss.append(" ");

            if (bytes[i] >= 32 && bytes[i] < 127) {
                sText.append((char)bytes[i]);
            } else {
                sText.append('.');
            }

            if ((j + 1)%column == 0) {
                ss.append("  ");
                ss.append(sText);
                ss.append("\n");
                cols += column;
                ss.append(hexDigits[(cols >> 12) & 0xF]);
                ss.append(hexDigits[(cols >> 8) & 0xF]);
                ss.append(hexDigits[(cols >> 4) & 0xF]);
                ss.append(hexDigits[cols & 0xF]);
                ss.append("   ");
                sText.delete(0, sText.length());
                continue;
            }

            if ((j + 1)%half == 0) {
                ss.append(" ");
                sText.append(" ");
            }
        }

        if (sText.length() > 0) {
            int num = j%column;
            int spaces;

            if (num < half) {
                spaces = (column - num)*3 + 3;
            } else {
                spaces = (column - num)*3 + 2;
            }
            for (i = 0; i < spaces; i++) {
                ss.append(" ");
            }
            ss.append(sText);
        }

        return ss.toString();
    }

    /**
     * 将byte数组转换成十六进制字符串
     */
    public static String bytesToHexStr(byte[] bytes) {
        return bytesToHexStr(bytes, 0, bytes.length);
    }

    /**
     * 将byte数组转换成十六进制字符串
     */
    public static String bytesToHexStr(byte[] bytes, int offset, int length) {

        char hexDigits[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'a', 'b', 'c', 'd', 'e', 'f'
        };

        StringBuilder ss = new StringBuilder();
        int end = offset + length;

        if (end > bytes.length) {
            end = bytes.length;
        }

        for (int i = offset; i < end; i++) {
            ss.append(hexDigits[(bytes[i] >> 4) & 0xF]);
            ss.append(hexDigits[bytes[i] & 0xF]);
        }

        return ss.toString();
    }

    /**
     * 将16进制字符转换成数字
     *
     * @param ch 16进制字符
     * @return 返回转换后的数字
     */
    public static int toDigit(char ch) throws ToolException {
        switch (ch) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return ch - '0';
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                return ch - 'a' + 10;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                return ch - 'A' + 10;
            default:
                throw new ToolException("The character '" + ch +
                        "' is not a hex character");
        }
    }

    /**
     * 将16进制的字符串转换成byte数组，不足数组长度的以0不齐
     *
     * @param hexStr 要转换的16进制字符串
     * @param bytes 用来保存转换后的byte的数组
     */
    public static void hexStrToBytes(String hexStr, byte[] bytes) throws ToolException {
        int i;
        int j = hexStr.length() - 1;
        char hi = '0';
        char lo = '0';

        for (i = bytes.length - 1; i >= 0; i--) {
            lo = hexStr.charAt(j--);
            if (j < 0) {
                hi = '0';
                break;
            }
            hi = hexStr.charAt(j--);
            if (j < 0) {
                break;
            }
            bytes[i] = (byte)(((toDigit(hi) & 0xF) << 4) | (toDigit(lo) & 0xF));
        }

        bytes[i--] = (byte)(((toDigit(hi) & 0xF) << 4) | (toDigit(lo) & 0xF));

        while (i >= 0) {
            bytes[i--] = 0;
        }
    }

    public static byte[] hexStrToBytes(String hexStr) throws ToolException {
        byte[] bytes;

        if (hexStr.length()%2 == 0) {
            bytes = new byte[hexStr.length()/2];
        } else {
            bytes = new byte[hexStr.length()/2 + 1];
        }

        hexStrToBytes(hexStr, bytes);

        return bytes;
    }

//	/**
//	 * The below method is used for testing
//	 * @param args
//	 */
//	public static void main(String[] args) throws Exception {
//	    byte[] a = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, (byte)0xe8};
//	    long b = bytesToLong(a, 0);
//	    System.out.println(String.valueOf(bytesToLong(a, 0)));
//
//	    byte[] a = intToBytes(1000, 3);
//	    for (int i = 0; i < a.length; i++) {
//	        System.out.println(a[i]);
//	    }
//
//       try {
//
//            int b = bytesToInt(a, 0, 3);
//            System.out.println(b);
//        } catch (ToolException t) {
//            System.out.println("error");
//        }
//		ByteArray ba1 = new ByteArray();
//		ByteArray ba2 = null;
//
//		if (ba1.equals(ba2)) {
//			System.err.println("Error1, ba1 is equals to null");
//			System.exit(0);
//		}
//
//		ba2 = new ByteArray(34);
//		if (!ba1.equals(ba2)) {
//			System.err.println("Error2, ba1 is not equals to ba2");
//			System.exit(0);
//		}
//
//		ba1.append((byte)0x89);
//		ba1.append((byte)0x91);
//		ba1.append((byte)0x45);
//
//		ba2.append((byte)0x89);
//		ba2.append((byte)0x91);
//		ba2.append((byte)0x95);
//		ba2.append((byte)0x65);
//		ba2.append((byte)0x45);
//		//ba2.append(95);
//
//		if (ba1.equals(ba2)) {
//			System.err.println("Error3, ba1 is equals to ba2");
//			System.exit(0);
//		}
//
//		ba2.delete(2, 4);
//		if (!ba1.equals(ba2)) {
//			System.err.println("Error4, ba1 is not equals to ba2");
//			System.exit(0);
//		}
//
//		System.out.println("Ok, all test for ByteArray is passed!!!");
//
//		ByteArray sba = new ByteArray();
//		sba.append("123HTTP/1.1!");
//		System.out.println(sba.startsWith(3, "HTTP"));
//
//		ByteArray stx = new ByteArray();
//		stx.append("123");
//		stx.append((byte)0x78);
//		stx.append((byte)0x00);
//		stx.append("worker man!!!!");
//		stx.append("--NextPart_000_0028_01C19839.84698430d");
//		//stx.append("fff");
//
//		System.out.println(ByteArray.indexOf(stx.getAllocBytes(),
//			10, stx.length(), "e".getBytes()));
//
//		System.out.println("01234".indexOf("234"));
//	}
}
