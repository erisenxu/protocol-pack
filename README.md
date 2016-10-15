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
5. OCMessage目录：为Object-C语言的实现提供支持的基础类和测试代码。如果您的项目采用Object-C语言，需要引入这些基础类。(需将pp目录下的代码拷贝到您的项目中)<p>
6. protocol-def目录：该目录下存放了一个数据结构定义的例子文件。

快速上手指南
=============

要使用PP，您只需要完成如下几步操作：<p>

1. <strong>采用XML编写结构或对象描述文件(或称为接口描述文件)，定义数据结构或对象</strong>。您可以把数据结构定义在不同的文件中。数据结构或对象可以跨文件相互引用，当您需要引用其他文件中定义的结构时，不需要显式引入其他文件。您可以参考protocol-def目录中的例子<a href='https://github.com/itfriday/protocol-pack/blob/master/protocol-def/msg.xml'>msg.xml</a>来编写结构定义文件。<p>
2. <strong>采用代码生成器生成指定语言的数据结构或对象</strong>。代码生成器会为每个结构生成独立的文件。例如，假定您在描述文件中定义了一个名为Person的结构，且选择生成C语言代码，会生成Person.h和Person.c这两个文件。<p>
3. <strong>将生成的代码及其依赖的基础代码添加到您的项目中</strong>。例如，假定您的项目采用C语言，除了需要把步骤2中生成的代码添加到项目中，还需要把CMessage目录中的代码添加到项目中。<p>
4. 代码生成器为每个结构体或对象均生成了encode、decode、format、toXml这4个函数(c语言的函数名会加上结构体名，例如结构体名若为Person，则这4个函数分别为person_field_encode、person_field_decode、person_field_format、person_field_to_xml)，您可以调用encode函数结构或对象编码为二进制数据；调用decode函数将二进制数据解码为结构体或对象；当需要日志输出数据结构时，可以调用format函数，将数据结构编码为可读字符串；当需要将数据对象保存为xml文件时，可以调用toXml函数将数据编码为xml格式的字符串，再输出到文件。<br>
&nbsp;&nbsp;&nbsp;例如，在C语言下，将结构体Person编码为二进制数据的语句如下：<br>
<pre>
    PERSON stPerson;
    person_field_encode(&stPerson, 1, &stBa); // 第二个参数1是指Person的tag，第3个参数stBa是保存二进制数据的数组，有关于它的说明和初始化语句见下面的说明
</pre>
从二进制数据解码Person结构体的语句如下：<br>
<pre>
    // 假定szBinData是待解码的二进制数据流，dwDataLen为二进制数据流的长度
    // 则将二进制解码为Person结构体的C语言如下：
    PERSON stPerson;
    memset(&stPerson, sizeof(stPerson), 0);
    person_field_decode(&stPerson, szBinData, dwDataLen);
</pre>
注意：C、C++及Java语言，都提供了一个名为ByteArray的字节数组，它是一个辅组类，负责处理二进制数据，包括编码、解码等辅组功能。对C语言，字节数组的初始化语句如下：<br>
<pre>
    char szMsg1[1024]; // 定义字节数组的大小，注意C语言的字节数组不会自动扩展大小，您必须在初始化时为数组分配足够的大小
    BYTEARRAY stBa; // 定义字节数组
    INIT_BYTE_ARRAY(stBa, szMsg1, sizeof(szMsg1)); // 初始化字节数组
</pre>
C++语言的字节数组初始化语句如下：<br>
<pre>
    MByteArray stBa; // 字节数组会自动扩展大小
    // 或
    MByteArray stBa(1024); // 初始化时，指定初始缓存大小，如果缓存不够，将自动扩展大小
    // 因为字节数组在扩展大小时，会重新申请内存，并将之前的数据拷贝到新的内存中，为避免频繁内存操作，建议采用指定初始缓存大小的形式。
