//Напишите программу, которая создает двоичный файл, записывает
// в него некоторые данные(например, числа) и затем читает эти данные из файла.(3 балла)
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    ofstream outFile("data.bin", ios::binary);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }

    int numbersToWrite[] = { 1, 2, 3, 4, 5 }; 
    for (int number : numbersToWrite) {
        outFile.write((char*)&number, sizeof(number));
    }
    outFile.close();
    ifstream inFile("data.bin", ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    int numbersToRead[5];
    for (int& number : numbersToRead) {
        inFile.read((char*)&number, sizeof(number));
    }
    inFile.close();
    cout << "Считанные числа из файла: ";
    for (int number : numbersToRead) {
        cout << number << " ";
    }
    cout << endl;

    return 0;
}
