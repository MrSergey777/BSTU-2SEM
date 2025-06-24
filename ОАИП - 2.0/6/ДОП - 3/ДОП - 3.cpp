//Создать список, содержащий элементы целого типа.
// Найти сумму отрицательных элементов, кратных 2, или выдать сообщение, что таких элементов нет.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct list
{
    int a;
    list* next;
};
void menu()
{
    cout << " 1 - Ввод числа" << endl;
    cout << " 2 - Удаление элемента" << endl;
    cout << " 3 - поиск элемента" << endl;
    cout << " 4 - Вывод списка" << endl;
    cout << " 5 - запись списка в файл" << endl;
    cout << " 6 - считывание списка из файла" << endl;
    cout << " 7 - Найти сумму отрицательных элементов, кратных 2" << endl;
    cout << " 8 - Выход" << endl;
    cout << "Сделайте выбор: ";
}

void in(list*& p, int value) {
    list* newP = new list;
    if (newP != NULL)
    {
        newP->a = value;
        newP->next = p;
        p = newP;
    }
    else
        cout << "Операция добавления не выполнена" << endl;
}

void out(list* p) {
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (p != NULL)
        {
            cout << "-->" << p->a;
            p = p->next;
        }
        cout << "-->NULL" << endl;
    }
}

void search_element(list* p) {
    cout << "Введите номер элемента для поиска: ";
    int n;
    cin >> n;
    int index = 0;
    while (p != NULL) {
        if (index == n) {
            cout << "Элемент найден: " << p->a << endl;
            return;
        }
        p = p->next;
        index++;
    }
    cout << "Элемент с указанным номером не найден." << endl;
}

int delet(list*& p, int value) {
    list* previous, * current, * temp;
    if (value == p->a)
    {
        temp = p;
        p = p->next;
        delete temp;
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->a != value)
        {
            previous = current;
            current = current->next;
        }
        if (current != NULL)
        {
            temp = current;
            previous->next = current->next;
            delete(temp);
            return value;
        }
    }
    return '\0';
}

void write(list* p) {
    ofstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\6\\pls.txt");
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла для записи" << endl;
        return;
    }
    while (p != nullptr) {
        file << p->a << endl;
        p = p->next;
    }
    file.close();
    cout << "Список успешно записан в файл" << endl;
}

void read(list*& p) {
    ifstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\6\\pls.txt");
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла для чтения" << endl;
        return;
    }
    int value;
    while (file >> value) {
        in(p, value);
    }
    file.close();
    cout << "Список успешно считан из файла" << endl;
}

void find_negative_even_sum(list* p) {
    int sum = 0;
    bool found = false;
    while (p != nullptr) {
        if (p->a < 0 && p->a % 2 == 0) {
            sum += p->a;
            found = true;
        }
        p = p->next;
    }
    if (found) {
        cout << "Сумма отрицательных элементов, кратных 2: " << sum << endl;
    }
    else {
        cout << "Таких элементов нет." << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    list* plist = nullptr;
    list* p;
    int choice = 0;
    menu();
    cin >> choice;
    while (choice != 8) {
        if (choice == 1) {
            cout << "Введите число: ";
            int q;
            cin >> q;
            in(plist, q);
        }
        else if (choice == 4) {
            out(plist);
        }
        else if (choice == 3) {
            search_element(plist);
        }
        else if (choice == 2) {
            cout << "Введите элемент, который хотите удалить: ";
            int qq;
            cin >> qq;
            delet(plist, qq);
        }
        else if (choice == 5) {
            write(plist);
        }
        else if (choice == 6) {
            read(plist);
        }
        else if (choice == 7) {
            find_negative_even_sum(plist);
        }
        menu();
        cin >> choice;
    }
}
