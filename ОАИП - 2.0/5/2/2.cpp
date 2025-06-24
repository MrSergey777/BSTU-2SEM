#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

struct Train {
    int number;
    string where;
    string daysofgo;
    union {
        struct {
            string prib;
            string otpr;
        };
        struct {
            char pribArr[50];
            char otprArr[50];
        };
    };

    Train() : number(0), where(""), daysofgo(""), prib(""), otpr("") {}  
    ~Train() {} 
};
Train List_of_trains[100];
void readFromFile(int& n) {
    fstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\5\\first.txt");
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла!\n";
        return;
    }

    n = 0;
    while (!file.eof() && n < 100) {
        file >> List_of_trains[n].number;
        file.ignore();
        getline(file, List_of_trains[n].where);
        getline(file, List_of_trains[n].daysofgo);
        getline(file, List_of_trains[n].prib);
        getline(file, List_of_trains[n].otpr);
        n++;
    }

    file.close();
    cout << "Данные успешно считаны из файла.\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int n = 0;
    int choice = 1;

    while (choice != 0) {
        cout << "1 - Ввод элементов структуры с клавиатуры\n";
        cout << "2 - Вывод элементов структуры в консольное окно\n";
        cout << "3 - Удаление заданной структурированной переменной\n";
        cout << "4 - Поиск по пункту назначения\n";
        cout << "5 - Запись информации в файл\n";
        cout << "6 - Чтение информации из файла\n";
        cout << "0 - Выход из программы\n\n";
        cout << "Введите номер операции: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Введите данные: Номер поезда, пункт назначения, дни следования, время прибытия, время отправления\n";
            cout << "Номер поезда: ";
            cin >> List_of_trains[n].number;
            cout << "Пункт назначения: ";
            cin.ignore();  // Очистка буфера ввода
            getline(cin, List_of_trains[n].where);
            cout << "Дни следования: ";
            getline(cin, List_of_trains[n].daysofgo);
            cout << "Время прибытия: ";
            getline(cin, List_of_trains[n].prib);
            cout << "Время отправления: ";
            getline(cin, List_of_trains[n].otpr);
            n++;
        }

        if (choice == 2) {
            cout << "Список поездов: \n";
            for (int i = 0; i < n; i++) {
                if (List_of_trains[i].where.empty()) continue;
                cout << "Номер поезда: " << List_of_trains[i].number << "\n";
                cout << "Пункт назначения: " << List_of_trains[i].where << "\n";
                cout << "Дни следования: " << List_of_trains[i].daysofgo << "\n";
                cout << "Время прибытия: " << List_of_trains[i].prib << "\n";
                cout << "Время отправления: " << List_of_trains[i].otpr << "\n\n";
            }
        }

        if (choice == 3) {
            cout << "Введите номер поезда, который хотите удалить: ";
            int nn;
            cin >> nn;
            for (int i = 0; i < n; i++) {
                if (List_of_trains[i].number == nn) {
                    List_of_trains[i].where.clear();
                    List_of_trains[i].daysofgo.clear();
                    List_of_trains[i].prib.clear();
                    List_of_trains[i].otpr.clear();
                    break;
                }
            }
        }

        if (choice == 4) {
            string destination;
            cout << "Введите пункт назначения для поиска данных: ";
            cin.ignore();
            getline(cin, destination);
            for (int i = 0; i < n; i++) {
                if (List_of_trains[i].where == destination) {
                    cout << "Номер поезда: " << List_of_trains[i].number << "\n";
                    cout << "Пункт назначения: " << List_of_trains[i].where << "\n";
                    cout << "Дни следования: " << List_of_trains[i].daysofgo << "\n";
                    cout << "Время прибытия: " << List_of_trains[i].prib << "\n";
                    cout << "Время отправления: " << List_of_trains[i].otpr << "\n\n";
                }
            }
        }

        if (choice == 5) {
            fstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\5\\first.txt");
            if (!file.is_open()) {
                cout << "Ошибка при открытии файла!\n";
                return 1;
            }
            for (int i = 0; i < n; i++) {
                if (List_of_trains[i].where.empty()) continue;
                file << List_of_trains[i].number << "\n";
                file << List_of_trains[i].where << "\n";
                file << List_of_trains[i].daysofgo << "\n";
                file << List_of_trains[i].prib << "\n";
                file << List_of_trains[i].otpr << "\n";
            }
            file.close();
            cout << "Данные успешно записаны в файл.\n";
        }

        if (choice == 6) {
            readFromFile(n);
        }
    }

    return 0;
}
