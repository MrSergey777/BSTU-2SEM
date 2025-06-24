#include <iostream>
using namespace std;

void permute(int arr[], int l, int r) {
    if (l == r) {
        for (int i = 0; i <= r; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else {
        for (int i = l; i <= r; i++) {
            swap(arr[l], arr[i]);        
            permute(arr, l + 1, r);         
            swap(arr[l], arr[i]);        
        }
    }
}
int main() {
    setlocale(LC_ALL, "ru");
    const int n = 5; 
    int arr[n];
    cout << "Введите 5 различных натуральных чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Все перестановки:" << endl;
    permute(arr, 0, n - 1);
    return 0;
}
