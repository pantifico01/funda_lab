#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

typedef enum state {
    OK,
    ERROR_RANGE,
    ERROR_NULL,
    ERROR_INPUT,
    ERROR_OVERFLOW
} state;

// Прототипы 
state NumberInt(int* n);
state NumberD(double *n);
state IsConvex(int n, int* res, ...);
state PolyValue(double x, int n, double* res, ...);
state GeoMeanVar(int count, double *res, ...);
state FastPow(double x, int n, double *res);
state FindKaprekar(int base, int *res, int count, ...);
state Dihotomiya(double a, double b, double eps, double (*f)(double), double* res);
long long ParseInBase(const char *s, int base);
int IsKaprekar(long long num, int base);

state NumberInt(int* n) {
    if (n == NULL) {
        return ERROR_INPUT;
    }
    int x;
    if (scanf("%d", &x) != 1) {
        return ERROR_INPUT;
    }
    *n = x;
    return OK;
}

state NumberD(double *n) {
    if (n == NULL) {
        return ERROR_INPUT;
    }
    double x;
    if (scanf("%lf", &x) != 1) {
        return ERROR_INPUT;
    }
    *n = x;
    return OK;
}

// Выпуклый многоугольник 
void DemoIsConvex() {
    int n;
    int res;
    state st;
    printf("count of top ");
    if (NumberInt(&n) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    if (n < 3 || n > 5) {
        return;
    }

    double X[5], Y[5];
    printf("enter coordinetes %d of top x and y:\n", n);
    for (int i = 0; i < n; ++i) {
        if (NumberD(&X[i]) != OK || NumberD(&Y[i]) != OK) {
            fprintf(stderr, "incorrect\n");
            return;
        }
    }

    if (n == 3) {
        st = IsConvex(3, &res, X[0], Y[0], X[1], Y[1], X[2], Y[2]);
    } else if (n == 4) {
        st = IsConvex(4, &res, X[0], Y[0], X[1], Y[1], X[2], Y[2], X[3], Y[3]);
    } else {
        st = IsConvex(5, &res, X[0], Y[0], X[1], Y[1], X[2], Y[2], X[3], Y[3], X[4], Y[4]);
    }

    if (st == OK) {
        if (res) {
            printf("is convex\n");
        } else {
            printf("isnt convex\n");
        }
    } else if (st == ERROR_INPUT) {
        fprintf(stderr, "incorrect arg\n");
    } else if (st == ERROR_RANGE) {
        fprintf(stderr, "3 tops are minimum\n");
    }
}

state IsConvex(int n, int* res, ...) {
    if (res == NULL) return ERROR_NULL;
    if (n < 3 || n > 5) return ERROR_RANGE;
    va_list param;
    va_start(param, res);

    double X[5];
    double Y[5];
    for (int i = 0; i < n; ++i) {
        X[i] = va_arg(param, double);
        Y[i] = va_arg(param, double);
    }
    va_end(param);

    int sign = 0;
    for (int i = 0; i < n; ++i) {
        int i1 = (i + 1) % n;
        int i2 = (i + 2) % n;

        double ABx = X[i1] - X[i];
        double ABy = Y[i1] - Y[i];
        double BCx = X[i2] - X[i1];
        double BCy = Y[i2] - Y[i1];

        double cross = ABx * BCy - ABy * BCx;

        if (cross > 0) {
            if (sign == 0) {
                sign = 1;
            } else if (sign == -1) {
                *res = 0;
                return OK;
            }
        } else if (cross < 0) {
            if (sign == 0) {
                sign = -1;
            } else if (sign == 1) {
                *res = 0;
                return OK;
            }
        }
    }

    if (sign != 0) {
        *res = 1;
    } else {
        *res = 0;
    }
    return OK;
}

// Многочлен
void DemoPolyValue() {
    int n;
    double x;
    state st;
    printf("enter point x: ");
    if (NumberD(&x) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    printf("enter degree (0-5): ");
    if (NumberInt(&n) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    if (n < 0 || n > 5) {
        fprintf(stderr, "incorrect degree\n");
        return;
    }

    double polinom[6];
    printf("enter %d coefficients from the highest degree to the lowest:\n", n + 1);
    for (int i = 0; i < n + 1; ++i) {
        if (NumberD(&polinom[i]) != OK) {
            fprintf(stderr, "incorrect\n");
            return;
        }
    }

    double res;
    if (n == 0) {
        st = PolyValue(x, 0, &res, polinom[0]);
    } else if (n == 1) {
        st = PolyValue(x, 1, &res, polinom[0], polinom[1]);
    } else if (n == 2) {
        st = PolyValue(x, 2, &res, polinom[0], polinom[1], polinom[2]);
    } else if (n == 3) {
        st = PolyValue(x, 3, &res, polinom[0], polinom[1], polinom[2], polinom[3]);
    } else if (n == 4) {
        st = PolyValue(x, 4, &res, polinom[0], polinom[1], polinom[2], polinom[3], polinom[4]);
    } else {
        st = PolyValue(x, 5, &res, polinom[0], polinom[1], polinom[2], polinom[3], polinom[4], polinom[5]);
    }

    if (st == OK) {
        printf("value %g\n", res);
    } else if (st == ERROR_NULL) {
        fprintf(stderr, "null pointer\n");
    } else if (st == ERROR_RANGE) {
        fprintf(stderr, "degree out\n");
    } else {
        fprintf(stderr, "error\n");
    }
}

state PolyValue(double x, int n, double* res, ...) {
    if (res == NULL) return ERROR_NULL;
    if (n < 0 || n > 5) return ERROR_RANGE;

    va_list param;
    va_start(param, res);

    *res = 0.0;
    for (int i = n; i >= 0; --i) {
        double coef = va_arg(param, double);
        *res = *res * x + coef;
    }
    va_end(param);
    return OK;
}

// Числа Капрекара 
long long ParseInBase(const char *s, int base) {
    long long num = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int d;
        if (s[i] >= '0' && s[i] <= '9') {
            d = s[i] - '0';
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            d = s[i] - 'A' + 10;
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            d = s[i] - 'a' + 10;
        } else {
            return -1;
        }
        if (d >= base) {
            return -1;
        }
        num = num * base + d;
    }
    return num;
}

int IsKaprekar(long long num, int base) {
    if (num < 0) {
        return 0;
    }
    long long sq = num * num;
    long long power = 1;

    while (power <= sq) {
        long long left = sq / power;
        long long right = sq % power;
        if (left + right == num) {
            return 1;
        }
        power *= base;
    }
    return 0;
}

void DemoFindKaprekar() {
    int base, count;
    int res;
    state st;
    char buf[5][64];

    printf("enter base");
    if (NumberInt(&base) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    if (base < 2 || base > 36) {
        return;
    }

    if (NumberInt(&count) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    if (count < 1 || count > 5) {
        return;
    }

    printf("enter %d numbers in base %d:\n", count, base);
    for (int i = 0; i < count; ++i) {
        if (scanf("%63s", buf[i]) != 1) {
            fprintf(stderr, "incorrect\n");
            return;
        }
    }

    if (count == 1) {
        st = FindKaprekar(base, &res, 1, buf[0]);
    } else if (count == 2) {
        st = FindKaprekar(base, &res, 2, buf[0], buf[1]);
    } else if (count == 3) {
        st = FindKaprekar(base, &res, 3, buf[0], buf[1], buf[2]);
    } else if (count == 4) {
        st = FindKaprekar(base, &res, 4, buf[0], buf[1], buf[2], buf[3]);
    } else {
        st = FindKaprekar(base, &res, 5, buf[0], buf[1], buf[2], buf[3], buf[4]);
    }

    if (st == OK) {
        if (res) {
            printf("have number of kapreker\n");
        } else {
            printf("no have number of kapreker\n");
        }
    } else if (st == ERROR_NULL) {
        fprintf(stderr, "null pointer\n");
    } else if (st == ERROR_RANGE) {
        fprintf(stderr, "incorrect base\n");
    } else {
        fprintf(stderr, "incorrect number\n");
    }
}

state FindKaprekar(int base, int *res, int count, ...) {
    if (res == NULL) {
        return ERROR_NULL;
    }
    if (base < 2 || base > 36) {
        return ERROR_RANGE;
    }
    if (count < 1 || count > 5) {
        return ERROR_RANGE;
    }

    va_list param;
    va_start(param, count);

    *res = 0;
    for (int i = 0; i < count; ++i) {
        const char *s = va_arg(param, const char *);
        long long num = ParseInBase(s, base);
        if (num < 0) {
            va_end(param);
            return ERROR_INPUT;
        }
        if (IsKaprekar(num, base)) {
            *res = 1;
            break;
        }
    }
    va_end(param);
    return OK;
}

// Среднее геометрическое 
state GeoMeanVar(int count, double *res, ...) {
    if (res == NULL) {
        return ERROR_NULL;
    }
    if (count < 1 || count > 5) {
        return ERROR_RANGE;
    }

    va_list param;
    va_start(param, res);

    double product = 1.0;
    for (int i = 0; i < count; ++i) {
        double val = va_arg(param, double);
        if (val < 0) {
            va_end(param);
            return ERROR_RANGE;
        }
        product *= val;
    }
    va_end(param);

    *res = pow(product, 1.0 / count);
    return OK;
}

void DemoGeoMean() {
    int n;
    double res;
    double vals[5];
    state st;

    printf("how much numbers ");
    if (NumberInt(&n) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    if (n < 1 || n > 5) {
        return;
    }

    printf("enter %d numbers:\n", n);
    for (int i = 0; i < n; ++i) {
        if (NumberD(&vals[i]) != OK) {
            fprintf(stderr, "incorect\n");
            return;
        }
    }

    if (n == 1) {
        st = GeoMeanVar(1, &res, vals[0]);
    } else if (n == 2) {
        st = GeoMeanVar(2, &res, vals[0], vals[1]);
    } else if (n == 3) {
        st = GeoMeanVar(3, &res, vals[0], vals[1], vals[2]);
    } else if (n == 4) {
        st = GeoMeanVar(4, &res, vals[0], vals[1], vals[2], vals[3]);
    } else {
        st = GeoMeanVar(5, &res, vals[0], vals[1], vals[2], vals[3], vals[4]);
    }

    if (st == OK) {
        printf("geometric mean %g\n", res);
    } else if (st == ERROR_NULL) {
        fprintf(stderr, " null pointer\n");
    } else if (st == ERROR_RANGE) {
        fprintf(stderr, "negative or bad\n");
    } else {
        fprintf(stderr, "error\n");
    }
}

// Быстрое возведение
state FastPow(double x, int n, double *res) {
    if (res == NULL) {
        return ERROR_NULL;
    }
    if (n == 0) {
        *res = 1.0;
        return OK;
    }
    if (n < 0) {
        if (x == 0.0) {
            return ERROR_INPUT;
        }
        double tmp;
        state st = FastPow(x, -n, &tmp);
        if (st != OK) {
            return st;
        }
        *res = 1.0 / tmp;
        return OK;
    }
    if (n % 2 == 0) {
        double half;
        state st = FastPow(x, n / 2, &half);
        if (st != OK) {
            return st;
        }
        *res = half * half;
    } else {
        double rest;
        state st = FastPow(x, n - 1, &rest);
        if (st != OK) {
            return st;
        }
        *res = x * rest;
    }
    return OK;
}

void DemoFastPow() {
    double x, res;
    int n;
    state st;

    printf("base of x ");
    if (NumberD(&x) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    printf("enter degree ");
    if (NumberInt(&n) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }

    st = FastPow(x, n, &res);
    if (st == OK) {
        printf("%g^%d = %g\n", x, n, res);
    } else if (st == ERROR_NULL) {
        fprintf(stderr, "null pointer\n");
    } else {
        fprintf(stderr, "0 cant be in degree\n");
    }
}

// Дихотомия 
static double F1(double x) { return x * x - 2.0; }
static double F2(double x) { return cos(x) - x; }
static double F3(double x) { return x * x * x - x - 1.0; }

state Dihotomiya(double a, double b, double eps, double (*f)(double), double* res) {
    if (f == NULL || res == NULL) {
        return ERROR_NULL;
    }
    if (eps <= 0) {
        return ERROR_RANGE;
    }

    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0) {
        return ERROR_INPUT;
    }

    while (b - a > eps) {
        double mid = (a + b) / 2.0;
        double fm = f(mid);
        if (fm == 0.0) {
            *res = mid;
            return OK;
        }
        if (fa * fm < 0) {
            b = mid;
            fb = fm;
        } else {
            a = mid;
            fa = fm;
        }
    }
    *res = (a + b) / 2.0;
    return OK;
}

void DemoDihotomiya() {
    double a, b, eps, res;
    int eq;
    state st;

    printf("choose equi\n");
    printf("  1: x^2 - 2 = 0\n");
    printf("  2: cos(x) - x = 0\n");
    printf("  3: x^3 - x - 1 = 0\n");
    printf("number: ");
    if (NumberInt(&eq) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }

    printf("enter left border a: ");
    if (NumberD(&a) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    printf("enter right border b: ");
    if (NumberD(&b) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }
    printf("enter accuracy eps: ");
    if (NumberD(&eps) != OK) {
        fprintf(stderr, "incorrect\n");
        return;
    }

    double (*f)(double) = NULL;
    if (eq == 1) {
        f = F1;
    } else if (eq == 2) {
        f = F2;
    } else if (eq == 3) {
        f = F3;
    } else {
        fprintf(stderr, "incorrect number of equi\n");
        return;
    }

    st = Dihotomiya(a, b, eps, f, &res);
    if (st == OK) {
        printf("root: %.10f\n", res);
    } else if (st == ERROR_NULL) {
        fprintf(stderr, "null pointer\n");
    } else if (st == ERROR_RANGE) {
        fprintf(stderr, "accuracy should be > 0\n");
    } else {
        fprintf(stderr, "root isnt separeted (f(a)*f(b) > 0)\n");
    }
}

int main() {
    int c = 0;

    printf("choose function (1-6): ");
    if (NumberInt(&c) != OK) {
        fprintf(stderr, "incorrect\n");
        return ERROR_INPUT;
    }

    if (c == 1) {
        DemoIsConvex();
    } else if (c == 2) {
        DemoPolyValue();
    } else if (c == 3) {
        DemoFindKaprekar();
    } else if (c == 4) {
        DemoGeoMean();
    } else if (c == 5) {
        DemoFastPow();
    } else if (c == 6) {
        DemoDihotomiya();
    } else {
        fprintf(stderr, "incorrect number of function \n");
        return ERROR_RANGE;
    }
    return OK;
}