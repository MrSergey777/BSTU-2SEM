#include <iostream>
#include <cstdarg>
using namespace std;
/*
Примеры, включенные в данный файл:
1. Передача данных в функцию по значению
2. Передача данных в функцию по ссылке
3. Передача данных в функцию по указателю
4. Использование глобальной переменной
5. Возврат нескольких значений из функции (использование структуры)
6. Возврат адреса переменной
7. Inline функции
8. Перегрузка функций
9. Функции с переменным числом параметров
10. Аргументы функции main()
11. Области видимости переменных для функций (локальные и глобальные переменные)
12. Операция уточнения области действия (::)
13. Указатель на функцию
14. Массив указателей на функции
15. Шаблоны функций
16. Аргументы по умолчанию
17. Организация рекурсии
18. Макросы
*/
// 1. Передача данных в функцию по значению
void incrementByValue(int a) {
    a++;
    cout << "Inside incrementByValue: " << a << endl;
}

// 2. Передача данных в функцию по ссылке
void incrementByReference(int& a) {
    a++;
    cout << "Inside incrementByReference: " << a << endl;
}

// 3. Передача данных в функцию по указателю
void incrementByPointer(int* a) {
    (*a)++;
    cout << "Inside incrementByPointer: " << *a << endl;
}

// 4. Использование глобальной переменной
int globalVariable = 10;

void incrementGlobal() {
    globalVariable++;
    cout << "Inside incrementGlobal: " << globalVariable << endl;
}

// 5. Возврат нескольких значений из функции (использование структуры)
struct Result {
    int a;
    int b;
};

Result getValues() {
    Result res;
    res.a = 1;
    res.b = 2;
    return res;
}

// 6. Возврат адреса переменной
int* getPointer() {
    int* ptr = new int(5);
    return ptr;
}

// 7. Inline функции
inline int addInline(int a, int b) {
    return a + b;
}

// 8. Перегрузка функций
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

// 9. Функции с переменным числом параметров
int sum(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    va_end(args);
    return total;
}
// 10. Аргументы функции main()
// Второй main() закомментирован, чтобы избежать конфликта
/*int main(int argc, char *argv[]) {
    cout << "Number of arguments: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "Argument " << i << ": " << argv[i] << endl;
    }
    return 0;
}*/
// 11. Области видимости переменных для функций (локальные и глобальные переменные)
void display() {
    int localVar = 20;
    cout << "Global variable: " << globalVariable << endl;
    cout << "Local variable: " << localVar << endl;
}

// 12. Операция уточнения области действия (::)
int var = 10;

void demoScopeResolution() {
    int var = 20;
    cout << "Local variable: " << var << endl;
    cout << "Global variable: " << ::var << endl;
}

// 13. Указатель на функцию
void hello() {
    cout << "Hello, World!" << endl;
}

void execute(void (*func)()) {
    func();
}

// 14. Массив указателей на функции
void func1() {
    cout << "Function 1" << endl;
}

void func2() {
    cout << "Function 2" << endl;
}

void executeAll(void (*funcArray[])(), int size) {
    for (int i = 0; i < size; i++) {
        funcArray[i]();
    }
}

// 15. Шаблоны функций
template<typename T>
T addTemplate(T a, T b) {
    return a + b;
}

// 16. Аргументы по умолчанию
void displayMessage(string message = "Hello, World!") {
    cout << message << endl;
}

// 17. Организация рекурсии
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void funcB();
void funcA() {
    cout << "Function A" << endl;
    funcB();
}
void funcB() {
    cout << "Function B" << endl;
    funcA();
}

// 18. Макросы
#define PI 3.14159
#define AREA(radius) (PI * (radius) * (radius))

int main(int argc, char* argv[]) {
    // Демонстрация передачи данных в функцию по значению
    int x = 10;
    incrementByValue(x);
    cout << "Outside incrementByValue: " << x << endl;

    // Демонстрация передачи данных в функцию по ссылке
    incrementByReference(x);
    cout << "Outside incrementByReference: " << x << endl;

    // Демонстрация передачи данных в функцию по указателю
    incrementByPointer(&x);
    cout << "Outside incrementByPointer: " << x << endl;

    // Демонстрация использования глобальной переменной
    incrementGlobal();
    cout << "Outside incrementGlobal: " << globalVariable << endl;

    // Демонстрация возврата нескольких значений из функции
    Result values = getValues();
    cout << "Values: a = " << values.a << ", b = " << values.b << endl;

    // Демонстрация возврата адреса переменной
    int* p = getPointer();
    cout << "Pointer value: " << *p << endl;
    delete p;

    // Демонстрация inline функции
    cout << "Inline add: " << addInline(3, 4) << endl;

    // Демонстрация перегрузки функций
    cout << "Int add: " << add(3, 4) << endl;
    cout << "Double add: " << add(3.5, 4.5) << endl;

    // Демонстрация функции с переменным числом параметров
    cout << "Sum of 3, 4, 5: " << sum(3, 3, 4, 5) << endl;
    // Демонстрация локальных и глобальных переменных
    display();

    // Демонстрация операции уточнения области действия
    demoScopeResolution();

    // Демонстрация указателя на функцию
    execute(hello);

    // Демонстрация массива указателей на функции
    void (*funcArray[])() = { func1, func2 };
    executeAll(funcArray, 2);

    // Демонстрация шаблонов функций
    cout << "Template add int: " << addTemplate(3, 4) << endl;
    cout << "Template add double: " << addTemplate(3.5, 4.5) << endl;

    // Демонстрация аргументов по умолчанию
    displayMessage();
    displayMessage("Custom message");

    // Демонстрация организации рекурсии
    cout << "Factorial of 5: " << factorial(5) << endl;
    // Демонстрация макросов
    cout << "Area of circle with radius 5: " << AREA(5) << endl;
    return 0;
}
