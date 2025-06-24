#ifndef FUNC_H
#define FUNC_H

#include <string>
using namespace std;

struct person {
    string surname;
    string name;
    string phone;
    string address;
    int out_money;
    bool diskountt;
};

void window();
void choice1(struct person clients[100], int& n, int diskount);
void choice2(struct person clients[100], int n);

#endif
