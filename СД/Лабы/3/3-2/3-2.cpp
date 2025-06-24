#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;

struct person {
    string surname;
    string phone;
    string address;
    int out_money;
    bool diskountt = false;
};

struct person clients[100];

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    const int diskount = 200;
    int n = 0;
    int choice = 1;
    while (choice != 0) {
        cout << "1 - ввод элементов структуры с клавиатуры\n";
        cout << "2 - вывод элементов структуры в консольное окно\n";
        cout << "3 - фильтрация данных по адресу\n";
        cout << "0 - Выход из программы\n\n";
        cout << "Введите номер операции: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "Введите данные: Фамилию, Имя,Контактный телефон, адрес" << endl;
            cout << "Введите вашу фамилию и имя: ";
            getline(cin, clients[n].surname);
            cout << "Введите ваш контактный телефон: ";
            cin >> clients[n].phone;
            cin.ignore();
            cout << "Введите ваш адрес: ";
            getline(cin, clients[n].address);
            clients[n].out_money = rand() % 1000;
            if (clients[n].out_money >= diskount) {
                clients[n].diskountt = true;
                cout << "Поздравляем, вы получаете скидку в 10%!" << endl;
            }
            n++;
        }

        if (choice == 2) {
            cout << "База данных" << endl;
            for (int i = 0; i < n; i++) {
                cout << clients[i].surname << " ";
                cout << clients[i].phone << " ";
                cout << clients[i].address << " ";
                if (clients[i].diskountt) {
                    cout << "Имеется скидка в десять процентов.";
                }
                cout << endl;
            }
        }
        if (choice == 3) {
            cout << "Введите адрес " << endl;
            bool ed = false;
            string s;
            cin >> s;
            for (int i = 0; i < n; i++) {
                if (clients[i].address == s) {
                    ed = true;
                    cout << clients[i].surname << " ";
                    cout << clients[i].phone << " ";
                    cout << clients[i].address << " ";
                    if (clients[i].diskountt) {
                        cout << "Имеется скидка в десять процентов.";
                    }
                }
            }
            if(!ed) cout << "Отсутствуют люди с таким адресом";
        }
    }
    return 0;
}
