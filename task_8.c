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

void number(const char *num, FILE *out) { //лид нули
    int start = 0;
    while (num[start] == '0' && num[start + 1] != '\0') {
        start++;
    }

    int maxDigit = 0;
    int i = start;
    while (num[i] != '\0') {
        int d = charToDigit(num[i]);
        if (d > maxDigit) {
            maxDigit = d;
        }
        i++;
    }

    int base = maxDigit + 1;
    if (base < 2) {
        base = 2;
    }

    // в десятич
    long long value = 0;
    i = start;
    while (num[i] != '\0') {
        int d = charToDigit(num[i]);
        value = value * base + d;
        i++;
    }
    fprintf(out, "%s %d %lld\n", num + start, base, value);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Error\n");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Error\n");
        fclose(in);
        return 1;
    }

    char buffer[256];
    int len = 0;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            if (len > 0) {
                buffer[len] = '\0';
                number(buffer, out);
                len = 0;
            }
        } else {
            if (len < 255) {
                buffer[len] = (char)ch;
                len++;
            }
        }
    }

    if (len > 0) { // послед слово если без \n
        buffer[len] = '\0';
        number(buffer, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}