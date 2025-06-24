#include <iostream>
#include <vector>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    vector<int> array1 = { 1, 2, 3, 4, 5 };
    vector<int> array2 = { 6, 7, 8, 9, 10 };
    vector<int> combinedArray;
    combinedArray.insert(combinedArray.end(), array1.begin(), array1.end());
    combinedArray.insert(combinedArray.end(), array2.begin(), array2.end());
    cout << "Объединенный массив:" << endl;
    for (int i = 0; i < combinedArray.size(); ++i) {
        cout << combinedArray[i] << " ";
    }
    cout << endl;
    return 0;
}
