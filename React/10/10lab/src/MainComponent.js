import React, { useState } from "react";
import Catalog from "./Catalog";
import SortTable from "./components/SortTable";
import { Provider } from "react-redux";
import { store } from "./redux/store";
import OrderForm from "./components/OrderForm";

function MainComponent() {
  const initialProducts = [
    {
      id: 1,
      name: "Смартфон Galaxy",
      price: 20000,
      quantity: 15,
      weight: 0.3, // вес продукта в килограммах
      description: "Мощный смартфон с большим экраном.",
      isNew: true,
      discount: 10,
    },
    {
      id: 2,
      name: "Ноутбук Pro",
      price: 80000,
      quantity: 8,
      weight: 2.5, // вес продукта в килограммах
      description: "Лёгкий и мощный ноутбук для работы.",
      isNew: false,
      discount: 15,
    },
    // Другие продукты...
  ];

  const [products, setProducts] = useState(initialProducts);

  const sortProducts = (field) => {
    let sorted = [...products];
  
    if (field === "name") {
      sorted.sort((a, b) => a[field].localeCompare(b[field]));
    } else if (["price", "quantity", "discount"].includes(field)) {
      sorted.sort((a, b) => a[field] - b[field]);
    }
  
    // Новинки всегда первыми
    sorted.sort((a, b) => b.isNew - a.isNew);
  
    setProducts(sorted);
  };
  
  

  return (
    <Provider store={store}>
      <div>
        <h1>Каталог товаров</h1>
        <SortTable products={products} onSort={sortProducts} />
        <Catalog products={products} />
        <OrderForm />
      </div>
    </Provider>
  );
}

export default MainComponent;
