#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
using namespace std;

// Глобальная переменная для подсчёта сравнений при поиске
int cmpCount = 0;

// Функция вычисления хеша строки (умножаем предыдущий результат на 31)
int hashString(const char* str) {
    int hash = 0;
    while (*str) {
        hash = hash * 31 + (*str);
        str++;
    }
    return (hash < 0 ? -hash : hash);
}

//------------------------------------------------------
// Структура WordEntry – хранит слово, вычисленный ключ и частоту (количество вхождений)
//------------------------------------------------------
struct WordEntry {
    int key;        // вычисленный хеш слова
    char* word;     // само слово
    int frequency;  // число вхождений

    // Конструктор с параметром
    WordEntry(const char* w) {
        frequency = 1;
        key = hashString(w);
        word = new char[strlen(w) + 1];
        strcpy(word, w);
    }
    WordEntry() {
        key = 0;
        word = nullptr;
        frequency = 0;
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
        // Поиск элемента в списке по ключу и полному сравнению слова; 
        // каждый выполненный шаг увеличивает cmpCount.
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

    // Поиск элемента в списке
    Element* Object::search(void* data) {
        Element* rc = head;
        WordEntry* query = (WordEntry*)data;
        while (rc != NULL) {
            cmpCount++; // сравнение ключей
            WordEntry* current = (WordEntry*)rc->data;
            if (current->key == query->key) {
                cmpCount++; // сравнение строк
                if (strcmp(current->word, query->word) == 0)
                    return rc;
            }
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
            delete e;  // удаляем узел списка (данные освобождаются отдельно!)
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

    // Вывод списка: для каждого элемента выводится слово и его частота
    void Object::scan() {
        Element* e = this->getFirst();
        while (e != NULL) {
            WordEntry* item = (WordEntry*)e->data;
            std::cout << "Слово: " << item->word
                << ", Частота: " << item->frequency << " / ";
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
        int size;                          // размер массива (число корзин)
        int (*FunKey)(void*);              // функция, получающая ключ
        listx::Object* Hash;               // динамический массив объектов списка (цепочки)

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
        return Hash[index].search(data);
    }

    // Удаление данных
    bool Object::deleteByData(void* data) {
        int index = hashFunction(data);
        return (Hash[index].deleteByData(data));
    }

    // Вывод всей хеш-таблицы (каждая "корзина" выводится по отдельности)
    void Object::Scan() {
        for (int i = 0; i < size; i++) {
            std::cout << "Корзина " << i << ": ";
            Hash[i].scan();
            std::cout << '\n';
        }
    }
}

//------------------------------------------------------
// Функция хэширования для элементов типа WordEntry
//------------------------------------------------------
int hf(void* d) {
    WordEntry* f = (WordEntry*)d;
    return f->key;
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

    // Создаем хеш-таблицу с заданным размером и функцией хэширования hf
    hashTC::Object H = hashTC::create(tableSize, hf);

    // Считываем слова из текстового файла (файл words.txt должен существовать в каталоге программы)
    ifstream fin("words.txt");
    if (!fin) {
        cout << "Ошибка открытия файла words.txt" << endl;
        return 1;
    }

    string token;
    while (fin >> token) {
        // Приводим слово к нижнему регистру для единообразия
        for (char& ch : token)
            ch = tolower(ch);
        WordEntry temp(token.c_str());
        listx::Element* found = H.search(&temp);
        if (found != nullptr) {
            // Если слово уже существует — увеличиваем его частоту
            WordEntry* entry = (WordEntry*)found->data;
            entry->frequency++;
        }
        else {
            WordEntry* newEntry = new WordEntry(token.c_str());
            H.insert(newEntry);
        }
    }
    fin.close();

    int choice;
    do {
        cout << "\nМеню:" << endl;
        cout << "1 - Вывести хеш-таблицу" << endl;
        cout << "2 - Поиск слова" << endl;
        cout << "3 - Удалить все слова, начинающиеся на указанную букву" << endl;
        cout << "0 - Выход" << endl;
        cout << "Сделайте выбор: ";
        cin >> choice;

        if (choice == 1) {
            H.Scan();
        }
        else if (choice == 2) {
            cout << "Введите слово для поиска: ";
            string searchWord;
            cin >> searchWord;
            for (char& ch : searchWord)
                ch = tolower(ch);
            WordEntry query(searchWord.c_str());
            cmpCount = 0;  // сбрасываем счетчик сравнений
            listx::Element* found = H.search(&query);
            if (found != nullptr) {
                WordEntry* entry = (WordEntry*)found->data;
                cout << "Найдено слово: " << entry->word
                    << ", Частота: " << entry->frequency << endl;
            }
            else {
                cout << "Слово не найдено." << endl;
            }
            cout << "Количество сравнений при поиске: " << cmpCount << endl;
        }
        else if (choice == 3) {
            cout << "Введите начальную букву для удаления слов: ";
            char letter;
            cin >> letter;
            letter = tolower(letter);
            // Для каждой корзины в хеш-таблице проходим по списку и удаляем слова,
            // начинающиеся на указанную букву.
            for (int i = 0; i < H.size; i++) {
                listx::Object& lst = H.Hash[i];
                listx::Element* current = lst.getFirst();
                while (current != NULL) {
                    listx::Element* next = current->getNext();
                    WordEntry* entry = (WordEntry*)current->data;
                    if (entry->word != nullptr && tolower(entry->word[0]) == letter) {
                        lst.deleteByElement(current);
                        delete entry; // освобождаем память, выделенную под WordEntry
                    }
                    current = next;
                }
            }
            cout << "После удаления слов, начинающихся на букву '" << letter << "':" << endl;
            H.Scan();
        }
    } while (choice != 0);

    return 0;
}
