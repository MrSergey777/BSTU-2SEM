import React, { useState } from 'react';

const sampleProducts = [
    { id: 1, name: 'iPhone 13', quantity: 5, weight: 0.174, price: 70000, image: 'https://encrypted-tbn1.gstatic.com/shopping?q=tbn:ANd9GcSk0wn-TZgELtJhgATZ8uVn4psy1B-N4BpVio0IRqzj4A2Wo4LQxRfbsQcwZ7S1gtjxblrdbIFcs91SghVzS_BshvFTf8TXdsRnxq-VcT6AKZKm3dfsIAkvDCKqau1d&usqp=CAc' },
    { id: 2, name: 'Samsung Galaxy S21', quantity: 3, weight: 0.169, price: 65000, image: 'data:image/webp;base64,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' },
    { id: 3, name: 'Google Pixel 6', quantity: 10, weight: 0.207, price: 80000, image: 'https://encrypted-tbn0.gstatic.com/shopping?q=tbn:ANd9GcRGZph5DBWPfnb81DH4wHmfcyyACoLXx0KT1C0-RuhDEjfIflRatIQ_3LBJHgnyYVXbH2gaQ9AHc31-ofYvYc0iP1UHD-UArENxh63HL--6s9kwghzAbOVBlTyPvA&usqp=CAc' },
];

const OrderForm = () => {
    const [currentPage, setCurrentPage] = useState(1);
    const [cartItems, setCartItems] = useState([]);
    const [selectedDelivery, setSelectedDelivery] = useState('');
    const [selectedPayment, setSelectedPayment] = useState('');
    const [quantities, setQuantities] = useState({});

    const handleNextPage = () => {
        setCurrentPage(prev => prev + 1);
    };

    const handlePrevPage = () => {
        setCurrentPage(prev => prev - 1);
    };

    const addToCart = (product) => {
        if (!cartItems.find(item => item.id === product.id)) {
            setCartItems([...cartItems, product]);
            setQuantities({ ...quantities, [product.id]: 1 }); // Устанавливаем начальное количество
        }
    };

    const removeFromCart = (id) => {
        setCartItems(cartItems.filter(item => item.id !== id));
        // Удаляем количество при удалении товара
        const newQuantities = { ...quantities };
        delete newQuantities[id];
        setQuantities(newQuantities);
    };

    const handleQuantityChange = (id, value) => {
        if (value < 1) return; 
        if (value > cartItems.find(item => item.id === id).quantity) return; 
        setQuantities({ ...quantities, [id]: value });
    };

    // Функция для расчета общей стоимости товаров в корзине
    const calculateTotalPrice = () => {
        return cartItems.reduce((totalPrice, item) => {
            return totalPrice + (item.price * (quantities[item.id] || 0));
        }, 0);
    };

    // Функция для расчета общей массы товаров в корзине
    const calculateTotalWeight = () => {
        return cartItems.reduce((totalWeight, item) => {
            return totalWeight + (item.weight * (quantities[item.id] || 0));
        }, 0);
    };

    // Функция для расчета стоимости доставки
    const calculateDeliveryCost = () => {
        const totalWeight = calculateTotalWeight();
        let deliveryCost = 0;

        if (selectedDelivery === "courier") {
            const totalPrice = calculateTotalPrice();
            deliveryCost = totalPrice < 200 ? 10 : 0;
        } else if (selectedDelivery === "post") {
            deliveryCost = totalWeight * 5; // Стоимость почтовой доставки
        } else if (selectedDelivery === "pickup") {
            deliveryCost = 0; // Самовывоз бесплатный
        }

        return deliveryCost;
    };

    return (
        <>
            {currentPage === 1 && (
                <>
                    <h2>Каталог товаров</h2>
                    {sampleProducts.map(product => (
                        <div key={product.id} style={{ display: 'flex', alignItems: 'center', marginBottom: '10px' }}>
                            <img src={product.image} alt={product.name} style={{ width: '50px', height: '50px', marginRight: '10px' }} />
                            <div style={{ flexGrow: 1 }}>
                                <span>{product.name} (Цена: {product.price} рублей)</span>
                                <div>
                                    Количество доступно: {product.quantity}
                                </div>
                                <button onClick={() => addToCart(product)}>Добавить в корзину</button>
                            </div>
                        </div>
                    ))}
                    
                    <h2>Корзина</h2>
                    {cartItems.length === 0 ? (
                        <p>Корзина пуста.</p>
                    ) : (
                        cartItems.map(item => (
                            <div key={item.id} style={{ display: 'flex', alignItems: 'center', marginBottom: '10px' }}>
                                <img src={item.image} alt={item.name} style={{ width: '50px', height: '50px', marginRight: '10px' }} />
                                <div style={{ flexGrow: 1 }}>
                                    <span>{item.name} (Масса: {item.weight} кг)</span>
                                    <div>
                                        Количество доступно: {item.quantity}
                                    </div>
                                    <input 
                                        type="number" 
                                        min="1" 
                                        max={item.quantity} 
                                        defaultValue={quantities[item.id] || 1} 
                                        onChange={(e) => handleQuantityChange(item.id, parseInt(e.target.value))}
                                    />
                                </div>
                                <button onClick={() => removeFromCart(item.id)}>Удалить</button>
                            </div>
                        ))
                    )}
                    {/* Отображение общей стоимости товаров */}
                    <div>
                        Общая стоимость товаров в корзине: {calculateTotalPrice()} рублей
                    </div>

                    {/* Выбор способа доставки */}
                    <h3>Выбор способа доставки</h3>
                    <div>
                        <input 
                            type="radio" 
                            name="delivery" 
                            value="courier" 
                            checked={selectedDelivery === "courier"} 
                            onChange={() => setSelectedDelivery("courier")} 
                        /> Курьером
                        <input 
                            type="radio" 
                            name="delivery" 
                            value="post" 
                            checked={selectedDelivery === "post"} 
                            onChange={() => setSelectedDelivery("post")} 
                        /> Почтой
                        <input 
                            type="radio" 
                            name="delivery" 
                            value="pickup" 
                            checked={selectedDelivery === "pickup"} 
                            onChange={() => setSelectedDelivery("pickup")} 
                        /> Самовывоз
                    </div>

                    {/* Отображение стоимости доставки */}
                    {selectedDelivery && (
                        <div>
                            Стоимость доставки: {calculateDeliveryCost()} рублей
                        </div>
                    )}

                    <button onClick={handleNextPage} disabled={cartItems.length === 0}>Далее</button>
                </>
            )}

            {currentPage === 2 && (
                <>
                    <h2>Выбор способа оплаты</h2>

                    {/* Выбор способа оплаты */}
                    <div>
                        <input 
                            type="radio" 
                            name="payment" 
                            value="cash" 
                            checked={selectedPayment === "cash"} 
                            onChange={() => setSelectedPayment("cash")} 
                        /> Наличными
                        <input 
                            type="radio" 
                            name="payment" 
                            value="card" 
                            checked={selectedPayment === "card"} 
                            onChange={() => setSelectedPayment("card")} 
                        /> Картой
                    </div>

                    <button onClick={handlePrevPage}>Назад</button>
                </>
            )}
        </>
    );
};

export default OrderForm;