</pre>
Java语言的字节数组初始化语句如下：<br>
<pre>
    ByteArray ba = new ByteArray(); // 字节数组会自动扩展大小
    // 或
    ByteArray ba = new ByteArray(1024); // 初始化时，指定初始缓存大小，如果缓存不够，将自动扩展大小
    // 因为字节数组在扩展大小时，会重新申请内存，并将之前的数据拷贝到新的内存中，为避免频繁内存操作，建议采用指定初始缓存大小的形式。
</pre>

Demo
=============

1. 每种语言都提供了例子，放在语言对应的test目录下。其中：<br>
&nbsp;&nbsp;&nbsp;&nbsp;<a href='https://github.com/itfriday/protocol-pack/blob/master/CMessage/test/main.c'>CMessage/test/main.c</a>，为C语言例子程序<br>
&nbsp;&nbsp;&nbsp;&nbsp;<a href='https://github.com/itfriday/protocol-pack/blob/master/JMessage/com/itfriday/test/Test.java'>JMessage/com/itfriday/test/Test.java</a>，为Java语言例子程序<br>
&nbsp;&nbsp;&nbsp;&nbsp;<a href='https://github.com/itfriday/protocol-pack/blob/master/Message/test/main.cpp'>Message/test/main.cpp</a>，为C++语言例子程序<p>

2. 要运行Demo程序，您必须先执行目录下的gen.bat(Windows下)或gen.sh(Linux下)程序生成相应的代码。gen.bat/gen.sh程序会调用PP代码生成器将protocol-def目录下定义的<a href='https://github.com/itfriday/protocol-pack/blob/master/protocol-def/msg.xml'>msg.xml</a>转变为结构或对象。<p>

3. 接着，您需要将生成的代码编译为可执行程序，然后执行。<br>
&nbsp;&nbsp;&nbsp;&nbsp;针对C语言，在Linux下，切换到CMessage/test目录，执行Make命令，即可编译出名为Message的可执行程序。<br>
&nbsp;&nbsp;&nbsp;&nbsp;针对C++语言，在Linux下，切换到Message/test目录，执行Make命令，即可编译出名为Message的可执行程序。<br>
&nbsp;&nbsp;&nbsp;&nbsp;针对Java语言，切换到JMessage目录，执行build命令，可以执行编译。<br>
&nbsp;&nbsp;&nbsp;&nbsp;针对Object-C语言，切换到OCMessage目录，使用XCode打开项目，编译、运行。<p>

4. 例子程序执行后的输出见下图：<p>
<pre>
// 将结构体编码为可读形式的输出
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
// 将结构体编码为XML形式的输出
&lt;CsMsgResponse>
    &lt;Eno>0&lt;/Eno>
    &lt;Cmd>2&lt;/Cmd>
    &lt;RespData>
        &lt;GetFriends>
            &lt;FriendNumber>2&lt;/FriendNumber>
            &lt;FriendInfo>
                &lt;GID>305419896&lt;/GID>
                &lt;FriendName>ErisenXu&lt;/FriendName>
                &lt;FriendImage>http://www.qq.com/erisenxu.jpg&lt;/FriendImage>
            &lt;/FriendInfo>
            &lt;FriendInfo>
                &lt;GID>2018915346&lt;/GID>
                &lt;FriendName>xy&lt;/FriendName>
                &lt;FriendImage>http://www.qq.com/xy.jpg&lt;/FriendImage>
            &lt;/FriendInfo>
            &lt;TypeNumber>3&lt;/TypeNumber>
            &lt;Types>3430008&lt;/Types>
            &lt;Types>9004884&lt;/Types>
            &lt;Types>2464388554683811993&lt;/Types>
        &lt;/GetFriends>
    &lt;/RespData>
