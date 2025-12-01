#include "csv_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_ops.h"
#include "books.h"
#include "configs.h"
#include "users.h"

void write_books_to_csv() {
    FILE* file = fopen(BOOKS_CSV_PATH, "w");
    if (file == NULL) {
        printf("Không thể mở file %s để ghi dữ liệu.\n", BOOKS_CSV_PATH);
        return;
    }

    // Ghi tiêu đề cột
    fprintf(file, "isbn%sname%sauthor%spublisher%syear%sgenre%sprice%scount\n",
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER);

    // Ghi dữ liệu sách
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn != 0) {
            fprintf(file, 
                    "%d%s"
                    "%s%s"
                    "%s%s"
                    "%s%s"
                    "%d%s"
                    "%s%s"
                    "%ld%s"
                    "%d\n",
                    BOOKS[i].isbn, CSV_DELIMITER,
                    BOOKS[i].name, CSV_DELIMITER,
                    BOOKS[i].author, CSV_DELIMITER,
                    BOOKS[i].publisher, CSV_DELIMITER,
                    BOOKS[i].year, CSV_DELIMITER,
                    BOOKS[i].genre, CSV_DELIMITER,
                    BOOKS[i].price, CSV_DELIMITER,
                    BOOKS[i].count);
        } else {
            break;  // Dừng khi gặp slot trống
        }
    }
    fclose(file);
    printf("Đã ghi dữ liệu sách vào file %s thành công.\n", BOOKS_CSV_PATH);
}

int read_books_from_csv() {
    FILE* file = fopen(BOOKS_CSV_PATH, "r");
    if (file == NULL) {
        printf("File %s không tồn tại. Bỏ qua việc đọc dữ liệu sách.\n",
               BOOKS_CSV_PATH);
        return 0;
    }

    char line[CSV_BUFFER_SIZE];
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
    return index;
}

void write_users_to_csv() {
    FILE* file = fopen(USERS_CSV_PATH, "w");
    if (file == NULL) {
        printf("Không thể mở file %s để ghi dữ liệu.\n", USERS_CSV_PATH);
        return;
    }

    // Ghi tiêu đề cột
    fprintf(file,
            "id%sname%sgender%semail%saddress%sbirth_year%sbirth_month%sbirth_"
            "day%screation_year%screation_month%screation_day%sexp_year%sexp_"
            "month%sexp_day\n",
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER);

    // Ghi dữ liệu người dùng
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id != 0) {
            fprintf(file,
                    "%d%s"
                    "%s%s"
                    "%d%s"
                    "%s%s"
                    "%s%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d\n",
                    USERS[i].id, CSV_DELIMITER,
                    USERS[i].name, CSV_DELIMITER,
                    USERS[i].gender, CSV_DELIMITER,
                    USERS[i].email, CSV_DELIMITER,
                    USERS[i].address, CSV_DELIMITER,
                    USERS[i].birthdate[0], CSV_DELIMITER,
                    USERS[i].birthdate[1], CSV_DELIMITER,
                    USERS[i].birthdate[2], CSV_DELIMITER,
                    USERS[i].creation_date[0], CSV_DELIMITER,
                    USERS[i].creation_date[1], CSV_DELIMITER,
                    USERS[i].creation_date[2], CSV_DELIMITER,
                    USERS[i].expiration_date[0], CSV_DELIMITER,
                    USERS[i].expiration_date[1], CSV_DELIMITER,
                    USERS[i].expiration_date[2]);
        } else {
            break;  // Dừng khi gặp slot trống
        }
    }
    fclose(file);
    printf("Đã ghi dữ liệu người dùng vào file %s thành công.\n",
           USERS_CSV_PATH);
}

int read_users_from_csv() {
    FILE* file = fopen(USERS_CSV_PATH, "r");
    if (file == NULL) {
        printf("File %s không tồn tại. Bỏ qua việc đọc dữ liệu người dùng.\n",
               USERS_CSV_PATH);
        return 0;
    }

    char line[CSV_BUFFER_SIZE];
    // Bỏ qua dòng tiêu đề
    fgets(line, sizeof(line), file);

    initialize_user_data();  // Khởi tạo lại dữ liệu người dùng

    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL && index < MAX_USERS) {
        char* token = strtok(line, CSV_DELIMITER);
        if (token != NULL) {
            USERS[index].id = atoi(token);

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;
                strncpy(USERS[index].name, token, MAX_STR_LEN);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                USERS[index].gender = atoi(token);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;
                strncpy(USERS[index].email, token, MAX_STR_LEN);
            }

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) {
                token[strcspn(token, "\n")] = 0;
                strncpy(USERS[index].address, token, MAX_STR_LEN);
            }

            // Đọc ngày sinh
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].birthdate[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].birthdate[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].birthdate[2] = atoi(token);

            // Đọc ngày tạo
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].creation_date[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].creation_date[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].creation_date[2] = atoi(token);

            // Đọc ngày hết hạn
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].expiration_date[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].expiration_date[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) USERS[index].expiration_date[2] = atoi(token);

            index++;
        }
    }
    fclose(file);
    printf("Đã đọc dữ liệu %d người dùng từ file %s thành công.\n", index,
           USERS_CSV_PATH);

    return index;
}

