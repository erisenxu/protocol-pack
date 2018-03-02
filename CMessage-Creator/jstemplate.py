#!/usr/bin/env python
#coding:utf-8
#=================================================================
# @ Author : Erisenxu @ Innovate Center
# @ Desc : 文件模版
# @ FileName : ctemplate.py
# @ Date : 2014-03-29
# @ ModifyHistory :
# @ Remark :
#==================================================================

#
# JavaScript文件模版-字段模版
#
JSTEMPLATE = '''if (typeof require === "function") {var PPField = require("./PPField");var Utils = require("./Utils");}
${ppMsgDefine}
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {module.exports = pp;}''';

#
# 类膜拜
#
JC_TEMPLATE = '''pp.${ClassName}=(function(){"use strict";
function ${ClassName}(opt){var o=opt||{};${AttrDefine}}
Utils.extend(${ClassName},PPField.PPCompositeField);${AttrSetGet}
${ClassName}.prototype.encodeSubField=function(baBuf){${FieldEncode}};
${ClassName}.prototype.getSubField=function(tag){switch(tag){${GetSubField}default:return null;}};
${ClassName}.prototype.fromJson=function(opt) {var o = opt || {};${FieldFromJson}};
${ClassName}.prototype.toJson=function(){return {${FieldToJson}};};return ${ClassName};
})();''';