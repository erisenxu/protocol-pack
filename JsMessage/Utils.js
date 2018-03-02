var Utils = {};
Utils.extend = function(c, p) {
    var F = function() {};
    F.prototype = p.prototype;
    c.prototype = new F();
    c.prototype.constructor = c;
    c.uber = p.prototype;
};

// Node.js check
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {
    module.exports = Utils;
}

// amd check
if (typeof define === "function" && define.amd) {
    define("utils", [], function() {
        return Utils;
    });
}