import React from "react";
import ReactDOM from "react-dom/client"; // Импортируйте ReactDOM для createRoot
import App from "./App";

const root = ReactDOM.createRoot(document.getElementById("root")); // Используйте createRoot
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
