#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <list>
#include <queue>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    vector<int> arr = { 1, 2, 3, 4, 5 };
    array<double, 5> arr1 = { 1, 2, 3, 4, 5 };
    multiset<long> arr2 = { 1, 2, 3, 4, 5 };
    set<long long> arr3 = { 1, 2, 3, 4, 5 };
    list<float> arr4 = { 1, 2, 3, 4, 5 };
    queue<short> arr5;
    for (auto val : { 1, 2, 3, 4, 5 }) {
        arr5.push(val);
    }
    double sum = 0;
    for (int val : arr) {
        sum += val;
    }
    cout << "Среднее для vector: " << sum / arr.size() << endl;
    sum = 0;
    for (double val : arr1) {
        sum += val;
    }
    cout << "Среднее для array: " << sum / arr1.size() << endl;
    sum = 0;
    for (long val : arr2) {
        sum += val;
    }
    cout << "Среднее для multiset: " << sum / arr2.size() << endl;
    sum = 0;
    for (long long val : arr3) {
        sum += val;
    }
    cout << "Среднее для set: " << sum / arr3.size() << endl;
    sum = 0;
    for (float val : arr4) {
        sum += val;
    }
    cout << "Среднее для list: " << sum / arr4.size() << endl;
    sum = 0;
    int count = 0;
    while (!arr5.empty()) {
        sum += arr5.front();
        arr5.pop();
        count++;
    }
    cout << "Среднее для queue: " << sum / count << endl;
    return 0;
}
