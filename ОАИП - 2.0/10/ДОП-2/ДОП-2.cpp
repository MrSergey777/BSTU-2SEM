#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
// Функция для подсчета смежных пар в разбиении
int countPairs(const vector<vector<int>>& adjMatrix, const vector<bool>& group) {
    int pairs = 0;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == 1 && group[i] != group[j]) {
                ++pairs;
            }
        }
    }
    return pairs;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Пример ввода
    vector<vector<int>> adjMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    int n = adjMatrix.size();
    int minPairs = INT_MAX;
    // Лучшая конфигурация
    vector<bool> bestGroup(n);
    // Перебор всех возможных разбиений
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<bool> group(n);
        for (int i = 0; i < n; ++i) {
            group[i] = (mask & (1 << i)) != 0;
        }
        int pairs = countPairs(adjMatrix, group);
        if (pairs < minPairs) {
            minPairs = pairs;
            bestGroup = group;
        }
    }
    cout << "Минимальное количество пар: " << minPairs << endl;
    cout << "Группа 1: ";
    for (int i = 0; i < n; ++i) {
        if (bestGroup[i]) cout << i << " ";
    }
    cout << endl;
    cout << "Группа 2: ";
    for (int i = 0; i < n; ++i) {
        if (!bestGroup[i]) cout << i << " ";
    }
    cout << endl;
    return 0;
}