&lt;/CsMsgResponse>
// 将结构体编码为二进制流形式的输出
0000   00 01 0b 00 00 00 d3 00  01 03 00 00 00 02 03 00   ........ ........
0010   02 00 03 0b 00 00 00 c2  00 02 0b 00 00 00 bb 00   ........ ........
0020   01 02 02 00 02 0c 00 00  00 82 00 02 00 02 0b 00   ........ ........
0030   00 00 3f 00 01 08 00 00  00 00 12 34 56 78 00 03   ..?..... ...4Vx..
0040   09 00 00 00 08 45 72 69  73 65 6e 58 75 00 04 09   .....Eri senXu...
0050   00 00 00 1e 68 74 74 70  3a 2f 2f 77 77 77 2e 71   ....http ://www.q
0060   71 2e 63 6f 6d 2f 65 72  69 73 65 6e 78 75 2e 6a   q.com/er isenxu.j
0070   70 67 00 02 0b 00 00 00  33 00 01 08 00 00 00 00   pg...... 3.......
0080   78 56 34 12 00 03 09 00  00 00 02 78 79 00 04 09   xV4..... ...xy...
0090   00 00 00 18 68 74 74 70  3a 2f 2f 77 77 77 2e 71   ....http ://www.q
00a0   71 2e 63 6f 6d 2f 78 79  2e 6a 70 67 00 03 02 03   q.com/xy .jpg....
00b0   00 04 0c 00 00 00 23 00  03 00 04 08 00 00 00 00   ......#. ........
00c0   00 34 56 78 00 04 08 00  00 00 00 00 89 67 54 00   .4Vx.... .....gT.
00d0   04 08 22 33 44 55 66 77  88 99                     .."3DUfw ..
// 解码为结构体后，将结构体输出为可读形式
[CSMsgResponse]
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

接口描述文件
=============

要使用PP，最重要的就是采用XML定义结构或对象描述文件，或者称为接口描述文件。本章将详细介绍如何定义一个接口描述文件。<p>

1. 描述文件基本结构。<p>
描述文件采用标准的XML编写，必须包含一个名为field-config的根节点。文件中定义的其他宏、结构体、枚举类型，都是field-config的子节点。
<pre>
&lt;?xml version="1.0" encoding="utf-8" standalone="yes" ?>
&lt;field-config version="1">
    &lt;!-- 在这里定义宏、枚举、结构体 等-->
    ......
&lt;/field-config>
</pre>

2. 如何定义宏 <p>
采用macro定义宏。暂时只支持定义整数类型的宏。name属性指定宏的名字，value指定宏的值，desc指定宏的描述：<br>
<pre>
&lt;macro name="MAX_URL_LEN"            value='256'           desc='最大URL地址长度' />
</pre>

3. 如何定义枚举类型 <p>
采用enum定义枚举。name属性指定枚举名字，desc属性指定枚举的描述，macro子节点定义枚举包含的元素。enum可以包含一个或多个macro子节点：<br>
<pre>
&lt;enum name="CS_MSG_TYPE_"  desc="客户端消息类型" >
    &lt;macro name="CS_MSG_LOGIN"                              value="1"        desc="登录" />
    &lt;macro name="CS_MSG_GET_FRIEND_LIST"                    value="2"        desc="获取好友列表" />
&lt;/enum>
</pre>

