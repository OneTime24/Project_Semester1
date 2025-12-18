#include <stdio.h>
#include <stdlib.h>

int* findIntersection(int *arr1, int size1, int *arr2, int size2, int *resultSize) {
    int *temp = (int*)malloc((size1 < size2 ? size1 : size2) * sizeof(int));
    if(temp == NULL) return NULL;

    int count = 0;

    for(int i = 0; i < size1; i++) {
        int foundInArr2 = 0;
        for(int j = 0; j < size2; j++) {
            if(*(arr1 + i) == *(arr2 + j)) {
                foundInArr2 = 1;
                break;
            }
        }

        int alreadyAdded = 0;
        for(int k = 0; k < count; k++) {
            if(*(temp + k) == *(arr1 + i)) {
                alreadyAdded = 1;
                break;
            }
        }

        if(foundInArr2 && !alreadyAdded) {
            *(temp + count) = *(arr1 + i);
            count++;
        }
    }

    if(count == 0) {
        free(temp);
        *resultSize = 0;
        return NULL;
    }

    *resultSize = count;
    int *result = (int*)malloc(count * sizeof(int));
    if(result == NULL) {
        free(temp);
        *resultSize = 0;
        return NULL;
    }

    for(int i = 0; i < count; i++)
        *(result + i) = *(temp + i);

    free(temp);
    return result;
}

int main() {
    printf("Momina Ahmad 25P-0503\n");

    int n1, n2;
    printf("Enter size of first array: ");
    scanf("%d", &n1);
    int *arr1 = (int*)malloc(n1 * sizeof(int));
    for(int i = 0; i < n1; i++)
        scanf("%d", arr1 + i);

    printf("Enter size of second array: ");
    scanf("%d", &n2);
    int *arr2 = (int*)malloc(n2 * sizeof(int));
    for(int i = 0; i < n2; i++)
        scanf("%d", arr2 + i);

    int resultSize;
    int *intersection = findIntersection(arr1, n1, arr2, n2, &resultSize);

    if(intersection == NULL) {
        printf("No intersection found.\n");
    } else {
        printf("Intersection elements: ");
        for(int i = 0; i < resultSize; i++)
            printf("%d ", *(intersection + i));
        printf("\n");
        free(intersection);
    }

    free(arr1);
    free(arr2);
    return 0;
}
