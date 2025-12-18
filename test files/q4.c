#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Momina Ahmad 25P-0503\n");

    int N;
    printf("Enter size of arrays (N): ");
    scanf("%d", &N);

    char c_arr[N];
    int i_arr[N];
    long long int ll_arr[N];

    srand(1);

    for(int i = 0; i < N; i++){
        c_arr[i] = 'A' + (rand() % 26);
        i_arr[i] = rand() % 100;
        ll_arr[i] = rand() % 1000000000LL;
    }

    printf("\nCHAR ARRAY:\n");
    char *cptr = c_arr;

    for(int i = 0; i < N; i++){
        printf("Index %d - Address: %p, Value: %c\n", i, (void*)cptr, *cptr);

        /*
           Pointer arithmetic:
           When you do cptr++, the pointer moves ahead by sizeof(char), which is 1 byte.
           So the address increases by 1.
        */
        cptr++;
    }

    printf("\nINT ARRAY:\n");
    int *iptr = i_arr;

    for(int i = 0; i < N; i++){
        printf("Index %d - Address: %p, Value: %d\n", i, (void*)iptr, *iptr);

        /*
           Pointer arithmetic:
           iptr++ moves the pointer ahead by sizeof(int).
           On most systems, sizeof(int) = 4 bytes.
           So the address increases by 4 bytes.
        */
        iptr++;
    }

    printf("\nLONG LONG ARRAY:\n");
    long long int *llptr = ll_arr;

    for(int i = 0; i < N; i++){
        printf("Index %d - Address: %p, Value: %lld\n", i, (void*)llptr, *llptr);

        /*
           Pointer arithmetic:
           llptr++ moves the pointer ahead by sizeof(long long int).
           Typically, sizeof(long long int) = 8 bytes.
           So the address jumps by 8 bytes each time.

           KEY IDEA:
           Pointers move in steps equal to the size of the data type they point to.
           This is why different pointer types "jump" different distances in memory.
        */
        llptr++;
    }

    return 0;
}