4. 如何定义Struct结构<p>
采用struct定义一个结构体。name属性指定结构名称，desc属性指定结构描述，field子节点定义结构包含的子元素。struct可以包含一个或多个field子节点。<br>
field子节点包含如下属性：<br>
<table width='100%'>
    <tr>
        <td>属性名</td>
        <td>属性说明</td>
        <td>是否必须指定</td>
    </tr>
    <tr>
        <td>name</td>
        <td>子元素名</td>
        <td>是</td>
    </tr>
    <tr>
        <td>type</td>
        <td>子元素类型，可取值为：uchar、char、ushort、short、uint、int、ulong、long、string、bytes、array、其他用struct或union定义的结构</td>
        <td>是</td>
    </tr>
    <tr>
        <td>tag</td>
        <td>子元素的标签。为保证协议前后兼容性，每个子元素的标签必须在其所属结构体的作用域中是唯一的</td>
        <td>是</td>
    </tr>
    <tr>
        <td>subtype</td>
        <td>子元素类型，可取值为：uchar、char、ushort、short、uint、int、ulong、long、其他用struct或union定义的结构。注意subtype不支持string、bytes、array，即数组元素不支持直接采用字符串、字节数组和数组，可以将它们定义到结构体中然后指定结构体为数组的元素（见后面的例子）。</td>
        <td>当type=array，表示子字段为数组时，必须指定subtype</td>
    </tr>
    <tr>
        <td>count</td>
        <td>用来指定字符串或数组元素的最大数量</td>
        <td>当type=array或type=string或type=bytes时，必须指定count</td>
    </tr>
    <tr>
        <td>refer</td>
        <td>数组有效元素数量，取值必须是结构体中定义的一个整形元素</td>
        <td>当type=array或type=bytes时，必须指定refer</td>
    </tr>
    <tr>
        <td>select</td>
        <td>union元素选择器，取值必须是结构体中定义的一个整形元素</td>
        <td>当type是一个union类型的结构体时，必须指定select</td>
    </tr>
    <tr>
        <td>desc</td>
        <td>子元素的描述</td>
        <td>否</td>
    </tr>
</table>
一个结构体的例子如下：<br>
<pre>
    &lt;struct name='FriendInfo' desc='好友信息'>
        &lt;field    name="GID"            type="ulong"         tag="1"                                            desc="好友GID" />
        &lt;field    name="FriendName"     type="string"        tag="3"            count="MAX_NAME_LEN"            desc="好友名称" />
        &lt;field    name="FriendImage"    type="string"        tag="4"            count="MAX_URL_LEN"             desc="好友头像URL地址" />
    &lt;/struct>
</pre>
它定义了一个名为FriendInfo的结构体，包含GID、FriendName、FriendImage这3个子字段，类型分别是ulong，string和string，其中FriendName的最大长度是MAX_NAME_LEN，FriendImage的最大长度是MAX_URL_LEN。MAX_NAME_LEN和MAX_URL_LEN是用macro定义的宏。如果是C语言，FriendInfo将被代码生成器转变为C语言的结构体：<br>
<pre>
struct tagFriendInfo
{
    U64 ullGID;                      // 好友GID
    char szFriendName[MAX_NAME_LEN]; // 好友名称
    char szFriendImage[MAX_URL_LEN]; // 好友头像URL地址
};
typedef struct tagFriendInfo  FRIENDINFO;
typedef struct tagFriendInfo* LPFRIENDINFO;
</pre>
当一个结构体被定义后，它将成为一个新的类型，可以被其他结构体引用。使用type或subtype即可以引用它，例子如下：<br>
<pre>
    &lt;struct name='FriendInfoList' desc='Just a Test Message object'>
        &lt;field    name="FriendNumber"    type="uchar"        tag='1'            default="0"                        desc="好友数量" />
        &lt;field    name="FriendInfo"      type="array"        tag="2"            subtype='FriendInfo'               count='MAX_FRIEND_NUMBER'      refer='FriendNumber'    desc="好友列表" />
        &lt;field    name="TypeNumber"      type="uchar"        tag='3'            default="0"                        desc="类型数量" />
        &lt;field    name="Types"           type="array"        tag="4"            subtype='ulong'                    count='MAX_TYPE_NUMBER'        refer='TypeNumber'      desc="类型列表" />
    &lt;/struct>
</pre>
这个例子定义了一个名为FriendInfoList的结构，它的子字段FriendInfo是一个数组，数组元素类型是FriendInfo，数组的最大元素数量由MAX_FRIEND_NUMBER指定，数组的有效元素数量由字段FriendNumber决定(注意这里的refer，它指定了数组FriendInfo的有效元素数量，由字段FriendNumber决定)。如果是C语言，FriendInfoList将被代码生成器转变为C语言的结构体如下：<br>
<pre>
struct tagFriendInfoList
{
    U8 bFriendNumber;                            // 好友数量
    FRIENDINFO astFriendInfo[MAX_FRIEND_NUMBER]; // 好友列表
    U8 bTypeNumber;                              // 类型数量
    U64 astTypes[MAX_TYPE_NUMBER];               // 类型列表
};
typedef struct tagFriendInfoList  FRIENDINFOLIST;
typedef struct tagFriendInfoList* LPFRIENDINFOLIST;
</pre>

