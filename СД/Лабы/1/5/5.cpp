//Написать программу, которая, в зависимости от 
//выбора пользователя, в консоли должна выводить название 
//планеты Солнечной системы, с использованием перечислений.
#include <iostream>
using namespace std;
enum Planets {
    Меркурий = 1,
    Венера,
    Земля,
    Марс,
    Юпитер,
    Сатурн,
    Уран,
    Нептун
};
void PlName(int planet) {
    switch (planet) {
    case Меркурий: cout << "Меркурий" << endl; break;
    case Венера: cout << "Венера" << endl; break;
    case Земля: cout << "Земля" << endl; break;
    case Марс: cout << "Марс" << endl; break;
    case Юпитер: cout << "Юпитер" << endl; break;
    case Сатурн: cout << "Сатурн" << endl; break;
    case Уран: cout << "Уран" << endl; break;
    case Нептун: cout << "Нептун" << endl; break;
    default: cout << "Неверный выбор" << endl; break;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    int choice;
    cout << "Выберите номер планеты Солнечной системы 1-8 ";
    cin >> choice;
    PlName(choice);
    return 0;
}
