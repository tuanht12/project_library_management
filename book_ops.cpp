#include "book_ops.h"

#include <stdio.h>

#include "books.h"
#include "configs.h"
#include "datetime_utils.h"
#include "users.h"
#include "utils.h"

int BORROW_CARD_IDS[MAX_BORROW_RECORDS];
int BORROW_USER_IDS[MAX_BORROW_RECORDS];
int BORROW_DATES[MAX_BORROW_RECORDS][3];
int EXPECTED_RETURN_DATES[MAX_BORROW_RECORDS][3];
int ACTUAL_RETURN_DATES[MAX_BORROW_RECORDS][3];
int BORROWED_ISBNS[MAX_BORROW_RECORDS][MAX_BORROWED_BOOKS];
long LATE_PENALTIES[MAX_BORROW_RECORDS];
long LOST_PENALTIES[MAX_BORROW_RECORDS][MAX_BORROWED_BOOKS];

void initialize_one_borrow_card(int index) {
    BORROW_CARD_IDS[index] = 0;
    BORROW_USER_IDS[index] = 0;
    BORROW_DATES[index][0] = 0;
    BORROW_DATES[index][1] = 0;
    BORROW_DATES[index][2] = 0;
    EXPECTED_RETURN_DATES[index][0] = 0;
    EXPECTED_RETURN_DATES[index][1] = 0;
    EXPECTED_RETURN_DATES[index][2] = 0;
    ACTUAL_RETURN_DATES[index][0] = 0;
    ACTUAL_RETURN_DATES[index][1] = 0;
    ACTUAL_RETURN_DATES[index][2] = 0;
    LATE_PENALTIES[index] = 0;
    for (int i = 0; i < MAX_BORROWED_BOOKS; i++) {
        BORROWED_ISBNS[index][i] = 0;
        LOST_PENALTIES[index][i] = 0;
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
        BORROW_CARD_IDS[i] = i + 1;
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
        BORROW_USER_IDS[i] = test_borrow_user_ids[i];
        BORROW_DATES[i][0] = test_borrow_dates[i][0];
        BORROW_DATES[i][1] = test_borrow_dates[i][1];
        BORROW_DATES[i][2] = test_borrow_dates[i][2];
        EXPECTED_RETURN_DATES[i][0] = test_expected_return_dates[i][0];
        EXPECTED_RETURN_DATES[i][1] = test_expected_return_dates[i][1];
        EXPECTED_RETURN_DATES[i][2] = test_expected_return_dates[i][2];
        ACTUAL_RETURN_DATES[i][0] = test_actual_return_dates[i][0];
        ACTUAL_RETURN_DATES[i][1] = test_actual_return_dates[i][1];
        ACTUAL_RETURN_DATES[i][2] = test_actual_return_dates[i][2];
        for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
            BORROWED_ISBNS[i][j] = test_borrowed_isbns[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        // Calculate late penalties
        if (ACTUAL_RETURN_DATES[i][0] != 0) {
            long late_penalty = calculate_late_penalty(
                BORROW_DATES[i][0], BORROW_DATES[i][1], BORROW_DATES[i][2],
                ACTUAL_RETURN_DATES[i][0], ACTUAL_RETURN_DATES[i][1],
                ACTUAL_RETURN_DATES[i][2]);
            LATE_PENALTIES[i] = late_penalty;

        } else {
            LATE_PENALTIES[i] = 0;
        }

        // Calculate lost book penalties
        for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
            if (test_lost_flags[i][j] == 1) {
                int isbn = BORROWED_ISBNS[i][j];
                if (isbn == 0) {
                    break;
                }
                LOST_PENALTIES[i][j] = get_price_by_isbn(isbn) * 2;
            }
        }
    }
    printf("Đã khởi tạo 5 bản ghi mượn sách mẫu cho testing!\n");
}

