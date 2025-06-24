// (10, 11) - Написать функции удаления(очистки) содержимого 
// вашей БД и полного удаления вашей БД. 
// Функции удаляют информацию как из файла, так и из структуры БД
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
        cout << "6. Выход" << endl;

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
        case 6:
            exitProgram = true;
            break;
        default:
            cout << "Неверный выбор. Попробуйте ещё раз." << endl;
        }
    }

    return 0;
}

