#include <stdio.h>

int main() {
    printf("Momina Ahmad 25P-0503\n");

    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    int *ptr1 = &num;
    int **ptr2 = &ptr1;

    printf("Original value: %d\n", num);

    **ptr2 = **ptr2 + 10;   // change value using ptr2

    printf("New value: %d\n", num);

    return 0;
}
