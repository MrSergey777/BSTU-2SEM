//Список клиентов гостиницы. Паспортные данные,  даты приезда и отъезда, номер, тип размещения 
//(люкс, одноместный, двухместный, трехместный, апартаменты).
//Поиск гостя по фамилии. 
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
struct client
{
	string surname;
	string pasd;
	string date_join;
	string date_out;
	string type_off_lat;
};
struct client List_of_hotel_clients[100];
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int n = 0;
	int choice = 1;
	while (choice != 0) {
		cout << "1 - ввод элементов структуры с клавиатуры\n";
		cout << "2 - вывод элементов структуры в консольное окно\n";
		cout << "3 - удаление заданной структурированной переменной\n";
		cout << "4 - Поиск по Фамилии\n";
		cout << "5 - запись информации в файл\n";
		cout << "6 - чтение данных из файла.\n";
		cout << "0 - Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		if (choice == 1) {
			cout << "Введите данные: Фамилию, Паспортные данные,  даты приезда и отъезда,тип размещения (люкс, одноместный, двухместный, трехместный, апартаменты) ";
			cin >> List_of_hotel_clients[n].surname;
			cin >> List_of_hotel_clients[n].pasd;
			cin >> List_of_hotel_clients[n].date_join;
			cin >> List_of_hotel_clients[n].date_out;
			cin >> List_of_hotel_clients[n].type_off_lat;
			n++;
		}
		if (choice == 2) {
			cout << "Cписок проживающих : " << endl;
			for (int i = 0; i < n; i++) {
				if (List_of_hotel_clients[i].surname == "") continue;
				cout << List_of_hotel_clients[i].surname << " ";
				cout << List_of_hotel_clients[i].pasd << " ";
				cout << List_of_hotel_clients[i].date_join << " ";
				cout << List_of_hotel_clients[i].date_out << " ";
				cout << List_of_hotel_clients[i].type_off_lat << " " << endl;
			}
		}
		if (choice == 3) {
			cout << "Введите порядковы номер человека, которого хотите удалить ";
			int nn;
			cin >> nn;
			List_of_hotel_clients[nn].surname = "";
			List_of_hotel_clients[nn].pasd = "";
			List_of_hotel_clients[nn].date_join = "";
			List_of_hotel_clients[nn].date_out = "";
			List_of_hotel_clients[nn].type_off_lat = "";
		}
		if (choice == 4) {
			for (int i = 0; i < n; i++) {
				string ss;
				cout << "Введите фамилию для поиска данных :";
				cin >> ss;
				for (int i = 0; i < n; i++) {
					if (List_of_hotel_clients[i].surname == ss) {
						cout << List_of_hotel_clients[i].surname << " ";
						cout << List_of_hotel_clients[i].pasd << " ";
						cout << List_of_hotel_clients[i].date_join << " ";
						cout << List_of_hotel_clients[i].date_out << " ";
						cout << List_of_hotel_clients[i].type_off_lat << " " << endl;
					}
				}
			}
		}
			if (choice == 5) {
				fstream one("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\СД\\Лабы\\4\\1.txt");
				if (!one.is_open()) {
					cout << "Ошибка при открытии файла!";
					return 1;
				}
				for (int i = 0; i < n; i++) {
					string sss;
					sss += List_of_hotel_clients[i].surname + " ";
					sss += List_of_hotel_clients[i].pasd + " ";
					sss += List_of_hotel_clients[i].date_join + " ";
					sss += List_of_hotel_clients[i].date_out + " ";
					sss += List_of_hotel_clients[i].type_off_lat + " ";
					one << sss << endl;
				}
				one.close();
				cout << "Выполнено "<< endl;
			}
			if (choice == 6) {
				int kol = 1;
				fstream one("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\СД\\Лабы\\4\\1.txt");
				if (!one.is_open()) {
					cout << "Ошибка при открытии файла!";
					return 1;
				}
				string sss = "1";
				while (sss != "") {
					getline(one,sss);
					string ssss = "";
					for (int i = 0; i < sss.size(); i++) {
						if (ssss[i] == ' ') {
							if (kol == 1) {
								List_of_hotel_clients[n].surname = ssss;
							}
							if (kol == 2) {
								List_of_hotel_clients[n].pasd = ssss;
							}
							if (kol == 3) {
								List_of_hotel_clients[n].date_join = ssss;
							}
							if (kol == 4) {
								List_of_hotel_clients[n].date_out = ssss;
							}
							if (kol == 5) {
								List_of_hotel_clients[n].type_off_lat = ssss;
							}
							ssss = "";
							kol++;
							n++;
						}
						else {
							ssss += sss[i];
						}
					}
				}
				one.close();
				cout << "Данные прочитаны из файла"<<endl;
			}
		}
}