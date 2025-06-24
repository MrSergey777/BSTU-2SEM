#include <iostream>
#include <cmath>
using namespace std;
union Shape {
    struct {
        double radius;
    } circle;
    struct {
        double side;
    } square;
    struct {
        double base;
        double height;
    } triangle;
};
int main() {
    setlocale(LC_ALL, "ru");
    int choice;
    Shape shape;
    cout << "Выберите тип фигуры:\n1. Круг\n2. Квадрат\n3. Треугольник\n";
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Введите радиус круга: ";
        cin >> shape.circle.radius;
        cout << "Площадь круга: " << 3.14 * pow(shape.circle.radius, 2) << endl;
        break;
    case 2:
        cout << "Введите сторону квадрата: ";
        cin >> shape.square.side;
        cout << "Площадь квадрата: " << pow(shape.square.side, 2) << endl;
        break;
    case 3:
        cout << "Введите основание и высоту треугольника: ";
        cin >> shape.triangle.base >> shape.triangle.height;
        cout << "Площадь треугольника: " << 0.5 * shape.triangle.base * shape.triangle.height << endl;
        break;
    default:
        cout << "Неправильный выбор!" << endl;
    }
    return 0;
}
