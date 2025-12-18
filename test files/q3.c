#include <stdio.h>
void reverse(int *arr, int size){
    int *start = arr;
    int *end = arr + size - 1;

    while(start < end){
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}
int main(){
    printf("Momina Ahmad 25P-0503\n");
	int arr[10];
    int i;
    printf("Enter 10 integers:\n");
    for(i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }
    printf("Original array: ");
    for(i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    reverse(arr, 10);

    printf("Reversed array: ");
    for(i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
