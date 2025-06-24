#include <iostream>
#include <array>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int n, nn;
    cout << "Введите количество чисел n 1 массива" << endl;
    cin >> n;
    cout << "Введите количество чисел n 2 массива" << endl;
    cin >> nn;
    array<int, 100> arr;
    array<int, 100> arr2;
    cout << "Введите массив 1 ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int sum = 0;
    cout << "Введите массив 2 ";
    for (int i = 0; i < nn + n; i++) {
        if (i >= nn) {
            arr2[i] = arr[i - nn];
        }
        else {
            int p;
            cin >> p;
            arr2[i] = p;
        }
        sum += arr2[i];
    }
    cout << "Сумма всех членов объединённого массива равна " << sum << endl;
}
