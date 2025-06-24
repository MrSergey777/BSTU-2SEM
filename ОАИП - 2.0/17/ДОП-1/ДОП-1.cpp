#include <stdio.h>
#define SIZE 5  
using namespace std;
void countingSort(const int input[], int output[], int n) {
    int count[SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        count[i] = 0; 
        for (int j = 0; j < n; j++) {
            if (input[j] < input[i])
                count[i]++;
        }
    }
    for (int i = 0; i < n; i++) {
        output[count[i]] = input[i];
    }


}
int main() {
    int B[SIZE] = { 20, -5, 10, 8, 7 };
    int sortedB[SIZE];
    countingSort(B, sortedB, SIZE);
    printf("Sorted massiv:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sortedB[i]);
    }
    printf("\n");
    return 0;
}
