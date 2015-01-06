Protocol-pack
=============

Protocol Pack is a way of encoding or decoding structured data, It's similar with Google Protocol Buffer. But easier to understand and use. And it produce code in C++, C...

Why Use Protocol-pack but not Protocol Buffer?
=============
First, the Protocol Pack is easier to understand and use. The code it produces is very simple.
Second, the Protocol Pack supports c language, which is used in many game servers.

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