void write_borrows_to_csv() {
    FILE* file = fopen(BORROWS_CSV_PATH, "w");
    if (file == NULL) {
        printf("Không thể mở file %s để ghi dữ liệu.\n", BORROWS_CSV_PATH);
        return;
    }

    // Ghi tiêu đề cột
    fprintf(file,
            "card_id%suser_id%sborrow_year%sborrow_month%sborrow_day%sexp_"
            "year%sexp_month%sexp_day%sactual_year%sactual_month%sactual_day%s"
            "isbns%slate_penalty%slost_penalties\n",
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER, CSV_DELIMITER,
            CSV_DELIMITER);

    // Ghi dữ liệu phiếu mượn
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id != 0) {
            fprintf(file, 
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s"
                    "%d%s",
                    BORROW_RECORDS[i].card_id, CSV_DELIMITER,
                    BORROW_RECORDS[i].user_id, CSV_DELIMITER,
                    BORROW_RECORDS[i].borrow_date[0], CSV_DELIMITER,
                    BORROW_RECORDS[i].borrow_date[1], CSV_DELIMITER,
                    BORROW_RECORDS[i].borrow_date[2], CSV_DELIMITER,
                    BORROW_RECORDS[i].expected_return_date[0], CSV_DELIMITER,
                    BORROW_RECORDS[i].expected_return_date[1], CSV_DELIMITER,
                    BORROW_RECORDS[i].expected_return_date[2], CSV_DELIMITER,
                    BORROW_RECORDS[i].actual_return_date[0], CSV_DELIMITER,
                    BORROW_RECORDS[i].actual_return_date[1], CSV_DELIMITER,
                    BORROW_RECORDS[i].actual_return_date[2], CSV_DELIMITER);

            // Ghi danh sách ISBN (phân cách bằng dấu chấm phẩy)
            int has_isbn = 0;
            for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
                if (BORROW_RECORDS[i].borrowed_isbns[j] != 0) {
                    if (has_isbn) fprintf(file, CSV_SUB_DELIMITER);
                    fprintf(file, "%d", BORROW_RECORDS[i].borrowed_isbns[j]);
                    has_isbn = 1;
                }
            }
            fprintf(file, "%s%ld%s", CSV_DELIMITER,
                    BORROW_RECORDS[i].late_penalty, CSV_DELIMITER);

            // Ghi danh sách phí phạt mất sách (phân cách bằng dấu chấm phẩy)
            int has_penalty = 0;
            for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
                if (BORROW_RECORDS[i].borrowed_isbns[j] != 0) {
                    if (has_penalty) fprintf(file, CSV_SUB_DELIMITER);
                    fprintf(file, "%ld", BORROW_RECORDS[i].lost_penalties[j]);
                    has_penalty = 1;
                }
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    printf("Đã ghi dữ liệu phiếu mượn vào file %s thành công.\n",
           BORROWS_CSV_PATH);
}

int read_borrows_from_csv() {
    FILE* file = fopen(BORROWS_CSV_PATH, "r");
    if (file == NULL) {
        printf("File %s không tồn tại. Bỏ qua việc đọc dữ liệu phiếu mượn.\n",
               BORROWS_CSV_PATH);
        return 0;
    }

    char line[CSV_BUFFER_SIZE * 2];
    // Bỏ qua dòng tiêu đề
    fgets(line, sizeof(line), file);

    initialize_borrow_data();  // Khởi tạo lại dữ liệu phiếu mượn

    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL &&
           index < MAX_BORROW_RECORDS) {
        char* token = strtok(line, CSV_DELIMITER);
        if (token != NULL) {
            BORROW_RECORDS[index].card_id = atoi(token);

            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) BORROW_RECORDS[index].user_id = atoi(token);

            // Đọc ngày mượn
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].borrow_date[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].borrow_date[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].borrow_date[2] = atoi(token);

            // Đọc ngày dự kiến trả
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].expected_return_date[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].expected_return_date[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].expected_return_date[2] = atoi(token);

            // Đọc ngày trả thực tế
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].actual_return_date[0] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].actual_return_date[1] = atoi(token);
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL)
                BORROW_RECORDS[index].actual_return_date[2] = atoi(token);

            // Đọc danh sách ISBN
            token = strtok(NULL, CSV_DELIMITER);
            char raw_isbns[CSV_BUFFER_SIZE];
            if (token != NULL) {
                strcpy(raw_isbns, token);
                raw_isbns[strcspn(raw_isbns, "\n")] = 0;
            }

            // Đọc phí phạt trễ
            token = strtok(NULL, CSV_DELIMITER);
            if (token != NULL) BORROW_RECORDS[index].late_penalty = atol(token);

            // Đọc danh sách phí phạt mất sách
            token = strtok(NULL, CSV_DELIMITER);
            char raw_penalties[CSV_BUFFER_SIZE];
            if (token != NULL) {
                strcpy(raw_penalties, token);
                raw_penalties[strcspn(raw_penalties, "\n")] = 0;
            }

            // Xử lý danh sách ISBN
            char* isbn_token = strtok(raw_isbns, CSV_SUB_DELIMITER);
            int isbn_index = 0;
            while (isbn_token != NULL && isbn_index < MAX_BORROWED_BOOKS) {
                BORROW_RECORDS[index].borrowed_isbns[isbn_index] =
                    atoi(isbn_token);
                isbn_token = strtok(NULL, CSV_SUB_DELIMITER);
                isbn_index++;
            }

            // Xử lý danh sách phí phạt mất sách
            char* penalty_token = strtok(raw_penalties, CSV_SUB_DELIMITER);
            int penalty_index = 0;
            while (penalty_token != NULL &&
                   penalty_index < MAX_BORROWED_BOOKS) {
                BORROW_RECORDS[index].lost_penalties[penalty_index] =
                    atol(penalty_token);
                penalty_token = strtok(NULL, CSV_SUB_DELIMITER);
                penalty_index++;
            }

            index++;
        }
    }
    fclose(file);
    printf("Đã đọc dữ liệu %d phiếu mượn từ file %s thành công.\n", index,
           BORROWS_CSV_PATH);
    return index;
}
