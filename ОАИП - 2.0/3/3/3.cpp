//1.Скопировать в файл FILE2 только те строки из FILE1, которые 
//начинаются с буквы «А». 
//Подсчитать количество слов в FILE2.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int words = 0;
    string s = "1";
    fstream first("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\3\\first.txt");
    fstream second("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\3\\second.txt");
    if (!first.is_open() || !second.is_open()) {
        cout << "Переделывай ";
        return 1;
    }
    while (s != "") {
        getline(first, s);
        if (s[0] == 'A' || s[0] == 'А') {
            second << s << endl;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == ' ') words++;
            }
            words++;
        }
    }
    first.close();
    second.close();
    cout << "Задача выполнена " << endl;
    cout << "Количество записанных слов: " << words;
    return 0;
}

