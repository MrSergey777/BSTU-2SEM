#include <iostream>
#include <cmath>
using namespace std;
int numsq(int a, int b) {
	if (b == 0 || b < 0) return 0;
	else {
		return floor(a / b) + numsq(b, a % b);
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	cout << "";
	int a, b;
	cin >> a >> b;
	cout << numsq(a, b);
}
