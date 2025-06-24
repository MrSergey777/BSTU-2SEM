#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int binarySearch(const vector<int>& data, int target) {
    int low = 0, high = data.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (data[mid] == target) {
            return mid;
        }
        else if (data[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}
int interpolationSearch(const vector<int>& data, int target) {
    int low = 0, high = data.size() - 1;

    while (low <= high && target >= data[low] && target <= data[high]) {
        if (low == high) {
            if (data[low] == target) return low;
            return -1;
        }
        int pos = low + ((target - data[low]) * (high - low) / (data[high] - data[low]));

        if (data[pos] == target) {
            return pos;
        }
        else if (data[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }

    return -1;
}

int main() {
    vector<int> database = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    sort(database.begin(), database.end()); 

    int target;
    cout << "Введите число для поиска: ";
    cin >> target;
    int binaryResult = binarySearch(database, target);
    if (binaryResult != -1) {
        cout << "Найдено с помощью бинарного поиска на индексе: " << binaryResult << endl;
    }
    else {
        cout << "Число не найдено с помощью бинарного поиска." << endl;
    }
    int interpolationResult = interpolationSearch(database, target);
    if (interpolationResult != -1) {
        cout << "Найдено с помощью интерполяционного поиска на индексе: " << interpolationResult << endl;
    }
    else {
        cout << "Число не найдено с помощью интерполяционного поиска." << endl;
    }

    return 0;
}
