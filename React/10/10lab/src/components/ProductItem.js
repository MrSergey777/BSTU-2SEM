import React from 'react';

const ProductItem = ({ product, onAddToCart }) => {
    return (
        <div className="catalog-item">
            <h2>{product.name}</h2>
            <p>Цена: {product.price} руб.</p>
            <p>{product.description}</p>
            <button onClick={() => onAddToCart(product)}>Добавить в корзину</button>
        </div>
    );
};

export default ProductItem;