void create_borrow_card() {
    int record_index = -1;
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_CARD_IDS[i] == 0) {
            record_index = i;
            BORROW_CARD_IDS[i] = i + 1;  // Assign a new record ID
            break;
        }
    }
    if (record_index == -1) {
        printf("Không thể tạo bản ghi mượn mới. Đã đạt giới hạn tối đa.\n");
        return;
    }

    printf("Nhập CMND người mượn: ");
    safe_scanf_int(BORROW_USER_IDS[record_index]);
    if (!is_existing_user(BORROW_USER_IDS[record_index])) {
        printf(
            "Người dùng với CMND %d không tồn tại. Vui lòng đăng ký "
            "trước.\n",
            BORROW_USER_IDS[record_index]);
        BORROW_CARD_IDS[record_index] = 0;  // Reset record ID
        return;
    }

    if (is_user_expired(BORROW_USER_IDS[record_index]) == 1) {
        printf("Tài khoản người dùng đã hết hạn. Không thể mượn sách.\n");
        BORROW_CARD_IDS[record_index] = 0;  // Reset record ID
        return;
    }
    printf("Tạo bản ghi mượn sách mới (ID: %d)\n",
           BORROW_CARD_IDS[record_index]);
    BORROW_DATES[record_index][0] = CURRENT_YEAR;
    BORROW_DATES[record_index][1] = CURRENT_MONTH;
    BORROW_DATES[record_index][2] = CURRENT_DAY;

    get_expiration_date(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY,
                        EXPECTED_RETURN_DATES[record_index][0],
                        EXPECTED_RETURN_DATES[record_index][1],
                        EXPECTED_RETURN_DATES[record_index][2]);

    ACTUAL_RETURN_DATES[record_index][0] = 0;
    ACTUAL_RETURN_DATES[record_index][1] = 0;
    ACTUAL_RETURN_DATES[record_index][2] = 0;

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
            BORROWED_ISBNS[record_index][book_count] = isbn;
            book_count++;
        } else {
            printf("Không thể mượn sách với ISBN %d. Vui lòng thử lại.\n",
                   isbn);
        }
    }
    if (book_count == 0) {
        printf("Không có sách nào được mượn. Hủy bản ghi mượn.\n");
        BORROW_CARD_IDS[record_index] = 0;  // Reset record ID
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
        if (BORROW_CARD_IDS[i] == card_id) {
            record_index = i;
            break;
        }
    }
    if (record_index == -1) {
        printf("Không tìm thấy bản ghi mượn với ID %d.\n", card_id);
        return;
    }

    if (ACTUAL_RETURN_DATES[record_index][0] != 0) {
        printf("Bản ghi mượn với ID %d đã được trả trước đó.\n", card_id);
        return;
    }

    for (int i = 0; i < MAX_BORROWED_BOOKS; i++) {
        int isbn = BORROWED_ISBNS[record_index][i];
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
            LOST_PENALTIES[record_index][i] = penalty;
            printf("Phí phạt mất sách: %ld VND\n", penalty);

        } else {
            return_book(isbn);  // Return the book to inventory
        }
    }

    LATE_PENALTIES[record_index] = calculate_late_penalty(
        BORROW_DATES[record_index][0], BORROW_DATES[record_index][1],
        BORROW_DATES[record_index][2], CURRENT_YEAR, CURRENT_MONTH,
        CURRENT_DAY);
    long late_penalty = LATE_PENALTIES[record_index];
    if (late_penalty > 0) {
        printf("Phí phạt trễ hạn: %ld VND\n", late_penalty);
    } else {
        printf("Không có phí phạt trễ hạn.\n");
    }
    ACTUAL_RETURN_DATES[record_index][0] = CURRENT_YEAR;
    ACTUAL_RETURN_DATES[record_index][1] = CURRENT_MONTH;
    ACTUAL_RETURN_DATES[record_index][2] = CURRENT_DAY;
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
        if (BORROW_CARD_IDS[i] == card_id) {
            record_index = i;
            break;
        }
    }
    if (record_index == -1) {
        printf("Không tìm thấy bản ghi mượn với ID %d.\n", card_id);
        return;
    }
    printf("Bản ghi mượn ID: %d\n", BORROW_CARD_IDS[record_index]);
    printf("CMND người mượn: %d\n", BORROW_USER_IDS[record_index]);
    get_date_string(date_str, BORROW_DATES[record_index][0],
                    BORROW_DATES[record_index][1],
                    BORROW_DATES[record_index][2]);
    printf("Ngày mượn: %s\n", date_str);
    get_date_string(date_str, EXPECTED_RETURN_DATES[record_index][0],
                    EXPECTED_RETURN_DATES[record_index][1],
                    EXPECTED_RETURN_DATES[record_index][2]);
    printf("Ngày dự kiến trả: %s\n", date_str);
    if (ACTUAL_RETURN_DATES[record_index][0] != 0) {
        get_date_string(date_str, ACTUAL_RETURN_DATES[record_index][0],
                        ACTUAL_RETURN_DATES[record_index][1],
                        ACTUAL_RETURN_DATES[record_index][2]);
        printf("Ngày trả thực tế: %s\n", date_str);
    } else {
        printf("Chưa trả sách.\n");
    }
    printf("Sách mượn:\n");
    for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
        int isbn = BORROWED_ISBNS[record_index][j];
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
        if (BORROW_CARD_IDS[i] != 0 && ACTUAL_RETURN_DATES[i][0] == 0) {
            print_a_borrow_record(BORROW_CARD_IDS[i]);
            printf("-----------------------------\n");
        }
    }
}
void print_all_borrow_records() {
    printf("\n===== Danh sách tất cả bản ghi mượn sách =====\n");
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_CARD_IDS[i] != 0) {
            print_a_borrow_record(BORROW_CARD_IDS[i]);
            printf("-----------------------------\n");
        }
    }
}

