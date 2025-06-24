#include <iostream>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int rows, cols;
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    vector<vector<int>> matrix(rows, vector<int>(cols));
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    int max_zeros = -1;
    int row_to_delete = -1;
    for (int i = 0; i < rows; i++) {
        int zero_count = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zero_count++;
            }
        }
        if (zero_count > max_zeros) {
            max_zeros = zero_count;
            row_to_delete = i;
        }
    }
    if (row_to_delete != -1) {
        for (int i = row_to_delete; i < rows - 1; i++) {
            matrix[i] = matrix[i + 1];
        }
        matrix.pop_back();
    }
    cout << "Матрица после удаления строки с наибольшим количеством нулей:" << endl;
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
