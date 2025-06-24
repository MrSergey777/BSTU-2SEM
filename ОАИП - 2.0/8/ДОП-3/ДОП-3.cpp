#include <iostream>
#include <queue>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    queue<double> numbers;
    double num;
    cout << "Введите вещественные числа (для завершения введите 'q'):\n";

    while (cin >> num) {
        numbers.push(num);
    }
    cin.clear();
    cin.ignore(1000, '\n');

    if (numbers.empty()) {
        cout << "Очередь пуста!\n";
        return 0;
    }
    double maxVal = numbers.front(); 
    size_t queueSize = numbers.size();

    for (size_t i = 0; i < queueSize; ++i) {
        double current = numbers.front();
        if (current > maxVal) {
            maxVal = current;
        }
        numbers.pop();
        numbers.push(current);
    }
    while (numbers.front() != maxVal) {
        double temp = numbers.front();
        numbers.pop();
        numbers.push(temp);
    }
    cout << "Очередь после циклического сдвига:\n";
    queueSize = numbers.size();
    for (size_t i = 0; i < queueSize; ++i) {
        cout << numbers.front() << " ";
        numbers.pop();
    }
    cout << endl;

    return 0;
}