4. 如何定义Union联合<p>
定义联合和定义结构体的语法类似，只是联合采用union来定义，name属性指定联合名称，desc属性指定联合描述，field子节点定义联合包含的子元素。union可以包含一个或多个field子节点。field子节点包含属性和struct节点的field子节点包含的属性一样，见上表。<br>

一个联合的例子如下：<br>
<pre>
    &lt;union name='CsRequestData' desc='客户端响应协议消息结构体'>
        &lt;field    name="Login"         type="LoginRequest"            tag='CS_MSG_LOGIN'                    desc='客户端登录请求' />
        &lt;field    name="GetFriends"    type="char"                    tag='CS_MSG_GET_FRIEND_LIST'          desc='获取好友列表请求' />
    &lt;/union>
</pre>
若转变为C语言，对应的代码如下：<br>
<pre>
struct tagCsRequestData
{
    U16 nSelector;  // 联合的选择器，由代码生成器自动添加。
    union
    {
        LOGINREQUEST stLogin; // 客户端登录请求
        S8 chGetFriends;     // 获取好友列表请求
    };
};
typedef struct tagCsRequestData  CSREQUESTDATA;
typedef struct tagCsRequestData* LPCSREQUESTDATA;
</pre>
这里，联合的选择器是由代码生成器自动添加的，当它值与联合中的某个字段的tag相同时，联合将用于保存该字段的值。即：<br>
<pre>
if (nSelector == CS_MSG_LOGIN) {
    // tagCsRequestData代表了stLogin
} else if (nSelector == CS_MSG_GET_FRIEND_LIST) {
    // tagCsRequestData代表了chGetFriends
}
</pre>

和struct结构体类似，当一个联合被定义后，它将成为一个新的类型，可以被其他结构体引用。使用type或subtype即可以引用它，但是必须为它指定select属性，例子如下：<br>
<pre>
    &lt;struct name="CsMsgRequest"    version="1"        desc="客户端请求协议" >
        &lt;field name="GID"            type="ulong"            tag="1"        desc="玩家GID" />
        &lt;field name="Cmd"            type="short"            tag="2"        desc="消息命令字" />
        &lt;field name="ReqData"        type="CsRequestData"    tag="3"        desc="消息结构体"    select="Cmd"/>
    &lt;/struct>
</pre>
对应的C语言如下:<br>
<pre>
struct tagCsMsgRequest
{
    U64 ullGID;              // 玩家GID
    S16 shCmd;               // 消息命令字
    CSREQUESTDATA stReqData; // 消息结构体
};
typedef struct tagCsMsgRequest  CSMSGREQUEST;
typedef struct tagCsMsgRequest* LPCSMSGREQUEST;
</pre>
这个例子定义了一个CsMsgReuqest结构，它的子字段ReqData的类型是CsRequestData，它是一个联合，它的选择器由select指定为Cmd，因此当Cmd==CS_MSG_LOGIN时，ReqData将代表stLogin字段，当Cmd==CS_MSG_GET_FRIEND_LIST时，ReqData将代表chGetFriends字段。

代码生成器使用说明
=============
代码生成器位于CMessage-Creator目录，它是python编写的工具，不需要编译可以跨平台使用。它需要python2.4以上的环境。<p>

代码生成器的主程序是generator.py，执行python generator.py --help可以查看帮助。<p>
<pre>
Description: message generator.
Version: 1.0.0.0
Usage: python generator.py [-?] [-h] [-s DIRECTORY] [-d DIRECTORY]
                           [-l {c, cpp, java, oc}] [-m FILE_NAME] [-p PACKAGE_NAME]
