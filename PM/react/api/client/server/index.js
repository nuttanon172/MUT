const express = require('express')
const app = express()
const port = 3000;
const cors = require('cors');

app.use(cors());

app.get('/api/data', (req,res) => {
	const data = {
		message : "This is message from A server"
	}

	res.json(data);
});

app.get('/api/myName', (req,res) => {
	const data = {
		id : "6511130035",
		Name: "Natthanon Tairattanapong",
		Tel: "098-XXX-XXXX"
	}

	res.json(data);
});

app.listen(port, () => {
  console.log("sever is running on port " + port);
});
