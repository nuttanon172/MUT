console.log("Timestamp2: %d", new Date());
let cutGrade = (hw, mid, final) =>{
	let = tmp = hw+mid+final;
	if (hw < 0 || hw > 40 || mid < 0 || mid > 30 || final < 0 || final > 30)
		return "Incorrect input!!";
	if (tmp > 70)
		return "A";
	else if (tmp > 60)
		return "B";
	else if (tmp > 50)
		return "C";
	else if (tmp > 40)
		return "D";
	else if (tmp > 0)
		return "F";
}

console.log(cutGrade(40, 20, 11));

console.log("Timestamp2: %d", new Date());
