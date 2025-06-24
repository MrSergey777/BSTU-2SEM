#include <iostream>
#include <list>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    list<int> arr = { 1, 2, 3, 4, 5 };
    cout << "Список в обратном порядке: ";
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) { 
        cout << *it << " ";
    }

    return 0;
}
