/**
 * @(#) MByteArray.h 字节数组对象，一般用于消息编码解码
 *
 * @author Erisen Xu
 * @version 1.0
 * @history 2010-12-19 ErisenXu 创建文件
 */

#ifndef MBYTE_ARRAY_H
#define MBYTE_ARRAY_H

#include "MBaseDef.h"
#include <string>

using namespace std;

class M_DLLIMPORT MByteArray
{
protected:
    int m_nSize;    // 数组总大小
    int m_nLen;     // 数据总大小
    char* m_szData; // 数据信息

public:
    /**
     * 构造函数
     * @param nSize 数组预分配大小
     */
    MByteArray(int nSize = 0);

    /**
     * 构造函数
     * @param szValue 添加到数组的字符串，字符串需以'\0'结尾
     */
    MByteArray(const char* szValue);

    /**
     * 构造函数
     * @param szValue 添加到数组的byte字符串
     * @param nLen 字符长度
     */
    MByteArray(const char* szValue, int nLen);

    /**
     * 拷贝构造函数
     */
    MByteArray(const MByteArray& baValue);

    /**
     * 析构函数
     */
    ~MByteArray();

    /**
     * 返回数据长度
     * @return 返回数据长度
     */
    int getLength() const {return m_nLen;}

    /**
     * 返回数据
     * @return 返回数据
     */
    char* getData() const {return m_szData;}

    /**
     * 将字符添加到数组
     * @param nVal 要添加到数组的字符
     */
    MByteArray& append(U8 nVal);

    /**
     * 将字符添加到数组
     * @param iVal 要添加到数组的字符
     */
    MByteArray& append(S8 iVal) {return append((U8)iVal);}

    /**
     * 将整数添加到数组
     * @param nVal 要添加到数组的整数
     */
    MByteArray& append(U16 nVal);

    /**
     * 将整数添加到数组
     * @param iVal 要添加到数组的整数
     */
    MByteArray& append(S16 iVal) {return append((U16)iVal);}

    /**
     * 将整数添加到数组
     * @param nVal 要添加到数组的整数
     */
    MByteArray& append(U32 nVal);

    /**
     * 将整数添加到数组
     * @param iVal 要添加到数组的整数
     */
    MByteArray& append(S32 iVal) {return append((U32)iVal);}

    /**
     * 将整数添加到数组
     * @param ulVal 要添加到数组的整数
     */
    MByteArray& append(U64 ulVal);
    
    /**
     * 将整数添加到数组
     * @param lVal 要添加到数组的整数
     */
    MByteArray& append(S64 lVal) {return append((U64)lVal);}

    /**
     * 将字符串添加到数组，字符串需以'\0'结尾
     * @param szVal 要添加到数组的字符串
     */
//    MByteArray& Append(const char* szVal);

    /**
     * 将字符串添加到数组
     * @param szVal 要添加到数组的字符串
     * @param nLen 字符串长度
     */
    MByteArray& append(const char* szVal, int nLen);

    /**
     * 将字符串添加到数组
     * @param sVal 要添加到数组的字符串
     */
    MByteArray& append(const string& sVal) {return append(sVal.c_str(), (int)sVal.size());}

    /**
     * 清空所有数据
     */
    void clear();

    /**
     * 返回字符串
     * @return 返回字符串
     */
    const char* toString();

    /**
     * 将字节数组转换成供打印的十六进制字符串
     * 
     * @param baBuf 用来保存数据的数组
     * @param szBytes 要打印的字节数组
     * @param nBufLen 字节数组szBytes的总长度
     * @param nOffset 要打印的数组的起始字节索引
     * @param nLength 要打印的数组中字节的总长度，若nLength=-1，则转换所有字节
     * @param nColumn 每行打印的列数
     */
    static void bytesToPrintable(MByteArray& baBuf, const char* szBytes,
        int nBufLen, int nOffset = 0, int nLength = -1, int nColumn = 16);

    /**
     * 将字节数组转成字符串，不可见字符以.表示
     * @param baBuf 用来保存数据的数组
     * @param szBytes 要打印的字节数组
     * @param nBufLen 字节数组szBytes的总长度
     * @param nOffset 要打印的数组的起始字节索引
     * @param nLength 要打印的数组中字节的总长度，若nLength=-1，则转换所有字节
     */
    static void bytesToStr(MByteArray& baBuf, const char* szBytes,
        int nBufLen, int nOffset = 0, int nLength = -1);

    /**
     * 将字节数组转换成十六进制字符串
     * @param baBuf 用来保存转换后的数据的数组
     * @param szBytes 被转换的字节数组
     * @param nBufLen 字节数组长度
     * @param nOffset 数组的起始字节索引
     */
    static void bytesToHexStr(MByteArray& baBuf, const char* szBytes,
        int nBufLen, int nOffset = 0);

    /**
     * 将十六进制字符串转换成字节数组
     * @param baBuf 用来保存转换后的数据的数组
     * @param szHexStr 被转换的十六进制字符串数据
     */
    static void hexStrToBytes(MByteArray& baBuf, const char* szHexStr);

    /**
     * 将十六进制字符转换成整数
     * @param chHex 被转换的十六进制字符
     */
    static U8 hexCharToInt(char chHex);

protected:
    /**
     * 扩充缓冲区大小
     * @param nSize 需要增加的缓冲区大小
     */
    void expand(int nSize);
};

#endif
