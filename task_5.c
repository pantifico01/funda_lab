// 5 задание часть 1 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// x^n/ n! 
double a(double x, double epsilon) {
    double sum = 0.0;
    int n = 0;

    while (1) {
        //  x^n
        double xn = 1.0;
        for (int i = 0; i < n; i++) {
            xn *= x;
        }
        // n! 
        double fact = 1.0;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        // x^n / n! 
        double temp = xn / fact;

        if (fabs(temp) < epsilon) {
            break;
        }
        sum += temp;
        n++;
    }
    return sum;
}

// (-1)^n * x^(2n) / (2n)! 
double b(double x, double epsilon) {
    double sum = 0.0;
    int n = 0;
    while (1) {
        // знак (-1)^n 
        double sign;
        if (n % 2 == 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }
        // x^(2n) 
        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }
        // (2n)! 
        double fact = 1.0;
        for (int i = 2; i <= 2 * n; i++) {
            fact *= i;
        }
        double temp = sign * x2n / fact;

        if (fabs(temp) < epsilon) {
            break;
        }
        sum += temp;
        n++;
    }
    return sum;
}

// 3^(3n) * (n!)^3 * x^(2n) / (3n)! 
double c(double x, double epsilon) {
    double sum = 0.0;
    int n = 0;
    while (1) {
        // 3^(3n) 
        double pow3 = 1.0; 
        for (int i = 0; i < 3 * n; i++) { 
            pow3 *= 3.0;
        }
        // n!
        double factN = 1.0;
        for (int i = 2; i <= n; i++) {
            factN *= i;
        }
        // (n!)^3 
        double factN3 = factN * factN * factN;

        // x^(2n) 
        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }
        // (3n)! 
        double fact3n = 1.0;
        for (int i = 2; i <= 3 * n; i++) {
            fact3n *= i;
        }
        double temp = pow3 * factN3 * x2n / fact3n;

        if (fabs(temp) < epsilon) {
            break;
        }
        sum += temp;
        n++;
    }
    return sum;
}

// (-1)^n * (2n-1)!! * x^(2n) / (2n)!! 
double d(double x, double epsilon) {
    double sum = 0.0;
    int n = 1;
    while (1) {

        // знак (-1)^n 
        double sign;
        if (n % 2 == 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }
        // (2n-1)!!  
        double dfact1 = 1.0;
        for (int i = 2 * n - 1; i >= 1; i -= 2) {
            dfact1 *= i;
        }
        // x^(2n) 
        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }
        // (2n)!!
        double dfact2 = 1.0;
        for (int i = 2 * n; i >= 2; i -= 2) {
            dfact2 *= i;
        }
        double temp = sign * dfact1 * x2n / dfact2;

        if (fabs(temp) < epsilon) {
            break;
        }
        sum += temp;
        n++;
    }
    return sum;
}

// строка в число 
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

    for (; str[i] != '\0' && str[i] != '.'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
        num = num * 10.0 + (str[i] - '0');
        hasDigit = 1;
    }
    if (str[i] == '.') {
        i++;
        double factor = 0.1;
        for (; str[i] != '\0'; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 1;
            }
            num = num + (str[i] - '0') * factor;
            factor = factor / 10.0;
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
    if (argc < 3) {
        return 1;
    }
    double x, epsilon;

    if (changeDouble(argv[1], &x) != 0 ||
        changeDouble(argv[2], &epsilon) != 0) {
        printf("Error\n");
        return 1;
    }
    if (epsilon <= 0) {
        printf("Error\n");
        return 1;
    }
    printf("x = %g, epsilon = %g\n", x, epsilon);
    printf("a. %f\n", a(x, epsilon));
    printf("b. %f\n", b(x, epsilon));
    printf("c. %f\n", c(x, epsilon));
    printf("d. %f\n", d(x, epsilon));

    return 0;
}