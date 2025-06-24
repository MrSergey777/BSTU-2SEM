#include "List.h"
#include <iostream>
#include <string>
#include <cstring>  // Для использования strncpy_s
using namespace std;

struct Person
{
    char pass[20] = "";       // Инициализированная пустой строкой
    string datein = "";
    string datteout = "";
    int number = 0;
    string type = "";
    int age = 0;
    Person* next = nullptr;
};

void print(void* b)  // Функция для вывода элемента
{
    Person* a = (Person*)b;
    cout << a->pass << "  "
        << a->datein << "  "
        << a->datteout << "  "
        << a->number << "  "
        << a->type << "  "
        << a->age << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Статическая инициализация тестовых объектов Person
    Person a1 = { "Петров", "", "", 0, "", 20, nullptr };
    Person a2 = { "Сидоров", "", "", 0, "", 25, nullptr };
    Person a3 = { "Гончаров", "", "", 0, "", 47, nullptr };
    bool rc;

    Object L1 = Create();   // создание списка с именем L1
    L1.Insert(&a1);
    L1.Insert(&a2);
    L1.Insert(&a3);

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Печать списка\n";
        cout << "2. Поиск по индексу\n";
        cout << "3. Удаление элемента по индексу\n";
        cout << "4. Подсчет числа элементов списка\n";
        cout << "5. Удаление всего списка\n";
        cout << "6. Добавление элемента\n";
        cout << "7. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nСписок:\n";
            L1.PrintList(print);
            break;
        case 2:
        {
            // Поиск элемента по индексу
            int index;
            cout << "\nВведите индекс элемента для поиска: ";
            cin >> index;
            int count = L1.CountList();
            if (index < 1 || index > count) {
                cout << "Элемент с таким индексом не найден." << endl;
            }
            else {
                Element* current = L1.GetFirst();
                for (int i = 1; i < index; i++)
                {
                    current = current->GetNext();
                }
                Person* res = (Person*)current->Data;
                cout << "Найден элемент: " << res->pass << endl;
            }
        }
        break;
        case 3:
        {
            // Удаление элемента по индексу
            int index;
            cout << "\nВведите индекс элемента для удаления: ";
            cin >> index;
            int count = L1.CountList();
            if (index < 1 || index > count) {
                cout << "Элемент не найден: индекс вне диапазона." << endl;
            }
            else
            {
                Element* current = L1.GetFirst();
                for (int i = 1; i < index; i++)
                {
                    current = current->GetNext();
                }
                rc = L1.Delete(current);
                if (rc)
                    cout << "Удален элемент с индексом " << index << endl;
                else
                    cout << "Удаление не выполнено." << endl;
            }
        }
        break;
        case 4:
        {
            int count = L1.CountList();
            cout << "\nКоличество элементов в списке: " << count << endl;
        }
        break;
        case 5:
        {
            if (L1.DeleteList())
                cout << "\nСписок успешно удален." << endl;
            else
                cout << "\nОшибка при удалении списка." << endl;
        }
        break;
        case 6:
        {
            // Добавление нового элемента в список
            Person* newPerson = new Person;
            string passInput, datein, datteout, type;
            int number, age;

            cout << "\nВведите фамилию (не более 19 символов): ";
            cin >> passInput;
            // Безопасное копирование строки с использованием strncpy_s
            strncpy_s(newPerson->pass, sizeof(newPerson->pass), passInput.c_str(), _TRUNCATE);

            cout << "Введите дату входа: ";
            cin >> datein;
            newPerson->datein = datein;

            cout << "Введите дату выхода: ";
            cin >> datteout;
            newPerson->datteout = datteout;

            cout << "Введите номер: ";
            cin >> number;
            newPerson->number = number;

            cout << "Введите тип: ";
            cin >> type;
            newPerson->type = type;

            cout << "Введите возраст: ";
            cin >> age;
            newPerson->age = age;

            newPerson->next = nullptr;

            if (L1.InsertEnd(newPerson))
                cout << "Новый элемент добавлен." << endl;
            else
                cout << "Ошибка при добавлении элемента." << endl;
        }
        break;
        case 7:
            cout << "\nВыход." << endl;
            break;
        default:
            cout << "\nНеверная опция. Повторите попытку." << endl;
        }
    } while (choice != 7);

    return 0;
}
