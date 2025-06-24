#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include "func.h"
using namespace std;

struct person clients[100];

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    const int diskount = 200;
    int n = 0;
    int choice = 1;
    cout << "\033[31m\n";
    while (choice != 0) {
        window();
        cin >> choice;
        if (choice == 1) {
            choice1(clients, n, diskount);
        }
        if (choice == 2) {
            choice2(clients, n);
        }
    }
}
