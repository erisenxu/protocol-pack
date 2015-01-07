Protocol-pack
=============

Protocol Pack is a way of encoding or decoding structured data, It's similar with Google Protocol Buffer. But easier to understand and use. And it produce code in C++, C...

Why Use Protocol-pack but not Protocol Buffer?
=============
First, the Protocol Pack is easier to understand and use. The code it produces is very simple.<p>
Second, the Protocol Pack supports c language, which is used in many game servers.<p>
Third, the Protocol Pack supports Union structure, which uses less RAM, this make it more suitable to develop mobile applications.

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
