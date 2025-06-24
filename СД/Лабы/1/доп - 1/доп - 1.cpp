//База отзывов. После заказа еды клиент может 
// оставить отзыв на конкретное блюдо. Отзыв содержит 
// в себе текстовую часть и оценку по пятибалльной шкале. 
// Если рейтинг блюда составляет менее двух, при 
// дальнейших заказах клиентам приходит предупреждение о
// низком рейтинге выбранного ими блюда.
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
struct eat
{
	string name;
	string advice;
	int oc;
};
struct eat ot[100];
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int n = 0;
	int choice = 1;
	while (choice != 0) {
		cout << "1 - Заказ\n";
		cout << "0 - Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		if (choice == 1) {
			cout << "Какую еду вы хотели бы заказать ";
			cin >> ot[n].name;
			for (int i = 0; i < n ; i++) {
				if (ot[n].name == ot[i].name) {
					if (ot[i].oc < 2) cout << "У этого блюда была хотя бы 1 низкая оценка" << endl;
					break;
				}
			}
				cout << "Оставте отзыв: ";
				cin >> ot[n].advice;
				cout << "Поставте оценку этому блюду от 1 до 5 ";
				cin >> ot[n].oc;
			}
			n++;
		}
	}