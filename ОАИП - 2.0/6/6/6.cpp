//Создать список, содержащий элементы вещественного 
//типа. Найти среднее значение положительных элементов.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct list
{
	double a;
	list* next;

};
void menu()
{
	cout << " 1 - Ввод числа" << endl;
	cout << " 2 - Удаление числа" << endl;
	cout << " 3 - поиск элемента" << endl;
	cout << " 4 - Вывод списка" << endl;
	cout << " 5 - запись списка в файл" << endl;
	cout << " 6 - считывание списка из файла" << endl;
	cout << " 7 - Вычисление среднего арифметического" << endl;
	cout << " 8 - Выход" << endl;
	cout << "Сделайте выбор: ";
}
void in(list*& p, double value) {
	list* newP = new list;
	if (newP != NULL)  
	{
		newP->a = value;
		newP->next = p;
		p = newP;
	}
	else
		cout << "Операция добавления не выполнена" << endl;

}
void out(list* p) {
	if (p == NULL)
		cout << "Список пуст" << endl;
	else
	{
		cout << "Список:" << endl;
		while (p != NULL)
		{
			cout << "-->" << p->a;
			p = p->next;
		}
		cout << "-->NULL" << endl;
	}

}
void search_element(list* p) {
	cout << "Введите номер элемента для поиска: ";
	int n;
	cin >> n;
	int index = 0;
	while (p != NULL) {
		if (index == n) {
			cout << "Элемент найден: " << p->a << endl;
			return;
		}
		p = p->next;
		index++;
	}
	cout << "Элемент с указанным номером не найден." << endl;
}double delet(list*& p, double value) {
		list* previous, * current, * temp;
		if (value == p->a)
		{
			temp = p;
			p = p->next;    
			delete temp;
			return value;
		}
		else
		{
			previous = p;
			current = p->next;
			while (current != NULL && current->a != value)
			{
				previous = current;
				current = current->next;
			}
			if (current != NULL)
			{
				temp = current;
				previous->next = current->next;
				delete(temp);
				return value;
			}
		}
	}
void write(list* p) {
	ofstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\6\\pls.txt");
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла для записи" << endl;
		return;
	}
	while (p != nullptr) {
		file << p->a << endl;
		p = p->next;
	}
	file.close();
	cout << "Список успешно записан в файл" << endl;
}
void read(list*& p) {
	ifstream file("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\6\\pls.txt");
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла для чтения" << endl;
		return;
	}
	double value;
	while (file >> value) { 
		in(p, value);
	}
	file.close();
	cout << "Список успешно считан из файла" << endl;
}
double sr(list* p) {
	double sum = 0;  
	int count = 0;   
	while (p != nullptr) {
		if (p->a > 0) {
			sum += p->a;
			count++;
		}
		p = p->next;  
	}
	if (count == 0) {
		cout << "Положительных элементов нет." << endl;
		return 0;
	}
	return sum / count;
}
int main()
{
	setlocale(LC_ALL, "ru");
	list* plist = nullptr; 
	list* p;               
	int number;         
	int choice = 0;
	menu();
	cin >> choice;
	while (choice != 8) {
		if (choice == 1) {
			cout << "Введите число ";
			double q;
			cin >> q;
			in(plist, q);
		}
		else if (choice == 4) {
			out(plist);
		}
		else if (choice == 3) {
			search_element(plist);
		}
		else if (choice == 2) {
			cout << "Введите число которое хотите удалить";
			double qq;
			cin >> qq;
			delet(plist, qq);
		}
		else if (choice == 5) {
			write(plist);
		}
		else if (choice == 6) {
			read(plist);
		}
		else if (choice == 7) {
			cout << "Среднее значение положительных элементов: " << sr(plist) << endl;
		}
		menu();
		cin >> choice;
	}
}