optional arguments:
  -?, -h, --help	Show this help information
  -s DIRECTORY, --srcpath DIRECTORY
			Set protocol define file search directory
  -l {c, cpp, java, oc}, --language {c, cpp, java, oc}	
			Major programming language you want to use, should be
			[c|cpp|java|oc]
  -d DIRECTORY, --directory DIRECTORY
			Set generate project directory for project
  -m FILE_NAME
			Set generate macro file name
  -p PACKAGE_NAME
			Set package for java
Example:
  python generator.py --help
  python generator.py -s . -d ../test -l c -m StarMacro
</pre>

可选输入参数说明如下：<p>
<pre>
可选参数:
  -?, -h, --help	显示本程序的帮助信息
  -s DIRECTORY, --srcpath DIRECTORY
			指定接口描述文件所在路径
  -l {c, cpp, java, oc}, --language {c, cpp, java, oc}	
			代码生成器生成的代码语言种类，目前可选c、cpp、java，和oc
  -d DIRECTORY, --directory DIRECTORY
			设置代码生成路径
  -m FILE_NAME
			设置宏定义文件名称
  -p PACKAGE_NAME
			设置包名，仅仅对java语言有用
</pre>
但是针对数字类型的数据(比如32位整数)，它们的长度是固定的，可以不必将长度编码到数据流中，所以它们的编码格式采用TTV
编码规则详解
=============
PP采用TT(L)V的格式对数据结构进行编码，其中：<p>
&nbsp;&nbsp;&nbsp;&nbsp;T(Tag)，字段标签，用来唯一标识或区别一个字段。编码为二进制时，占用2个字节长度。<p>
&nbsp;&nbsp;&nbsp;&nbsp;T(Type)，字段类型，用来标识字段类型。编码为二进制时，占用1个占用长度。<p>
&nbsp;&nbsp;&nbsp;&nbsp;L(Length)，字段的值(Value)的长度。当字段类型(Type)为整形时，不包含长度。编码为二进制时，长度占用4个字节。<p>
&nbsp;&nbsp;&nbsp;&nbsp;V(Value)，字段的值。所占字节长度由L(Length)指定<p>

PP支持的字段类型包括：<p>
<table width='100%'>
    <tr>
        <td>类型</td>
        <td>Type的值</td>
        <td>字节长度</td>
        <td>类型说明</td>
    </tr>
    <tr>
        <td>char</td>
        <td>1</td>
        <td>1</td>
		<td>有符号整数，占1个字节</td>
    </tr>
    <tr>
        <td>uchar</td>
        <td>2</td>
        <td>1</td>
		<td>无符号整数，占1个字节</td>
    </tr>
    <tr>
        <td>short</td>
        <td>3</td>
        <td>2</td>
		<td>有符号整数，占2个字节</td>
    </tr>
    <tr>
        <td>ushort</td>
        <td>4</td>
        <td>2</td>
		<td>无符号整数，占2个字节</td>
    </tr>
    <tr>
        <td>int</td>
        <td>5</td>
        <td>4</td>
		<td>有符号整数，占4个字节</td>
    </tr>
    <tr>
        <td>uint</td>
        <td>6</td>
        <td>4</td>
		<td>无符号整数，占4个字节</td>
    </tr>
    <tr>
        <td>long</td>
        <td>7</td>
        <td>8</td>
		<td>有符号整数，占8个字节</td>
    </tr>
    <tr>
        <td>ulong</td>
        <td>8</td>
        <td>8</td>
		<td>无符号整数，占8个字节</td>
    </tr>
    <tr>
        <td>string</td>
        <td>9</td>
        <td>不固定</td>
		<td>字符串类型，长度由Length字段指定</td>
    </tr>
    <tr>
        <td>bytes</td>
        <td>10</td>
        <td>不固定</td>
		<td>字节数组类型，长度由Length字段指定(当前暂不支持)</td>
    </tr>
    <tr>
        <td>结构体类型</td>
        <td>11</td>
        <td>不固定</td>
		<td>在接口描述文件中，采用Struct和Union定义的结构体类型，长度由Length字段指定</td>
    </tr>
    <tr>
        <td>array</td>
        <td>12</td>
        <td>不固定</td>
		<td>数组类型，长度由Length字段指定</td>
    </tr>
