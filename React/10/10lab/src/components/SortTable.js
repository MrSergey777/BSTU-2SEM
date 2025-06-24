import React, { useState } from 'react';

const SortTable = ({ products }) => {
    const [sortField, setSortField] = useState('name');

    const sortedProducts = [...products].sort((a, b) => {
        if (sortField === 'name') return a.name.localeCompare(b.name);
        if (sortField === 'price') return a.price - b.price;
        if (sortField === 'quantity') return a.quantity - b.quantity;
        if (sortField === 'discount') return a.discount - b.discount;
        return 0;
    });

    return (
        <div>
            <select onChange={(e) => setSortField(e.target.value)}>
                <option value="name">Наименование</option>
                <option value="price">Стоимость</option>
                <option value="quantity">Количество</option>
                <option value="discount">Скидка</option>
            </select>
            <table>
                <thead>
                    <tr>
                        <th>Наименование</th>
                        <th>Стоимость</th>
                        <th>Количество</th>
                        <th>Изображение</th>
                        <th>Описание</th>
                        <th>Новинка</th>
                        <th>Скидка</th>
                    </tr>
                </thead>
                <tbody>
                    {sortedProducts.map(product => (
                        <tr key={product.id}>
                            <td>{product.name}</td>
                            <td>{product.price} руб.</td>
                            <td>{product.quantity}</td>
                            <td><img src={product.image} alt={product.name} width={50} /></td>
                            <td>{product.description}</td>
                            <td>{product.isNew ? 'Да' : 'Нет'}</td>
                            <td>{product.discount}%</td>
                        </tr>
                    ))}
                </tbody>
            </table>
        </div>
    );
};

export default SortTable;
