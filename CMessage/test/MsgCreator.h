
#ifndef TEST_MSG_CREATOR
#define TEST_MSG_CREATOR

#include "TestReq.h"
#include "TestReq2.h"

union tagTestMsgGroup
{
    TESTREQ stTestReq;
    TESTREQ2 stTestReq2;
};

typedef union tagTestMsgGroup   TESTMSGGROUP;
typedef union tagTestMsgGroup*  LPTESTMSGGROUP;

struct tagTestMsgCreator
{
    U16 nMsgType;
    TESTMSGGROUP stMsgData;
};

typedef struct tagTestMsgCreator    TESTMSGCREATOR;
typedef struct tagTestMsgCreator*   LPTESTMSGCREATOR;

#ifdef __cplusplus
extern "C"
{
#endif

LPFIELD msg_parser(LPTESTMSGCREATOR pstTestMsgCreator, const char* szMsgBuf, int iMsgLen);

#ifdef __cplusplus
}
#endif

#endif

