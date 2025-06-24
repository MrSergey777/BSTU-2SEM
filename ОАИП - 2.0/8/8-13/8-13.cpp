#include <iostream>
#include <fstream>
#include <queue>
#include <cctype>
#include <string>
using namespace std;
void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream fin(inputFilename);
    ofstream fout(outputFilename);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть входной файл!" << endl;
        return;
    }
    if (!fout.is_open()) {
        cerr << "Не удалось открыть выходной файл!" << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        queue<char> nonDigits;
        queue<char> digits;
        for (char c : line) {
            if (isdigit(c)) {
                digits.push(c);
            }
            else {
                nonDigits.push(c);
            }
        }
        while (!nonDigits.empty()) {
            fout << nonDigits.front();
            nonDigits.pop();
        }
        while (!digits.empty()) {
            fout << digits.front();
            digits.pop();
        }

        fout << endl;
    }

    fin.close();
    fout.close();
}
int main() {
    setlocale(LC_ALL, "ru");
    string inputFile = "f.txt";
    string outputFile = "g.txt";
    processFile(inputFile, outputFile);
    cout << "Обработка файла завершена. Результат записан в " << outputFile << endl;
    return 0;
}