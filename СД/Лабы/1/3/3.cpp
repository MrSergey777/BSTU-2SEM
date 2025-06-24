//Написать программу, в которой нужно создать 
// объединение для хранения двух типов данных 
// (например, целых чисел и логических значений) 
// и написать функцию для вывода этих значений на экран.
#include <iostream>
#include <time.h>
using namespace std;
union two {
	int number;
	bool b;
};
two many[100];
void out(two many[], int n) {
	for (int i = 0; i < n; i++) {
		cout << many[i].number<<" ";
		cout << many[i].b << endl;
	}
}
int main()
{
	srand(time(NULL));
	int n = rand() % 100;
	for (int i = 0; i < n; i++) {
		many[i].number = rand() % 1000;
		if (many[i].number % 2 != 0) many[i].b = true;
		else many[i].b = false;
	}
	out(many, n);
}
