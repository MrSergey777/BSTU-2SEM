//1.Объедините два массива целых чисел в один и выведите его элементы 
#include <iostream>
#include <array>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    array<int, 5> array1 = { 1, 2, 3, 4, 5 };
    array<int, 5> array2 = { 6, 7, 8, 9, 10 };
    array<int, 10> combinedArray;
    for (int i = 0; i < 5; ++i) {
        combinedArray[i] = array1[i];
        combinedArray[i + 5] = array2[i];
    }
    cout << "Объединенный массив:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << combinedArray[i] << " ";
    }
    cout << endl;
    return 0;
}
