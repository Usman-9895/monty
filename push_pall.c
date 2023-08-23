#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

int stack[STACK_SIZE];
int top = -1; // Index of the top element in the stack

// Push an element onto the stack
void push(int value) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = value;
}

// Print all elements in the stack from top to bottom
void pall() {
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char line[100];
    int line_number = 1;

    while (fgets(line, sizeof(line), file)) {
        char opcode[100];
        int value;
        
        if (sscanf(line, "%s %d", opcode, &value) == 2) {
            if (strcmp(opcode, "push") == 0) {
                push(value);
            } else {
                fprintf(stderr, "Unknown opcode: %s\n", opcode);
                fclose(file);
                return EXIT_FAILURE;
            }
        } else if (strcmp(opcode, "pall") == 0) {
            pall();
        } else {
            fprintf(stderr, "Invalid instruction on line %d\n", line_number);
            fclose(file);
            return EXIT_FAILURE;
        }

        line_number++;
    }

    fclose(file);
    return EXIT_SUCCESS;
}
