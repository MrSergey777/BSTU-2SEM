// ДОП-1.cpp : 1. Ввести цифру А, записать в файл все возможные числа, состоящие из цифр, 
// не превышающих или равных A. Количество цифр в числах должно быть равно А.
#include <iostream>
#include <string>
#include <fstream>
#include <cmath> 
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите n: ";
    cin >> n;
    string s = "";
    for (int i = 0; i < n + 1; i++) {
        s += to_string(i);
    }
    fstream file("2.txt", ios::out);
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла!\n";
        return 0;
    }
    long long start = pow(10, n - 1);
    long long end = pow(10, n);
    for (long long a = start; a < end; a++) {
        string s1 = to_string(a);
        bool flag = true;
        for (int i = 0; i < s1.size(); i++) {
            if (s.find(s1[i]) == string::npos) {
                flag = false;
                break;
            }
        }
        if (flag)
            file << a << endl;
    }
    file.close();
    return 0;
}
