#include <iostream>
#include <list>
using namespace std;
int main() {
    list<int> arr = { 1, 2, 3, 4, 5 };
    for (auto it = arr.begin(); it != arr.end(); ) {
        if (*it % 2 == 0) {
            it = arr.erase(it);
        }
        else {
            ++it;
        }
    }
    for (int x : arr) {
        cout << x << " ";
    }
    return 0;
}
