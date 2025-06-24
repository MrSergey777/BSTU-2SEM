import { useState } from "react";

function ContactForm() {
  const [formData, setFormData] = useState({
    name: "",
    email: "",
    message: "",
    gender: "male",
  });

  const [submittedData, setSubmittedData] = useState([]);
  const [errors, setErrors] = useState({});

  const validateForm = () => {
    let newErrors = {};
    if (!formData.name.trim()) newErrors.name = "Имя обязательно.";
    if (!formData.email.match(/^[^\s@]+@[^\s@]+\.[^\s@]+$/)) newErrors.email = "Некорректный email.";
    if (!formData.message.trim()) newErrors.message = "Введите сообщение.";
    return newErrors;
  };

  const handleChange = (e) => {
    setFormData({ ...formData, [e.target.name]: e.target.value });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    const newErrors = validateForm();
    if (Object.keys(newErrors).length > 0) {
      setErrors(newErrors);
    } else {
      setSubmittedData([...submittedData, formData]);
      setFormData({ name: "", email: "", message: "", gender: "male" });
      setErrors({});
    }
  };

  return (
    <div>
      <h2>Форма контакта</h2>
      <form onSubmit={handleSubmit}>
        <label>
          Имя:
          <input type="text" name="name" value={formData.name} onChange={handleChange} />
        </label>
        {errors.name && <p className="error">{errors.name}</p>}

        <label>
          Email:
          <input type="email" name="email" value={formData.email} onChange={handleChange} />
        </label>
        {errors.email && <p className="error">{errors.email}</p>}

        <label>
          Сообщение:
          <textarea name="message" value={formData.message} onChange={handleChange}></textarea>
        </label>
        {errors.message && <p className="error">{errors.message}</p>}

        <div>
          <label>
            <input
              type="radio"
              name="gender"
              value="male"
              checked={formData.gender === "male"}
              onChange={handleChange}
            />
            Мужчина
          </label>
          <label>
            <input
              type="radio"
              name="gender"
              value="female"
              checked={formData.gender === "female"}
              onChange={handleChange}
            />
            Женщина
          </label>
        </div>

        <button type="submit">Отправить</button>
      </form>

      {submittedData.length > 0 && (
        <div>
          <h3>Отправленные данные</h3>
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
              {submittedData.map((data, index) => (
                <tr key={index}>
                  <td>{data.name}</td>
                  <td>{data.email}</td>
                  <td>{data.message}</td>
                  <td>{data.gender === "male" ? "Мужчина" : "Женщина"}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  );
}

export default ContactForm;
