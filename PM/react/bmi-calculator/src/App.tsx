import { useState } from "react";
import "./App.css";

function App() {
  const [weight, setWeight] = useState(0);
  const [height, setHeight] = useState(0);
  const [bmi, setBmi] = useState(0);

  const handleOnChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = event.target;
    
    if (name === "weight") {
      setWeight(Number(value));
      console.log(weight);
    } else if (name === "height") {
      setHeight(Number(value));
      console.log(height);
    }
  };

  const calculateBmi = () => {
    // const bmi = weight / ((height / 100) * (height / 100))

    const bmi = weight / (height / 100) ** 2;
    setBmi(bmi);
  };

  const checkBmiResult = () => {
    if (bmi === 0) return "-";
    if (bmi < 18.5) return "อยู่ในเกณฑ์น้ำหนักน้อย / ผอม";
    if (bmi < 25) return "อยู่ในเกณฑ์ปกติ (สุขภาพดี)";
    if (bmi < 30) return "อยู่ในเกณฑ์ท้วม / โรคอ้วนระดับ 1";
    if (bmi < 35) return "อยู่ในเกณฑ์อ้วน / โรคอ้วนระดับ 2";
    if (bmi >= 35) return "อยู่ในเกณฑ์อ้วนมาก / โรคอ้วนระดับ 3";
  };

  const getResultClass = () => {
    if (bmi < 18.5) return "gray";
    if (bmi < 22.9) return "green";
    if (bmi < 24.9) return "yellow";
    return "red";
  };

  return (
    <div className="bmi-app">
      <h1 className="title">BMI Calculator</h1>
      <p className="subtitle">โปรแกรมคำนวณค่าดัชนีมวลกาย - BMI</p>

      <label htmlFor="wight">น้ำหนัก (kg)</label>
      <input type="number" name="weight" onChange={handleOnChange} />

      <label htmlFor="height">ส่วนสูง (cm)</label>
      <input type="number" name="height" onChange={handleOnChange} />

      <button type="button" onClick={calculateBmi}>
        คำนวณ
      </button>

      <div className="result">
        <p>ค่า BMI คือ: {bmi}</p>
        <p>ผลลัพธ์</p>
        <p className={getResultClass()}>{checkBmiResult()}</p>
      </div>
      <hr />
    </div>
  );
}

export default App;
