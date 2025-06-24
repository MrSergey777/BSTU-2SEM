// 6-7(1).cpp : Основываясь на  вашей схеме базы данных из лаборат
// орной работы №2, реа-лизовать структуры, 
// создать индексы для каждой структуры, а так же реали-зовать вывод структур, 
// линейный поиск данных по индексу (при вводе ин-декса, выводило/удаляло всю структуру). 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  // Добавляем для работы с файлами
using namespace std;

struct Person {
    int id;
    string name;
};

void add(string s, vector<Person>& arr) {
    Person temp;
    temp.id = arr.size() + 1;
    temp.name = s;
    arr.push_back(temp);
}

void out(vector<Person>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i].id << " " << arr[i].name << endl;
    }
}

void search(vector<Person>& arr) {
    cout << "Введите номер нужной структуры ";
    int n;
    cin >> n;
    cout << "Если нужно вывести введите 1, если удалить 2";
    if (n == 1)
        cout << arr[n].id << " " << arr[n].name << endl;
    else {
        arr.erase(arr.begin() + n);
    }
}
void saveToFile(const vector<Person>& arr) {
    ofstream outFile("in.txt");
    if (!outFile) {
        cout << "Ошибка открытия файла  для записи!" << endl;
        return;
    }
    for (const auto& p : arr) {
        outFile << p.id << " " << p.name << "\n";
    }
    outFile.close();
    cout << "Данные успешно записаны в файл " << "in.txt" << endl;
}
void readFromFile(vector<Person>& arr) {
    ifstream inFile("out.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    arr.clear();
    Person temp;
    while (inFile >> temp.id >> temp.name) {
        arr.push_back(temp);
    }
    inFile.close();
    cout << "Данные успешно прочитаны из файла " << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Person> arr;
    int choice;
    string name;
    string filename;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить запись\n";
        cout << "2. Вывести список записей\n";
        cout << "3. Поиск/Удаление записи\n";
        cout << "4. Записать данные в файл\n";
        cout << "5. Прочитать данные из файла\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите имя: ";
            cin >> name;  
            add(name, arr);
            break;
        case 2:
            out(arr);
            break;
        case 3:
            search(arr);
            break;
        case 4:
            saveToFile(arr);
            break;
        case 5:
            readFromFile(arr);
            break;
        case 6:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 6);

    return 0;
}
