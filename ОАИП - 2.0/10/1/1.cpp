#include <iostream>
#include <cmath>
using namespace std;
int func(int m, int n) {
    if (abs(n - m) <= 1) return n;
    if ((m + n) % 2 == 0)
        return max(m, n);
    else {
        return func((n + m + 1) / 2, n + 1) + func(m, (n + m + 1) / 2);
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Введите m и n через пробел ";
    int m, n;
    cin >> m >> n;
    cout << func(m, n);
}
