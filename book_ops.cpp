#include "book_ops.h"

#include <stdio.h>
#include <string.h>

#include "books.h"
#include "configs.h"
#include "datetime_utils.h"
#include "users.h"
#include "utils.h"

BorrowRecord BORROW_RECORDS[MAX_BORROW_RECORDS];

void initialize_one_borrow_card(int index) {
    BORROW_RECORDS[index].card_id = 0;
    BORROW_RECORDS[index].user_id = 0;
    BORROW_RECORDS[index].borrow_date[0] = 0;
    BORROW_RECORDS[index].borrow_date[1] = 0;
    BORROW_RECORDS[index].borrow_date[2] = 0;
    BORROW_RECORDS[index].expected_return_date[0] = 0;
    BORROW_RECORDS[index].expected_return_date[1] = 0;
    BORROW_RECORDS[index].expected_return_date[2] = 0;
    BORROW_RECORDS[index].actual_return_date[0] = 0;
    BORROW_RECORDS[index].actual_return_date[1] = 0;
    BORROW_RECORDS[index].actual_return_date[2] = 0;
    BORROW_RECORDS[index].late_penalty = 0;
    for (int i = 0; i < MAX_BORROWED_BOOKS; i++) {
        BORROW_RECORDS[index].borrowed_isbns[i] = 0;
        BORROW_RECORDS[index].lost_penalties[i] = 0;
    }
}

void initialize_borrow_data() {
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        initialize_one_borrow_card(i);
    }
}

void initialize_test_borrows() {
    // Sample borrow cards
    for (int i = 0; i < 5; i++) {
        BORROW_RECORDS[i].card_id = i + 1;
    }
    int test_borrow_user_ids[5] = {123456, 234567, 345678, 456789, 567890};
    int test_borrow_dates[5][3] = {{2024, 5, 1},
                                   {2024, 5, 3},
                                   {2024, 4, 20},
                                   {2024, 3, 15},
                                   {2024, 2, 28}};
    int test_expected_return_dates[5][3] = {{2024, 5, 8},
                                            {2024, 5, 10},
                                            {2024, 4, 27},
                                            {2024, 3, 22},
                                            {2024, 3, 6}};
    int test_actual_return_dates[5][3] = {
        {2024, 5, 7}, {0, 0, 0}, {2024, 4, 30}, {2024, 3, 25}, {0, 0, 0}};
    int test_borrowed_isbns[5][10] = {
        {1001, 1002},  // User 1001 borrowed books with ISBNs 1001 and 1002
        {1003},        // User 1002 borrowed book with ISBN 1003
        {1004, 1005,
         1006},       // User 1003 borrowed books with ISBNs 1004,1005,1006
        {1007},       // User 1004 borrowed book with ISBN 1007
        {1008, 1009}  // User 1005 borrowed books with ISBNs 1008 and 1009
    };
    int test_lost_flags[5][10] = {
        {0, 0},     // No lost books for user 1
        {0},        // No lost books for user 2
        {0, 1, 0},  // User 3 lost book with ISBN 1005
        {0},        // No lost books for user 4
        {1, 0}      // User 5 lost book with ISBN 1008
    };

    for (int i = 0; i < 5; i++) {
        BORROW_RECORDS[i].user_id = test_borrow_user_ids[i];
        BORROW_RECORDS[i].borrow_date[0] = test_borrow_dates[i][0];
        BORROW_RECORDS[i].borrow_date[1] = test_borrow_dates[i][1];
        BORROW_RECORDS[i].borrow_date[2] = test_borrow_dates[i][2];
        BORROW_RECORDS[i].expected_return_date[0] =
            test_expected_return_dates[i][0];
        BORROW_RECORDS[i].expected_return_date[1] =
            test_expected_return_dates[i][1];
        BORROW_RECORDS[i].expected_return_date[2] =
            test_expected_return_dates[i][2];
        BORROW_RECORDS[i].actual_return_date[0] =
            test_actual_return_dates[i][0];
        BORROW_RECORDS[i].actual_return_date[1] =
            test_actual_return_dates[i][1];
        BORROW_RECORDS[i].actual_return_date[2] =
            test_actual_return_dates[i][2];
        for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
            BORROW_RECORDS[i].borrowed_isbns[j] = test_borrowed_isbns[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        // Calculate late penalties
        if (BORROW_RECORDS[i].actual_return_date[0] != 0) {
            long late_penalty =
                calculate_late_penalty(BORROW_RECORDS[i].borrow_date[0],
                                       BORROW_RECORDS[i].borrow_date[1],
                                       BORROW_RECORDS[i].borrow_date[2],
                                       BORROW_RECORDS[i].actual_return_date[0],
                                       BORROW_RECORDS[i].actual_return_date[1],
                                       BORROW_RECORDS[i].actual_return_date[2]);
            BORROW_RECORDS[i].late_penalty = late_penalty;

        } else {
            BORROW_RECORDS[i].late_penalty = 0;
        }

        // Calculate lost book penalties
        for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
            if (test_lost_flags[i][j] == 1) {
                int isbn = BORROW_RECORDS[i].borrowed_isbns[j];
                if (isbn == 0) {
                    break;
                }
                BORROW_RECORDS[i].lost_penalties[j] =
                    get_price_by_isbn(isbn) * 2;
            }
        }
    }
    printf("Đã khởi tạo 5 bản ghi mượn sách mẫu cho testing!\n");
}

