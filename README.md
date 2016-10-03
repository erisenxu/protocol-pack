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
        <td>子元素的标签</td>
        <td>是</td>
    </tr>
    <tr>
        <td>subtype</td>
        <td>子元素类型，可取值为：uchar、char、ushort、short、uint、int、ulong、long、其他用struct或union定义的结构</td>
        <td>当type=array，表示子字段为数组时，必须指定subtype；当type!=array时，不必指定subtype</td>
    </tr>
    <tr>
        <td>count</td>
        <td>用来指定字符串或数组元素的最大数量</td>
        <td>当type=array或type=string或type=bytes时，必须指定count；当type!=array且type!=string且type!=bytes时，不必指定count</td>
    </tr>
    <tr>
        <td>refer</td>
        <td>数组元素数量，取值必须是结构体中定义的一个整形元素</td>
        <td>当type=array或type=bytes时，必须指定refer；当type!=array且type!=bytes时，不必指定refer</td>
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

代码生成器使用说明
=============

编码规则详解
=============
