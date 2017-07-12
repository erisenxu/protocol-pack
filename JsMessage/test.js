var ByteArray = require("./ByteArray");

var s = '中东方丽景撒旦法拉圣诞节福利及阿评委proiwpiokldow90er349-jroprw902094395djfgjjg但是分集爱上了附近萨拉街坊邻居卡萨房间卡设计费沙发束带结发拉世纪东方安抚as发送到发斯蒂芬拉束带结发撒代理费阿斯蒂芬撒发生多了几分私搭乱建放假啊死定了福建师大发法警队法律手段简历发士大夫撒代理费圣诞节福建省凉快圣诞节疯狂咯我肉卫生间佛问饿哦ID是大佛哦已uweoi我让我去而欧文强弱我奇瑞哦亲微弱iwqoijjxgoisadfiosafoi斯顿发了数据拉附件是2384023的肌肤有文4q981230xyz';

var ba = new ByteArray();
ba.appendString(s);
//console.log(x);

var y = ByteArray.fromUTF8(ba.getBytes());
console.log(y===s);
console.log(ba.length);
//ba.appendS8(-4);
//ba.appendS8(7);
//ba.appendS8(8);
ba.clear();
ba.appendInt64('1311768467294899695');
console.log(ba.dataView);
console.log(ba.getInt64(0) === '1311768467294899695');//*/
//for (var i = 0; i < ba.length; i++) {
//	console.log(ba.getU8(i).toString(16));
//}