Protocol-Pack简介
=============

Protocol-Pack(以下简称PP)是和google的Protocol Buffer(简称PB)类似的一种二进制数据交换的格式。它采用TT(L)V（即Tag-Type-Length-Value）的格式对数据信息进行编码，具有向前、向后兼容的特性。PP提供了多种语言的实现：C、C++、Java、Object-C，每种实现都尽量追求极简的编码风格，简单、干净、容易理解。

Protocol-Pack特点
=============
1. PP支持Union数据结构 <p>
2. PP的每种语言的实现均提供encode、decode、format、toXml这4个函数，其中encode函数将Union或Struct数据结构编码为二进制数据(大端序/网络序)；decode函数将二进制数据解码为Union或Struct数据结构，format函数将数据结构编码为可读字符串，一般用于日志打印；toXml函数将数据结构编码为xml格式的字符串。<p>
3. PP的C、C++实现，提供了读取xml的功能函数，不过读取xml配置文件的功能需要结合CXmlLoader和XmlLoader这两个项目。<p>

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
