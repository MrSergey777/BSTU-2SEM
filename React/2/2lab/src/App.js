import './App.css';
import { useState, Component } from 'react';

function App() {
  const [selectedJob, setSelectedJob] = useState("");
  return (
    <div>
      <SelectJob setSelectedJob={setSelectedJob} />
      <JobMenu selectedJob={selectedJob} />
      <Clock format='24' timezone='Europe/Minsk' />
      <Clock format='12' timezone='America/New_York' />
    </div>
  );
}

function SelectJob({ setSelectedJob }) {
  return (
    <div>
      <div>Выберите профессию:</div>
      <select onChange={(e) => setSelectedJob(e.target.value)}>
        <option value="">--Выберите профессию--</option>
        <option value="Программист">Программист</option>
        <option value="Дизайнер">Дизайнер</option>
        <option value="Менеджер">Менеджер</option>
        <option value="Инженер">Инженер</option>
        <option value="Слесарь">Слесарь</option>
      </select>
    </div>
  );
}

function JobMenu({ selectedJob }) {
  return (
    <div>
      <div>Полезные ссылки для профессии: {selectedJob || "не выбрано"}</div>
      <ul>
        {selectedJob === "Программист" && (
          <>
            <li>Документация по JavaScript</li>
            <li>Курсы по React</li>
            <li>GitHub</li>
            <li>Форумы программистов</li>
          </>
        )}
        {selectedJob === "Дизайнер" && (
          <>
            <li>Уроки Photoshop</li>
            <li>Dribbble</li>
            <li>Курсы по дизайну</li>
            <li>Фриланс-платформы</li>
          </>
        )}
        {selectedJob === "Менеджер" && (
          <>
            <li>Книги по менеджменту</li>
            <li>Курсы по Agile</li>
            <li>Форумы менеджеров</li>
            <li>Тренинги по лидерству</li>
          </>
        )}
        {selectedJob === "Инженер" && (
          <>
            <li>Курсы по AutoCAD</li>
            <li>Форумы инженеров</li>
            <li>Технические гайды</li>
            <li>Книги инженера</li>
          </>
        )}
        {selectedJob === "Слесарь" && (
          <>
            <li>Руководства по ремонту</li>
            <li>Инструкции по безопасности</li>
            <li>Форумы слесарей</li>
            <li>Магазины инструментов</li>
          </>
        )}
      </ul>
    </div>
  );
}

class Clock extends Component {
  constructor(props) {
    super(props);
    this.state = { time: "" };
  }

  componentDidMount() {
    this.updateClock();
    this.intervalId = setInterval(this.updateClock, 1000);
  }

  componentWillUnmount() {
    clearInterval(this.intervalId);
  }

  updateClock = () => {
    const { format, timezone } = this.props;
    const now = new Date();
    const localTime = new Date(now.toLocaleString('en-US', { timeZone: timezone }));
    const hours = format === '12' ? localTime.getHours() % 12 || 12 : localTime.getHours();
    const minutes = localTime.getMinutes().toString().padStart(2, '0');
    const seconds = localTime.getSeconds().toString().padStart(2, '0');
    const period = format === '12' ? (localTime.getHours() >= 12 ? 'PM' : 'AM') : '';
    this.setState({ time: `${hours}:${minutes}:${seconds} ${period}` });
  };
  render() {
    return (
      <div>
        <h1>{this.state.time}</h1>
      </div>
    );
  }
}
export default App;
