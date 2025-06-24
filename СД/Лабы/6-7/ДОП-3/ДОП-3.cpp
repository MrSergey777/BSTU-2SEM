#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct IndexEntry {
    string name;     // имя контакта
    string phone;    // номер телефона (ключ поиска)
    string fileName; // имя файла, из которого была загружена запись
};

int main() {
    const int MAX_ENTRIES = 300;      // максимальное количество записей в индексе
    IndexEntry indexEntries[MAX_ENTRIES];
    int entryCount = 0;

    // Массив имен файлов, из которых собираются записи
    const int numFiles = 3;
    string dataFiles[numFiles] = { "in1.txt", "in2.txt", "in3.txt" };

    // Построение индекса: считываем записи из каждого файла
    for (int i = 0; i < numFiles; i++) {
        ifstream fin(dataFiles[i]);
        if (!fin) {
            cout << "Ошибка открытия файла " << dataFiles[i] << endl;
            continue;
        }
        // Предполагается, что каждая строка имеет формат: имя номер_телефона
        while (fin >> indexEntries[entryCount].name >> indexEntries[entryCount].phone) {
            indexEntries[entryCount].fileName = dataFiles[i];
            entryCount++;
            if (entryCount >= MAX_ENTRIES) break;
        }
        fin.close();
    }

    int choice = -1;
    while (choice != 0) {
        // Вывод меню
        cout << "\nМеню:\n";
        cout << "1. Поиск записи по номеру телефона\n";
        cout << "2. Вывод всех записей\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Поиск записи по номеру телефона
            string searchPhone;
            cout << "Введите номер телефона для поиска: ";
            cin >> searchPhone;
            bool found = false;

            // Открываем файл out.txt для записи результатов поиска (режим добавления)
            ofstream fout("out.txt", ios::app);
            for (int j = 0; j < entryCount; j++) {
                if (indexEntries[j].phone == searchPhone) {
                    cout << "Запись найдена: "
                        << indexEntries[j].name << " - "
                        << indexEntries[j].phone
                        << " (файл: " << indexEntries[j].fileName << ")" << endl;
                    fout << "Запись найдена: "
                        << indexEntries[j].name << " - "
                        << indexEntries[j].phone
                        << " (файл: " << indexEntries[j].fileName << ")" << endl;
                    found = true;
                    // Если в разных файлах могут быть дубликаты, можно не делать break,
                    // чтобы вывести все совпадения.
                }
            }
            if (!found) {
                cout << "Запись с номером " << searchPhone << " не найдена." << endl;
                fout << "Запись с номером " << searchPhone << " не найдена." << endl;
            }
            fout.close();
            break;
        }
        case 2: {
            // Вывод всех записей в индексе
            cout << "\nВсе записи в индексе:" << endl;
            for (int j = 0; j < entryCount; j++) {
                cout << j + 1 << ". "
                    << indexEntries[j].name << " - "
                    << indexEntries[j].phone
                    << " (файл: " << indexEntries[j].fileName << ")" << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный выбор. Пожалуйста, попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}
