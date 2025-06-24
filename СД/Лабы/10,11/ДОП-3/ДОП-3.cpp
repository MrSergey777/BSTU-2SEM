#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main() {
  
    {
        ofstream outFile("words.txt");
        if (!outFile) {
            cerr << "Ошибка при создании файла words.txt" << endl;
            return 1;
        }
       
        outFile << "apple\nbanana\napricot\ngrape\norange\navocado";
     
    }

  
    fstream file("words.txt", ios::in | ios::out);
    if (!file) {
        cerr << "Ошибка открытия файла words.txt" << endl;
        return 1;
    }

    
    vector<string> words;
    string line;
    while (getline(file, line)) {
        words.push_back(line);
    }

    
    char target;
    cout << "Введите букву, с которой начинаются слова для удаления: ";
    cin >> target;

  
    vector<string> filtered;
    for (const auto& w : words) {
        if (!w.empty() && tolower(w[0]) == tolower(target)) {
            cout << "Удалено слово: " << w << endl;
        }
        else {
            filtered.push_back(w);
        }
    }

    cout << "Осталось слов: " << filtered.size() << endl;

   
    file.close(); 
    ofstream outFile("words.txt", ios::out | ios::trunc);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return 1;
    }
    for (const auto& w : filtered) {
        outFile << w << "\n";
    }
    outFile.close();

    return 0;
}
