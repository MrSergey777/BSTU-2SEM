#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct person
{
    string id;
    string f;
    string i;
};
struct person list_of_persons[100];
void insertionSort(person list_of_persons[], int n) {
    for (int i = 1; i < n; i++) {
        person key = list_of_persons[i];
        int j = i - 1;
        while (j >= 0 && list_of_persons[j].f > key.f) {
            list_of_persons[j + 1] = list_of_persons[j];
            j--;
        }
        list_of_persons[j + 1] = key;
    }
}
void saveToFile(person list_of_persons[], int n) {
    ofstream two("2.txt");
    if (!two.is_open()) {
        cout << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        two << list_of_persons[i].id << " "
            << list_of_persons[i].f << " "
            << list_of_persons[i].i << endl;
    }

    two.close();
}

int main()
{
    int n = 0;
    fstream one("1.txt", ios::in);
    if (!one.is_open()) {
        cout << "Ошибка при открытии файла!" << endl;
        return 1;
    }
    while (one >> list_of_persons[n].id) {
        one >> list_of_persons[n].f;
        one >> list_of_persons[n].i;
        n++;
    }
    for (int i = 0; i < n; i++) {
        cout << list_of_persons[i].id << " ";
        cout << list_of_persons[i].f << " ";
        cout << list_of_persons[i].i << endl;
    }
    insertionSort(list_of_persons, n);
    saveToFile(list_of_persons, n);
    return 0;
}
