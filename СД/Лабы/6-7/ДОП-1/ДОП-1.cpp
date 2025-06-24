#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
};

int main() {
    setlocale(LC_ALL, "ru");
    const int MAX_CONTACTS = 100;
    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;

    ifstream fin("in.txt");
    if (!fin) {
        cout << "Ошибка открытия файла in.txt" << endl;
        return 1;
    }
    while (fin >> contacts[contactCount].name >> contacts[contactCount].phoneNumber) {
        contactCount++;
        if (contactCount >= MAX_CONTACTS) {
            break;
        }
    }
    fin.close();

    int choice = -1;
    while (choice != 0) {
        cout << "\nМеню:\n";
        cout << "1. Поиск контакта по номеру телефона\n";
        cout << "2. Вывод всех контактов\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1: {
            // Поиск контакта
            string searchNumber;
            cout << "Введите номер телефона для поиска: ";
            cin >> searchNumber;

            bool found = false;
            // Открываем файл для записи найденного результата (в режиме добавления)
            ofstream fout("out.txt", ios::app);
            for (int i = 0; i < contactCount; i++) {
                if (contacts[i].phoneNumber == searchNumber) {
                    cout << "Контакт найден: "
                        << contacts[i].name << " - "
                        << contacts[i].phoneNumber << endl;
                    fout << "Контакт найден: "
                        << contacts[i].name << " - "
                        << contacts[i].phoneNumber << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Контакт с номером " << searchNumber << " не найден." << endl;
                fout << "Контакт с номером " << searchNumber << " не найден." << endl;
            }
            fout.close();
            break;
        }
        case 2: {
            // Вывод всех контактов
            cout << "\nСписок контактов:" << endl;
            for (int i = 0; i < contactCount; i++) {
                cout << i + 1 << ". " << contacts[i].name
                    << " - " << contacts[i].phoneNumber << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный выбор, попробуйте снова." << endl;
        }
    }

    return 0;
}
