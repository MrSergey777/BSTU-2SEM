//Напишите программу, которая запрашивает у пользователя последовательность целых чисел и 
//сохраняет их в контейнере vector. Затем программа должна удалить все дубликаты из этой
//последовательности и вывести на экран новую последовательность.
#include <iostream>
#include <vector>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    int n, num;
    vector<int> numbers, unique_numbers;
    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Введите числа: ";
    for (int i = 0; i < n; ++i) {
        cin >> num;
        numbers.push_back(num);
    }
    for (int i = 0; i < numbers.size(); ++i) {
        bool is_duplicate = false;
        for (int j = 0; j < unique_numbers.size(); ++j) {
            if (numbers[i] == unique_numbers[j]) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            unique_numbers.push_back(numbers[i]);
        }
    }
    cout << "Последовательность без дубликатов: ";
    for (int i = 0; i < unique_numbers.size(); ++i) {
        cout << unique_numbers[i] << " ";
    }
    cout << endl;
    return 0;
}
