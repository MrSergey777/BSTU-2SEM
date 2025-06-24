#include <iostream>
#include <fstream>
#include <vector>
#include <string>
    using namespace std;

    int main() {
        setlocale(LC_ALL, "RU");
        string filename = "1.txt";
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Ошибка открытия файла " << filename << " для чтения." << endl;
            return 1;
        }
        vector<string> records;
        string line;
        while (getline(inFile, line)) {
            records.push_back(line);
        }
        inFile.close();
        string keyword = "Sergey";
        vector<string> remainingRecords;
        for (const auto& record : records) {
            if (record.find(keyword) != string::npos) {
                cout << "Удалена запись: " << record << endl;
            }
            else {

                remainingRecords.push_back(record);
            }
        }


        cout << "Осталось записей: " << remainingRecords.size() << endl;


        ofstream outFile(filename, ios::out | ios::trunc);
        if (!outFile) {
            cout << "Ошибка открытия файла " << filename << " для записи." << endl;
            return 1;
        }

        for (const auto& record : remainingRecords) {
            outFile << record << endl;
        }
        outFile.close();

        return 0;
    }

