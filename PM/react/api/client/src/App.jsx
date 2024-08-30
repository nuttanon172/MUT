import { useEffect, useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import axios from 'axios'

function App() {
  const [data, setData] = useState({})
  const [data2, setData2] = useState({})

  useEffect(() => {
    axios.get("http://localhost:3000/api/data").then(res => {
      setData(res.data);
    }).catch(err => {
      console.error("error")
    })
  })

  useEffect(() => {
    axios.get("http://localhost:3000/api/myName").then(res => {
      setData2(res.data);
    }).catch(err => {
      console.error("error")
    })
  })

  return (
    <>
      <table border={1}>
        <tr>
          <div>{data.message}</div>
        </tr>
        <tr>
          <td>{data2.id}</td>
          <td>{data2.Name}</td>
          <td>{data2.Tel}</td>
        </tr>
      </table>
      
    </>
  )
}

export default App
