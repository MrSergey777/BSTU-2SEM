
import React, { useState } from "react";
import Catalog from "./Catalog";
import SortTable from "./SortTable";
import Search from "./Search";

function MainComponent() {
  const initialProducts = [
    {
      id: 1,
      name: "Смартфон Galaxy",
      price: 20000,
      quantity: 15,
      image: "",
      description: "Мощный смартфон с большим экраном.",
      isNew: true,
      discount: 10,
    },
    {
      id: 2,
      name: "Ноутбук Pro",
      price: 80000,
      quantity: 8,
      image: "",
      description: "Лёгкий и мощный ноутбук для работы.",
      isNew: false,
      discount: 15,
    },
    {
      id: 3,
      name: "Наушники Bass Boost",
      price: 5000,
      quantity: 20,
      image: "",
      description: "Высококачественные наушники с глубоким басом.",
      isNew: true,
      discount: 5,
    },
    {
      id: 4,
      name: "Умные часы FitTrack",
      price: 10000,
      quantity: 10,
      image: "",
      description: "Следите за здоровьем с умными часами.",
      isNew: false,
      discount: 20,
    },
  ];

  const [products, setProducts] = useState(initialProducts);

  const sortProducts = (field) => {
    let sorted = [...products];
    if (field === "name") {
      sorted.sort((a, b) => a[field].localeCompare(b[field]));
    } else if (field === "price" || field === "quantity" || field === "discount") {
      sorted.sort((a, b) => a[field] - b[field]);
    }
    sorted = sorted.sort((a, b) => b.isNew - a.isNew);
    setProducts(sorted);
  };

  return (
    <div>
      <h1>Каталог товаров</h1>
      <Search products={products} />
      <SortTable products={products} onSort={sortProducts} />
      <Catalog products={products} />
    </div>
  );
}

export default MainComponent;
