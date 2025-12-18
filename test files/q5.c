#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Momina Ahmad 25P-0503\n");

    int N;
    printf("Enter number of elements (N): ");
    scanf("%d", &N);

    int *ptr = (int*)malloc(N * sizeof(int));
    if(ptr == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    int *p = ptr;
    printf("Enter %d integers:\n", N);
    for(int i = 0; i < N; i++) {
        scanf("%d", p);
        p++;
    }

    int sum = 0;
    p = ptr;
    for(int i = 0; i < N; i++) {
        sum += *p;
        p++;
    }

    printf("Sum of array = %d\n", sum);

    free(ptr);
    return 0;
}
