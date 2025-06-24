#include <iostream>
#include <set>
using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    set<int> set1; 
    set<int> set2; 
    int n1, n2, num;
    cout << "Введите количество элементов первого множества: ";
    cin >> n1;
    cout << "Введите элементы первого множества: ";
    for (int i = 0; i < n1; i++) {
        cin >> num;
        set1.insert(num);
    }
    cout << "Введите количество элементов второго множества: ";
    cin >> n2;
    cout << "Введите элементы второго множества: ";
    for (int i = 0; i < n2; i++) {
        cin >> num;
        set2.insert(num);
    }
    cout << "Общие элементы: ";
    for (int x : set1) {
        if (set2.count(x) > 0) { 
            cout << x << " ";
        }
    }
    cout << endl;
    return 0;
}
