import React, { useState } from "react";

function Comments() {
  const [comments, setComments] = useState([]);
  const [newComment, setNewComment] = useState({
    username: "",
    avatar: "",
    email: "",
    text: "",
    secret: "",
  });

  const handleAddComment = () => {
    const commentWithTimestamp = {
      ...newComment,
      id: Date.now(),
      lastUpdated: new Date().toLocaleString(),
    };
    setComments([...comments, commentWithTimestamp]);
    setNewComment({ username: "", avatar: "", email: "", text: "", secret: "" });
  };

  const handleEditComment = (id, updatedText) => {
    setComments((prevComments) =>
      prevComments.map((comment) =>
        comment.id === id
          ? { ...comment, text: updatedText, lastUpdated: new Date().toLocaleString() }
          : comment
      )
    );
  };

  const handleDeleteComment = (id, secret) => {
    const comment = comments.find((c) => c.id === id);
    if (comment && comment.secret === secret) {
      setComments(comments.filter((comment) => comment.id !== id));
    } else {
      alert("Секретное слово неверное!");
    }
  };

  const handleViewInfo = (comment) => {
    alert(
      `Имя пользователя: ${comment.username}\nДата изменения: ${comment.lastUpdated}\nЭлектронная почта: ${comment.email}`
    );
  };

  return (
    <div className="comments-container">
      <h2>Комментарии</h2>
      <div className="new-comment-form">
        <input
          type="text"
          placeholder="Имя пользователя"
          value={newComment.username}
          onChange={(e) => setNewComment({ ...newComment, username: e.target.value })}
        />
        <input
          type="text"
          placeholder="URL аватара"
          value={newComment.avatar}
          onChange={(e) => setNewComment({ ...newComment, avatar: e.target.value })}
        />
        <input
          type="email"
          placeholder="Электронная почта"
          value={newComment.email}
          onChange={(e) => setNewComment({ ...newComment, email: e.target.value })}
        />
        <textarea
          placeholder="Текст сообщения"
          value={newComment.text}
          onChange={(e) => setNewComment({ ...newComment, text: e.target.value })}
        />
        <input
          type="password"
          placeholder="Секретное слово"
          value={newComment.secret}
          onChange={(e) => setNewComment({ ...newComment, secret: e.target.value })}
        />
        <button onClick={handleAddComment}>Добавить комментарий</button>
      </div>

      <div className="comments-list">
        {comments.map((comment) => (
          <div key={comment.id} className="comment">
            <img src={comment.avatar} alt="avatar" className="avatar" />
            <h3>{comment.username}</h3>
            <p>{comment.text}</p>
            <button
              onClick={() => {
                const updatedText = prompt("Введите новый текст:", comment.text);
                if (updatedText) handleEditComment(comment.id, updatedText);
              }}
            >
              Изменить
            </button>
            <button
              onClick={() => {
                const secret = prompt("Введите секретное слово:");
                if (secret) handleDeleteComment(comment.id, secret);
              }}
            >
              Удалить
            </button>
            <button onClick={() => handleViewInfo(comment)}>Информация</button>
          </div>
        ))}
      </div>
    </div>
  );
}

export default Comments;


