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

调用format函数，将结构体编码为可读字符串：<p>
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

