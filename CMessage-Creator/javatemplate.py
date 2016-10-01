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
# Java文件模版-字段模版
#
JTEMPLATE = '''/*
 * @(#) ${ClassName}.java Created by @itfriday message creator
 */

package ${PackageName};

import com.itfriday.protocol.ppfield.*;
import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * $ClassDesc
 */
public class ${ClassName} extends PPCompositeField${ImplUnion} {${AttrDefine}${AttrSetGet}
    @Override
    public void encode(ByteArray baBuf, short tag) throws ToolException {
        baBuf.append(tag).append(PPFieldType.FIELD_TYPE_TLV);

        // 预留长度字段
        baBuf.append(0);
        // 子字段编码前长度
        int iOldLen = baBuf.length();

        // 编码子字段${FieldEncode}

        // 这个必须放后面，因为append有可能那个将baBuf的Data的地址改变
        int nAddLen = baBuf.length() - iOldLen;
        byte[] byLen = ByteArray.intToBytes(nAddLen);
        for (int i = iOldLen - 4, j = 0; i < baBuf.length() && j < byLen.length; i++, j++) {
            baBuf.set(i, byLen[j]);
        }
    }

    @Override
    public void format(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";
        sbBuf.append(sPrefix).append("[").append(sFieldName).append("]\\n");${Formats}
    }

    @Override
    public void toXml(StringBuilder sbBuf, String sFieldName, String sPrefix) {
        String sSubPrefix = sPrefix + "    ";

        sbBuf.append(sPrefix).append("<").append(sFieldName).append(">\\n");${ToXmls}
        sbBuf.append(sPrefix).append("</").append(sFieldName).append(">\\n");
    }

    @Override
    protected PPField getSubField(short tag) {
        switch (tag) {${GetSubField}
        default:
            return null;
        }
    }
}
''';
