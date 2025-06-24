import React, { useState, useEffect } from "react";

const ColorPicker = () => {
  const [selectedColor, setSelectedColor] = useState("");
  const [savedColors, setSavedColors] = useState([]);

  useEffect(() => {
    const colors = localStorage.getItem("savedColors");
    if (colors) {
      setSavedColors(JSON.parse(colors));
    }
  }, []);
0
  useEffect(() => {
    localStorage.setItem("savedColors", JSON.stringify(savedColors));
  }, [savedColors]);

  const colorPalette = ["red", "blue", "green", "yellow", "orange", "purple"];

  const handleColorSelect = (color) => {
    setSelectedColor(color);
  };

  const handleReset = () => {
    setSelectedColor("");
  };

  const handleSave = () => {
    if (selectedColor && !savedColors.includes(selectedColor)) {
      setSavedColors([...savedColors, selectedColor]);
    }
  };

  return (
    <div style={{ padding: "20px" }}>
      <h2>Выберите цвет</h2>
      
      <div style={{ display: "flex", gap: "10px", marginBottom: "20px" }}>
        {colorPalette.map((color) => (
          <div
            key={color}
            onClick={() => handleColorSelect(color)}
            style={{
              width: "50px",
              height: "50px",
              borderRadius: "50%",
              backgroundColor: color,
              cursor: "pointer",
              border: selectedColor === color ? "3px solid black" : "none",
            }}
          ></div>
        ))}
      </div>

      {selectedColor && (
        <div>
          <p>Выбранный цвет: <span style={{ color: selectedColor }}>{selectedColor}</span></p>
        </div>
      )}

      <div style={{ marginTop: "20px" }}>
        <button onClick={handleReset} style={{ marginRight: "10px" }}>Reset</button>
        <button onClick={handleSave}>Save</button>
      </div>

      {savedColors.length > 0 && (
        <div style={{ marginTop: "20px" }}>
          <h3>Сохраненные цвета:</h3>
          <div style={{ display: "flex", gap: "10px" }}>
            {savedColors.map((color, index) => (
              <div
                key={index}
                style={{
                  width: "50px",
                  height: "50px",
                  borderRadius: "50%",
                  backgroundColor: color,
                }}
              ></div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
};

export default ColorPicker;

