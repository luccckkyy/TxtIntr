#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>

// Function to convert word representation to double
double wordToDouble(const char* word) {
    // Simple mapping for demonstration purposes
    if (strcmp(word, "zero") == 0) return 0.0;
    if (strcmp(word, "one") == 0) return 1.0;
    if (strcmp(word, "two") == 0) return 2.0;
    if (strcmp(word, "three") == 0) return 3.0;
    if (strcmp(word, "four") == 0) return 4.0;
    if (strcmp(word, "five") == 0) return 5.0;
    if (strcmp(word, "six") == 0) return 6.0;
    if (strcmp(word, "seven") == 0) return 7.0;
    if (strcmp(word, "eight") == 0) return 8.0;
    if (strcmp(word, "nine") == 0) return 9.0;
    if (strcmp(word, "ten") == 0) return 10.0;

    // If not found, return NaN (Not a Number)
    return NAN;
}

void print_help() {
    printf("Usage: calculator [-o operation] operand\n");
    printf("Operations:\n");
    printf("  -o atg   - arctangent (in degrees or radians)\n");
    printf("  -o actg  - arccotangent (in degrees or radians)\n");
    printf("  -d       - result in degrees\n");
    printf("  -r       - result in radians (default)\n");
}

double atg(double x, int degrees) {
    double result = atan(x);
    if (degrees) {
        result = result * 180 / M_PI;
    }
    return result;
}

double actg(double x, int degrees) {
    double result = atan(1/x);
    if (degrees) {
        result = result * 180 / M_PI;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int opt;
    char *operation = NULL;
    double operand;
    int degrees = 0;

    while ((opt = getopt(argc, argv, "o:drh")) != -1) {
        switch (opt) {
            case 'o':
                operation = optarg;
                break;
            case 'd':
                degrees = 1;
                break;
            case 'r':
                degrees = 0;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                print_help();
                return 1;
        }
    }

    if (operation == NULL || argc - optind != 1) {
        print_help();
        return 1;
    }

    // Try to convert the operand from word representation first
    operand = wordToDouble(argv[optind]);
    if (isnan(operand)) {
        // If not a word representation, try to convert from numeric string
        operand = atof(argv[optind]);
    }

    if (strcmp(operation, "atg") == 0) {
        printf("Arctangent of %f is %f\n", operand, atg(operand, degrees));
    } else if (strcmp(operation, "actg") == 0) {
        printf("Arccotangent of %f is %f\n", operand, actg(operand, degrees));
    } else {
        print_help();
        return 1;
    }

    return 0;
}