void create_borrow_card() {
    int record_index = -1;
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id == 0) {
            record_index = i;
            BORROW_RECORDS[i].card_id = i + 1;  // Assign a new record ID
            break;
        }
    }
    if (record_index == -1) {
        printf("Không thể tạo bản ghi mượn mới. Đã đạt giới hạn tối đa.\n");
        return;
    }

    printf("Nhập CMND người mượn: ");
    safe_scanf_int(BORROW_RECORDS[record_index].user_id);
    if (!is_existing_user(BORROW_RECORDS[record_index].user_id)) {
        printf(
            "Người dùng với CMND %d không tồn tại. Vui lòng đăng ký "
            "trước.\n",
            BORROW_RECORDS[record_index].user_id);
        BORROW_RECORDS[record_index].card_id = 0;  // Reset record ID
        return;
    }

    if (is_user_expired(BORROW_RECORDS[record_index].user_id) == 1) {
        printf("Tài khoản người dùng đã hết hạn. Không thể mượn sách.\n");
        BORROW_RECORDS[record_index].card_id = 0;  // Reset record ID
        return;
    }
    printf("Tạo bản ghi mượn sách mới (ID: %d)\n",
           BORROW_RECORDS[record_index].card_id);
    BORROW_RECORDS[record_index].borrow_date[0] = CURRENT_YEAR;
    BORROW_RECORDS[record_index].borrow_date[1] = CURRENT_MONTH;
    BORROW_RECORDS[record_index].borrow_date[2] = CURRENT_DAY;

    get_expiration_date(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY,
                        BORROW_RECORDS[record_index].expected_return_date[0],
                        BORROW_RECORDS[record_index].expected_return_date[1],
                        BORROW_RECORDS[record_index].expected_return_date[2]);

    BORROW_RECORDS[record_index].actual_return_date[0] = 0;
    BORROW_RECORDS[record_index].actual_return_date[1] = 0;
    BORROW_RECORDS[record_index].actual_return_date[2] = 0;

    printf("Nhập ISBN các sách mượn (nhập 0 để kết thúc):\n");
    int book_count = 0;
    while (book_count < MAX_BORROWED_BOOKS) {
        int isbn;
        printf("ISBN sách thứ %d: ", book_count + 1);
        safe_scanf_int(isbn);
        if (isbn == 0) {
            break;
        }
        int borrow_result = borrow_book(isbn);
        if (borrow_result == 1) {
            BORROW_RECORDS[record_index].borrowed_isbns[book_count] = isbn;
            book_count++;
        } else {
            printf("Không thể mượn sách với ISBN %d. Vui lòng thử lại.\n",
                   isbn);
        }
    }
    if (book_count == 0) {
        printf("Không có sách nào được mượn. Hủy bản ghi mượn.\n");
        BORROW_RECORDS[record_index].card_id = 0;  // Reset record ID
        return;
    }
    printf("Tạo bản ghi mượn sách thành công!\n");
}

