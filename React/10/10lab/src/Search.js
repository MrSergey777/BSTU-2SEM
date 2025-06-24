import React, { useState } from "react";

function Search({ products }) {
  const [searchTerm, setSearchTerm] = useState("");
  const [isExactMatch, setIsExactMatch] = useState(false);
  const [searchResults, setSearchResults] = useState([]);

  const handleSearch = () => {
    const results = products.filter((product) =>
      isExactMatch
        ? product.name.toLowerCase() === searchTerm.toLowerCase()
        : product.name.toLowerCase().includes(searchTerm.toLowerCase())
    );
    setSearchResults(results);
  };

  return (
    <div style={{ margin: "20px" }}>
      <h2>Поиск товаров</h2>
      <div style={{ marginBottom: "10px" }}>
        <input
          type="text"
          placeholder="Введите название товара"
          value={searchTerm}
          onChange={(e) => setSearchTerm(e.target.value)}
          style={{
            padding: "8px",
            width: "300px",
            marginRight: "10px",
            border: "1px solid #ccc",
            borderRadius: "4px",
          }}
        />
        <button
          onClick={handleSearch}
          style={{
            padding: "8px 16px",
            backgroundColor: "#007BFF",
            color: "#fff",
            border: "none",
            borderRadius: "4px",
            cursor: "pointer",
          }}
        >
          Искать
        </button>
      </div>
      <label style={{ display: "block", marginBottom: "10px" }}>
        <input
          type="checkbox"
          checked={isExactMatch}
          onChange={() => setIsExactMatch(!isExactMatch)}
          style={{ marginRight: "8px" }}
        />
        Точный поиск
      </label>
      <div>
        <h3>Результаты поиска:</h3>
        {searchResults.length > 0 ? (
          <ul>
            {searchResults.map((product) => (
              <li key={product.id} style={{ marginBottom: "10px" }}>
                <h4>{product.name}</h4>
                <p>Количество: {product.quantity}</p>
                <p>Цена: {product.price} руб.</p>
                {product.discount > 0 && (
                  <p>
                    Цена со скидкой:{" "}
                    {(product.price * (1 - product.discount / 100)).toFixed(2)}{" "}
                    руб.
                  </p>
                )}
                <p>Описание: {product.description}</p>
              </li>
            ))}
          </ul>
        ) : (
          <p>Ничего не найдено.</p>
        )}
      </div>
    </div>
  );
}

export default Search;
