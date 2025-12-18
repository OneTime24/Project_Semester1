#include <stdio.h>
#include <stdlib.h>
int main() {
    printf("Momina Ahmad 25P-0503\n");
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    int *arr = (int*)malloc(rows * cols * sizeof(int));
    if(arr == NULL) return 1;
    printf("Enter elements row-wise:\n");
    int *p = arr;
    for(int i = 0; i < rows * cols; i++) {
        scanf("%d", p);
        p++;
    }
    printf("\nRow sums:\n");
    for(int i = 0; i < rows; i++) {
        int sum = 0;
        for(int j = 0; j < cols; j++) {
            sum += *(arr + i * cols + j);
        }
        printf("Row #%d Sum = %d\n", i + 1, sum);
    }
    printf("\nColumn sums:\n");
    for(int j = 0; j < cols; j++) {
        int sum = 0;
        for(int i = 0; i < rows; i++) {
            sum += *(arr + i * cols + j);
        }
        printf("Column #%d Sum = %d\n", j + 1, sum);
    }

    free(arr);
    return 0;
}