void create_return_card() {
    printf("Nhập ID phiếu mượn để trả sách: ");
    int card_id;
    safe_scanf_int(card_id);
    int record_index = -1;
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id == card_id) {
            record_index = i;
            break;
        }
    }
    if (record_index == -1) {
        printf("Không tìm thấy bản ghi mượn với ID %d.\n", card_id);
        return;
    }

    if (BORROW_RECORDS[record_index].actual_return_date[0] != 0) {
        printf("Bản ghi mượn với ID %d đã được trả trước đó.\n", card_id);
        return;
    }

    for (int i = 0; i < MAX_BORROWED_BOOKS; i++) {
        int isbn = BORROW_RECORDS[record_index].borrowed_isbns[i];
        if (isbn == 0) {
            break;
        }
        printf(
            "Trả sách với ISBN %d. Sách có bị mất không? (1: Có, 0: "
            "Không): ",
            isbn);
        int is_lost;
        while (1) {
            safe_scanf_int(is_lost);
            if (is_lost == 0 || is_lost == 1) {
                break;
            } else {
                printf(
                    "Lựa chọn không hợp lệ. Vui lòng nhập lại (1 hoặc "
                    "0): ");
            }
        }
        if (is_lost == 1) {
            printf("Sách với ISBN %d được đánh dấu là mất.\n", isbn);
            long penalty = calculate_lost_penalty_by_isbn(isbn);
            BORROW_RECORDS[record_index].lost_penalties[i] = penalty;
            printf("Phí phạt mất sách: %ld VND\n", penalty);

        } else {
            return_book(isbn);  // Return the book to inventory
        }
    }

    BORROW_RECORDS[record_index].late_penalty =
        calculate_late_penalty(BORROW_RECORDS[record_index].borrow_date[0],
                               BORROW_RECORDS[record_index].borrow_date[1],
                               BORROW_RECORDS[record_index].borrow_date[2],
                               CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
    long late_penalty = BORROW_RECORDS[record_index].late_penalty;
    if (late_penalty > 0) {
        printf("Phí phạt trễ hạn: %ld VND\n", late_penalty);
    } else {
        printf("Không có phí phạt trễ hạn.\n");
    }
    BORROW_RECORDS[record_index].actual_return_date[0] = CURRENT_YEAR;
    BORROW_RECORDS[record_index].actual_return_date[1] = CURRENT_MONTH;
    BORROW_RECORDS[record_index].actual_return_date[2] = CURRENT_DAY;
    printf("Đã tạo bản ghi trả sách thành công!\n");
}

long calculate_late_penalty(int borrow_year, int borrow_month, int borrow_day,
                            int return_year, int return_month, int return_day) {
    int days_between =
        calculate_days_between(borrow_year, borrow_month, borrow_day,
                               return_year, return_month, return_day);
    if (days_between > MAX_BORROW_DAYS) {
        return (days_between - MAX_BORROW_DAYS) * LATE_FINE_PER_DAY;
    } else {
        return 0;
    }
}

long calculate_lost_penalty_by_isbn(int isbn) {
    return get_price_by_isbn(isbn) * LOST_PENALTY_FACTOR;
}
void print_a_borrow_record(int card_id) {
    int record_index = -1;
    char date_str[11];
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id == card_id) {
            record_index = i;
            break;
        }
    }
    if (record_index == -1) {
        printf("Không tìm thấy bản ghi mượn với ID %d.\n", card_id);
        return;
    }
    printf("Bản ghi mượn ID: %d\n", BORROW_RECORDS[record_index].card_id);
    printf("CMND người mượn: %d\n", BORROW_RECORDS[record_index].user_id);
    get_date_string(date_str, BORROW_RECORDS[record_index].borrow_date[0],
                    BORROW_RECORDS[record_index].borrow_date[1],
                    BORROW_RECORDS[record_index].borrow_date[2]);
    printf("Ngày mượn: %s\n", date_str);
    get_date_string(date_str,
                    BORROW_RECORDS[record_index].expected_return_date[0],
                    BORROW_RECORDS[record_index].expected_return_date[1],
                    BORROW_RECORDS[record_index].expected_return_date[2]);
    printf("Ngày dự kiến trả: %s\n", date_str);
    if (BORROW_RECORDS[record_index].actual_return_date[0] != 0) {
        get_date_string(date_str,
                        BORROW_RECORDS[record_index].actual_return_date[0],
                        BORROW_RECORDS[record_index].actual_return_date[1],
                        BORROW_RECORDS[record_index].actual_return_date[2]);
        printf("Ngày trả thực tế: %s\n", date_str);
    } else {
        printf("Chưa trả sách.\n");
    }
    printf("Sách mượn:\n");
    for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
        int isbn = BORROW_RECORDS[record_index].borrowed_isbns[j];
        if (isbn == 0) {
            break;
        }
        char book_name[MAX_STR_LEN];
        get_book_name_by_isbn(isbn, book_name);
        printf(" - ISBN: %d - Tên sách: %s\n", isbn, book_name);
    }
}

