#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

//------------------------------------------------------
// Структура LetterEntry — Задает букву и количество её вхождений
//------------------------------------------------------
struct LetterEntry {
    int key;       // Ключ для хеш-таблицы (ASCII-код буквы)
    char letter;   // Буква
    int count;     // Количество вхождений

    LetterEntry(int k, char lt, int c) {
        key = k;
        letter = lt;
        count = c;
    }
    LetterEntry() {
        key = 0;
        letter = '\0';
        count = 0;
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
        if (head == NULL)
            head = new Element(NULL, data, head);
        else
            head = (head->prev = new Element(NULL, data, head));
        return true;
    }

    // Поиск элемента в списке по ключевому полю (сравнение по полю key)
    Element* Object::search(void* data) {
        Element* rc = head;
        while (rc != NULL && (((LetterEntry*)rc->data)->key != ((LetterEntry*)data)->key))
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

    // Вывод списка: для каждого элемента выводится буква и количество её вхождений
    void Object::scan() {
        Element* e = this->getFirst();
        while (e != NULL) {
            LetterEntry* item = (LetterEntry*)e->data;
            cout << "Буква: " << item->letter
                << ", Частота: " << item->count << " / ";
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
        int size;                           // Размер массива (число корзин)
        int (*FunKey)(void*);               // Функция для получения ключа
        listx::Object* Hash;                // Динамический массив объектов списка (цепочки)

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
            cout << '\n';
        }
    }
}

//------------------------------------------------------
// Функция хэширования для элементов типа LetterEntry
//------------------------------------------------------
int hf(void* d) {
    LetterEntry* f = (LetterEntry*)d;
    return f->key;
}

//------------------------------------------------------
// Функция для вывода найденного элемента (если необходимо)
//------------------------------------------------------
void Letter_print(listx::Element* e) {
    LetterEntry* item = (LetterEntry*)e->data;
    cout << "Буква: " << item->letter << ", Частота: " << item->count << " / ";
}

//------------------------------------------------------
// Функция main — Главная программа
//------------------------------------------------------
int main() {
    setlocale(LC_ALL, "rus");

    int tableSize;
    cout << "Введите размер хеш-таблицы:" << endl;
    cin >> tableSize;
    cin.ignore(); 
    // Создаём хеш-таблицу с заданным размером и функцией хэширования hf
    hashTC::Object H = hashTC::create(tableSize, hf);
    cout << "Введите строку:" << endl;
    string input;
    getline(cin, input);

    // Обрабатываем каждый символ строки: если это буква, приводим к нижнему регистру
    // и вставляем или обновляем элемент в хеш-таблице
    for (char ch : input) {
        if (isalpha((unsigned char)ch)) {
            ch = tolower(ch);
            LetterEntry temp;
            temp.key = (int)ch;
            temp.letter = ch;
            listx::Element* found = H.search(&temp);
            if (found != NULL) {
                // Если запись с такой буквой уже есть, увеличиваем число вхождений
                LetterEntry* entry = (LetterEntry*)found->data;
                entry->count++;
            }
            else {
                // Если записи нет, создаём новый элемент с count = 1
                LetterEntry* newEntry = new LetterEntry();
                newEntry->key = (int)ch;
                newEntry->letter = ch;
                newEntry->count = 1;
                H.insert(newEntry);
            }
        }
    }
    cout << "\nХеш-таблица с буквами и их вхождениями:" << endl;
    H.Scan();
    cout << "\nВведите букву для поиска:" << endl;
    char query;
    cin >> query;
    query = tolower(query);
    LetterEntry queryEntry;
    queryEntry.key = (int)query;
    queryEntry.letter = query;
    listx::Element* searchResult = H.search(&queryEntry);
    if (searchResult != NULL) {
        LetterEntry* resultEntry = (LetterEntry*)searchResult->data;
        cout << "Найденная буква: " << resultEntry->letter
            << ", Вхождения: " << resultEntry->count << endl;
    }
    else {
        cout << "Буква " << query << " не найдена в хеш-таблице." << endl;
    }

    return 0;
}
