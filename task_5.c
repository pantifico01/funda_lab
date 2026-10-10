// 5 задание
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// x^n / n!
double a(double x, double epsilon) {
    double sum = 0.0;
    int n = 0;

    while (1) {
        double xn = 1.0;
        for (int i = 0; i < n; i++) {
            xn *= x;
        }
        double fact = 1.0;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
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
        double sign;
        if (n % 2 == 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }

        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }

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
        double pow3 = 1.0;
        for (int i = 0; i < 3 * n; i++) {
            pow3 *= 3.0;
        }

        double factN = 1.0;
        for (int i = 2; i <= n; i++) {
            factN *= i;
        }
        double factN3 = factN * factN * factN;

        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }

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
        double sign;
        if (n % 2 == 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }

        double dfact1 = 1.0;
        for (int i = 2 * n - 1; i >= 1; i -= 2) {
            dfact1 *= i;
        }

        double x2n = 1.0;
        for (int i = 0; i < 2 * n; i++) {
            x2n *= x;
        }

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

// 2 часть
// ln(1+x)/x
double a1(double x) {
    if (fabs(x) < 1e-9) {
        return 1.0;
    }
    return log(1.0 + x) / x;
}

//  e^(-x^2/2)
double b1(double x) {
    return exp(-x * x / 2.0);
}

// ln(1/(1-x))
double c1(double x) {
    return log(1.0 / (1.0 - x));
}

// x^x
double d1(double x) {
    if (fabs(x) < 1e-9) {
        return 1.0;
    }
    return pow(x, x);
}

// Метод трапеций
double trapezoid(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return sum * h;
}

// Интегр с точн epsilon
double integrate(double (*f)(double), double a, double b, double epsilon) {
    double prev = 0.0;
    double cur = 1.0;
    int n = 1;

    while (fabs(cur - prev) > epsilon) {
        prev = cur;
        cur = trapezoid(f, a, b, n);
        n = n * 2;
    }
    return cur;
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

    printf("\nPart 1 - sums:\n");
    printf("a. %f\n", a(x, epsilon));
    printf("b. %f\n", b(x, epsilon));
    printf("c. %f\n", c(x, epsilon));
    printf("d. %f\n", d(x, epsilon));

    printf("\nPart 2 - integrals:\n");
    printf("a. %f\n", integrate(a1, 0.0, 1.0, epsilon));
    printf("b. %f\n", integrate(b1, 0.0, 1.0, epsilon));
    printf("c. %f\n", integrate(c1, 0.0, 1.0, epsilon));
    printf("d. %f\n", integrate(d1, 0.0, 1.0, epsilon));

    return 0;
}