#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}
int main() {
    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл data.txt" << endl;
        return 1;
    }
    vector<int> data;
    int value;
    while (inputFile >> value) {
        data.push_back(value);
    }
    inputFile.close();
    quickSort(data, 0, data.size() - 1);
    ofstream outputFile("sorted_data.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл sorted_data.txt" << endl;
        return 1;
    }

    for (const int& num : data) {
        outputFile << num << endl;
    }
    outputFile.close();

    cout << "Данные успешно отсортированы и сохранены в файле sorted_data.txt" << endl;
    return 0;
}
