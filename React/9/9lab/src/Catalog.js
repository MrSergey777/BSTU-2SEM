import React from "react";

function Catalog({ products }) {
  return (
    <div style={{ margin: "20px" }}>
      <h2>Список товаров</h2>
      <div style={{ display: "flex", flexWrap: "wrap", gap: "20px" }}>
        {products.map((product) => (
          <div
            key={product.id}
            style={{
              border: "1px solid #ccc",
              borderRadius: "8px",
              padding: "16px",
              width: "300px",
              boxShadow: "0 2px 4px rgba(0, 0, 0, 0.1)",
            }}
          >
            {product.image && (
              <img
                src={product.image}
                alt={product.name}
                style={{ width: "100%", borderRadius: "8px" }}
              />
            )}
            <h3>{product.name}</h3>
            <p>Описание: {product.description}</p>
            <p>Цена: {product.price} руб.</p>
            <p>Количество: {product.quantity}</p>
            {product.discount > 0 && (
              <p>
                Цена со скидкой:{" "}
                {(product.price * (1 - product.discount / 100)).toFixed(2)} руб.
              </p>
            )}
            {product.isNew && <span style={{ color: "green" }}>Новинка!</span>}
          </div>
        ))}
      </div>
    </div>
  );
}

export default Catalog;
