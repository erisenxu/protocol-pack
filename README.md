Protocol-Pack简介
=============

Protocol-Pack(以下简称PP)是和google的Protocol Buffer(简称PB)类似的一种二进制数据交换的格式。它采用TT(L)V（即Tag-Type-Length-Value）的格式对数据信息进行编码，具有向前、向后兼容的特性。PP提供了多种语言的实现：C、C++、Java、Object-C，每种实现都尽量追求极简的编码风格，简单、干净、容易理解。<p>

PP可以用于客户端与服务器之间的数据交换，也可以用于读、写配置文件，PP的几种语言的实现均提供了将数据结构或对象编码为XML格式的字符串的功能，C、C++的实现还提供了处理(或解码)XML元素数据的功能函数，读取XML配置文件的功能可以结合CXmlLoader和XmlLoader这两个项目来实现。

Protocol-Pack特点
=============
1. PP采用xml格式定义数据结构或对象，然后通过代码生成器生成的代码读写数据结构或对象。目前代码生成器可以生成C、C++、Java、Object-C这几种语言的代码。<p>
2. PP支持Union、Struct数据结构，还支持enum数据结构，支持采用marco定义宏或常量，支持数组等。PP支持的数据结构详情请见下面章节。<p>
3. PP的每种语言的实现均提供encode、decode、format、toXml这4个函数，其中encode函数将Union或Struct数据结构编码为二进制数据(大端序/网络序)；decode函数将二进制数据解码为Union或Struct数据结构；format函数将数据结构编码为可读字符串，一般用于日志打印；toXml函数将数据结构编码为xml格式的字符串。<p>
4. 一般地，PP采用TTLV的格式对数据结构进行编码，但是针对数字类型的数据(比如32位整数)，它们的长度是固定的，可以不必将长度编码到数据流中，所以它们的编码格式采用TTV。PP的编码格式详解请见下面章节。<p>
5. PP的C、C++实现，提供了读取XMl元素数据的功能函数，不过读取xml配置文件的功能需要结合CXmlLoader和XmlLoader这两个项目。<p>
6. PP的代码生成器采用python语言，不需要编译即可跨平台使用。代码生成器需在python2.4以上的环境下工作。

项目路径说明
=============
1. CMessage-Creator目录：代码生成器路径。代码生成器使用说明请见下面章节。<p>
2. CMessage目录：为C语言的实现提供支持的基础函数和测试代码。如果您的项目采用C语言，需要引入这些代码做为依赖项。<p>
3. JMessage目录：为Java语言的实现提供支持的基础类和测试代码。如果您的项目采用Java语言，需要引入这些基础类。<p>
4. Message目录：为C++语言的实现提供支持的基础类和测试代码。如果您的项目采用C++语言，需要引入这些基础类。<p>
5. protocol-def目录：该目录下存放了一个数据结构定义的例子文件。

快速上手指南
=============

要使用PP，您只需要完成如下几步操作：<p>

1. 采用XML编写结构或对象描述文件，定义数据结构或对象。您可以把数据结构定义在不同的文件中。数据结构或对象可以跨文件相互引用，当您需要引用其他文件中定义的结构时，不需要显式引入其他文件。您可以参考protocol-def目录中的例子<a href='https://github.com/itfriday/protocol-pack/blob/master/protocol-def/msg.xml'>msg.xml</a>来编写结构定义文件。<p>
2. 采用代码生成器生成指定语言的数据结构或对象。代码生成器会为每个结构生成独立的文件。例如，假定您在描述文件中定义了一个名为Person的结构，且选择生成C语言代码，会生成Person.h和Person.c这两个文件。<p>
3. 将生成的代码及其依赖的基础代码添加到您的项目中。例如，假定您的项目采用C语言，除了需要把步骤2中生成的代码添加到项目中，还需要把CMessage目录中的代码添加到项目中。<p>
4. 代码生成器为每个结构体或对象均生成了encode、decode、format、toXml这4个函数，您可以调用encode函数结构或对象编码为二进制数据；调用decode函数将二进制数据解码为结构体或对象；当需要日志输出数据结构时，可以调用format函数，将数据结构编码为可读字符串；当需要将数据对象保存为xml文件时，可以调用toXml函数将数据编码为xml格式的字符串，再输出到文件。<p>

Demo
=============

