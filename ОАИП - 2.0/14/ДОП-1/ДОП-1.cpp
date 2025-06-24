#include <iostream>
#include <cstdlib>
#include <clocale>
#include <chrono>

using namespace std;

// Специальный маркер удалённого элемента (DEL). Используется для пометки ячеек после удаления.
#define HASHDEL (void*)-1
static void* DEL = (void*)HASHDEL;

//---------------------------------------------------------------------
// Определения хеш-функций

/*
 * Универсальное хеширование.
 * Формула: h(key) = ((a * key + b) mod p) mod size,
 * где p – простое число, a и b – константы (1 ≤ a < p, 0 ≤ b < p).
 * Это обеспечивает равномерное распределение ключей независимо от входных данных.
 */
int UniversalHashFunction(int key, int size) {
    const int p = 101;   // Простое число (для демонстрации)
    const int a = 3;     // Константа a (1 ≤ a < p)
    const int b = 7;     // Константа b (0 ≤ b < p)
    return ((a * key + b) % p) % size;
}

/*
 * Модульное хеширование.
 * Формула: h(key) = key mod size
 * Это самый простой способ получения индекса, хотя при неравномерном распределении ключей
 * может возникать много коллизий.
 */
int ModularHashFunction(int key, int size) {
    return key % size;
}

/*
 * Функция для вычисления следующей позиции (проба) при коллизии.
 * Здесь используется формула: next_index = (initial + 5*i + 3*i*i) mod size,
 * где i – номер попытки.
 */
int Next_hash(int initial, int size, int i) {
    return (initial + 5 * i + 3 * i * i) % size;
}

//---------------------------------------------------------------------
// Структура Object – хеш-таблица с открытой адресацией

/*
 * Object хранит:
 *   - data: массив указателей (void**) для хранения данных;
 *   - size: число ячеек таблицы;
 *   - N: число занятых ячеек;
 *   - collisionCount: суммарное число коллизий при вставках;
 *   - getKey: функция для извлечения ключа из элемента (универсальна);
 *   - hashFunc: выбранная функция хеширования с сигнатурой (int (*)(int, int)).
 */
struct Object {
    void** data;
    int size;
    int N;
    int collisionCount;
    int (*getKey)(void*);
    int (*hashFunc)(int, int);

    // Конструктор принимает размер, функцию извлечения ключа и указатель на функцию хеширования.
    Object(int size, int (*getkey)(void*), int (*hashF)(int, int));

    bool insert(void*);
    int searchInd(int key);
    void* search(int key);
    void* deleteByKey(int key);
    bool deleteByValue(void*);
    void scan(void(*)(void*));
};

// Конструктор: выделяет память под массив data заданного размера, инициализирует все ячейки значением NULL.
Object::Object(int size, int (*getkey)(void*), int (*hashF)(int, int)) {
    N = 0;
    collisionCount = 0;
    this->size = size;
    this->getKey = getkey;
    this->hashFunc = hashF;
    data = new void* [size];
    for (int i = 0; i < size; ++i)
        data[i] = NULL;
}

/*
 * Метод insert – вставляет элемент d в таблицу.
 * Начальный индекс вычисляется через выбранную hashFunc.
 * При коллизии (ячейка занята) производится переход с помощью Next_hash.
 * Для каждого неудачного запроса (когда ячейка уже занята) увеличивается счетчик коллизий.
 */
bool Object::insert(void* d) {
    bool inserted = false;
    if (N != size) {
        int keyVal = getKey(d);
        int initial = hashFunc(keyVal, size);
        int i = 0;
        int j = initial;
        while (i < size && !inserted) {
            if (data[j] == NULL || data[j] == DEL) {
                data[j] = d;
                N++;
                inserted = true;
            }
            else {
                // Если ячейка занята, фиксируем коллизию
                collisionCount++;
            }
            if (!inserted) {
                i++;
                j = Next_hash(initial, size, i);
            }
        }
    }
    return inserted;
}

