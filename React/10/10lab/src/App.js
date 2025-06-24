import React from 'react';
import Catalog from './components/Catalog'; // Импортируем компонент каталога
import OrderForm from './components/OrderForm'; // Импортируем компонент оформления заказа

const App = () => {
    return (
        <div>
            <h1>Интернет-магазин</h1>
            {}
            <Catalog />
            <OrderForm />
        </div>
    );
};

export default App;