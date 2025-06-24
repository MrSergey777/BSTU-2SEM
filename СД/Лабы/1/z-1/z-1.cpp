#include <iostream>
#include <time.h>
using namespace std;
struct book{
	double price;
};
struct book many[10];
int main()
{
	setlocale(LC_ALL, "Ru");
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		many[i].price = rand() % 100;
		cout << "Цена "<< i+1 << " книги перед инфляцией "<< many[i].price << endl;
		double a = (many[i].price / 100) * 10;
		many[i].price += a;
		cout << "Цена " << i+1 << " книги после инфляции "<< many[i].price << endl;
	}
}
A