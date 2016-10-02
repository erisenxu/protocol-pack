Protocol-Pack简介
=============

Protocol-Pack(以下简称PP)是和google的Protocol Buffer(简称PB)类似的一种二进制数据交换的格式。它采用TT(L)V（即Tag-Type-Length-Value）的格式对数据信息进行编码，具有向前、向后兼容的特性。PP提供了多种语言的实现：C、C++、Java、Object-C，每种实现都尽量追求极简的编码风格，简单、干净、容易理解。

Protocol-Pack特点
=============
1. PP采用xml格式定义数据结构，然后通过代码生成器生成的代码读写数据结构。目前代码生成器可以生成C、C++、Java、Object-C这几种语言的代码。<p>
2. PP支持Union、Struct数据结构，还支持enum数据结构，支持采用marco定义宏或常量，支持数组等。PP支持的数据结构详情请见下面章节。<p>
3. PP的每种语言的实现均提供encode、decode、format、toXml这4个函数，其中encode函数将Union或Struct数据结构编码为二进制数据(大端序/网络序)；decode函数将二进制数据解码为Union或Struct数据结构;format函数将数据结构编码为可读字符串，一般用于日志打印；toXml函数将数据结构编码为xml格式的字符串。<p>
4. 一般地，PP采用TTLV的格式对数据结构进行编码，但是针对数字类型的数据(比如32位整数)，它们的长度是固定的，可以不必将长度编码到数据流中，所以它们的编码格式采用TTV。PP的编码格式详解请见下面章节。<p>
5. PP的C、C++实现，提供了读取xml的功能函数，不过读取xml配置文件的功能需要结合CXmlLoader和XmlLoader这两个项目。<p>
6. PP的代码生成器采用python语言，不需要编译即可跨平台使用。代码生成器需在python2.4以上的环境下工作。<p>

项目路径说明
=============
1. CMessage-Creator目录：代码生成器路径。代码生成器使用说明请见下面章节。<p>
2. CMessage目录：为C语言的实现提供支持的基础函数和测试代码。如果您的项目采用C语言，需要引入这些代码做为依赖项。<p>
3. JMessage目录：为Java语言的实现提供支持的基础类和测试代码。如果您的项目采用Java语言，需要引入这些基础类。<p>
4. Message目录：为C++语言的实现提供支持的基础类和测试代码。如果您的项目采用C++语言，需要引入这些基础类。<p>
5. protocol-def目录：该目录下存放了一个数据结构定义的例子文件。<p>

Quick Example
=============
You write a .xml file like this:
<pre>
&lt;?xml version="1.0" encoding="utf-8" standalone="yes" ?>

&lt;field-config version="1">
	&lt;struct name="Person"	desc="Person Object">
		&lt;field	name="ID"		type="uint"		version="1"		default="0"		tag="1"		desc="ID of person" />
		&lt;field	name="Name"		type="string"	version="1"		count="20"		tag="2"		desc="Name of person" />
		&lt;field	name="Email"	type="string"	version="1"		count="30"		tag="3"		desc="Email of person" />
	&lt;/struct>
&lt;/field-config>
</pre>

<!-- The following code is for txt readers -->
<!--
<?xml version="1.0" encoding="utf-8" standalone="yes" ?>

<field-config version="1">
	<struct name="Person"	desc="Person Object">
		<field	name="ID"		type="uint"		version="1"		default="0"		tag="1"		desc="ID of person" />
		<field	name="Name"		type="string"	version="1"		count="20"		tag="2"		desc="Name of person" />
		<field	name="Email"	type="string"	version="1"		count="30"		tag="3"		desc="Email of person" />
	</struct>
</field-config>
-->
<pre>
Then you use protocol buffer generator, to produce code in C++, C, C# or Java.

If you are using C++, you will get the following C++ files: 
  Person.h
  Person.cpp

Or if you are using c, you will get the following c files:
  Person.h
  Person.c

Or if you are using Java, you will get the following Java file:
  Person.java

Then you add these files to your application, and compile them with your application.

For a more complete example, see the tutorials.
</pre>
