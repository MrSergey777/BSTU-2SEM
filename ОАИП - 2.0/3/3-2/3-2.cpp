//2. Ввести с клавиатуры строку символов, состоящую из групп цифр и нулей, и 
// записать ее в файл. Прочитать из файла данные и вывести самую короткую группу. 
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
void read(string s) {
	fstream one("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\3\\one.txt");
	one.is_open();
	one << s;
	one.close();
}
string write(string s) {
	fstream one("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\3\\one.txt");
	one.is_open();
	one >> s;
	one.close();
	return s;
}
int main()
{
	setlocale(LC_ALL, "ru");
	string s;
	cout << "Введите строку состоящую из групп цифр и нулей" << endl;
	cin >> s;
	read(s);
	s = write(s);
	int checker = 0;
	int minchecker = INT_MAX;
	string minst = "";
	string st = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') {
			if (checker > 0 && checker < minchecker) {
				minchecker = checker;
				minst = st;
			}
			checker = 0;
			st = "";
		}
		else {
			st += s[i];
			checker++;
		}
	}
	if (checker > 0 && checker < minchecker) {
		minchecker = checker;
		minst = st;
	}
	cout << "Задача выполнена " << endl;
	cout << "Cамая короткая группа: " << minst << endl;
	return 0;
}