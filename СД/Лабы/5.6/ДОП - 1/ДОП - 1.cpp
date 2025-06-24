#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

struct client {
    string surname;
    string pasd;
    int date_join;
    string date_out;
    string type_off_lat;
};

struct client List_of_hotel_clients[100];

void insertionSortAscending(client arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j - 1].date_join > arr[j].date_join) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

void insertionSortDescending(client arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j - 1].date_join < arr[j].date_join) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}
void sortSurname(client arr[], int n) {
    for (int i = 1; i < n / 2; i++) {
        int j = i;
        while (j > 0 && arr[j - 1].surname > arr[j].surname) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
    for (int i = n / 2; i < n; i++) {
        int j = i;
        while (j > n / 2 && arr[j - 1].surname < arr[j].surname) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    int n = 0;
    int choice = 1;
    while (choice != 0) {
        cout << "1 - ввод элементов структуры с клавиатуры\n";
        cout << "2 - вывод элементов структуры в консольное окно\n";
        cout << "3 - удаление заданной структурированной переменной\n";
        cout << "4 - отсортировать по дате прибытия (возрастание)\n";
        cout << "5 - запись информации в файл\n";
        cout << "6 - чтение данных из файла\n";
        cout << "7 - отсортировать по дате прибытия (убывание)\n";
        cout << "8 - отсортировать по фамилии (возрастание)(убывание)\n";
        cout << "0 - Выход из программы\n\n";
        cout << "Введите номер операции: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Введите данные: Фамилию, Паспортные данные, дату приезда, дату отъезда, тип размещения: ";
            cin >> List_of_hotel_clients[n].surname;
            cin >> List_of_hotel_clients[n].pasd;
            cin >> List_of_hotel_clients[n].date_join;
            cin >> List_of_hotel_clients[n].date_out;
            cin >> List_of_hotel_clients[n].type_off_lat;
            n++;
        }
        if (choice == 2) {
            cout << "Список проживающих: " << endl;
            for (int i = 0; i < n; i++) {
                if (List_of_hotel_clients[i].surname.empty()) continue;
                cout << List_of_hotel_clients[i].surname << " ";
                cout << List_of_hotel_clients[i].pasd << " ";
                cout << List_of_hotel_clients[i].date_join << " ";
                cout << List_of_hotel_clients[i].date_out << " ";
                cout << List_of_hotel_clients[i].type_off_lat << " " << endl;
            }
        }
        if (choice == 3) {
            cout << "Введите порядковый номер клиента, которого хотите удалить: ";
            int nn;
            cin >> nn;
            if (nn >= 0 && nn < n) {
                List_of_hotel_clients[nn].surname = "";
                List_of_hotel_clients[nn].pasd = "";
                List_of_hotel_clients[nn].date_join = 0;
                List_of_hotel_clients[nn].date_out = "";
                List_of_hotel_clients[nn].type_off_lat = "";
            }
            else {
                cout << "Некорректный номер клиента!" << endl;
            }
        }
        if (choice == 4) {
            insertionSortAscending(List_of_hotel_clients, n);
            cout << "Сортировка по возрастанию выполнена." << endl;
        }
        if (choice == 5) {
            fstream one("clients.txt", ios::out);
            if (!one.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
                return 1;
            }
            for (int i = 0; i < n; i++) {
                if (List_of_hotel_clients[i].surname.empty()) continue;
                one << List_of_hotel_clients[i].surname << " "
                    << List_of_hotel_clients[i].pasd << " "
                    << List_of_hotel_clients[i].date_join << " "
                    << List_of_hotel_clients[i].date_out << " "
                    << List_of_hotel_clients[i].type_off_lat << endl;
            }
            one.close();
            cout << "Информация записана в файл." << endl;
        }
        if (choice == 6) {
            fstream one("clients.txt", ios::in);
            if (!one.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
                return 1;
            }
            n = 0;
            while (one >> List_of_hotel_clients[n].surname) {
                one >> List_of_hotel_clients[n].pasd;
                one >> List_of_hotel_clients[n].date_join;
                one >> List_of_hotel_clients[n].date_out;
                one >> List_of_hotel_clients[n].type_off_lat;
                n++;
            }
            one.close();
            cout << "Данные прочитаны из файла." << endl;
        }
        if (choice == 7) {
            insertionSortDescending(List_of_hotel_clients, n);
            cout << "Сортировка по убыванию выполнена." << endl;
        }
        if (choice == 8) {
            sortSurname(List_of_hotel_clients, n);
            cout << "Сортировка по фамилии выполнена." << endl;
        }
    }
}
