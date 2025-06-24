import React from "react";

function Catalog({ products }) {
  return (
    <div style={{ display: "flex", flexWrap: "wrap", gap: "10px" }}>
      {products.map((product) => (
        <div key={product.id} style={{ border: "1px solid #ccc", padding: "10px", width: "200px" }}>
          <img src={product.image} alt={product.name} style={{ width: "100%", height: "auto" }} />
          <h3>{product.name}</h3>
          <p><strong>Описание:</strong> {product.description}</p>
          <p><strong>Стоимость:</strong> {product.price}₽</p>
          {product.discount > 0 && (
            <p>
              <strong>Стоимость со скидкой:</strong>{" "}
              {Math.round(product.price - (product.price * product.discount / 100))}₽
            </p>
          )}
          <p><strong>Количество:</strong> {product.quantity}</p>
          <p><strong>Новинка:</strong> {product.isNew ? "Да" : "Нет"}</p>
        </div>
      ))}
    </div>
  );
}

export default Catalog;
