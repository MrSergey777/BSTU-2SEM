#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
list<int> getUniqueElements(const list<int>& input) {
    list<int> uniqueElements;
    for (int num : input) {
        if (count(input.begin(), input.end(), num) == 1) {
            uniqueElements.push_back(num);
        }
    }
    return uniqueElements;
}
int main() {
    list<int> input = { 1, 2, 2, 3, 4, 4, 5 };
    list<int> result = getUniqueElements(input);

    cout << "Уникальные элементы: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
