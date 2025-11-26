#include "csv_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "books.h"
#include "configs.h"

void write_books_to_csv() {
    FILE* file = fopen(BOOKS_CSV_PATH, "w");
    if (file == NULL) {
        printf("Không thể mở file %s để ghi dữ liệu.\n", BOOKS_CSV_PATH);
        return;
    }

    // Ghi tiêu đề cột
    fprintf(file, "ID%sTitle%sAuthor%sPublisher%sYear%sQuantity\n",
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER);

    // Ghi dữ liệu sách
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn != 0) {
            fprintf(file, "%d%s%s%s%s%s%s%s%d%s%d\n", BOOKS[i].isbn,
                    CSV_DELIMITER, BOOKS[i].name, CSV_DELIMITER,
                    BOOKS[i].author, CSV_DELIMITER, BOOKS[i].publisher,
                    CSV_DELIMITER, BOOKS[i].year, CSV_DELIMITER,
                    BOOKS[i].count);
        } else {
            break;  // Dừng khi gặp slot trống
        }
    }
    fclose(file);
    printf("Đã ghi dữ liệu sách vào file %s thành công.\n", BOOKS_CSV_PATH);
}

void read_books_from_csv() {
    FILE* file = fopen(BOOKS_CSV_PATH, "r");
    if (file == NULL) {
        printf("Không thể mở file %s để đọc dữ liệu.\n", BOOKS_CSV_PATH);
        return;
    }

    char line[512];
    // Bỏ qua dòng tiêu đề
    fgets(line, sizeof(line), file);

    initialize_book_data();  // Khởi tạo lại dữ liệu sách

    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL && index < MAX_BOOKS) {
        char* token = strtok(line, CSV_DELIMITER);
        if (token != NULL) {
            BOOKS[index].isbn = atoi(token);

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;  // Xóa ký tự xuống dòng
                strncpy(BOOKS[index].name, token, MAX_STR_LEN);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;  // Xóa ký tự xuống dòng
                strncpy(BOOKS[index].author, token, MAX_STR_LEN);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;  // Xóa ký tự xuống dòng
                strncpy(BOOKS[index].publisher, token, MAX_STR_LEN);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                BOOKS[index].year = atoi(token);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                BOOKS[index].count = atoi(token);
            }

            index++;
        }
    }
    fclose(file);
    printf("Đã đọc dữ liệu %d sách từ file %s thành công.\n", index,
           BOOKS_CSV_PATH);
}
