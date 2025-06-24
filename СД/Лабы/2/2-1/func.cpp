#include <iostream>
#include "func.h"
using namespace std;

void window() {
    cout << "1 - ввод элементов структуры с клавиатуры\n";
    cout << "2 - вывод элементов структуры в консольное окно\n";
    cout << "0 - Выход из программы\n\n";
    cout << "Введите номер операции: ";
}

void choice1(struct person clients[100], int& n, int diskount) {
    cout << "Введите данные: Фамилию, Имя, Контактный телефон, адрес" << endl;
    cout << "Введите вашу фамилию ";
    cin >> clients[n].surname;
    cout << "Введите ваше имя ";
    cin >> clients[n].name;
    cout << "Введите ваш контактный телефон ";
    cin >> clients[n].phone;
    cout << "Введите ваш адрес ";
    cin >> clients[n].address;
    clients[n].out_money = rand() % 1000;
    if (clients[n].out_money >= diskount) {
        clients[n].diskountt = true;
        cout << "Поздравляем вы получаете скидку в 10% " << endl;
    }
    n++;
}

void choice2(struct person clients[100], int n) {
    cout << "База данных" << endl;
    for (int i = 0; i < n; i++) {
        cout << clients[i].surname << " ";
        cout << clients[i].name << " ";
        cout << clients[i].phone << " ";
        cout << clients[i].address << " ";
        if (clients[i].diskountt == true) {
            cout << "Имеется скидка в десять процентов";
        }
        cout << endl;
    }
}
