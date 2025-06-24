#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#define size 100000
using namespace std;

struct eat {
    string name;
    int price;
    string shortdess;
    string comprouds;
};

const string nameoffood[] = {
    "Макароны по-флотски",
    "Стейк",
    "Хлеб",
    "Котлеты",
    "Хачапури"
};

const string comproud[] = {
    "Рецепт 1",
    "Рецепт 2",
    "Рецепт 3",
    "Рецепт 4",
    "Рецепт 5"
};

const string shortdes[] = {
    "Не берите",
    "Вроде вкусно",
    "Ай, дружище, бери, не пожалеешь",
    "Ай, брат, просто пальцы будешь облизывать",
    "Ай-ай-ай"
};

struct eat menu[100];

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    int n = rand() % 100;
    for (int i = 0; i < n; i++) {
        menu[i].name = nameoffood[rand() % 5];
        menu[i].price = rand() % size;
        menu[i].shortdess = shortdes[rand() % 5];
        menu[i].comprouds = comproud[rand() % 5];
    }

    for (int i = 0; i < n; i++) {
        cout << menu[i].name << " ";
        cout << menu[i].price << " ";
        cout << menu[i].shortdess << " ";
        cout << menu[i].comprouds << endl;
    }

    return 0;
}
