#include <iostream>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    cout << "Введите длину провода: ";
    int l;
    cin >> l;
    cout << "Количество направо: ";
    int n;
    cin >> n;
    vector<int> r(n);
    if (n > 0) {
        cout << "Позиции направо: ";
        for (int i = 0; i < n; ++i) {
            cin >> r[i];
        }
    }
    cout << "Количество налево: ";
    int m;
    cin >> m;
    vector<int> ll(m);
    if (m > 0) {
        cout << "Позиции налево: ";
        for (int i = 0; i < m; ++i) {
            cin >> ll[i];
        }
    }
    cout << "Считаем направо..." << endl;
    vector<int> res1(n);
    for (int i = 0; i < n; ++i) {
        res1[i] = l - r[i];
        cout << "Позиция " << r[i] << ", взлет через " << res1[i] << " мин." << endl;
    }

    cout << "Считаем налево..." << endl;
    vector<int> res2(m);
    for (int i = 0; i < m; ++i) {
        res2[i] = ll[i];
        cout << "Позиция " << ll[i] << ", взлет через " << res2[i] << " мин." << endl;
    }

    cout << "Направо: ";
    for (int t : res1) {
        cout << t << " ";
    }
    cout << endl;

    cout << "Налево: ";
    for (int t : res2) {
        cout << t << " ";
    }
    cout << endl;

    return 0;
}
