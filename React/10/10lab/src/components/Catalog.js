import React from 'react';
import { useSelector } from 'react-redux';

const Catalog = () => {
    const items = useSelector(state => state.items || []); // Получаем элементы из Redux

    if (!Array.isArray(items)) {
        return <div>Нет доступных элементов.</div>; // Обработка случая, когда items не является массивом
    }

    const filteredItems = items.filter(item => item.someCondition); // Фильтрация элементов

    return (
        <div>
            {filteredItems.map(item => (
                <div key={item.id}>{item.name}</div>
            ))}
        </div>
    );
};

export default Catalog;