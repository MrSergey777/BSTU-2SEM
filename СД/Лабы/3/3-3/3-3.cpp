#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    vector<int> arr;
    vector<int> arr1;
    vector<int> arr2;
    int n, n1;
    cout << "Введите количество элементов первого массива: ";
    cin >> n;
    cout << "Введите количество элементов второго массива: ";
    cin >> n1;
    cout << "Введите первый массив: ";
    for (int i = 0; i < n; i++) {
        int q;
        cin >> q;
        arr.push_back(q);
    }

    cout << "Введите второй массив: ";
    for (int i = 0; i < n1; i++) {
        int q;
        cin >> q;
        arr1.push_back(q);
    }
    for (int i = 0; i < n; i++) {
        arr2.push_back(arr[i]);
    }
    for (int i = 0; i < n1; i++) {
        bool flag = false;
        for (int j = 0; j < n; j++) {
            if (arr1[i] == arr[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            arr2.push_back(arr1[i]);
        }
    }
    cout << "Неповторяющиеся элементы: ";
    for (int i = 0; i < arr2.size(); i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    return 0;
}
