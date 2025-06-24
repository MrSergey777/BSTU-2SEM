import { useState } from "react";
import ContactForm from "./ContactForm";

function App() {
  const [contacts, setContacts] = useState([]);

  const handleFormSubmit = (newContact) => {
    setContacts([...contacts, newContact]);
  };

  return (
    <div>
      <h1>Форма обратной связи</h1>
      <ContactForm onSubmit={handleFormSubmit} />
      
      {contacts.length > 0 && (
        <div>
          <h2>Отправленные данные</h2>
          <table border="1">
            <thead>
              <tr>
                <th>Имя</th>
                <th>Email</th>
                <th>Сообщение</th>
                <th>Пол</th>
              </tr>
            </thead>
            <tbody>
              {contacts.map((contact, index) => (
                <tr key={index}>
                  <td>{contact.name}</td>
                  <td>{contact.email}</td>
                  <td>{contact.message}</td>
                  <td>{contact.gender === "male" ? "Мужчина" : "Женщина"}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  );
}

export default App;
