/*
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

#include <stdio.h>

#include "field/IntField.h"
#include "field/ArrayField.h"
#include "test/TestMsg2.h"
#include "test/TestUnion3.h"

#include <string.h>

void testIntFieldEncode()
{
    INTFIELD stIntField;
    char szMsg[256];
    BYTEARRAY stByteArray;

    char szOut[256];
    BYTEARRAY stBuf;

    INIT_BYTE_ARRAY(stByteArray, szMsg, sizeof(szMsg));
    INIT_BYTE_ARRAY(stBuf, szOut, sizeof(szOut));

    init_int_field(&stIntField, "test", 1, NULL, 1, 0x123456);

    field_encode(&stIntField, &stByteArray, 1);

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);
}

void testArrayFieldEncode()
{
    U16 nFieldNum = 0;
    INTFIELD astIntField[32];
    ARRAYFIELD stArrField;

    char szMsg[256];
    BYTEARRAY stByteArray;

    char szOut[256];
    BYTEARRAY stBuf;

    INIT_BYTE_ARRAY(stByteArray, szMsg, sizeof(szMsg));
    INIT_BYTE_ARRAY(stBuf, szOut, sizeof(szOut));

    init_array_field(&stArrField, &g_stIntFieldInfo, "array", 2, NULL, 1, (char*)astIntField, &nFieldNum, sizeof(astIntField[0]), 256);

    astIntField[nFieldNum].iValue = 0x123456;
    nFieldNum++;

    astIntField[nFieldNum].iValue = 0x789012;
    nFieldNum++;

    field_encode(&stArrField, &stByteArray, 1);

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);
}

void testTestMsg()
{
    char szMsg[1024];
    BYTEARRAY stByteArray;

    char szOut[1024];
    BYTEARRAY stBuf;

    TESTMSG stTestMsg;
    TESTMSG stTestMsg2;

    int i;

    INIT_BYTE_ARRAY(stByteArray, szMsg, sizeof(szMsg));
    INIT_BYTE_ARRAY(stBuf, szOut, sizeof(szOut));

    init_field((LPFIELD)&stTestMsg, &g_stTestMsgFieldInfo, "Test", 1, NULL, 1);
    stTestMsg.stMoney.iValue = 0x870921;
    stTestMsg.stGold.iValue = 0x214365;

    stTestMsg.astIntField[stTestMsg.nIntFieldNum].iValue = 0x343536;
    stTestMsg.nIntFieldNum++;

    stTestMsg.astIntField[stTestMsg.nIntFieldNum].iValue = 0x373839;
    stTestMsg.nIntFieldNum++;

    stTestMsg.astIntField[stTestMsg.nIntFieldNum].iValue = 0x404142;
    stTestMsg.nIntFieldNum++;

    field_encode(&stTestMsg, &stByteArray, 1);

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);

    init_field((LPFIELD)&stTestMsg2, &g_stTestMsgFieldInfo, "Test2", 2, NULL, 1);
    field_decode(&stTestMsg2, stByteArray.pszData, stByteArray.dwLen);

    printf("money=0x%x, gold=0x%x, arrNum=%d\n", stTestMsg2.stMoney.iValue, stTestMsg2.stGold.iValue, stTestMsg2.nIntFieldNum);

    for (i = 0; i < stTestMsg2.nIntFieldNum; i++)
    {
        printf("%d=0x%x ", i + 1, stTestMsg2.astIntField[i].iValue);
    }
    printf("\n");
}

void testTestMsg2()
{
    char szMsg[256];
    BYTEARRAY stByteArray;

    char szOut[1024];
    BYTEARRAY stBuf;

    TESTMSG2 stTestMsg;
    TESTMSG2 stTestMsg2;
    int i;
    int j;

    INIT_BYTE_ARRAY(stByteArray, szMsg, sizeof(szMsg));
    INIT_BYTE_ARRAY(stBuf, szOut, sizeof(szOut));

    memset(&stTestMsg, 0, sizeof(stTestMsg));
    init_field((LPFIELD)&stTestMsg, &g_stTestMsg2FieldInfo, "Test", 2, NULL, 1);

    stTestMsg.nTestMsgNum = 0;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].stMoney.iValue = 0x870921;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].stGold.iValue = 0x214365;
    //stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum = 0;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].astIntField[stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum].iValue = 0x505152;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum++;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].astIntField[stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum].iValue = 0x606162;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum++;
    stTestMsg.nTestMsgNum++;

    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].stMoney.iValue = 0x242325;
    stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].stGold.iValue = 0x121314;
    //stTestMsg.astTestMsg[stTestMsg.nTestMsgNum].nIntFieldNum = 0;
    stTestMsg.nTestMsgNum++;

    //stTestMsg.nIntFieldNum = 0;
    stTestMsg.astIntField[stTestMsg.nIntFieldNum].iValue = 0x343536;
    stTestMsg.nIntFieldNum++;

    field_encode(&stTestMsg, &stByteArray, 1);

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);

    init_field((LPFIELD)&stTestMsg2, &g_stTestMsg2FieldInfo, "Test2", 2, NULL, 1);
    field_decode(&stTestMsg2, stByteArray.pszData, stByteArray.dwLen);

    for (i = 0; i < stTestMsg2.nTestMsgNum; i++)
    {
        printf("money=0x%x, gold=0x%x, ", stTestMsg2.astTestMsg[i].stMoney.iValue, stTestMsg2.astTestMsg[i].stGold.iValue);

        for (j = 0; j < stTestMsg2.astTestMsg[i].nIntFieldNum; j++)
        {
            printf("%d=0x%x ", j + 1, stTestMsg2.astTestMsg[i].astIntField[j].iValue);
        }
        printf("\n");
    }

    for (i = 0; i < stTestMsg2.nIntFieldNum; i++)
    {
        printf("%d=0x%x ", i + 1, stTestMsg2.astIntField[i].iValue);
    }
    printf("\n");

    stByteArray.dwLen = 0;
    stBuf.dwLen = 0;

    field_encode(&stTestMsg2, &stByteArray, 1);

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);
}

void testUnion()
{
    TESTUNION3 stUnion3;

    memset(&stUnion3, 0, sizeof(stUnion3));
    init_field((LPFIELD)&stUnion3, &g_stTestUnion3FieldInfo, "Test", 2, NULL, 1);

    stUnion3.stReason.iValue = 1;
    stUnion3.stReason2.iValue = 2;
    stUnion3.stUnion2.stReason.iValue = 3;
    stUnion3.stUnion2.stUnion.stSelection.nValue = 3;
    stUnion3.stUnion2.stUnion.stTestMsg.nIntFieldNum = 0;
    stUnion3.stUnion2.stUnion.stTestMsg.stGold.iValue = 4;

    // 编码测试
    char szMsg[256];
    BYTEARRAY stByteArray;
    INIT_BYTE_ARRAY(stByteArray, szMsg, sizeof(szMsg));

    field_encode(&stUnion3, &stByteArray, 1);

    char szOut[8192];
    BYTEARRAY stBuf;
    INIT_BYTE_ARRAY(stBuf, szOut, sizeof(szOut));

    bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", stBuf.pszData);

    // 格式化测试
    bytearray_clear(&stBuf);
    field_format(&stUnion3, &stBuf, "", 1);
    //bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", byte_array_to_string(&stBuf));

    // to xml测试
    bytearray_clear(&stBuf);
    field_toxml(&stUnion3, &stBuf, "", 1);
    //bytes_to_printable(&stBuf, stByteArray.pszData, stByteArray.dwLen, 0, -1, 16);

    printf("%s\n", byte_array_to_string(&stBuf));

    // 解码测试
    char szMsgDecode[256];
    memcpy(szMsgDecode, szMsg, sizeof(szMsgDecode));
    TESTUNION3 stUnion4;
    init_field((LPFIELD)&stUnion4, &g_stTestUnion3FieldInfo, "Test", 2, NULL, 1);
    field_decode(&stUnion4, szMsg, stByteArray.dwLen);

    // 格式化测试
    bytearray_clear(&stBuf);
    field_format(&stUnion4, &stBuf, "", 1);
    printf("%s\n", byte_array_to_string(&stBuf));

    // 以下为兼容性测试，将Union的selection修改为0x05，看能否被作为不认识的字段而被丢弃？
    szMsg[39] = (U8)0x05;
    TESTUNION3 stUnion5;
    init_field((LPFIELD)&stUnion5, &g_stTestUnion3FieldInfo, "Test", 2, NULL, 1);
    field_decode(&stUnion5, szMsg, stByteArray.dwLen);

    // 格式化测试
    bytearray_clear(&stBuf);
    field_format(&stUnion5, &stBuf, "", 1);
    printf("%s\n", byte_array_to_string(&stBuf));
}

int main()
{
    //testIntFieldEncode();
    //testArrayFieldEncode();
    //testTestMsg();
    //testTestMsg2();
    testUnion();

    return 0;
}

