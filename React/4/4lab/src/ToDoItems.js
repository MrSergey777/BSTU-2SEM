import React from 'react';

const ToDoItems = ({ tasks, toggleTaskCompletion }) => {
    return (
        <ul>
            {tasks.map((task, index) => (
                <li key={index}>
                    <input 
                        type="checkbox" 
                        checked={task.completed} 
                        onChange={() => toggleTaskCompletion(index)} 
                    />
                    {task.name}
                </li>
            ))}
        </ul>
    );
};

export default ToDoItems;