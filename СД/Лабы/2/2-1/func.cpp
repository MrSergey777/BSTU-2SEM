#include <iostream>
#include "func.h"
using namespace std;

void window() {
    cout << "1 - ���� ��������� ��������� � ����������\n";
    cout << "2 - ����� ��������� ��������� � ���������� ����\n";
    cout << "0 - ����� �� ���������\n\n";
    cout << "������� ����� ��������: ";
}

void choice1(struct person clients[100], int& n, int diskount) {
    cout << "������� ������: �������, ���, ���������� �������, �����" << endl;
    cout << "������� ���� ������� ";
    cin >> clients[n].surname;
    cout << "������� ���� ��� ";
    cin >> clients[n].name;
    cout << "������� ��� ���������� ������� ";
    cin >> clients[n].phone;
    cout << "������� ��� ����� ";
    cin >> clients[n].address;
    clients[n].out_money = rand() % 1000;
    if (clients[n].out_money >= diskount) {
        clients[n].diskountt = true;
        cout << "����������� �� ��������� ������ � 10% " << endl;
    }
    n++;
}

void choice2(struct person clients[100], int n) {
    cout << "���� ������" << endl;
    for (int i = 0; i < n; i++) {
        cout << clients[i].surname << " ";
        cout << clients[i].name << " ";
        cout << clients[i].phone << " ";
        cout << clients[i].address << " ";
        if (clients[i].diskountt == true) {
            cout << "������� ������ � ������ ���������";
        }
        cout << endl;
    }
}
