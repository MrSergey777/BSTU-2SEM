#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Client {
    string name;
    string city;
};

int main() {
    setlocale(LC_ALL, "ru");
    const int MAX_CLIENTS = 100;
    Client clients[MAX_CLIENTS];
    int clientCount = 0;

    // Чтение клиентов из файла in.txt
    ifstream fin("in.txt");
    if (!fin) {
        cout << "Ошибка открытия файла in.txt" << endl;
        return 1;
    }

    // Предполагается, что каждая строка файла имеет формат: имя город
    while (fin >> clients[clientCount].name >> clients[clientCount].city) {
        clientCount++;
        if (clientCount >= MAX_CLIENTS) {
            break;
        }
    }
    fin.close();

    int choice = -1;
    while (choice != 0) {
        // Вывод меню
        cout << "\nМеню:" << endl;
        cout << "1. Поиск клиента по имени и городу" << endl;
        cout << "2. Вывод всех клиентов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // удаление символа новой строки

        switch (choice) {
        case 1: {
            // Поиск клиента
            string searchName, searchCity;
            cout << "Введите имя: ";
            cin >> searchName;
            cout << "Введите город: ";
            cin >> searchCity;

            bool found = false;
            // Открываем файл out.txt в режиме дополнения, чтобы не стирать предыдущие результаты
            ofstream fout("out.txt", ios::app);
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].name == searchName && clients[i].city == searchCity) {//сл инд
                    cout << "Клиент найден: "
                        << clients[i].name << " - "
                        << clients[i].city << endl;
                    fout << "Клиент найден: "
                        << clients[i].name << " - "
                        << clients[i].city << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Клиент с именем \"" << searchName
                    << "\" и городом \"" << searchCity << "\" не найден." << endl;
                fout << "Клиент с именем \"" << searchName
                    << "\" и городом \"" << searchCity << "\" не найден." << endl;
            }
            fout.close();
            break;
        }
        case 2: {
            // Вывод всех клиентов
            cout << "\nСписок клиентов:" << endl;
            for (int i = 0; i < clientCount; i++) {
                cout << i + 1 << ". " << clients[i].name
                    << " - " << clients[i].city << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    }

    return 0;
}
