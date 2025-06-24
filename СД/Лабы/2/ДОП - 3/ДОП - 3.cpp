#include <iostream>
#include <array>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    array<int, 10> numbers;
    int sum = 0;
    cout << "Введите 10 целых чисел:" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> numbers[i];
        sum += numbers[i]; 
    }
    double average = sum / 10.0;
    cout << "Числа, которые больше среднего арифметического (" << average << "):" << endl;
    for (int i = 0; i < 10; ++i) {
        if (numbers[i] > average) {
            cout << numbers[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
