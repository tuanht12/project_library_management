#include "utils.h"

#include <stdio.h>
#include <string.h>

#include "configs.h"
void cleanup_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void safe_input_str(char buffer[MAX_STR_LEN], int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void safe_scanf_int(int& value) {
    scanf("%d", &value);
    cleanup_input_buffer();
}
int ask_to_edit_field() {
    printf(
        "Bạn muốn thay đổi không? Nhấn Enter để bỏ qua, gõ 'y' để thay đổi: ");
    while (1) {
        char choice[10];
        safe_input_str(choice, sizeof(choice));
        if (strlen(choice) == 0) {
            return 0;
        } else if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0) {
            return 1;
        } else {
            printf(
                "Lựa chọn không hợp lệ. Vui lòng nhấn Enter để bỏ qua, gõ 'y' "
                "để thay đổi: ");
        }
    }
}
