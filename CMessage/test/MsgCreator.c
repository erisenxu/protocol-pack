
#include "MsgCreator.h"

#include "comm/BaseFuncDef.h"

LPFIELD msg_parser(LPTESTMSGCREATOR pstTestMsgCreator, const char* szMsgBuf, int iMsgLen)
{
    if (NULL == pstTestMsgCreator || NULL == szMsgBuf || iMsgLen < sizeof(pstTestMsgCreator->nMsgType)) return NULL;

    /* Get message type */
    M_CHAR_TO_U16(pstTestMsgCreator->nMsgType, szMsgBuf);

    switch (pstTestMsgCreator->nMsgType)
    {
    case MSG_TEST_REQ:
        {
            LPFIELD pstField = (LPFIELD)&pstTestMsgCreator->stMsgData.stTestReq;
            init_field(pstField, &g_stTestReqFieldInfo, "testReq", pstTestMsgCreator->nMsgType, 1);
            if (field_decode(pstField, szMsgBuf, iMsgLen) != 0) return NULL;
            return pstField;
        }
        break;
    case MSG_TEST_REQ2:
        {
            LPFIELD pstField = (LPFIELD)&pstTestMsgCreator->stMsgData.stTestReq2;
            init_field(pstField, &g_stTestReq2FieldInfo, "testReq2", pstTestMsgCreator->nMsgType, 1);
            if (field_decode(pstField, szMsgBuf, iMsgLen) != 0) return NULL;
            return pstField;
        }
        break;
    }

    return NULL;
}

