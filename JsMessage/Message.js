if (typeof require === "function") var bigInt = require("ByteArray");

var PPField = {};

PPField.FIELD_TYPE_INVALID = 0; // 不合法(未初始化)的字段类型
PPField.FIELD_TYPE_BYTE = 1; // S8，占1个字节
PPField.FIELD_TYPE_UBYTE = 2; // U8，占1个字节
PPField.FIELD_TYPE_SHORT = 3; // S16，占2个字节
PPField.FIELD_TYPE_USHORT = 4; // U16，占2个字节
PPField.FIELD_TYPE_INT = 5; // S32，占4个字节
PPField.FIELD_TYPE_UINT = 6; // U32，占4个字节
PPField.FIELD_TYPE_LONG = 7; // S64，占8个字节
PPField.FIELD_TYPE_ULONG = 8; // U64，占8个字节
PPField.FIELD_TYPE_STRING = 9; // 字符串，特殊的TLV字段
PPField.FIELD_TYPE_BYTES = 10; // 字节数组，特殊的TLV字段
PPField.FIELD_TYPE_TLV = 11; // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
PPField.FIELD_TYPE_ARRAY = 12; // 数组

// 获取字段的长度
PPField.getLengthByType = function(fieldType, baBuf, start) {
    var minLen = Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT;
    switch (fieldType) {
        case PPField.FIELD_TYPE_BYTE:
            return minLen + Int8Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_UBYTE:
            return minLen + Uint8Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_SHORT:
            return minLen + Int16Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_USHORT:
            return minLen + Uint16Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_INT:
            return minLen + Int32Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_UINT:
            return minLen + Uint32Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_LONG:
            return minLen + Float64Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_ULONG:
            return minLen + Float64Array.BYTES_PER_ELEMENT;
        case PPField.FIELD_TYPE_STRING:
        case PPField.FIELD_TYPE_BYTES:
        case PPField.FIELD_TYPE_TLV:
        case PPField.FIELD_TYPE_ARRAY:
            {
                if (baBuf && baBuf.length >= start + minLen + Uint32Array.BYTES_PER_ELEMENT) {
                    var len = baBuf.getUint32(start + minLen);
                    return minLen + Uint32Array.BYTES_PER_ELEMENT + len;
                }
                return -1;
            }
        default:
            return -2;
    }
};

PPField.PPByteField = (function() {
    "use strict";

    function PPByteField(value) {
        this.value = value || 0;
    }

    PPByteField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_BYTE).appendInt8(this.value);
    };

    PPByteField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getInt8(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPByteField;
})();

PPField.PPUByteField = (function() {
    "use strict";

    function PPUByteField(value) {
        this.value = value || 0;
    }

    PPUByteField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_UBYTE).appendUint8(this.value);
    };

    PPUByteField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getUint8(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPUByteField;
})();

PPField.PPShortField = (function() {
    "use strict";

    function PPShortField(value) {
        this.value = value || 0;
    }

    PPShortField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_SHORT).appendInt16(this.value);
    };

    PPShortField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getInt16(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPShortField;
})();

PPField.PPUShortField = (function() {
    "use strict";

    function PPUShortField(value) {
        this.value = value || 0;
    }

    PPUShortField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_USHORT).appendUint16(this.value);
    };

    PPUShortField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getUint16(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPUShortField;
})();

PPField.PPIntField = (function() {
    "use strict";

    function PPIntField(value) {
        this.value = value || 0;
    }

    PPIntField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_INT).appendInt32(this.value);
    };

    PPIntField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getInt32(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPIntField;
})();

PPField.PPUIntField = (function() {
    "use strict";

    function PPUIntField(value) {
        this.value = value || 0;
    }

    PPUIntField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_UINT).appendUint32(this.value);
    };

    PPUIntField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getUint32(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPUIntField;
})();

PPField.PPLongField = (function() {
    "use strict";

    function PPLongField(value) {
        this.value = value || '0';
    }

    PPLongField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_LONG).appendInt64(this.value);
    };

    PPLongField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getInt64(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPLongField;
})();

PPField.PPULongField = (function() {
    "use strict";

    function PPULongField(value) {
        this.value = value || '0';
    }

    PPULongField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_ULONG).appendUint64(this.value);
    };

    PPULongField.prototype.decode = function(baBuf, start) {
        this.value = baBuf.getUint64(start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT);
    };

    return PPULongField;
})();

PPField.PPStringField = (function() {
    "use strict";

    function PPStringField(value) {
        this.value = value || '';
    }

    PPStringField.prototype.encode = function(baBuf, tag) {
        var v = ByteArray.toUTF8(this.value);
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_STRING).appendUint32(v.length).appendBytes(v);
    };

    PPStringField.prototype.decode = function(baBuf, start) {
        var istart = start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT;
        var len = baBuf.getUint32(istart);
        istart += Uint32Array.BYTES_PER_ELEMENT;
        var b = baBuf.getBytes(istart, len);
        this.value = ByteArray.fromUTF8(b);
    };

    return PPStringField;
})();

