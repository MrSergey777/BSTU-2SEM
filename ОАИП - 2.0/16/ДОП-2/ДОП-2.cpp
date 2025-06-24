#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>
#include <cmath>
using namespace std;

// Глобальная переменная для подсчёта сравнений при поиске
int cmpCount = 0;

//------------------------------------------------------
// Структура IntEntry — Хранит целое число (ключ для хеш-таблицы)
//------------------------------------------------------
struct IntEntry {
    int key;  // само число
    IntEntry(int k) : key(k) {}
    IntEntry() : key(0) {}
};

//------------------------------------------------------
// Пространство имён listx — Реализация двусвязного списка
//------------------------------------------------------
namespace listx {

    // Элемент списка
    struct Element {
        Element* prev;
        Element* next;
        void* data;

        Element(Element* pr, void* dat, Element* nt) {
            prev = pr;
            data = dat;
            next = nt;
        }
        Element* getNext() {
            return next;
        }
        Element* getPrev() {
            return prev;
        }
    };

    static Element* NIL = nullptr;

    // Класс списка, содержащий указатель на голову списка
    struct Object {
        Element* head;

        Object() {
            head = NIL;
        }

        Element* getFirst() {
            return head;
        }
        Element* getLast();
        // Поиск элемента по ключевому полю (в данном случае IntEntry::key)
        Element* search(void* data);
        bool insert(void* data);
        bool deleteByElement(Element* e);
        bool deleteByData(void* data);
        void scan();
    };

    // Создать объект списка
    Object create() {
        return *(new Object());
    }

    // Вставка нового элемента (новый элемент становится головой списка)
    bool Object::insert(void* data) {
        if (head == NULL)
            head = new Element(NULL, data, head);
        else
            head = (head->prev = new Element(NULL, data, head));
        return true;
    }

    // Поиск элемента в списке с подсчётом сравнений
    Element* Object::search(void* data) {
        Element* rc = head;
        while (rc != NULL) {
            cmpCount++;  // каждое сравнение между ключами учитывается
            if (((IntEntry*)rc->data)->key == ((IntEntry*)data)->key)
                return rc;
            rc = rc->getNext();
        }
        return nullptr;
    }

    // Удаление элемента по указателю (корректно перенастраиваются связи)
    bool Object::deleteByElement(Element* e) {
        bool rc = false;
        if (e != NULL) {
            rc = true;
            if (e->next != NULL)
                e->next->prev = e->prev;
            if (e->prev != NULL)
                e->prev->next = e->next;
            else
                head = e->next;
            delete e;
            cout << "Элемент удален" << endl;
        }
        return rc;
    }

    // Поиск узла по данным с последующим удалением
    bool Object::deleteByData(void* data) {
        return deleteByElement(search(data));
    }

    // Поиск последнего элемента списка
    Element* Object::getLast() {
        Element* e = this->getFirst();
        Element* rc = this->getFirst();
        while (e != NULL) {
            rc = e;
            e = e->getNext();
        }
        return rc;
    }

    // Вывод списка: для каждого элемента выводится число
    void Object::scan() {
        Element* e = this->getFirst();
        while (e != NULL) {
            IntEntry* item = (IntEntry*)e->data;
            cout << "Число: " << item->key << " / ";
            e = e->getNext();
        }
    }
}

//------------------------------------------------------
// Пространство имён hashTC — Хэш-таблица с цепочками
//------------------------------------------------------
namespace hashTC {

    // Структура хеш-таблицы
    struct Object {
        int size;                           // размер массива (число корзин)
        int (*FunKey)(void*);               // функция для получения ключа
        listx::Object* Hash;                // динамический массив объектов списка (цепочки)

        Object(int siz, int(*f)(void*)) {
            size = siz;
            FunKey = f;
            Hash = new listx::Object[size];
        }

        int hashFunction(void* data);
        bool insert(void* data);
        listx::Element* search(void* data);
        bool deleteByData(void* data);
        void Scan();
    };

    // Создание хеш-таблицы
    Object create(int size, int(*f)(void*)) {
        return *(new Object(size, f));
    }

    // Вычисление хеш-функции (остаток от деления ключа на размер таблицы)
    int Object::hashFunction(void* data) {
        return (FunKey(data) % size);
    }

    // Вставка данных в хеш-таблицу
    bool Object::insert(void* data) {
        int index = hashFunction(data);
        return (Hash[index].insert(data));
    }

    // Поиск элемента по данным
    listx::Element* Object::search(void* data) {
        int index = hashFunction(data);
        // Обратите внимание: cmpCount считается внутри search списка
        return Hash[index].search(data);
    }

    // Удаление данных
    bool Object::deleteByData(void* data) {
        int index = hashFunction(data);
        return (Hash[index].deleteByData(data));
    }

    // Вывод всей хеш-таблицы (каждая корзина выводится по отдельности)
    void Object::Scan() {
        for (int i = 0; i < size; i++) {
            cout << "Корзина " << i << ": ";
            Hash[i].scan();
            cout << '\n';
        }
    }
}

//------------------------------------------------------
// Функция хэширования для элементов типа IntEntry
//------------------------------------------------------
int hf(void* d) {
    IntEntry* p = (IntEntry*)d;
    // Используем абсолютное значение, чтобы избежать отрицательных индексов
    return abs(p->key);
}

//------------------------------------------------------
// Функция main — Главная программа
//------------------------------------------------------
int main() {
    // Для корректного отображения кириллицы
    setlocale(LC_ALL, "rus");

    int tableSize;
    cout << "Введите размер хеш-таблицы:" << endl;
    cin >> tableSize;

    // Создаём хеш-таблицу с заданным размером и функцией хэширования hf
    hashTC::Object H = hashTC::create(tableSize, hf);

    // Открываем текстовый файл, содержащий целые числа (файл numbers.txt должен существовать)
    ifstream fin("numbers.txt");
    if (!fin) {
        cout << "Ошибка открытия файла numbers.txt" << endl;
        return 1;
    }

    int num;
    while (fin >> num) {
        IntEntry* newEntry = new IntEntry(num);
        H.insert(newEntry);
    }
    fin.close();

    // Выводим хеш-таблицу, сформированную из чисел файла
    cout << "\nХеш-таблица, сформированная из чисел файла:" << endl;
    H.Scan();

    // Осуществляем поиск введенного числа в хеш-таблице
    int searchNum;
    cout << "\nВведите число для поиска в хеш-таблице:" << endl;
    cin >> searchNum;

    IntEntry searchEntry(searchNum);
    cmpCount = 0;  // сбрасываем счетчик сравнений
    listx::Element* found = H.search(&searchEntry);
    if (found != NULL) {
        IntEntry* entry = (IntEntry*)found->data;
        cout << "Найдено число: " << entry->key << endl;
    }
    else {
        cout << "Число " << searchNum << " не найдено в хеш-таблице." << endl;
    }
    cout << "Количество сравнений при поиске: " << cmpCount << endl;

    return 0;
}
