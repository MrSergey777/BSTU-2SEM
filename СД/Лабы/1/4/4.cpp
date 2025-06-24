#include <iostream>
#include <bitset>
using namespace std;

union inf {
    int ii;
    char bArray[sizeof(int)];
};
int main() {
    setlocale(LC_ALL, "ru");
    inf m;
    m.ii = 5;
    cout << "Представление в виде целого числа: " << m.ii << endl;
    cout << "Представление в виде двоичного кода: ";
    for (int i = 0; i < sizeof(m.bArray); ++i) {
        cout << bitset<8>(m.bArray[i]) << " ";
    }
    cout << endl;
    return 0;
}