PPField.PPBytesField = (function() {
    "use strict";

    function PPBytesField(value) {
        this.value = value || [];
    }

    PPBytesField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_BYTES).appendUint32(this.value.length).appendBytes(this.value);
    };

    PPBytesField.prototype.decode = function(baBuf, start) {
        var istart = start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT;
        var len = baBuf.getUint32(istart);
        istart += Uint32Array.BYTES_PER_ELEMENT;
        this.value = baBuf.getBytes(istart, len);
    };

    return PPBytesField;
})();

PPField.PPArrayField = (function() {
    "use strict";

    function PPArrayField(fieldCreator) {
        this.value = [];
        this.fieldCreator = fieldCreator;
    }

    PPArrayField.prototype.getFieldByIndex = function(index) {
        // index 只可以>=0 && <= mValue.size(),如果等于mValue.size(), 需要重新创建一个新的
        if (index < 0 || index > mValue.size()) {
            throw "getFieldByIndex error, the index " + index + " is invalid";
        }
        if (index < this.value.length) return this.value[index];

        if (!this.fieldCreator) {
            throw "getFieldByIndex error, field to create subfield, cause the field creator is null";
        }

        var field = this.fieldCreator.create();
        this.value.push(field);
        return field;
    };

    PPArrayField.prototype.encode = function(baBuf, tag) {
        baBuf.appendUint16(tag).appendUint8(PPField.FIELD_TYPE_ARRAY);
        var lenPos = baBuf.length;
        baBuf.appendUint32(0);
        var oldLen = baBuf.length;
        baBuf.appendUint16(this.value.length);
        for (var i = 0; i < this.value.length; i++) {
            this.value[i].encode(baBuf, tag);
        }
        baBuf.dataView.setUint32(lenPos, baBuf.length - oldLen);
    };

    PPArrayField.prototype.decode = function(baBuf, start) {
        var istart = start + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint32Array.BYTES_PER_ELEMENT;
        // 剩余字节长度
        var leftLen = baBuf.length - istart;
        // 数组数量
        var arrNum = baBuf.getUint16(istart);
        leftLen -= Uint16Array.BYTES_PER_ELEMENT;
        istart += Uint16Array.BYTES_PER_ELEMENT;
        // 数组元素类型长度检查
        if (baBuf.length < istart + Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT) {
            throw "Array field decode error, the message buffer is too short";
        }
        // 数组元素类型
        var fieldType = baBuf.getUint8(istart + Uint16Array.BYTES_PER_ELEMENT);
        // 清空数据
        this.value = [];
        // 解析子字段
        for (var i = 0; i < arrNum; i++) {
            // 通过类型获得数据长度
            var msgLen = PPField.getLengthByType(fieldType, baBuf, istart);
            if (leftLen < msgLen || msgLen < 0) {
                throw "Array field decode error, the message buffer is too short";
            }
            // 解码子字段
            this.getFieldByIndex(i).decode(baBuf, istart);
            istart += msgLen;
            leftLen -= msgLen;
        }
    };

    return PPArrayField;
})();

PPField.PPCompositeField = (function() {
    "use strict";

    function PPCompositeField() {}

    PPCompositeField.prototype.encode = function(baBuf, tag) {};

    PPCompositeField.prototype.getSubField = function(tag) {
        return null;
    }

    PPCompositeField.prototype.decode = function(baBuf, start) {
        if (null == baBuf || start < 0) {
            throw "Composite field decode error, the parameter is null";
        }

        var iMinLen = Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT; // 字段最小长度
        var pstSubField = null;

        var nTag = 0;
        var bType = 0;
        var istart = start + iMinLen;

        var iLeftLen = 0;
        var iFieldLen = 0;

        if (baBuf.length < istart + Uint32Array.BYTES_PER_ELEMENT) {
            throw "Composite field decode error, the length of the bytes is less than" + (istart + Uint32Array.BYTES_PER_ELEMENT);
        }

        // 求字段长度
        iLeftLen = baBuf.getUint32(istart);
        istart += Uint32Array.BYTES_PER_ELEMENT;

        while (iLeftLen > 0) {

            // 解析Tag和Type
            if (baBuf.length < istart + iMinLen) {
                throw new ToolException("Composite field decode error, the length of the bytes is less than" + (istart + iMinLen));
            }

            // Tag和类型
            nTag = baBuf.getUint16(istart);
            bType = baBuf.getUint8(istart + 2);

            // 消息长度
            iFieldLen = PPField.getLengthByType(bType, baBuf, istart);
            if (iFieldLen < 0 || baBuf.length < istart + iFieldLen) {
                throw "Composite field decode error, the length of the bytes is less than" + (istart + iFieldLen);
            }

            // 取消息对象
            pstSubField = this.getSubField(nTag);

            // 对认识的字段进行解码，不认识的字段直接丢弃
            if (pstSubField) {
                pstSubField.decode(baBuf, istart);
            }
            // 不认识的字段，直接丢弃 (兼容旧版本)
            istart += iFieldLen;
            iLeftLen -= iFieldLen;
        }
    }

    return PPCompositeField;
})();

// Node.js check
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {
    module.exports = PPField;
}

// amd check
if (typeof define === "function" && define.amd) {
    define("pp-field", [], function() {
        return PPField;
    });
}