void print_finished_returns() {
    printf("\n===== Danh sách bản ghi trả sách =====\n");
    char date_str[11];

    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_CARD_IDS[i] != 0 && ACTUAL_RETURN_DATES[i][0] != 0) {
            long total_penalty = 0;
            printf("Bản ghi mượn ID: %d\n", BORROW_CARD_IDS[i]);
            printf("CMND người mượn: %d\n", BORROW_USER_IDS[i]);
            get_date_string(date_str, BORROW_DATES[i][0], BORROW_DATES[i][1],
                            BORROW_DATES[i][2]);
            printf("Ngày mượn: %s\n", date_str);
            get_date_string(date_str, EXPECTED_RETURN_DATES[i][0],
                            EXPECTED_RETURN_DATES[i][1],
                            EXPECTED_RETURN_DATES[i][2]);
            printf("Ngày dự kiến trả: %s\n", date_str);
            get_date_string(date_str, ACTUAL_RETURN_DATES[i][0],
                            ACTUAL_RETURN_DATES[i][1],
                            ACTUAL_RETURN_DATES[i][2]);
            printf("Ngày trả thực tế: %s\n", date_str);
            printf("Sách mượn:\n");
            for (int j = 0; j < MAX_BORROWED_BOOKS; j++) {
                int isbn = BORROWED_ISBNS[i][j];
                if (isbn == 0) {
                    break;
                }
                printf(" - ISBN: %d", isbn);
                if (LOST_PENALTIES[i][j] > 0) {
                    printf(" (Mất sách, Phí phạt: %ld VND)",
                           LOST_PENALTIES[i][j]);
                    total_penalty += LOST_PENALTIES[i][j];
                }
                printf("\n");
            }
            printf("Phí phạt trễ hạn: %ld VND\n", LATE_PENALTIES[i]);
            printf("Tổng phí phạt: %ld VND\n",
                   total_penalty + LATE_PENALTIES[i]);
            printf("-----------------------------\n");
        }
    }
}
