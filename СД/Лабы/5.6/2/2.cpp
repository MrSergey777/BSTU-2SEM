//Написать программу, в которой в начало
// двусвязного списка добавляется n элементов и вывести на экран.
#include <iostream>
#include <list>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    list <int> arr = { 1,2,3,4,5};
    cout << "Введите число n";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        arr.push_front(rand() % 100);
    }
    cout << "Список: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " "; 
    }
    return 0;
}
