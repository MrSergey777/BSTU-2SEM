#include <iostream>
#include <array>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите количество чисел n" << endl;
	cin >> n;
	array <int, 100> arr;
	int max = INT_MIN;
	int min = INT_MAX;
	cout << "Введите массив ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	cout << "Сумма максимального и минимального элемента равна "<< min + max;
}
