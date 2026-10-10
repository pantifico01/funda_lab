#include <stdio.h>
#include <math.h>

// Эпсилон + знач-я квадр ур-я a*x^2 + b*x + c = 0
// Вывести решения для всех уникальных перестановок
int q(double epsilon, double a1, double b1, double c1) {
    double coef[3] = {a1, b1, c1};
    int perest[6][3] = {
        {0, 1, 2}, {0, 2, 1},
        {1, 0, 2}, {1, 2, 0},
        {2, 0, 1}, {2, 1, 0}
    };
    for (int i = 0; i < 6; i++) {
        double a = coef[perest[i][0]];
        double b = coef[perest[i][1]];
        double c = coef[perest[i][2]];

        if (fabs(a) < epsilon) {
            if (fabs(b) < epsilon) {
                if (fabs(c) < epsilon) {
                    printf("Infinite solutions\n");
                } else {
                    printf("No solutions\n");
                }
            } else {
                double x = -c / b;
                printf("Linear equi x = %.6f\n", x);
            }
        } else {
            double D = b * b - 4 * a * c;
            if (D < -epsilon) {
                printf("No roots\n");
            } else if (fabs(D) < epsilon) {
                double x = -b / (2 * a);
                printf("One root x = %.6f\n", x);
            } else {
                double sqrtD = sqrt(D);
                double x1 = (-b + sqrtD) / (2 * a);
                double x2 = (-b - sqrtD) / (2 * a);
                printf("Two roots x1 = %.6f, x2 = %.6f\n", x1, x2);
            }
        }
    }
    return 0;
}


// определить делится ли второе число на первое 
int m(int a, int b) {
    if (b == 0) {
        printf("Error\n");
        return 1;
    }
    if (a % b == 0) {
        printf("%d is divisible by %d\n", a, b);
    } else {
        printf("%d isnt divisible by %d\n", a, b);
    }
    return 0;
}


// эпсилон  + стороны треуг
// определить может ли этот трег быть прямоуг c^2= a^2 + b^2
int t(double epsilon, double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Error\n");
        return 1;
    }
    double max = a;
    double k1 = b, k2 = c;
    if (b > max) {
        max = b;
        k1 = a;
        k2 = c;
    }
    if (c > max) {
        max = c;
        k1 = a;
        k2 = b;
    }
    double gip = max * max;
    double katet = k1 * k1 + k2 * k2;
    
    if (fabs(gip - katet) < epsilon) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}


//  в int
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

// в double
int changeDouble(const char *str, double *result) {
    if (str == NULL || *str == '\0') {
        return 1;
    }

    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    double num = 0.0;
    int hasDigit = 0;

    for (; str[i] != '\0' && str[i] != '.'; i++) { // целая часть 
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
        num = num * 10.0 + (str[i] - '0');
        hasDigit = 1;
    }

    //дробная
    if (str[i] == '.') {
        i++;
        double el = 0.1;
        for (; str[i] != '\0'; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 1;
            }
            num = num + (str[i] - '0') * el;
            el = el / 10.0;
            hasDigit = 1;
        }
    }
    if (!hasDigit) {
        return 1;
    }
    *result = num * sign;
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    char flag = argv[1][1];

    if (flag == 'q') {
        if (argc < 6) {
            return 1;
        }
        double eps, a, b, c;
        if (changeDouble(argv[2], &eps) != 0 ||
            changeDouble(argv[3], &a) != 0 ||
            changeDouble(argv[4], &b) != 0 ||
            changeDouble(argv[5], &c) != 0) {
            printf("Error\n");
            return 1;
        }
        q(eps, a, b, c);
    } else if (flag == 'm') {
        if (argc < 4) {
            return 1;
        }
        int a, b;
        if (change(argv[2], &a) != 0 || change(argv[3], &b) != 0) {
            printf("Error\n");
            return 1;
        }
        m(a, b);
    }
    else if (flag == 't') {
        if (argc < 6) {
            return 1;
        }
        double eps, a, b, c;
        if (changeDouble(argv[2], &eps) != 0 ||
            changeDouble(argv[3], &a) != 0 ||
            changeDouble(argv[4], &b) != 0 ||
            changeDouble(argv[5], &c) != 0) {
            printf("Error\n");
            return 1;
        }
        t(eps, a, b, c);
    }
    else {
        return 1;
    }
    return 0;
}

