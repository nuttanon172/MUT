var i = 10; // Var Global variable
let y = 20;
const x = 30;

if (i==10){
	let a = 40;
	var b = 50;

	console.log(i);
	console.log("y: " + y);
	console.log(x);
}
//console.log(a);
console.log(b);
console.log("Timestamp:2 %d", new Date());
let user = { // object
	id: "6511130035",
	name: "Metin",
	GPA: 3.0
};

console.log("ID: %s", user.id);
console.log("Name: %s", user.name);
console.log("GPA: %f",user.GPA);
console.log("object: %o",user);

console.log("Timestamp:2 %d", new Date());

let fruit = ["Apple", "Banana", "Orange"]
for (let i =0;i < fruit.length;i++){
	console.log("%d. %s", i+1, fruit[i]);
}

function currentDate(){
	let date = new Date().toDateString();
	console.log("The current date is: " + date);
}

function add2Num(a, b){
	console.log("%d + %d = %d", a + b);
}

function getNum(){
	return 5;
}

currentDate();
add2Num(2, 10);
console.log(getNum());