/*
 * Метод searchInd – ищет индекс элемента с заданным ключом,
 * используя ту же последовательность проб, что и при вставке.
 */
int Object::searchInd(int key) {
    int indexFound = -1;
    if (N != 0) {
        int initial = hashFunc(key, size);
        int i = 0;
        int j = initial;
        while (i < size && data[j] != NULL) {
            if (data[j] != DEL && getKey(data[j]) == key) {
                indexFound = j;
                break;
            }
            i++;
            j = Next_hash(initial, size, i);
        }
    }
    return indexFound;
}

void* Object::search(int key) {
    int index = searchInd(key);
    return (index >= 0) ? data[index] : NULL;
}

void* Object::deleteByKey(int key) {
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
 * Метод scan – обход всей таблицы.
 * Для каждой ячейки выводится её индекс и состояние: пусто, удалено или содержимое (через переданную функцию).
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

/*
 * Структура AAA – пример пользовательского типа с полями:
 *   - key: целочисленный ключ;
 *   - mas: строка (массив char).
 */
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
 * Функция для извлечения ключа из объекта типа AAA.
 */
int keyFunction(void* d) {
    AAA* a = (AAA*)d;
    return a->key;
}

/*
 * Функция печати объекта типа AAA.
 */
void AAA_print(void* d) {
    cout << " ключ " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}

//---------------------------------------------------------------------
// Функция для замера времени поиска в хеш-таблице (из предыдущего примера).

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
// Функция тестирования: сравнение числа коллизий при вставке одинаковых ключей
// в две хеш-таблицы: одну с универсальным хешированием и другую с модульным.

void compareCollisions(int tableSize, int numElements, int keyValue) {
    // Создаем две таблицы одинакового размера, но с разными хеш-функциями.
    Object H_uni(tableSize, keyFunction, UniversalHashFunction);
    Object H_mod(tableSize, keyFunction, ModularHashFunction);

    // Для теста будем вставлять одинаковые элементы (одинаковые ключ и строка)
    for (int i = 0; i < numElements; i++) {
        AAA* a1 = new AAA(keyValue, (char*)"uni");
        AAA* a2 = new AAA(keyValue, (char*)"mod"); 
        H_uni.insert(a1);
        H_mod.insert(a2);
    }

    cout << "\nРезультаты теста:" << endl;
    cout << "Универсальное хеширование:" << endl;
    cout << "Вставлено элементов: " << H_uni.N << endl;
    cout << "Количество коллизий: " << H_uni.collisionCount << endl;

    cout << "\nМодульное хеширование:" << endl;
    cout << "Вставлено элементов: " << H_mod.N << endl;
    cout << "Количество коллизий: " << H_mod.collisionCount << endl;
}

//---------------------------------------------------------------------
// Главная функция с меню

int main() {
    setlocale(LC_ALL, "rus");
    int siz, choice, k;
    cout << "Введите размер хеш-таблицы: ";
    cin >> siz;

    // Создаем основную хеш-таблицу с универсальным хешированием (это значение по умолчанию в меню)
    Object H(siz, keyFunction, UniversalHashFunction);

    for (;;) {
        cout << "\nМеню:" << endl;
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента по ключу" << endl;
        cout << "4 - поиск элемента по ключу" << endl;
        cout << "5 - измерение времени поиска" << endl;
        cout << "6 - сравнение коллизий (одинаковые ключи)" << endl;
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
            char* str = new char[20];
            cout << "Введите ключ: ";
            cin >> k;
            a->key = k;
            cout << "Введите строку: ";
            cin >> str;
            a->mas = str;
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
            int numElements, keyTest;
            cout << "Введите количество элементов для тестирования: ";
            cin >> numElements;
            cout << "Введите ключ, который будет использоваться для всех элементов: ";
            cin >> keyTest;
            compareCollisions(siz, numElements, keyTest);
            break;
        }
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }

    return 0;
}
