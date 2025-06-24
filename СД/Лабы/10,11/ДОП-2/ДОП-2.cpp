#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
   
    ofstream out("numbers.txt");
    if (!out) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    out << "5 10 15 20 25";
    out.close();

    
    vector<int> numbers;
    ifstream in("numbers.txt");
    if (!in) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    int num;
    while (in >> num) {
        numbers.push_back(num);
    }
    in.close();

    
    for (int& n : numbers) {
        n += 10;
    }

    
    out.open("numbers.txt");
    if (!out) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    for (int n : numbers) {
        out << n << " ";
    }
    out.close();

    
    ifstream inFile("numbers.txt");
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    cout << "Обновленный файл numbers.txt:" << endl;
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    return 0;
}
