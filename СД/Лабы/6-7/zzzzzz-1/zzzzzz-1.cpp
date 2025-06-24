#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct A {
    int id1;
    string FAM;
    string I;
};

struct B {
    int id2;
    int price;
    int cen;
};

struct ISX {
    int id1;
    int id2;
    int kol;
};

void readFromFileA(vector<A>& arr) {
    ifstream inFile("A.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла A.txt для чтения!" << endl;
        return;
    }
    arr.clear();
    A temp;
    while (inFile >> temp.id1 >> temp.FAM >> temp.I) {
        arr.push_back(temp);
    }
    inFile.close();
    cout << "Данные успешно прочитаны из файла A.txt" << endl;
}

void readFromFileB(vector<B>& arr) {
    ifstream inFile("B.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла B.txt для чтения!" << endl;
        return;
    }
    arr.clear();
    B temp;
    while (inFile >> temp.id2 >> temp.price >> temp.cen) {
        arr.push_back(temp);
    }
    inFile.close();
    cout << "Данные успешно прочитаны из файла B.txt" << endl;
}

int main()
{
    vector<A> Persons;
    vector<B> Price;
    vector<ISX> ITOG;


    setlocale(LC_ALL, "RU");


    readFromFileA(Persons);
    readFromFileB(Price);
    if (Persons.size() != Price.size()) {
        cout << "Ошибка: количество записей в файлах A.txt и B.txt не совпадает!" << endl;
        return 1;
    }
    for (int i = 0; i < Persons.size(); ++i) {
        ISX tmp;
        tmp.id1 = Persons[i].id1;
        tmp.id2 = Price[i].id2;
        if (Price[i].cen != 0)
            tmp.kol = Price[i].price / Price[i].cen;
        else {
            cout << "Ошибка: деление на ноль для записи с id2 = " << Price[i].id2 << endl;
            tmp.kol = 0;
        }
        ITOG.push_back(tmp);
    }
    ofstream outFile("ISX.txt");
    if (!outFile) {
        cout << "Ошибка открытия файла ISX.txt для записи!" << endl;
        return 1;
    }
    for (const auto& item : ITOG) {
        outFile << item.id1 << " " << item.id2 << " " << item.kol << "\n";
    }
    outFile.close();
    cout << "Данные успешно записаны в файл ISX.txt" << endl;

    int maxKolIndex = 0;
    for (int i = 1; i < ITOG.size(); ++i) {
        if (ITOG[i].kol > ITOG[maxKolIndex].kol) {
            maxKolIndex = i;
        }
    }
    int maxCenIndex = 0;
    for (int i = 1; i < Price.size(); ++i) {
        if (Price[i].cen > Price[maxCenIndex].cen) {
            maxCenIndex = i;
        }
        cout << "\nЧеловек с максимальным kol:" << endl;
        cout << "id1: " << Persons[maxKolIndex].id1
            << ", Фамилия: " << Persons[maxKolIndex].FAM
            << ", Имя: " << Persons[maxKolIndex].I
            << ", kol: " << ITOG[maxKolIndex].kol << endl;

        cout << "\nЧеловек с максимальным cen:" << endl;
        cout << "id1: " << Persons[maxCenIndex].id1
            << ", Фамилия: " << Persons[maxCenIndex].FAM
            << ", Имя: " << Persons[maxCenIndex].I
            << ", cen: " << Price[maxCenIndex].cen << endl;

        return 0;
    }
}
