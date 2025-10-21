#include <stdio.h>
#include <string.h>

void cleanup_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safe_input_str(char buffer[100], int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void safe_scanf_int(int& value) {
    scanf("%d", &value);
    cleanup_input_buffer();
}
