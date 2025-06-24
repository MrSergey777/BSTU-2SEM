#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
set<int> symmetricDifference(const set<int>& setA, const set<int>& setB) {
    set<int> result;
    for (int x : setA) {
        if (setB.count(x) == 0) {
            result.insert(x);
        }
    }
    for (int x : setB) {
        if (setA.count(x) == 0) {
            result.insert(x);
        }
    }

    return result;
}
set<int> symmetricDifferenceThree(const set<int>& set1, const set<int>& set2, const set<int>& set3) {
    set<int> temp = symmetricDifference(set1, set2);
    return symmetricDifference(temp, set3);
}
int main() {
    setlocale(LC_ALL, "ru");
    set<int> set1, set2, set3;
    int n1, n2, n3, num;
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
    cout << "Введите количество элементов третьего множества: ";
    cin >> n3;
    cout << "Введите элементы третьего множества: ";
    for (int i = 0; i < n3; i++) {
        cin >> num;
        set3.insert(num);
    }
    set<int> result = symmetricDifferenceThree(set1, set2, set3);
    cout << "Симметричная разность трёх множеств: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
