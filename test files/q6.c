#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Momina Ahmad 25P-0503\n");

    int n;
    printf("Enter initial array size: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    if(arr == NULL) return 1;

    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", arr + i);

    printf("\nArray before resizing: ");
    for(int i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");

    int newSize;
    printf("\nEnter new resized array size: ");
    scanf("%d", &newSize);

    arr = (int*)realloc(arr, newSize * sizeof(int));
    if(arr == NULL) return 1;

    if(newSize > n) {
        printf("Enter %d more elements:\n", newSize - n);
        for(int i = n; i < newSize; i++)
            scanf("%d", arr + i);
    }

    printf("\nArray after resizing: ");
    for(int i = 0; i < newSize; i++)
        printf("%d ", *(arr + i));
    printf("\n");

    for(int i = 0; i < newSize; i++) {
        for(int j = i + 1; j < newSize; j++) {
            if(*(arr + j) < *(arr + i)) {
                int temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }

    printf("\nSecond lowest number = %d\n", arr[1]);

    free(arr);
    return 0;
}
