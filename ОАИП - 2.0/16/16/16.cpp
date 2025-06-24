#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
using namespace std;

//------------------------------------------------------
// Структура AAA (Email Address Entry)
//------------------------------------------------------
// Поля:
//   key     – год создания (ключ для хеш-таблицы)
//   address – адрес (например, email адрес)
//   surname – фамилия абонента
//------------------------------------------------------
struct AAA {
    int key;           // год создания (ключ)
    char* address;     // адрес
    char* surname;     // фамилия абонента

    AAA(int k, char* addr, char* sname) {
        key = k;
        address = addr;
        surname = sname;
    }
    AAA() {
        key = 0;
        address = nullptr;
        surname = nullptr;
    }
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
        bool rc = false;
        if (head == NULL)
            head = new Element(NULL, data, head);
        else
            head = (head->prev = new Element(NULL, data, head));
        return rc;
    }

    // Поиск элемента в списке по ключевому полю (год создания)
    Element* Object::search(void* data) {
        Element* rc = head;
        while (rc != NULL && (((AAA*)rc->data)->key != ((AAA*)data)->key))
            rc = rc->next;
        return rc;
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
            std::cout << "Элемент удален" << std::endl;
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

    // Вывод списка: для каждого элемента выводятся год, адрес и фамилия
    void Object::scan() {
        Element* e = this->getFirst();
        while (e != NULL) {
            AAA* item = (AAA*)e->data;
            std::cout << "Год: " << item->key
                << ", Адрес: " << item->address
                << ", Фамилия: " << item->surname << " / ";
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
        int (*FunKey)(void*);               // функция, получающая ключ
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

    Object create(int size, int(*f)(void*)) {
        return *(new Object(size, f));
    }

    int Object::hashFunction(void* data) {
        return (FunKey(data) % size);
    }

    bool Object::insert(void* data) {
        int index = hashFunction(data);
        return (Hash[index].insert(data));
    }

    listx::Element* Object::search(void* data) {
        int index = hashFunction(data);
        return Hash[index].search(data);
    }

    bool Object::deleteByData(void* data) {
        int index = hashFunction(data);
        return (Hash[index].deleteByData(data));
    }

    void Object::Scan() {
        for (int i = 0; i < size; i++) {
            Hash[i].scan();
            std::cout << '\n';
        }
    }
}

//------------------------------------------------------
// Функция хэширования для элементов типа AAA
//------------------------------------------------------
// Возвращает год создания как ключ
int hf(void* d) {
    AAA* f = (AAA*)d;
    return f->key;
}

//------------------------------------------------------
// Функция для вывода найденного элемента
//------------------------------------------------------
void AAA_print(listx::Element* e) {
    AAA* item = (AAA*)e->data;
    std::cout << "Год: " << item->key
        << ", Адрес: " << item->address
        << ", Фамилия: " << item->surname << " / ";
}

//------------------------------------------------------
// Функция main — Главная программа
//------------------------------------------------------
int main() {
    // Для корректного отображения кириллицы
    setlocale(LC_ALL, "rus");

    int current_size;
    cout << "Введите размер хеш-таблицы:" << endl;
    cin >> current_size;

    // Создаём хеш-таблицу с заданным размером и функцией хэширования hf
    hashTC::Object H = hashTC::create(current_size, hf);

    int choice;
    for (;;) {
        cout << "\nМеню:" << endl;
        cout << "1 - Вывод хеш-таблицы" << endl;
        cout << "2 - Добавление элемента" << endl;
        cout << "3 - Удаление элемента" << endl;
        cout << "4 - Поиск элемента" << endl;
        cout << "0 - Выход" << endl;
        cout << "Сделайте выбор: ";
        cin >> choice;

        if (choice == 0)
            exit(0);

        switch (choice) {
        case 1:
            H.Scan();
            break;
        case 2: {
            AAA* a = new AAA;
            cout << "Введите год создания (ключ):" << endl;
            cin >> a->key;
            // Ввод адреса
            char bufferAddr[50];
            cout << "Введите адрес:" << endl;
            cin >> bufferAddr;
            a->address = new char[strlen(bufferAddr) + 1];
            strcpy(a->address, bufferAddr);
            // Ввод фамилии абонента
            char bufferSurname[50];
            cout << "Введите фамилию абонента:" << endl;
            cin >> bufferSurname;
            a->surname = new char[strlen(bufferSurname) + 1];
            strcpy(a->surname, bufferSurname);

            H.insert(a);
            break;
        }
        case 3: {
            AAA* b = new AAA;
            cout << "Введите год создания для удаления:" << endl;
            cin >> b->key;
            if (!H.deleteByData(b))
                cout << "Элемент не найден для удаления." << endl;
            break;
        }
        case 4: {
            AAA* c = new AAA;
            cout << "Введите год создания для поиска:" << endl;
            cin >> c->key;
            listx::Element* found = H.search(c);
            if (found == NULL)
                cout << "Элемент не найден" << endl;
            else {
                cout << "Найден элемент: ";
                AAA_print(found);
                cout << endl;
            }
            break;
        }
        default:
            cout << "Неверный выбор, попробуйте ещё раз." << endl;
        }
    }
    return 0;
}
