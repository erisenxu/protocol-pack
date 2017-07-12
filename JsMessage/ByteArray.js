if (typeof require === "function") var bigInt = require("big-integer");

var ByteArray = (function() {
    "use strict";

    function ByteArray(size) {
        this.size = size || 1024;
        this.length = 0;
        this.buffer = new ArrayBuffer(this.size);
        this.dataView = new DataView(this.buffer);
    }

    ByteArray.prototype.clear = function() {
        this.length = 0;
    }

    ByteArray.prototype.appendInt8 = function(v) {
        this.expand(Int8Array.BYTES_PER_ELEMENT);
        this.dataView.setInt8(this.length, v);
        this.length += Int8Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getInt8 = function(pos) {
        return this.dataView.getInt8(pos || 0);
    };

    ByteArray.prototype.appendUint8 = function(v) {
        this.expand(Uint8Array.BYTES_PER_ELEMENT);
        this.dataView.setUint8(this.length, v);
        this.length += Uint8Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getUint8 = function(pos) {
        return this.dataView.getUint8(pos || 0);
    };

    ByteArray.prototype.appendInt16 = function(v) {
        this.expand(Int16Array.BYTES_PER_ELEMENT);
        this.dataView.setInt16(this.length, v);
        this.length += Int16Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getInt16 = function(pos) {
        return this.dataView.getInt16(pos || 0);
    };

    ByteArray.prototype.appendUint16 = function(v) {
        this.expand(Uint16Array.BYTES_PER_ELEMENT);
        this.dataView.setUint16(this.length, v);
        this.length += Uint16Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getUint16 = function(pos) {
        return this.dataView.getUint16(pos || 0);
    };

    ByteArray.prototype.appendInt32 = function(v) {
        this.expand(Int32Array.BYTES_PER_ELEMENT);
        this.dataView.setInt32(this.length, v);
        this.length += Int32Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getInt32 = function(pos) {
        return this.dataView.getInt32(pos || 0);
    };

    ByteArray.prototype.appendUint32 = function(v) {
        this.expand(Uint32Array.BYTES_PER_ELEMENT);
        this.dataView.setUint32(this.length, v);
        this.length += Uint32Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getUint32 = function(pos) {
        return this.dataView.getUint32(pos || 0);
    };

    ByteArray.prototype.appendInt64 = function(v) {
        var bg = new bigInt(v);
        this.expand(Float64Array.BYTES_PER_ELEMENT);
        this.dataView.setUint32(this.length, bg.shiftRight(32).and(0xFFFFFFFF));
        this.length += Uint32Array.BYTES_PER_ELEMENT;
        this.dataView.setUint32(this.length, bg.and(0xFFFFFFFF));
        this.length += Uint32Array.BYTES_PER_ELEMENT;
        return this;
    };

    ByteArray.prototype.getInt64 = function(pos) {
        var v1 = this.dataView.getUint32(pos || 0);
        var v2 = this.dataView.getUint32((pos || 0) + Uint32Array.BYTES_PER_ELEMENT);
        return new bigInt(v1).shiftLeft(32).or(v2).toString();
    };

    ByteArray.prototype.appendUint64 = function(v) {
        return this.appendInt64(v);
    };

    ByteArray.prototype.getUint64 = function(pos) {
        return this.getInt64(pos || 0);
    };

    ByteArray.prototype.appendBytes = function(v) {
        v = v || [];
        this.expand(v.length);
        for (var i = 0; i < v.length; i++) {
            this.appendInt8(v[i]);
        }
        return this;
    };

    ByteArray.prototype.getBytes = function(start, len) {
        var v = new Uint8Array(this.buffer, start || 0, len || this.length);
        return Array.prototype.slice.call(v);
    };

    ByteArray.prototype.appendString = function(s) {
        s = s || '';
        this.appendBytes(ByteArray.toUTF8(s));
        return this;
    };

    ByteArray.prototype.expand = function(size) {
        if (size <= 0 || this.length + size <= this.size) return;

        var newSize = this.size + size;
        var newBuffer = new ArrayBuffer(newSize);

        var dataView = new DataView(newBuffer);
        for (var i = 0; i < this.length; i++) {
            dataView.setUint8(i, this.dataView.getUint8(i));
        }

        this.buffer = newBuffer;
        this.dataView = dataView;
        this.size = newSize;
    };

    ByteArray.fromUTF8 = function(arr) {
        if (typeof arr === 'string') {
            return arr;
        }
        var UTF = '';
        for (var i = 0; i < arr.length; i++) {
            var one = arr[i].toString(2);
            var v = one.match(/^1+?(?=0)/);
            if (v && one.length == 8) {
                var bytesLength = v[0].length;
                var store = arr[i].toString(2).slice(7 - bytesLength);
                for (var st = 1; st < bytesLength; st++) {
                    store += arr[st + i].toString(2).slice(2);
                }
                UTF += String.fromCharCode(parseInt(store, 2));
                i += bytesLength - 1;
            } else {
                UTF += String.fromCharCode(arr[i]);
            }
        }
        return UTF;
    };

    ByteArray.toUTF8 = function(s) {
        var back = [];
        var byteSize = 0;
        for (var i = 0; i < s.length; i++) {
            var code = s.charCodeAt(i);
            if (0x00 <= code && code <= 0x7f) {
                byteSize += 1;
                back.push(code);
            } else if (0x80 <= code && code <= 0x7ff) {
                byteSize += 2;
                back.push((192 | (31 & (code >> 6))));
                back.push((128 | (63 & code)));
            } else if ((0x800 <= code && code <= 0xd7ff) ||
                (0xe000 <= code && code <= 0xffff)) {
                byteSize += 3;
                back.push((224 | (15 & (code >> 12))));
                back.push((128 | (63 & (code >> 6))));
                back.push((128 | (63 & code)));
            }
        }
        for (i = 0; i < back.length; i++) {
            back[i] &= 0xff;
        }
        return back;
    };

    return ByteArray;
})();

// Node.js check
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {
    module.exports = ByteArray;
}

// amd check
if (typeof define === "function" && define.amd) {
    define("byte-array", [], function() {
        return ByteArray;
    });
}