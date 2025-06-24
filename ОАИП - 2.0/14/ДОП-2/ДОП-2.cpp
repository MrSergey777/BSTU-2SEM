#include <iostream>
#include <cstdlib>
#include <clocale>
#include <chrono>
#include <cmath>    // для floor()

using namespace std;

// Специальный маркер удалённого элемента (DEL), чтобы отличать пустую ячейку от удалённой.
#define HASHDEL (void*)-1
static void* DEL = (void*)HASHDEL;

//---------------------------------------------------------------------
// Функции хеширования

// Модульное хеширование: наивно возвращает остаток от деления ключа на размер таблицы.
int ModularHashFunction(int key, int size) {
    return key % size;
}

// Мультипликативное хеширование: используется дробная часть произведения key * A.
// A выбирается равным 0.6180339887 (примерно золотое сечение).
int MultiplicativeHashFunction(int key, int size) {
    const double A = 0.6180339887;
    double frac = key * A - floor(key * A); // дробная часть
    return static_cast<int>(size * frac);
}

/*
 * Функция для вычисления следующей позиции при коллизии.
 * Здесь используется нелинейная схема: next_index = (initial + 5*i + 3*i*i) mod size,
 * где i – номер попытки.
 */
int Next_hash(int initial, int size, int i) {
    return (initial + 5 * i + 3 * i * i) % size;
}

//---------------------------------------------------------------------
// Структура хеш-таблицы с открытой адресацией

/*
 * Структура Object хранит:
 *  - data: массив указателей типа void* для хранения элементов,
 *  - size: количество ячеек таблицы,
 *  - N: текущее число занятых ячеек,
 *  - collisionCount: суммарное число коллизий, произошедших при вставке,
 *  - getKey: функция для извлечения ключа (например, из структуры AAA),
 *  - hashFunc: указатель на функцию хеширования с сигнатурой (int (*)(int, int)).
 */
struct Object {
    void** data;
    int size;
    int N;
    int collisionCount;
    int (*getKey)(void*);
    int (*hashFunc)(int, int);

    Object(int size, int (*getkey)(void*), int (*hashF)(int, int));

    bool insert(void*);
    int searchInd(int key);
    void* search(int key);
    void* deleteByKey(int key);
    bool deleteByValue(void*);
    void scan(void(*)(void*));
};

Object::Object(int s, int (*getkey)(void*), int (*hashF)(int, int)) {
    N = 0;
    collisionCount = 0;
    size = s;
    getKey = getkey;
    hashFunc = hashF;
    data = new void* [size];
    for (int i = 0; i < size; ++i)
        data[i] = NULL;
}

/*
 * Метод insert – вставляет элемент d в таблицу.
 * Вычисляется начальный индекс через выбранную функцию hashFunc.
 * При занятой ячейке происходит шаг по последовательности проб с помощью Next_hash;
 * при каждом столкновении увеличивается счётчик collisionCount.
 */
bool Object::insert(void* d) {
    if (N == size) return false;
    int keyVal = getKey(d);
    int initial = hashFunc(keyVal, size);
    int i = 0, j = initial;
    bool inserted = false;
    while (i < size && !inserted) {
        if (data[j] == NULL || data[j] == DEL) {
            data[j] = d;
            inserted = true;
            N++;
        }
        else {
            collisionCount++;
        }
        if (!inserted) {
            i++;
            j = Next_hash(initial, size, i);
        }
    }
    return inserted;
}

/*
 * Метод searchInd ищет индекс элемента по ключу,
 * проходя по той же последовательности проб, что и при вставке.
 */
int Object::searchInd(int key) {
    if (N == 0) return -1;
    int initial = hashFunc(key, size);
    int i = 0, j = initial;
    while (i < size && data[j] != NULL) {
        if (data[j] != DEL && getKey(data[j]) == key)
            return j;
        i++;
        j = Next_hash(initial, size, i);
    }
    return -1;
}

void* Object::search(int key) {
    int index = searchInd(key);
    return (index >= 0) ? data[index] : NULL;
}

