#include <stdio.h>
#include <string.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void input_str(char buffer[100], int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character
}
