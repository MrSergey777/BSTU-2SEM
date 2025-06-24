#include <iostream>
#include <cmath> 
using namespace std;
double nthRoot(double a, int n) {
    double low = 0, high = a, mid; 
    double epsilon = 1e-7; 
    while (high - low > epsilon) {
        mid = (low + high) / 2;
        if (pow(mid, n) < a) {
            low = mid;
        }
        else {
            high = mid; 
        }
    }
    return mid; 
}
int main() {
    setlocale(LC_ALL, "ru");
    double a;
    int n;
    cout << "Введите число a и степень n через пробел: ";
    cin >> a >> n;
    double result = nthRoot(a, n);
    cout.precision(7);
    cout << "Корень " << n << "-й степени из " << a << ": " << result << endl;
    return 0; 
}
