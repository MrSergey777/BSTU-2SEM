import React, { useState } from 'react';

const ToDoForm = ({ addTask }) => {
    const [taskName, setTaskName] = useState('');

    const handleSubmit = (e) => {
        e.preventDefault();
        if (taskName.trim()) { //не пустое
            addTask(taskName);
            setTaskName('');
        }
    };

    return (
        <form onSubmit={handleSubmit}>
            <input 
                type="text" 
                value={taskName} 
                onChange={(e) => setTaskName(e.target.value)} 
                placeholder="Введи задание" 
            />
            <button type="submit">Добавить</button>
        </form>
    );
};

export default ToDoForm;