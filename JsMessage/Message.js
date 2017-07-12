if (typeof require === "function") var bigInt = require("./ByteArray");

var PPField = {};

PPField.FIELD_TYPE_INVALID = 0; // 不合法(未初始化)的字段类型
PPField.FIELD_TYPE_BYTE = 1;    // S8，占1个字节
PPField.FIELD_TYPE_UBYTE = 2;   // U8，占1个字节
PPField.FIELD_TYPE_SHORT = 3;   // S16，占2个字节
PPField.FIELD_TYPE_USHORT = 4;  // U16，占2个字节
PPField.FIELD_TYPE_INT = 5;     // S32，占4个字节
PPField.FIELD_TYPE_UINT = 6;    // U32，占4个字节
PPField.FIELD_TYPE_LONG = 7;    // S64，占8个字节
PPField.FIELD_TYPE_ULONG = 8;   // U64，占8个字节
PPField.FIELD_TYPE_STRING = 9;  // 字符串，特殊的TLV字段
PPField.FIELD_TYPE_BYTES = 10;  // 字节数组，特殊的TLV字段
PPField.FIELD_TYPE_TLV = 11;    // Tag-Length-Value字段，长度由length决定。其中length占位4个字节，其长度不包含自己
PPField.FIELD_TYPE_ARRAY = 12;   // 数组

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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Int8Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Int16Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint16Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Int32Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint32Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Float64Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Float64Array.BYTES_PER_ELEMENT;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint32Array.BYTES_PER_ELEMENT + len;
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
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint32Array.BYTES_PER_ELEMENT + len;
	};

	return PPBytesField;
})();

PPField.PPArrayField = (function() {
	"use strict";

	function PPArrayField(fieldCreator) {
		this.value = [];
		this.fieldCreator = fieldCreator;
	}

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
		var arrNum = baBuf.getUint16(istart);
		//istart += ;
		this.value = baBuf.getBytes(istart, len);
		// TODO
		return Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT + Uint32Array.BYTES_PER_ELEMENT + len;
	};

	return PPArrayField;
})();

PPField.PPCompositeField = (function() {
	"use strict";

	function PPCompositeField() {
	}

	PPCompositeField.prototype.encode = function(baBuf, tag) {
	};

	PPCompositeField.prototype.decode = function(baBuf, start) {
		var minLen = Uint16Array.BYTES_PER_ELEMENT + Uint8Array.BYTES_PER_ELEMENT;
		var istart += minLen;
		if (baBuf.length < istart + Uint32Array.BYTES_PER_ELEMENT) {
			throw "Composite field decode error, the length of the bytes is less than " + (istart + Uint32Array.BYTES_PER_ELEMENT);
		}

		var leftLen = ByteArray.getUint32(istart);
		istart += Uint32Array.BYTES_PER_ELEMENT;

		while (leftLen > 0) {
			// 解析Tag和Type
			if (baBuf.length < istart + minLen) {
				throw "Composite field decode error, the length of the bytes is less than" + (istart + minLen);
			}
			var tag = ByteArray.getUint16(istart);
			var type = ByteArray.getUint8(istart + Uint16Array.BYTES_PER_ELEMENT);
			// TODO:
		}
	}

	return PPCompositeField;
})();

// Node.js check
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {
	module.exports = PPField;
}

// amd check
if (typeof define === "function" && define.amd ) {  
	define( "pp-field", [], function() {
		return PPField;
	});
}