void print_unreturned_borrows() {
    printf("\n===== Danh sách bản ghi mượn chưa trả =====\n");
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id != 0 &&
            BORROW_RECORDS[i].actual_return_date[0] == 0) {
            print_a_borrow_record(BORROW_RECORDS[i].card_id);
            printf("-----------------------------\n");
        }
    }
}
void print_all_borrow_records() {
    printf("\n===== Danh sách tất cả bản ghi mượn sách =====\n");
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id != 0) {
            print_a_borrow_record(BORROW_RECORDS[i].card_id);
            printf("-----------------------------\n");
        }
    }
}

void print_finished_returns() {
    printf("\n===== Danh sách bản ghi trả sách =====\n");
    char date_str[11];

    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_RECORDS[i].card_id != 0 &&
            BORROW_RECORDS[i].actual_return_date[0] != 0) {
            long total_penalty = 0;
            printf("Bản ghi mượn ID: %d\n", BORROW_RECORDS[i].card_id);
            printf("CMND người mượn: %d\n", BORROW_RECORDS[i].user_id);
            get_date_string(date_str, BORROW_RECORDS[i].borrow_date[0],
                            BORROW_RECORDS[i].borrow_date[1],
                            BORROW_RECORDS[i].borrow_date[2]);
            printf("Ngày mượn: %s\n", date_str);
            get_date_string(date_str, BORROW_RECORDS[i].expected_return_date[0],
                            BORROW_RECORDS[i].expected_return_date[1],
                            BORROW_RECORDS[i].expected_return_date[2]);
            printf("Ngày dự kiến trả: %s\n", date_str);
            get_date_string(date_str, BORROW_RECORDS[i].actual_return_date[0],
                            BORROW_RECORDS[i].actual_return_date[1],
                            BORROW_RECORDS[i].actual_return_date[2]);
            printf("Ngày trả thực tế: %s\n", date_str);
            printf("Sách mượn:\n");
            for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
                int isbn = BORROW_RECORDS[i].borrowed_isbns[j];
                if (isbn == 0) {
                    break;
                }
                printf(" - ISBN: %d", isbn);
                if (BORROW_RECORDS[i].lost_penalties[j] > 0) {
                    printf(" (Mất sách, Phí phạt: %ld VND)",
                           BORROW_RECORDS[i].lost_penalties[j]);
                    total_penalty += BORROW_RECORDS[i].lost_penalties[j];
                }
                printf("\n");
            }
            printf("Phí phạt trễ hạn: %ld VND\n",
                   BORROW_RECORDS[i].late_penalty);
            printf("Tổng phí phạt: %ld VND\n",
                   total_penalty + BORROW_RECORDS[i].late_penalty);
            printf("-----------------------------\n");
        }
    }
}

void print_borrowed_books_by_username(char username[MAX_STR_LEN]) {
    int user_ids[MAX_USERS];
    int found = 0;

    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id != 0 && strcmp(USERS[i].name, username) == 0) {
            user_ids[found] = USERS[i].id;
            found++;
        }
    }
    if (found == 0) {
        printf("Không tìm thấy người dùng với tên '%s'.\n", username);
        return;
    }
    printf("\n===== Danh sách sách đã mượn của người dùng '%s' =====\n",
           username);
    int any_borrows = 0;
    for (int i = 0; i < found; i++) {
        int user_id = user_ids[i];
        for (int j = 0; j < MAX_BORROW_RECORDS; j++) {
            if (BORROW_RECORDS[j].user_id == user_id) {
                any_borrows = 1;
                print_a_borrow_record(BORROW_RECORDS[j].card_id);
                printf("-----------------------------\n");
            }
        }
    }
    if (!any_borrows) {
        printf("Người dùng '%s' chưa mượn sách nào.\n", username);
    }
}
