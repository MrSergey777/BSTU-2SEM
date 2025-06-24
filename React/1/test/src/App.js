import React from 'react';
import './App.css';

function App() {
  let date = new Date();
  date = date.toString();

  return (
    <div>
      <div>{date}</div>
      {gentable()}
      {ChessBoard()}
    </div>
  );
}

function gentable() {
  let stocks = [
    {
      stock_name: "EFX",
      company_name: "Equifax Inc",
      price: 163.55,
      currency: "USD",
      change: "+9.03"
    },
    {
      stock_name: "IRM",
      company_name: "Iron Mountain Inc",
      price: 33.21,
      currency: "USD",
      change: "+1.42"
    },
    {
      stock_name: "NTAP",
      company_name: "NetApp Inc",
      price: 54.81,
      currency: "USD",
      change: "-6.01"
    },
    {
      stock_name: "CTL",
      company_name: "Centurylink Inc",
      price: 13.79,
      currency: "USD",
      change: "-1.37"
    }
  ];
  let rows = [];
  for (let i = 0; i < stocks.length; i++) {
    let changeClass = stocks[i].change.startsWith('+') ? 'positive-change' : 'negative-change';
    rows.push(
      <tr key={i}>
        <td>{stocks[i].stock_name}</td>
        <td>{stocks[i].company_name}</td>
        <td>{stocks[i].price}</td>
        <td>{stocks[i].currency}</td>
        <td className={changeClass}>{stocks[i].change}</td>
      </tr>
    );
  }
  return (
    <table border={"2px"}>
      <tr>
        <th>Stock Name</th>
        <th>Company Name</th>
        <th>Price</th>
        <th>Currency</th>
        <th>Change</th>
      </tr>
      {rows}
    </table>
  );
}
function ChessBoard() {
  const renderSquare = (i, j) => {
    const black = (i + j) % 2 === 1 ? "black" : "white";
    return (
      <div className={`square ${black}`} key={`${i}-${j}`}>
        {i === 7 && <div className="notation-x">{String.fromCharCode(97 + j)}</div>}
        {j === 0 && <div className="notation-y">{8 - i}</div>}
        {i === 7 && <div className="notation-x1">{String.fromCharCode(97 + j)}</div>}
        {j === 0 && <div className="notation-y1">{8 - i}</div>}
      </div>
    );
  };

  const renderBoard = () => {
    let board = [];
    for (let i = 0; i < 8; i++) {
      for (let j = 0; j < 8; j++) {
        board.push(renderSquare(i, j));
      }
    }
    return board;
  };

  return (
    <div className="chess-board">
      {renderBoard()}
    </div>
  );
}
export default App;