void* Object::deleteByKey(int key) {
    int index = searchInd(key);
    if (index == -1) return NULL;
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
 * Метод scan обходит всю таблицу и для каждой ячейки:
 *  - если ячейка пуста (NULL) – выводит сообщение "пусто",
 *  - если содержит маркер DEL – выводит "удален",
 *  - иначе – вызывает переданную функцию (например, AAA_print) для вывода содержимого.
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

//---------------------------------------------------------------------
// Пользовательский тип данных AAA

struct AAA {
    int key;
    char* mas;

    AAA(int k, char* z) {
        key = k;
        mas = z;
    }
    AAA() {}
};

/*
 * Функция keyFunction извлекает целочисленный ключ из объекта типа AAA.
 */
int keyFunction(void* d) {
    AAA* a = (AAA*)d;
    return a->key;
}

/*
 * Функция AAA_print выводит данные объекта типа AAA в консоль.
 */
void AAA_print(void* d) {
    AAA* a = (AAA*)d;
    cout << " ключ " << a->key << " - " << a->mas << endl;
}

//---------------------------------------------------------------------
// Функция measureSearchTime измеряет время поиска элемента с заданным ключом в таблице.
void measureSearchTime(Object& H, int key) {
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

//---------------------------------------------------------------------
// Функция compareSearchTimes создаёт две таблицы одинакового размера:
// одну с мультипликативным, а другую с модульным хешированием.
// Для каждой таблицы выполняется набор поисковых запросов,
 // суммируется общее время и выводится среднее время поиска.
void compareSearchTimes(int tableSize, int numSearches) {
    // Создаём две таблицы одинакового размера.
    Object H_mul(tableSize, keyFunction, MultiplicativeHashFunction);
    Object H_mod(tableSize, keyFunction, ModularHashFunction);

    // Вставляем одинаковые элементы (например, ключи от 1 до tableSize/2).
    for (int i = 1; i <= tableSize / 2; i++) {
        char* s = new char[20];
        snprintf(s, 20, "Elem%d", i);
        AAA* a1 = new AAA(i, s);
        AAA* a2 = new AAA(i, s);
        H_mul.insert(a1);
        H_mod.insert(a2);
    }

    long long totalTime_mul = 0;
    long long totalTime_mod = 0;
    for (int i = 0; i < numSearches; i++) {
        int key = rand() % tableSize;
        auto start_mul = chrono::high_resolution_clock::now();
        H_mul.search(key);
        auto end_mul = chrono::high_resolution_clock::now();
        long long duration_mul = chrono::duration_cast<chrono::nanoseconds>(end_mul - start_mul).count();
        totalTime_mul += duration_mul;

        auto start_mod = chrono::high_resolution_clock::now();
        H_mod.search(key);
        auto end_mod = chrono::high_resolution_clock::now();
        long long duration_mod = chrono::duration_cast<chrono::nanoseconds>(end_mod - start_mod).count();
        totalTime_mod += duration_mod;
    }

    cout << "\nСравнение времени поиска (среднее по " << numSearches << " запросов):" << endl;
    cout << "Мультипликативное хеширование: " << totalTime_mul / numSearches
        << " наносекунд (суммарно " << totalTime_mul << ")." << endl;
    cout << "Модульное хеширование: " << totalTime_mod / numSearches
        << " наносекунд (суммарно " << totalTime_mod << ")." << endl;
}

//---------------------------------------------------------------------
// Главная функция с меню

int main() {
    setlocale(LC_ALL, "rus");
    int siz, choice, k;
    cout << "Введите размер хеш-таблицы: ";
    cin >> siz;

    // Создаём основную таблицу с мультипликативным хешированием (используется по умолчанию).
    Object H(siz, keyFunction, MultiplicativeHashFunction);

    for (;;) {
        cout << "\nМеню:" << endl;
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента по ключу" << endl;
        cout << "4 - поиск элемента по ключу" << endl;
        cout << "5 - измерение времени поиска элемента" << endl;
        cout << "6 - сравнение времени поиска (Мультипликативное vs Модульное хеширование)" << endl;
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
            char* s = new char[20];
            cout << "Введите ключ: ";
            cin >> k;
            a->key = k;
            cout << "Введите строку: ";
            cin >> s;
            a->mas = s;
            if (H.N == H.size)
                cout << "Таблица заполнена" << endl;
            else
                H.insert(a);
            break;
        }
        case 3: {
            cout << "Введите ключ для удаления: ";
            cin >> k;
            if (H.deleteByKey(k))
                cout << "Элемент удалён" << endl;
            else
                cout << "Элемент не найден" << endl;
            break;
        }
        case 4: {
            cout << "Введите ключ для поиска: ";
            cin >> k;
            void* found = H.search(k);
            if (found == NULL)
                cout << "Элемент не найден" << endl;
            else
                AAA_print(found);
            break;
        }
        case 5: {
            cout << "Введите ключ для измерения времени поиска: ";
            cin >> k;
            measureSearchTime(H, k);
            break;
        }
        case 6: {
            int numSearches;
            cout << "Введите количество поисковых запросов для сравнения: ";
            cin >> numSearches;
            compareSearchTimes(siz, numSearches);
            break;
        }
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }

    return 0;
}
