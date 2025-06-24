//Написать программу, в которой нужно найти произведение всех элементов деки и вывести его на экран.
#include <deque>
#include <iostream>
using namespace std;
int rec(const deque<int>& arr, int n) {
    if (n == arr.size()) {
        return 1;
    }
    return arr[n] * rec(arr, n + 1);
}
int main() {
    setlocale(LC_ALL, "ru");
    deque<int> arr = { 100, 2, 3, 4, 5, 6, 100 };
    cout << "Произведение всех элементов деки: " << rec(arr, 0) << endl;
    return 0;
}
