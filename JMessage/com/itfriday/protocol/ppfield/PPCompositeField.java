package com.itfriday.protocol.ppfield;

import com.itfriday.utils.ByteArray;
import com.itfriday.utils.ToolException;

/**
 * Created by erisenxu on 2016/9/3.
 */
public abstract class PPCompositeField implements PPField {
    @Override
    public void decode(byte[] szBuf, int iStart) throws ToolException {
        if (null == szBuf || iStart < 0) {
            throw new ToolException("Composite field decode error, the parameter is null");
        }

        int iMinLen = 3;//sizeof(U16) + sizeof(U8);    // 字段最小长度
        PPField pstSubField = null;

        short nTag = 0;
        byte bType = 0;
        int start = iStart + iMinLen;

        int iLeftLen;
        int iFieldLen;

        if (szBuf.length < start + 4) {
            throw new ToolException("Composite field decode error, the length of the bytes is less than" + (start + 4));
        }

        // 求字段长度
        iLeftLen = ByteArray.bytesToInt(szBuf, start);
        start += 4;

        while (iLeftLen > 0) {

            // 解析Tag和Type
            if (szBuf.length < start + iMinLen) {
                throw new ToolException("Composite field decode error, the length of the bytes is less than" + (start + iMinLen));
            }

            // Tag和类型
            nTag = ByteArray.bytesToShort(szBuf, start);
            bType = szBuf[start + 2];

            // 消息长度
            iFieldLen = getLengthByType(bType, szBuf, start);
            if (iFieldLen < 0 || szBuf.length < start + iFieldLen) {
                throw new ToolException("Composite field decode error, the length of the bytes is less than" + (start + iFieldLen));
            }

            // 取消息对象
            pstSubField = getSubField(nTag);

            // 对认识的字段进行解码，不认识的字段直接丢弃
            if (pstSubField != null) {
                pstSubField.decode(szBuf, start);
            }
            // 不认识的字段，直接丢弃 (兼容旧版本)
            start += iFieldLen;
            iLeftLen -= iFieldLen;
        }
    }

    @Override
    public void setValue(String value) {
    }

    /**
     * 取某个类型字段的长度
     * @param bType 字段类型
     * @param szBuf 要解析的协议，里面可能包含长度字段
     * @param iStart 协议的起始
     * @return 返回字段的长度(byte)，长度包含Tag和Type的长度
     */
    public static int getLengthByType(byte bType, byte[] szBuf, int iStart) throws ToolException {
        int iMinLen = 3;

        switch (bType) {
            case PPFieldType.FIELD_TYPE_BYTE:
            case PPFieldType.FIELD_TYPE_UBYTE:
                return iMinLen + 1;
            case PPFieldType.FIELD_TYPE_SHORT:
            case PPFieldType.FIELD_TYPE_USHORT:
                return iMinLen + 2;
            case PPFieldType.FIELD_TYPE_INT:
            case PPFieldType.FIELD_TYPE_UINT:
                return iMinLen + 4;
            case PPFieldType.FIELD_TYPE_LONG:
            case PPFieldType.FIELD_TYPE_ULONG:
                return iMinLen + 8;
            case PPFieldType.FIELD_TYPE_STRING:
            case PPFieldType.FIELD_TYPE_BYTES:
            case PPFieldType.FIELD_TYPE_TLV:
            case PPFieldType.FIELD_TYPE_ARRAY: {
                if (null != szBuf && szBuf.length >= iStart + iMinLen + 4) {
                    int nLen = ByteArray.bytesToInt(szBuf, iStart + iMinLen);
                    return iMinLen + 4 + nLen;
                }
                return -1;
            }
            default:
                return -2;
        }
        //return iMinLen;
    }

    /**
     * 通过标签查询子字段
     * @param tag 子字段的标签
     * @return 返回tag对应的子字段，若没有子字段，返回null
     */
    protected abstract PPField getSubField(short tag);
}
