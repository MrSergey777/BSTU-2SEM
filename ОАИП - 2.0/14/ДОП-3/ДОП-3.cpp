#include <iostream>
#include <cstdlib>
#include <clocale>
#include <chrono>
#include <cstring>   // Для strcmp и strcpy

using namespace std;

// Специальный маркер удалённого элемента (DEL)
#define HASHDEL (void*)-1
static void* DEL = (void*)HASHDEL;

/*
 * Аддитивная хеш-функция для строк.
 * Функция проходит по символам строки, складывая их ASCII-коды,
 * а затем берёт остаток от деления на размер таблицы.
 */
int AdditiveHashFunction(const char* key, int size) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += static_cast<int>(key[i]);
    }
    return sum % size;
}

/*
 * Функция для вычисления следующей позиции (проба) при коллизии.
 * Формула: next_index = (initial + 5*i + 3*i*i) mod size,
 * где i — номер попытки.
 */
int Next_hash(int initial, int size, int i) {
    return (initial + 5 * i + 3 * i * i) % size;
}

/*
 * Структура Object реализует хеш-таблицу с открытой адресацией.
 * Поля:
 *    - data: массив указателей для хранения элементов.
 *    - size: размер таблицы.
 *    - N: количество занятых ячеек.
 *    - getKey: функция, возвращающая строковый ключ из элемента.
 */
struct Object {
    void** data;                       // Массив для хранения элементов
    int size;                          // Размер таблицы
    int N;                             // Количество занятых ячеек
    const char* (*getKey)(void*);      // Функция для извлечения строкового ключа

    Object(int size, const char* (*getkey)(void*));

    bool insert(void* d);
    int searchInd(const char* key);
    void* search(const char* key);
    void* deleteByKey(const char* key);
    bool deleteByValue(void* d);
    void scan(void(*)(void*));
};

Object::Object(int size, const char* (*getkey)(void*)) {
    N = 0;
    this->size = size;
    this->getKey = getkey;
    data = new void* [size];
    for (int i = 0; i < size; ++i)
        data[i] = NULL;
}

/*
 * Метод insert – вставляет элемент d в хеш-таблицу.
 * Начальный индекс вычисляется с помощью аддитивной хеш-функции по строковому ключу.
 * При коллизии используется последовательность проб с помощью Next_hash.
 */
bool Object::insert(void* d) {
    bool inserted = false;
    if (N != size) {
        const char* keyStr = getKey(d);
        int initial = AdditiveHashFunction(keyStr, size);
        for (int i = 0, j = initial; i != size && !inserted; j = Next_hash(initial, size, ++i)) {
            if (data[j] == NULL || data[j] == DEL) {
                data[j] = d;
                N++;
                inserted = true;
            }
        }
    }
    return inserted;
}

/*
 * Метод searchInd – ищет индекс элемента с заданным строковым ключом.
 * При пробировании используется та же последовательность: начальный индекс по AdditiveHashFunction,
 * затем Next_hash.
 */
int Object::searchInd(const char* key) {
    int indexFound = -1;
    if (N != 0) {
        int initial = AdditiveHashFunction(key, size);
        for (int i = 0, j = initial; i != size && data[j] != NULL; j = Next_hash(initial, size, ++i)) {
            if (data[j] != DEL && strcmp(getKey(data[j]), key) == 0) {
                indexFound = j;
                break;
            }
        }
    }
    return indexFound;
}

/*
 * Метод search – возвращает элемент с заданным ключом (или NULL, если не найден).
 */
void* Object::search(const char* key) {
    int index = searchInd(key);
    return (index >= 0) ? data[index] : NULL;
}

/*
 * Метод deleteByKey – удаляет элемент по заданному строковому ключу.
 * Если элемент найден, ячейка помечается маркером DEL, а N уменьшается.
 */
void* Object::deleteByKey(const char* key) {
    int index = searchInd(key);
    if (index == -1)
        return NULL;
    void* temp = data[index];
    if (temp != NULL) {
        data[index] = DEL;
        N--;
    }
    return temp;
}

bool Object::deleteByValue(void* d) {
    return (deleteByKey(getKey(d)) != NULL);
}

/*
 * Метод scan – обход всей таблицы. Для каждой ячейки выводится её индекс и состояние.
 * Если ячейка пуста (NULL) – выводится "пусто", если содержит маркер удаления (DEL) – "удален",
 * иначе вызывается переданная функция для вывода элемента.
 */
void Object::scan(void(*f)(void*)) {
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i;
        if (data[i] == NULL)
            cout << "  пусто" << endl;
        else if (data[i] == DEL)
            cout << "  удален" << endl;
        else
            f(data[i]);
    }
}

/*
 * Структура AAA – пользовательский тип данных.
 * Теперь ключ – строка, а поле mas – дополнительная строка.
 */
struct AAA {
    char key[50];  // строковый ключ
    char mas[50];  // дополнительное строковое поле

    AAA() {}  // Конструктор по умолчанию
};

/*
 * Функция для извлечения ключа из объекта типа AAA.
 */
const char* keyFunction(void* d) {
    AAA* a = (AAA*)d;
    return a->key;
}

/*
 * Функция печати объекта типа AAA.
 */
void AAA_print(void* d) {
    AAA* a = (AAA*)d;
    cout << " ключ: " << a->key << " - " << a->mas << endl;
}

/*
 * Функция measureSearchTime измеряет время поиска элемента с заданным ключом.
 */
void measureSearchTime(Object& H, const char* key) {
    auto start = chrono::high_resolution_clock::now();
    void* result = H.search(key);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Время поиска: " << duration << " наносекунд." << endl;
    if (result == NULL)
        cout << "Элемент не найден" << endl;
    else
        AAA_print(result);
}

/*
 * Главная функция. Реализовано меню для:
 *   1. Вывода хеш-таблицы.
 *   2. Добавления элемента.
 *   3. Удаления элемента по ключу.
 *   4. Поиска элемента по ключу.
 *   5. Замера времени поиска.
 */
int main() {
    setlocale(LC_ALL, "rus");
    int siz, choice;
    char tempKey[50];

    cout << "Введите размер хеш-таблицы: ";
    cin >> siz;
    Object H(siz, keyFunction);

    for (;;) {
        cout << "\nМеню:" << endl;
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента" << endl;
        cout << "4 - поиск элемента" << endl;
        cout << "5 - измерение времени поиска" << endl;
        cout << "0 - выход" << endl;
        cout << "Сделайте выбор: ";
        cin >> choice;
        switch (choice) {
        case 0:
            exit(0);
        case 1:
            H.scan(AAA_print);
            break;
        case 2: {
            AAA* a = new AAA;
            cout << "Введите ключ: ";
            cin >> a->key;
            cout << "Введите строку: ";
            cin >> a->mas;
            if (H.N == H.size)
                cout << "Таблица заполнена" << endl;
            else
                H.insert(a);
            break;
        }
        case 3: {
            cout << "Введите ключ для удаления: ";
            cin >> tempKey;
            if (H.deleteByKey(tempKey))
                cout << "Элемент удалён" << endl;
            else
                cout << "Элемент не найден" << endl;
            break;
        }
        case 4: {
            cout << "Введите ключ для поиска: ";
            cin >> tempKey;
            void* found = H.search(tempKey);
            if (found == NULL)
                cout << "Элемент не найден" << endl;
            else
                AAA_print(found);
            break;
        }
        case 5: {
            cout << "Введите ключ для измерения времени поиска: ";
            cin >> tempKey;
            measureSearchTime(H, tempKey);
            break;
        }
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }
    return 0;
}
