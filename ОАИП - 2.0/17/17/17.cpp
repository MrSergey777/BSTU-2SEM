#include <iostream>
#include <time.h>
using namespace std;
void quicksort(int arr[], int left, int right) {
	if (left > right) return;
	int mid = arr[(left + right) / 2];
	int i = left;
	int j = right;
	while (i <= j) {
		while (arr[i] > mid) i++;
		while (arr[j] < mid) j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	quicksort(arr, left, j );
	quicksort(arr, i, right);
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid;    
    int *L, *R;
    L = new int[n1];
    R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	int n;
	cout << "Введите количество элементов массива : ";
	cin >> n;
	int* arr;
	arr = new int[n];
	cout << "Элементы массива : ";
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 1000 + 1;
		cout << arr[i] << " ";
	}
	int barr[2000];
	int n1 = 0;
	cout << endl << "Элементы получившегося массива : ";
	for (int i = 0; i < n; i++) {
		if (((i + 1) % 2 == 0) && ((i + 1) < n) && (arr[i + 1] % 2 != 0)) {
			barr[n1] = arr[i];
			cout << barr[n1] << " ";
			n1++;
		}
	}
	n = n1;
    quicksort(barr, 0, n - 1);
	cout << endl << "Элементы получившегося массива : ";
	for (int i = 0; i < n; i++) {
		cout << " " << barr[i] << " ";
	}
}