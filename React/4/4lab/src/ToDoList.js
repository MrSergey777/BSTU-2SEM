import React, { useState } from 'react';
import ToDoForm from './ToDoForm';
import ToDoItems from './ToDoItems';

const ToDoList = () => {
    const [tasks, setTasks] = useState([]);
    const [filter, setFilter] = useState('all');

    const addTask = (task) => {
        setTasks([...tasks, { name: task, completed: false }]);
    };

    const toggleTaskCompletion = (index) => {
        const newTasks = [...tasks];
        newTasks[index].completed = !newTasks[index].completed;
        setTasks(newTasks);
    };

    const handleFilterChange = (e) => {
        setFilter(e.target.value);
    };

    const filteredTasks = tasks.filter(task => {
        if (filter === 'completed') return task.completed;
        if (filter === 'uncompleted') return !task.completed;
        return true;
    });

    return (
        <div>
            <h1>Список дел</h1>
            <ToDoForm addTask={addTask} />
            <div>
                <label>
                Показывать:
                    <select onChange={handleFilterChange}>
                        <option value="all">Все</option>
                        <option value="completed">Выполненые</option>
                        <option value="uncompleted">Невыполненые</option>
                    </select>
                </label>
            </div>
            <ToDoItems tasks={filteredTasks} toggleTaskCompletion={toggleTaskCompletion} />
        </div>
    );
};

export default ToDoList;
