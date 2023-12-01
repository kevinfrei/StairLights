import React from 'react';
// import logo from './logo.svg';
import './App.css';
import { CallServer } from './comm';

export function App(): JSX.Element {
  const post = () => {
    CallServer('info')
      .then((v) => console.log(`Result: ${v}`))
      .catch((r) => console.error(r));
  };
  // <img src={logo} className="App-logo" alt="logo" />
  return (
    <div className="App">
      <header className="App-header">
        <p>Click this button. I dare you!</p>
        <p>
          <button onClick={post}>Stuff</button>
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}