</table>

举个例子，Tag为1，类型为ushort，16进制值为0x1234的整数，编码为二进制为：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 01 04 12 34 <p>

Tag为4，类型为string的字符串http://www.qq.com/xy.jpg，编码为二进制为：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 04 09 00 00 00 18 68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67<p>
其中：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 04 为Tag<p>
&nbsp;&nbsp;&nbsp;&nbsp;09 为类型<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 00 00 18 为字符串长度，这里长度是0x18，即24<p>
&nbsp;&nbsp;&nbsp;&nbsp;68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67为字符串的值<p>

而复合结构体的编码为各子字段编码的拼接，例如，假定一个结构体包含以上两个字段(即一个ushort一个string)，则结构体编码为二进制为：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 02 0b 00 00 00 24 00 01 04 12 34 00 04 09 00 00 00 18 68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67<p>
其中：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 02 为结构体Tag<p>
&nbsp;&nbsp;&nbsp;&nbsp;0b 为类型<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 00 00 24 为结构体长度，这里长度是0x24，即36个字节<p>

&nbsp;&nbsp;&nbsp;&nbsp;00 01 为第一个子字段的Tag<p>
&nbsp;&nbsp;&nbsp;&nbsp;04 为类型<p>
&nbsp;&nbsp;&nbsp;&nbsp;12 34为第一个字段的值<p>

&nbsp;&nbsp;&nbsp;&nbsp;00 04 为第二个子字段的Tag<p>
&nbsp;&nbsp;&nbsp;&nbsp;09 为类型(字符串)<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 00 00 18 为字符串长度，这里长度是0x18，即24<p>
&nbsp;&nbsp;&nbsp;&nbsp;68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67为字符串的值<p>

数组字段的编码，编码Value前，会编码数组数量，数组数量会占用2字节。例如，假定一个数组元素为上面定义的结构体，且数量为2，编码为二进制为：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 03 0c 00 00 00 58 00 02<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 03 0b 00 00 00 24 00 01 04 12 34 00 04 09 00 00 00 18 68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 03 0b 00 00 00 24 00 01 04 12 34 00 04 09 00 00 00 18 68 74 74 70  3a 2f 2f 77 77 77 2e 71 71 2e 63 6f 6d 2f 78 79  2e 6a 70 67<p>
其中：<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 03 为数组Tag<p>
&nbsp;&nbsp;&nbsp;&nbsp;0c 为类型<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 00 00 58 为数组长度，这里长度是0x58，即88个字节<p>
&nbsp;&nbsp;&nbsp;&nbsp;00 02 为数组元素数量，这里数量为2<p>
其他两行编码为数组元素结构体的编码。注意这里数组元素结构体的Tag与数组的Tag相同，都为0x03。<p>

联合(union)的编码规则和符合结构体的编码规则一样，只是要注意一点的是，union的标签Tag即是它的选择器selector，也即是它的有效子字段的标签。只有Tag对应的union子字段会被编码，其他无效的子字段不会被编码。<p>
例如，对于联合CsRequestData
<pre>
    &lt;union name='CsRequestData' desc='客户端响应协议消息结构体'>
        &lt;field    name="Login"         type="LoginRequest"            tag='CS_MSG_LOGIN'                    desc='客户端登录请求' />
        &lt;field    name="GetFriends"    type="char"                    tag='CS_MSG_GET_FRIEND_LIST'          desc='获取好友列表请求' />
    &lt;/union>
</pre>
若其字段Login有效，则编码为二进制时，CsRequestData的tag将为CS_MSG_LOGIN，只有Login子字段会被编码；<p>
若其字段GetFriends有效，则编码为二进制时，CsRequestData的tag为CS_MSG_GET_FRIEND_LIST，只有GetFriends子字段会被编码<p>