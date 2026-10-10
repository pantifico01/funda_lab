#include <stdio.h>
#include <stdlib.h>

// h: числа до 100, делящиеся на данное число   
int h(int x) {
    if (x <= 0) {
        printf("Error\n");
        return 1;
    }
    int foundDiv = 0;
    for (int i = x; i <= 100; i += x) {
        printf("%d ", i);
        foundDiv = 1;
    }
    if (!foundDiv) {
        printf("No have\n");
    } else {
        printf("\n");
    } return 0;
}

// p: простое или составное 
int p(int x) {
    if (x < 2) {
        printf("not simple or composite\n");
        return 0;
    }
    int isSimple = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
        isSimple = 0;
        break;
        }
    }
    if (isSimple) {
        printf("%d is simple\n", x);
    } else {
        printf("%d is composite\n", x);
    } 
    return 0;
}

// s: 16-я система 
int s(int x) {
    if (x <= 0) {
        printf("Error\n");
        return 1;
    }
    char digits[16] = {'0','1','2','3','4','5','6','7',
                       '8','9','A','B','C','D','E','F'};
    char result[32];
    int count = 0;
    int temp = x;
    while (temp > 0) {
        int ostatok = temp % 16;          
        result[count] = digits[ostatok];  
        count++;                   
        temp = temp / 16;            
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%c ", result[i]);
    }
    printf("\n");
    return 0;
}

// e: таблица степеней 
int e(int x) {
    if (x <= 0 || x > 10) {
        printf("Error\n");
        return 1;
    }
    for (int base = 1; base <= 10; base++) {
        printf("Base %d: ", base);
        for (int degree = 1; degree <= x; degree++) {
            long long val = 1;
            for (int k = 0; k < degree; k++) {
                val *= base;
            }
            printf("%lld ", val);
        }
        printf("\n");
    }
    return 0;
}

// а: сложить все числа от 1 до x
int a(int x) {
    if (x <= 0) {
        printf("Error\n");
        return 1;
    }
    long long sum = 0;
    for (int i = 1; i <= x; i++) {
        sum += i;
    }
    printf("%lld\n", sum);
    return 0;
}

// f: факториал
int f(int x) {
    if (x < 0 || x > 20) {
        printf("Error\n");
        return 1;
    }
    unsigned long long fact = 1;
    for (int i = 2; i <= x; i++) {
        fact *= i;
    }
    printf("%llu\n", fact);
    return 0;
}

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

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("not enough arguments\n");
        return 1;
    }

    char flag = argv[1][1];
    int x;
    if (change(argv[2], &x) != 0) {
        printf("Error\n");
        return 1;
    }

    if (flag == 'h') {
        h(x);
    } else if (flag == 'p') {
        p(x);
    } else if (flag == 's') {
        s(x);
    } else if (flag == 'e') {
        e(x);
    } else if (flag == 'a') {
        a(x);
    } else if (flag == 'f') {
        f(x);
    } else {
        printf("error\n");
    }
    return 0;
}