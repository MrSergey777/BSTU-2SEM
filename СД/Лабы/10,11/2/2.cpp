#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

struct Record {
    int id;
    string name;
};

const int dbCapacity = 100;
Record* database = new Record[dbCapacity];
int dbSize = 0;

void addRecord(int id, const string& name) {
    if (dbSize < dbCapacity) {
        database[dbSize].id = id;
        database[dbSize].name = name;
        dbSize++;
        cout << "Запись добавлена!" << endl;
    }
    else {
        cout << "База данных заполнена." << endl;
    }
}

void printDB() {
    if (dbSize == 0) {
        cout << "БД пуста." << endl;
    }
    else {
        cout << "Содержимое БД:" << endl;
        for (int i = 0; i < dbSize; i++) {
            cout << "id: " << database[i].id
                << ", name: " << database[i].name << endl;
        }
    }
}

void writeDBToFile() {
    ofstream outFile("1.txt", ios::out | ios::trunc);
    if (!outFile) {
        cout << "Ошибка открытия файла для записи." << endl;
        return;
    }
    for (int i = 0; i < dbSize; i++) {
        outFile << "id: " << database[i].id
            << ", name: " << database[i].name << "\n";
    }
    outFile.close();
    cout << "БД записана в файл 1.txt." << endl;
}

void clearDBContent() {
    dbSize = 0;
    cout << "Содержимое БД в памяти очищено." << endl;
    ofstream outFile("1.txt", ios::out | ios::trunc);
    if (!outFile) {
        cout << "Ошибка открытия файла для очистки." << endl;
    }
    outFile.close();
    cout << "Содержимое файла 1.txt очищено." << endl;
}

void deleteDB() {
    delete[] database;
    database = nullptr;
    dbSize = 0;
    cout << "БД в памяти полностью удалена." << endl;
    if (remove("1.txt") == 0) {
        cout << "Файл 1.txt удалён." << endl;
    }
    else {
        cout << "Ошибка при удалении файла 1.txt или файл не существует." << endl;
    }
}

void deleteRecord(int index) {
    if (index < 0 || index >= dbSize) {
        cout << "Некорректный индекс. Удаление невозможно." << endl;
        return;
    }
    for (int i = index; i < dbSize - 1; i++) {
        database[i] = database[i + 1];
    }
    dbSize--;
    cout << "Запись удалена." << endl;
}

void editRecord(int index, int newId, const string& newName) {
    if (index < 0 || index >= dbSize) {
        cout << "Некорректный индекс. Редактирование невозможно." << endl;
        return;
    }
    database[index].id = newId;
    database[index].name = newName;
    cout << "Запись обновлена." << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\nВыберите действие:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Вывести содержимое БД" << endl;
        cout << "3. Записать БД в файл" << endl;
        cout << "4. Очистить содержимое БД и файла" << endl;
        cout << "5. Полное удаление БД (память и файл)" << endl;
        cout << "6. Удалить запись по индексу" << endl;
        cout << "7. Редактировать запись по индексу" << endl;
        cout << "8. Выход" << endl;

        cout << "Введите номер действия: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name;
            cout << "Введите id: ";
            cin >> id;
            cout << "Введите имя: ";
            cin.ignore();
            getline(cin, name);
            addRecord(id, name);
            break;
        }
        case 2:
            printDB();
            break;
        case 3:
            writeDBToFile();
            break;
        case 4:
            clearDBContent();
            break;
        case 5:
            deleteDB();
            exitProgram = true;
            break;
        case 6: {
            int deleteIndex;
            cout << "Введите индекс удаляемой записи: ";
            cin >> deleteIndex;
            deleteRecord(deleteIndex);
            break;
        }
        case 7: {
            int editIndex, newId;
            string newName;
            cout << "Введите индекс редактируемой записи: ";
            cin >> editIndex;
            cout << "Введите новый id: ";
            cin >> newId;
            cout << "Введите новое имя: ";
            cin.ignore();
            getline(cin, newName);
            editRecord(editIndex, newId, newName);
            break;
        }
        case 8:
            exitProgram = true;
            break;
        default:
            cout << "Неверный выбор. Попробуйте ещё раз." << endl;
        }
    }

    return 0;
}
