import { useState } from "react";
import "./App.css";

function App() {
  const [homework, setHomework] = useState(0);
  const [mid, setMid] = useState(0);
  const [final, setFinal] = useState(0);
  const [score, setScore] = useState(0);

  const handleOnChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = event.target;

    if (name === "homework") {
      setHomework(Number(value));
      console.log(homework);
    } else if (name === "mid") {
      setMid(Number(value));
      console.log(mid);
    } else if (name === "final") {
      setFinal(Number(value));
      console.log(final);
    }
  };

  const calculateScore = () => {
    setScore(0);
    if (homework < 0 || homework > 40)
      alert("Invalid:\nHomework Exam Score Input (0-40)");
    else if (mid < 0 || mid > 25)
      alert("Invalid:\nMidterm Exam Score Input (0-25)");
    else if (final < 0 || final > 35)
      alert("Invalid:\nFinalterm Exam Score Input (0-35)");
    else {
      const score = homework + mid + final;
      console.log(score);
      setScore(score);
    }
  };

  const checkScoreResult = () => {
    if (score >= 71 && score <= 100) return "A";
    if (score >= 61 && score <= 70) return "B";
    if (score >= 51 && score <= 60) return "C";
    if (score >= 41 && score <= 50) return "D";
    if (score >= 0 && score <= 40) return "F";
    return "Error score";
  };

  const getResultClass = () => {
    if (score >= 71 && score <= 100) return "Grade A";
    if (score >= 61 && score <= 70) return "Grade B";
    if (score >= 51 && score <= 60) return "Grade C";
    if (score >= 41 && score <= 50) return "Grade D";
    if (score >= 0 && score <= 40) return "Grade F";
    return "Grade Error";
  };

  return (
    <div className="score-app">
      <h1 className="title">Grade Calculator</h1>
      <h3 className="subtitle">โปรแกรมคำนวณเกรด</h3>

      <div className="inputContainer">
        <label htmlFor="homework">Homework Score (Max 40)</label>
        <input type="number" name="homework" onChange={handleOnChange} />
      </div>
      <div className="inputContainer">
        <label htmlFor="mid">Midterm Exam Score (Max 25)</label>
        <input type="number" name="mid" onChange={handleOnChange} />
      </div>
      <div className="inputContainer">
        <label htmlFor="final">Finalterm Exam Score (Max 35)</label>
        <input type="number" name="final" onChange={handleOnChange} />
      </div>
      <button type="button" onClick={calculateScore}>
        คำนวณ
      </button>

      <div className="result">
        <p>คะแนนรวม: {score}</p>
        <p>ผลลัพธ์</p>
        <p className={getResultClass()}>Grade: {checkScoreResult()}</p>
      </div>
      <hr />
    </div>
  );
}

export default App;
