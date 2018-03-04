if (typeof require === "function") {var PPField = require("./PPField");var Utils = require("./Utils");}

var pp = {}

pp.PeopleInfo = (function() {
    "use strict";

    function PeopleInfo(peopleInfo) {
        var o = peopleInfo || {};
        this.userName = new PPField.PPStringField(o.userName);
        this.cityInfos = new PPField.PPArrayField(pp.CityInfo, o.cityInfos);
        this.sex = new PPField.PPUByteField(o.sex);
    }

    Utils.extend(PeopleInfo, PPField.PPCompositeField);

    PeopleInfo.prototype.getUserName = function() {
        return this.userName.value;
    };

    PeopleInfo.prototype.setUserName = function(v) {
        this.userName.value = v;
    };

    PeopleInfo.prototype.getCityInfos = function() {
        return this.cityInfos;
    };

    PeopleInfo.prototype.getSex = function() {
        return this.sex.value;
    };

    PeopleInfo.prototype.setSex = function(v) {
        this.sex.value = v;
    };

    PeopleInfo.prototype.encodeSubField = function(baBuf) {
        this.userName.encode(baBuf, 1);
        this.cityInfos.encode(baBuf, 2);
        this.sex.encode(baBuf, 3);
    };

    PeopleInfo.prototype.getSubField = function(tag) {
        switch (tag) {
            case 1:return this.userName;
            case 2:return this.cityInfos;
            case 3:return this.sex;
            default:return null;
        }
    };

    PeopleInfo.prototype.fromJson = function(opt) {
        var o = opt || {};
        this.userName.fromJson(o.userName);
        this.cityInfos.fromJson(o.cityInfos);
        this.sex.fromJson(o.sex);
    };

    PeopleInfo.prototype.toJson = function() {
        return {userName:this.userName.toJson(), cityInfos:this.cityInfos.toJson(), sex:this.sex.toJson()};
    };

    return PeopleInfo;
})();

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