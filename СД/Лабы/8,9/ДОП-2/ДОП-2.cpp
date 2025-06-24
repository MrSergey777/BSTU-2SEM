
//Напишите программу, которая запрашивает у пользователя последовательность целых чисел и сохраняет
// их в контейнере deque.Затем программа должна отсортировать эту последовательность в порядке возрастания и вывести на экран первые 5 элементов.
#include <iostream>
#include <deque>
#include <algorithm> 
using namespace std;
int main() {
    setlocale(LC_ALL, "RU");
    deque<int> numbers;
    int num;
    cout << "Введите последовательность целых чисел. Для завершения введите 0:" << endl;
    while (true) {
        cout << "Введите число: ";
        cin >> num;
        if (num == 0) break; 
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());
    cout << "Первые 5 элементов после сортировки: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
