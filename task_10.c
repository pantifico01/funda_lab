#include <stdio.h>
#include <stdlib.h>

int charToDigit(int ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;
    }
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10;
    }
    return -1;
}

char digitToChar(int d) {
    if (d >= 0 && d <= 9) {
        return '0' + d;
    }
    return 'A' + (d - 10);
}

//строка в число
int strToNumber(const char *str, int base, long long *result) {
    if (str == NULL || *str == '\0') {
        return 1;
    }

    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    long long num = 0;
    int hasDigit = 0;

    for (; str[i] != '\0'; i++) {
        int d = charToDigit(str[i]);
        if (d < 0 || d >= base) {
            return 1;
        }
        num = num * base + d;
        hasDigit = 1;
    }

    if (!hasDigit) {
        return 1;
    }

    *result = num * sign;
    return 0;
}

const char* delZero(const char *str) {
    int i = 0;
    while (str[i] == '0' && str[i + 1] != '\0') {
        i++;
    }
    return str + i;
}

void numberToString(long long num, int base, char *buffer) {
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int sign = 0;
    if (num < 0) {
        sign = 1;
        num = -num;
    }

    char temp[64];
    int count = 0;

    while (num > 0) {
        int d = num % base;
        temp[count] = digitToChar(d);
        count++;
        num = num / base;
    }

    int pos = 0;
    if (sign) {
        buffer[pos] = '-';
        pos++;
    }
    for (int i = count - 1; i >= 0; i--) {
        buffer[pos] = temp[i];
        pos++;
    }
    buffer[pos] = '\0';
}

int isStop(const char *str) {
    if (str[0] != 'S') {
        return 0;
    }
    if (str[1] != 't') {
        return 0;
    }
    if (str[2] != 'o') {
        return 0;
    }
    if (str[3] != 'p') {
        return 0;
    }
    if (str[4] != '\0') {
        return 0;
    }
    return 1;
}

int main(void) {
    int base;

    if (scanf("%d", &base) != 1) {
        return 1;
    }
    if (base < 2 || base > 36) {
        return 1;
    }

    char input[64];
    long long sum = 0;
    long long maxAbs = 0;
    int count = 0;

    while (1) {
        if (scanf("%63s", input) != 1) {
            break;
        }
        if (isStop(input)) {
            break;
        }

        long long num;
        if (strToNumber(input, base, &num) != 0) {
            printf("Error '%s'\n", input);
            continue;
        }
        sum += num;

        long long absNum;
        if (num < 0) {
            absNum = -num;
        } else {
            absNum = num;
        }

        if (count == 0 || absNum > maxAbs) {
            maxAbs = absNum;
        }
        count++;
    }

    if (count == 0) {
        printf("No entered\n");
        return 0;
    }

    printf("\nMax by abs: %lld\n", maxAbs);
    printf("Sum: %lld\n", sum);

    char buffer[64];

    printf("\nMax by abs:\n");

    numberToString(maxAbs, 10, buffer);
    printf("  base 10: %s\n", delZero(buffer));

    numberToString(maxAbs, 9, buffer);
    printf("  base  9: %s\n", delZero(buffer));

    numberToString(maxAbs, 18, buffer);
    printf("  base 18: %s\n", delZero(buffer));

    numberToString(maxAbs, 27, buffer);
    printf("  base 27: %s\n", delZero(buffer));

    numberToString(maxAbs, 36, buffer);
    printf("  base 36: %s\n", delZero(buffer));

    printf("\nSum:\n");

    numberToString(sum, 10, buffer);
    printf("  base 10: %s\n", delZero(buffer));

    numberToString(sum, 9, buffer);
    printf("  base  9: %s\n", delZero(buffer));

    numberToString(sum, 18, buffer);
    printf("  base 18: %s\n", delZero(buffer));

    numberToString(sum, 27, buffer);
    printf("  base 27: %s\n", delZero(buffer));

    numberToString(sum, 36, buffer);
    printf("  base 36: %s\n", delZero(buffer));

    return 0;
}