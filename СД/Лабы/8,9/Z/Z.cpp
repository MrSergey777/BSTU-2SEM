#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    // Запись двоичных данных в файл
    fstream one;
    one.open("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\4\\1.bin", ios::binary | ios::out);
    if (!one) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    int data[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(data);
    one.write((char*)&data, size);
    one.close();
    // Чтение двоичных данных из файла
    one.open("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\4\\1.bin", ios::binary | ios::in);
    if (!one) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    int readData[5];
    one.read((char*)&readData, size);
    one.close();
    // Вывод прочитанных данных
    for (int i = 0; i < 5; i++) {
        cout << readData[i] << " ";
    }
    //Запись и чтение текстового файла
    fstream two;
    string s = "123456";
    two.open("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\4\\2.txt", ios::out);
    if (!two.is_open()) {
        cout << "error";
        return 0;
    }
    two << s;
    two.close();
    two.open("C:\\Users\\ASUS\\Desktop\\ЛАБЫ\\ОАИП - 2.0\\4\\2.txt", ios::in);
    string ss = "";
    getline(two, ss);
    cout << ss;
    two.close();
}
