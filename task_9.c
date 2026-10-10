#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// из стр в int
int change(const char *str, int *result) {
    if (str == NULL || *str == '\0') {
        return 1;
    }
    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    int num = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
        num = num * 10 + (str[i] - '0');
    }
    *result = num * sign;
    return 0;
}

// фикс массив
#define FIXED_SIZE 20

void addRandom(int *arr, int size, int a, int b) {
    for (int i = 0; i < size; i++) {
        int value;
        do {
            value = rand();
        } while (value < a || value > b);
        arr[i] = value;
    }
}

void changeMinMax(int *arr, int size) {
    int maxi = 0;
    int mini = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxi]) {
            maxi = i;
        }
        if (arr[i] < arr[mini]) {
            mini = i;
        }
    }

    int temp = arr[maxi];
    arr[maxi] = arr[mini];
    arr[mini] = temp;
}

void printArray(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int part1(int a, int b) {
    if (a > b) {
        return 1;
    }

    int arr[FIXED_SIZE];
    addRandom(arr, FIXED_SIZE, a, b);

    printf("Before change:\n");
    printArray(arr, FIXED_SIZE);

    changeMinMax(arr, FIXED_SIZE);

    printf("After change:\n");
    printArray(arr, FIXED_SIZE);

    return 0;
}

// динам массивы
int findClosest(const int *B, int sizeB, int x) {
    int closest = B[0];
    int raznitsa = abs(B[0] - x);

    for (int i = 1; i < sizeB; i++) {
        int diff = abs(B[i] - x);
        if (diff < raznitsa) {
            raznitsa = diff;
            closest = B[i];
        }
    }
    return closest;
}

int part2(void) {
    int sizeA;
    do {
        sizeA = rand();
    } while (sizeA < 10 || sizeA > 10000);

    int sizeB;
    do {
        sizeB = rand();
    } while (sizeB < 10 || sizeB > 10000);

    int *A = (int *)malloc(sizeA * sizeof(int));
    if (A == NULL) {
        return 1;
    }

    int *B = (int *)malloc(sizeB * sizeof(int));
    if (B == NULL) {
        free(A);
        return 1;
    }

    int *C = (int *)malloc(sizeA * sizeof(int));
    if (C == NULL) {
        free(A);
        free(B);
        return 1;
    }

    for (int i = 0; i < sizeA; i++) {
        A[i] = -1000 + rand() % (1000 - (-1000) + 1);
    }
    for (int i = 0; i < sizeB; i++) {
        B[i] = -1000 + rand() % (1000 - (-1000) + 1);
    }
    for (int i = 0; i < sizeA; i++) {
        int closest = findClosest(B, sizeB, A[i]);
        C[i] = A[i] + closest;
    }
    for (int i = 0; i < 10 && i < sizeA; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    for (int i = 0; i < 10 && i < sizeB; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");

    for (int i = 0; i < 10 && i < sizeA; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc < 3) {
        return 1;
    }
    int a, b;
    if (change(argv[1], &a) != 0 || change(argv[2], &b) != 0) {
        return 1;
    }
    printf("Part 1\n");
    part1(a, b);

    printf("\nPart 2\n");
    part2();

    return 0;
}