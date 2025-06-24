import React from "react";

function SortTable({ products, onSort }) {
  return (
    <table border="1" style={{ width: "100%", textAlign: "left" }}>
      <thead>
        <tr>
          <th onClick={() => onSort("name")}>Наименование</th>
          <th onClick={() => onSort("price")}>Стоимость</th>
          <th onClick={() => onSort("quantity")}>Количество</th>
          <th>Изображение</th>
          <th>Описание</th>
          <th>Новинка</th>
          <th onClick={() => onSort("discount")}>Скидка</th>
        </tr>
      </thead>
      <tbody>
        {products.map((product) => (
          <tr key={product.id}>
            <td>{product.name}</td>
            <td>{product.price}₽</td>
            <td>{product.quantity}</td>
            <td>
              <img
                src={product.image}
                alt={product.name}
                style={{ width: "50px", height: "50px" }}
              />
            </td>
            <td>{product.description}</td>
            <td>{product.isNew ? "Да" : "Нет"}</td>
            <td>{product.discount}%</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}

export default SortTable;
