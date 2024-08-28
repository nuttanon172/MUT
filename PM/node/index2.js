let str1 = "test this is string";
let str2 = "test this is string";
let d = "2024/08/02"

let tmp = d.split("/");
let dd = d.slice(8,10);
let mm = d.slice(5,7);
let yy = d.slice(0,4);
yy  = parseInt(yy) + 543
console.log(dd + '-' + mm + '-' + yy)


console.log(tmp[2] + '-' + tmp[1] + '-' + tmp[0])
console.log(str1);
console.log(str2 + 1);
