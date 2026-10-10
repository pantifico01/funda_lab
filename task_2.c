#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// (1 \ n!)
double eRyad(double epsilon) {
    double sum = 0.0;
    int n = 0;
    while (1) {
        double fact = 1.0;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        double temp = 1.0 / fact;   
        if (temp < epsilon) {
            break;   
        }
        sum += temp;
        n++;
    }
    return sum;
}

// (1 + 1\n)^ n
double eLimit(double epsilon) {
    double prev = 0.0;
    double cur = 1.0;
    int n = 1;
    while (fabs(cur - prev) > epsilon) {
        prev = cur;
        cur = pow(1.0 + 1.0 / n, n);
        n++;
    }
    return cur;
}

// ln x = 1
double eEqui(double epsilon) {
    double left = 2.0;
    double right = 3.0;
    double mid;
    while (right - left > epsilon) {
        mid = (left + right) / 2.0;
        if (log(mid) < 1.0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return (left + right) / 2.0;
}

// 4 * Е (-1)^(n-1) / (2n-1) 
double pRyad(double epsilon) {
    double sum = 0.0;
    int n = 1;
    double temp = 1.0;  

    while (temp > epsilon) {
        double sign;
        if (n % 2 == 1) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }
        temp = 1.0 / (2.0 * n - 1.0);
        sum += sign * temp;
        n++;
    }
    return 4.0 * sum;
}
#define MAX_N 5
double pLimit(double epsilon) {
    double prev = 0.0;
    double cur = 1.0;  
    int n = 1;
    while (fabs(cur - prev) > epsilon && n <= MAX_N) {
        prev = cur;

        double factN = 1.0; // n!
        for (int i = 2; i <= n; i++) {
            factN *= i;
        }

        double fact2n = 1.0; // (2n)!
        for (int i = 2; i <= 2 * n; i++) {
            fact2n *= i;
        }

        double twoN = 1.0; // 2^n
        for (int i = 0; i < n; i++) {
            twoN *= 2.0;
        }
        
        double num = twoN * factN; // (2^n * n!) ^ 4
        num = num * num * num * num;

        double temp = n * fact2n * fact2n;  // n*((2n)!) ^ 2

        cur = num / temp;
        n++;
    }
    return cur;
}

// cos(x) = -1 
double pEqui(double epsilon) {
    double left = 3.0;
    double right = 4.0;
    double mid;
    double delta = 0.0001;

    while (right - left > epsilon) {
        mid = (left + right) / 2.0;
        if (cos(mid) > cos(mid + delta)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return (left + right) / 2.0;
}


// Е (-1)^ n-1 / n 
double ln2Ryad(double epsilon) {
    double sum = 0.0;
    double temp = 1.0;  
    int n = 1;
    double sign = 1.0;   

    while (temp > epsilon) {
        temp = 1.0 / n;
        sum += sign * temp;   
        sign = -sign;        
        n++;
    }

    return sum;
}
// n * (2^(1/n) - 1)
double ln2Limit(double epsilon) {
    double prev = 0.0;
    double cur = 1.0;   
    int n = 2;

    while (fabs(cur - prev) > epsilon) {
        prev = cur;
        double root = pow(2.0, 1.0 / n); // 2^(1/n) 
        cur = n * (root - 1.0); // n*(2^(1/n) - 1) 
        n++;
    }
    return cur;
}

// e^x = 2
double ln2Equi(double epsilon) {
    double left = 0.0;
    double right = 1.0;
    double mid;

    while (right - left > epsilon) {
        mid = (left + right) / 2.0;
        if (exp(mid) < 2.0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return (left + right) / 2.0;
}

// 2 ^(2^(-k))
double sqrt2Ryad(double epsilon) {
    double proizv = 1.0;
    int k = 2;
    double element = 0.0;   
    while (fabs(element - 1.0) > epsilon) {
        double power = pow(2.0, -k); // 2^(-k) 
        element = pow(2.0, power);   // 2^(2^(-k)) 
        proizv *= element;
        k++;
    }
    return proizv;
}


// lim x_n, x_{n+1} = x_n - (x_n)^2/2 + 1,   x_0 = -0.5
double sqrt2Limit(double epsilon) {
    double prev = 0.0;
    double cur = -0.5;  
    int n = 0;
    while (fabs(cur - prev) > epsilon) {
        prev = cur; 
        cur = prev - (prev * prev) / 2.0 + 1.0; 
        n++;
    }
    return cur;
}


// x^2 = 2 
// x = 2 ^ (1/2)
double sqrt2Equi(double epsilon) {
    double left = 1.0;
    double right = 2.0;
    double mid;
    while (right - left > epsilon) {
        mid = (left + right) / 2.0;
        if (mid * mid < 2.0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return (left + right) / 2.0;
}


// C_m^k((-1)^k / k) ln (k!)
double gammaLimit(double epsilon) {
    double prev = 0.0;
    double cur = 1.0;   
    int m = 1;
    while (fabs(cur - prev) > epsilon) {
        prev = cur;
        double sum = 0.0;
        for (int k = 1; k <= m; k++) { //C_m^k = m!/(k! * (m-k)!)
            double fact_m = 1.0;
            for (int i = 2; i <= m; i++) {
                fact_m *= i;
            }
            double fact_k = 1.0;
            for (int i = 2; i <= k; i++) {
                fact_k *= i;
            }
            double fact_mk = 1.0;
            for (int i = 2; i <= m - k; i++) {
                fact_mk *= i;
            }
            double C = fact_m / (fact_k * fact_mk);
            double sign;
            if (k % 2 == 0) { // (-1)^k / k
                sign = 1.0;
            } else {
                sign = -1.0;
            }
            double temp1 = sign / k;
            double temp2 = log(fact_k); // ln(k!)

            sum += C * temp1 * temp2;
        }
        cur = sum;
        m++;
    }
    return cur;
}


//(-P^2)/6 + (1/(k^1/2) - 1/k)
double gammaRyad(double epsilon) {
    double sum = -M_PI * M_PI / 6.0;  
    int k = 2;
    double temp = 0.0;
    while (1) {
        temp = 1.0 / sqrt((double)k) - 1.0 / (double)k;
        sum += temp;
        if (fabs(temp) < epsilon) {
            break;
        }
        k++;
    }
    return sum;
}

// простое 
int isPrime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// lim (ln t * P ((p-1)/p))
double gammaEqui(double epsilon) {
    double x = 0.0;
    double prev = -1000000000000.0;
    int t = 10;

    while (fabs(x - prev) >= epsilon) {
        prev = x;
        t *= 2;

        double P = 1.0;
        for (int p = 2; p <= t; p++) {
            if (isPrime(p)) {
                P *= (p - 1.0) / p;
            }
        }
        x = log(t) * P;
    }
    return -log(x);
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
    double epsilon;
    if (changeDouble(argv[1], &epsilon) != 0) {
        printf("Error\n");
        return 1;
    }

    if (epsilon <= 0) {
        printf("Error\n");
        return 1;
    }

    printf("e:\n");
    printf("  ryad:  %.10f\n", eRyad(epsilon));
    printf("  limit: %.10f\n", eLimit(epsilon));
    printf("  equi:  %.10f\n", eEqui(epsilon));

    printf("pi:\n");
    printf("  ryad:  %.10f\n", pRyad(epsilon));
    printf("  limit: %.10f\n", pLimit(epsilon));
    printf("  equi:  %.10f\n", pEqui(epsilon));

    printf("ln2:\n");
    printf("  ryad:  %.10f\n", ln2Ryad(epsilon));
    printf("  limit: %.10f\n", ln2Limit(epsilon));
    printf("  equi:  %.10f\n", ln2Equi(epsilon));

    printf("sqrt2:\n");
    printf("  ryad:  %.10f\n", sqrt2Ryad(epsilon));
    printf("  limit: %.10f\n", sqrt2Limit(epsilon));
    printf("  equi:  %.10f\n", sqrt2Equi(epsilon));

    printf("gamma:\n");
    printf("  ryad:  %.10f\n", gammaRyad(epsilon));
    printf("  limit: %.10f\n", gammaLimit(epsilon));
    printf("  equa:  %.10f\n", gammaEqui(epsilon));

    return 0;
}