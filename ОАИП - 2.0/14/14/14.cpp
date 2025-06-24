#include <iostream>
#include <cstdlib>
#include <clocale>
#include <chrono>   // Для замера времени

using namespace std;

// Специальный маркер удалённого элемента (DEL). Для отмечания ячеек после удаления
#define HASHDEL (void*)-1
static void* DEL = (void*)HASHDEL;

/*
 * Универсальное хеширование.
 * Универсальное хеширование — это метод выбора хеш-функции из семейства функций таким образом,
 * чтобы для любых двух различных ключей вероятность коллизии была не больше 1/M, где M — размер таблицы.
 * Это гарантирует равномерное распределение ключей в таблице даже при неблагоприятном распределении входных данных.
 *
 * Здесь используется формула:
 *      h(key) = ((a * key + b) mod p) mod size,
 * где p — простое число, a и b — константы (1 ≤ a < p и 0 ≤ b < p).
 */
int UniversalHashFunction(int key, int size) {
    const int p = 101;   
    const int a = 3;    
    const int b = 7;     
    return ((a * key + b) % p) % size;
}
int Next_hash(int initial, int size, int i) {
    return (initial + 5 * i + 3 * i * i) % size;
}

/*
 * Структура Object реализует хеш-таблицу с открытой адресацией.
 * Поля:
 *    - data: массив указателей (void**) для хранения элементов.
 *    - size: размер таблицы — количество ячеек.
 *    - N: текущее число занятых ячеек.
 *    - getKey: указатель на функцию, которая извлекает целочисленный ключ из элемента.
 */
struct Object {
    void** data;             
    int size;               
    int N;                    
    int (*getKey)(void*);    
    Object(int size, int (*getkey)(void*));

    bool insert(void*);
    int searchInd(int key);
    void* search(int key);
    void* deleteByKey(int key);
    bool deleteByValue(void*);
    void scan(void(*)(void*));
};

Object::Object(int size, int (*getkey)(void*)) {
    N = 0;
    this->size = size;
    this->getKey = getkey;
    data = new void* [size];
    for (int i = 0; i < size; ++i)
        data[i] = NULL;
}

/*
 * Метод insert – вставляет элемент d в таблицу.
 * Начальный индекс вычисляется с помощью универсальной хеш-функции.
 * При коллизии применяется последовательность проб с помощью Next_hash.
 */
bool Object::insert(void* d) {
    bool inserted = false;
    if (N != size) {
        int keyVal = getKey(d);
        int initial = UniversalHashFunction(keyVal, size);
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
 * Метод searchInd – ищет индекс элемента с заданным ключом.
 * Используется та же последовательность проб: начальный индекс от универсальной хеш-функции,
 * затем вызовы Next_hash.
 */
int Object::searchInd(int key) {
    int indexFound = -1;
    if (N != 0) {
        int initial = UniversalHashFunction(key, size);
        for (int i = 0, j = initial; i != size && data[j] != NULL; j = Next_hash(initial, size, ++i)) {
            if (data[j] != DEL && getKey(data[j]) == key) {
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
void* Object::search(int key) {
    int index = searchInd(key);
    return (index >= 0) ? data[index] : NULL;
}

/*
 * Метод deleteByKey – удаляет элемент по ключу.
 * Если элемент находит, ячейка получает маркер DEL и количество элементов уменьшается.
 */
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
 * Пользовательский тип данных AAA – простой класс с целочисленным ключом и строкой.
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

/*
 * Функция measureSearchTime измеряет время поиска элемента с заданным ключом в хеш-таблице.
 * Используется high_resolution_clock из библиотеки <chrono>.
 */
void measureSearchTime(Object& H, int key) {
    // Зафиксировать начало замера времени
    auto start = chrono::high_resolution_clock::now();
    void* result = H.search(key);
    // Зафиксировать окончание замера времени
    auto end = chrono::high_resolution_clock::now();
    // Вычислить длительность в наносекундах
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
 *   5. Замера и демонстрации времени поиска.
 */
int main() {
    setlocale(LC_ALL, "rus");
    int siz, choice, k;
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
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }

    return 0;
}
