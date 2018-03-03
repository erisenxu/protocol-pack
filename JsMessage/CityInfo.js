if (typeof require === "function") {var PPField = require("./PPField");var Utils = require("./Utils");}

var pp = {}

pp.CoutryInfo = (function() {
    "use strict";

    function CoutryInfo(coutryInfo) {
    	var ci = coutryInfo || {};
        this.cityInfo = new pp.CityInfo(ci.cityInfo);
    }

    Utils.extend(CoutryInfo, PPField.PPCompositeField);

    CoutryInfo.prototype.getCityInfo = function() {
    	return this.cityInfo;
    };

    CoutryInfo.prototype.encodeSubField = function(baBuf) {
        this.cityInfo.encode(baBuf, 1);
    };

    CoutryInfo.prototype.getSubField = function(tag) {
    	switch (tag) {
    		case 1:return this.cityInfo;
    		default:return null;
    	}
    };

    CoutryInfo.prototype.fromJson = function(opt) {
    	var o = opt || {};
    	this.cityInfo.fromJson(o.cityInfo);
    };

    CoutryInfo.prototype.toJson = function() {
    	return {cityInfo:this.cityInfo.toJson()};
    };

    return CoutryInfo;
})();

pp.CityInfo = (function() {
    "use strict";

    function CityInfo(cityInfo) {
    	var o = cityInfo || {};
        this.cityCode = new PPField.PPStringField(o.cityCode);
        this.cityName = new PPField.PPStringField(o.cityName);
    }

    Utils.extend(CityInfo, PPField.PPCompositeField);

    CityInfo.prototype.setCityCode = function(cityCode) {
    	this.cityCode.value = cityCode;
    };

    CityInfo.prototype.getCityCode = function() {
    	return this.cityCode.value;
    };

    CityInfo.prototype.setCityName = function(cityName) {
    	this.cityName.value = cityName;
    };

    CityInfo.prototype.getCityName = function() {
    	return this.cityName.value;
    };

    CityInfo.prototype.encodeSubField = function(baBuf) {
        this.cityCode.encode(baBuf, 1);
        this.cityName.encode(baBuf, 2);
    };

    CityInfo.prototype.getSubField = function(tag) {
    	switch (tag) {
    		case 1:return this.cityCode;
    		case 2:return this.cityName;
    		default:return null;
    	}
    };

    CityInfo.prototype.fromJson = function(opt) {
    	var o = opt || {};
    	this.cityCode.fromJson(o.cityCode);
    	this.cityName.fromJson(o.cityName);
    };

    CityInfo.prototype.toJson = function() {
    	return {cityCode:this.cityCode.toJson(), cityName:this.cityName.toJson()};
    };

    return CityInfo;
})();

// Node.js check
if (typeof module !== "undefined" && module.hasOwnProperty("exports")) {
    module.exports = pp;
}

// amd check
if (typeof define === "function" && define.amd) {
    define("pp", [], function() {
        return pp;
    });
}