1. 每种语言都提供了例子，放在语言对应的test目录下。例如对C语言，例子程序放在CMessage/test目录下，名为main.c(其他语言类似)，<p>
<pre>
#include &lt;stdlib.h>
#include &lt;string.h>
#include &lt;stdio.h>
#include "test/CsMsgResponse.h"
int main()
{
    /* 对象结构体申明及赋值 */
    CSMSGRESPONSE stMsgResponse;
    stMsgResponse.shCmd = CS_MSG_GET_FRIEND_LIST;
    stMsgResponse.shEno = 0;

    stMsgResponse.stRespData.nSelector = CS_MSG_GET_FRIEND_LIST;

    /* 数组字段 */
    stMsgResponse.stRespData.stGetFriends.bFriendNumber = 2;

    stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].ullGID = 0x12345678l;
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].szFriendName, "ErisenXu");
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[0].szFriendImage, "http://www.qq.com/erisenxu.jpg");

    stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].ullGID = 0x78563412l;
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].szFriendName, "xy");
    strcpy(stMsgResponse.stRespData.stGetFriends.astFriendInfo[1].szFriendImage, "http://www.qq.com/xy.jpg");

    stMsgResponse.stRespData.stGetFriends.bTypeNumber = 3;
    stMsgResponse.stRespData.stGetFriends.astTypes[0] = 0x345678;
    stMsgResponse.stRespData.stGetFriends.astTypes[1] = 0x896754;
    stMsgResponse.stRespData.stGetFriends.astTypes[2] = 0x2233445566778899l;

    char szMsg1[1024];
    BYTEARRAY stBa1;
    INIT_BYTE_ARRAY(stBa1, szMsg1, sizeof(szMsg1));

    /* 格式化 */
    cs_msg_response_field_format("CSMsgResponse", &stMsgResponse, &stBa1, "");
    bytearray_append_u8(&stBa1, (U8)0);

    printf("%s", stBa1.pszData);

    /* 转换为xml */
    bytearray_clear(&stBa1);
    cs_msg_response_field_to_xml("CSMsgResponse", &stMsgResponse, &stBa1, "");
    bytearray_append_u8(&stBa1, (U8)0);

    printf("%s", stBa1.pszData);

    /* 消息编码成二进制 */
    bytearray_clear(&stBa1);
    cs_msg_response_field_encode(&stMsgResponse, 1, &stBa1);

    char szOut2[8192];
    BYTEARRAY stBuf2;
    INIT_BYTE_ARRAY(stBuf2, szOut2, sizeof(szOut2));

    bytes_to_printable(&stBuf2, stBa1.pszData, stBa1.dwLen, 0, -1, 16);

    printf("%s\n", stBuf2.pszData);

    /* 将二进制数据解码为消息对象 */
    CSMSGRESPONSE stMsgResp;
    memset(&stMsgResp, sizeof(stMsgResp), 0);
    cs_msg_response_field_decode(&stMsgResp, stBa1.pszData, stBa1.dwLen);

    /* 格式化输出解码后的消息 */
    bytearray_clear(&stBuf2);
    cs_msg_response_field_format("CSMsgResponse", &stMsgResp, &stBuf2, "");
    bytearray_append_u8(&stBuf2, (U8)0);

    printf("%s", stBuf2.pszData);

    return 0;
}
</pre>

2. 要运行Demo程序，您必须先执行目录下的gen.bat(Windows下)或gen.sh(Linux下)程序生成相应的代码。gen.bat/gen.sh程序会调用PP代码生成器将protocol-def目录下定义的<a href='https://github.com/itfriday/protocol-pack/blob/master/protocol-def/msg.xml'>msg.xml</a>转变为结构或对象。<p>

3. 接着，您需要将生成的代码编译为可执行程序，然后执行。例如，如果是C或C++语言，您可以在Linux下，在test目录执行Make命令，即可编译出Message可执行程序。

调用format函数，将结构体编码为可读字符串：<p>
<pre>
[CsMsgResponse]
    Eno = 0
    Cmd = 2
    [RespData]
        [GetFriends]
            FriendNumber = 2
            [FriendInfo]
                GID = 305419896
                FriendName = ErisenXu
                FriendImage = http://www.qq.com/erisenxu.jpg
            [FriendInfo]
                GID = 2018915346
                FriendName = xy
                FriendImage = http://www.qq.com/xy.jpg
            TypeNumber = 3
            Types = 3430008
            Types = 9004884
            Types = 2464388554683811993
</pre>
