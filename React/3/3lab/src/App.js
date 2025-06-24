import { useState } from 'react';

function EmailForm() {
  const [email, setEmail] = useState('');
  const [message, setMessage] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();

    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (emailRegex.test(email)) {
      setMessage('Форма успешно отправлена!');
    } else {
      setMessage('Пожалуйста, введите корректный email');
    }
  };

  return (
    <div style={{ marginBottom: '40px' }}>
      <h2>Форма отправки email</h2>
      <form onSubmit={handleSubmit}>
        <label>
          Email:
          <input
            type="text"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            style={{ margin: '0 10px' }}
          />
        </label>
        <button type="submit">Отправить</button>
      </form>
      {message && <p>{message}</p>}
    </div>
  );
}

function ProductCatalog() {
  const initialProducts = [
    { id: 1, name: 'Ноутбук', price: 50000, quantity: 5 },
    { id: 2, name: 'Смартфон', price: 30000, quantity: 2 },
    { id: 3, name: 'Наушники', price: 5000, quantity: 0 },
    { id: 4, name: 'Клавиатура', price: 2000, quantity: 10 },
    { id: 5, name: 'Мышь', price: 1500, quantity: 3 },
  ];

  const [products, setProducts] = useState(initialProducts);
  const [sortConfig, setSortConfig] = useState({ key: null, direction: 'asc' });

  const requestSort = (key) => {
    let direction = 'asc';
    if (sortConfig.key === key && sortConfig.direction === 'asc') {
      direction = 'desc';
    }
    setSortConfig({ key, direction });

    const sortedProducts = [...products].sort((a, b) => {
      if (a[key] < b[key]) {
        return direction === 'asc' ? -1 : 1;
      }
      if (a[key] > b[key]) {
        return direction === 'asc' ? 1 : -1;
      }
      return 0;
    });

    setProducts(sortedProducts);
  };

  const totalQuantity = products.reduce((sum, product) => sum + product.quantity, 0);
  const totalPrice = products.reduce((sum, product) => sum + (product.price * product.quantity), 0);

  const getRowStyle = (quantity) => {
    if (quantity === 0) return { backgroundColor: '#ffcccc' };
    if (quantity < 3) return { backgroundColor: '#fffacd' };
    return {};
  };

  return (
    <div>
      <h2>Каталог товаров</h2>
      <table style={{ width: '100%', borderCollapse: 'collapse', marginBottom: '20px' }}>
        <thead>
          <tr>
            <th style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left', backgroundColor: '#f2f2f2' }}>№</th>
            <th 
              onClick={() => requestSort('name')}
              style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left', backgroundColor: '#f2f2f2', cursor: 'pointer' }}
            >
              Название {sortConfig.key === 'name' && (sortConfig.direction === 'asc' ? '↑' : '↓')}
            </th>
            <th 
              onClick={() => requestSort('price')}
              style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left', backgroundColor: '#f2f2f2', cursor: 'pointer' }}
            >
              Цена {sortConfig.key === 'price' && (sortConfig.direction === 'asc' ? '↑' : '↓')}
            </th>
            <th 
              onClick={() => requestSort('quantity')}
              style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left', backgroundColor: '#f2f2f2', cursor: 'pointer' }}
            >
              Количество {sortConfig.key === 'quantity' && (sortConfig.direction === 'asc' ? '↑' : '↓')}
            </th>
          </tr>
        </thead>
        <tbody>
          {products.map((product, index) => (
            <tr key={product.id} style={getRowStyle(product.quantity)}>
              <td style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left' }}>{index + 1}</td>
              <td style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left' }}>{product.name}</td>
              <td style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left' }}>{product.price} ₽</td>
              <td style={{ border: '1px solid #ddd', padding: '8px', textAlign: 'left' }}>{product.quantity}</td>
            </tr>
          ))}
        </tbody>
      </table>

      <div style={{ marginTop: '20px', fontWeight: 'bold' }}>
        <p>Общее количество товаров: {totalQuantity}</p>
        <p>Общая стоимость: {totalPrice} ₽</p>
      </div>
    </div>
  );
}

function App() {
  return (
    <div style={{ maxWidth: '800px', margin: '0 auto', padding: '20px' }}>
      <EmailForm />
      <ProductCatalog />
    </div>
  );
}

export default App;