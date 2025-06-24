#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string name = "Galya";
    ifstream file("1.txt"); 
    if (!file) {
        cout << "Ошибка: файл не открыт!" << endl;
        return 1;
    }
    string line; 
    while (getline(file, line)) { 
        if (line.find(name) != string::npos) { 
            cout << line << endl;
        }
    }
    file.close();
    return 0;
}
