#include <iostream>
#include <set>
using namespace std;
int main() {
    using namespace std;
    set<int> set1;
    set<int> set2;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    cout << "Общие элементы: ";
    for (int num : set1) {
        if (set2.count(num) > 0) {
            cout << num << " ";
        }
    }
    return 0;
}
