//Написать программу, в которой нужно найти минимальный элемент
// деки и добавить его в начало, с выводом на экран .
#include <deque>
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Ru");
    deque <double> arr = {100, 1, 0.5, 7, 8, 8.5};
    double min = DBL_MAX;
    for (int i = 0; i < arr.size(); i++) {
        if (min > arr[i]) min = arr[i];
    }
    arr.push_front(min);
    cout << "Результат программы: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}
