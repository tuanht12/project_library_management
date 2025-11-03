#include "stats.h"

#include <stdio.h>
#include <string.h>

#include "book_ops.h"
#include "books.h"
#include "configs.h"
#include "datetime_utils.h"
#include "users.h"
void print_total_number_of_books() {
    int total_books = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        total_books += BOOKCOUNTS[i];
    }
    printf("Tổng số  cuốn sách trong thư viện: %d cuốn.\n", total_books);
}

void print_number_books_by_genre() {
    char current_genre[MAX_STR_LEN];

    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKCOUNTS[i] == 0) {
            continue;
        }
        strcpy(current_genre, BOOKGENRES[i]);
        int has_done = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(BOOKGENRES[j], current_genre) == 0) {
                has_done = 1;
                break;
            }
        }
        if (has_done) continue;

        int current_count = BOOKCOUNTS[i];
        for (int j = i + 1; j < 100; j++) {
            if (strcmp(BOOKGENRES[j], current_genre) == 0) {
                current_count += BOOKCOUNTS[j];
            }
        }
        printf("Số lượng sách thể loại %s: %d cuốn.\n", current_genre,
               current_count);
    }
}

void print_number_users() {
    int user_counts = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERIDS[i] > 0) user_counts++;
    }
    printf("Số lượng người dùng hiện tại là: %d người.", user_counts);
}

void print_number_users_by_gender() {
    int num_male = 0;
    int num_female = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERIDS[i] <= 0) continue;
        if (USER_GENDERS[i] == 0) {
            num_female++;
        } else {
            num_male++;
        }
    }
    printf("Số lượng người dùng NAM hiện tại là: %d người.\n", num_male);
    printf("Số lượng người dùng NỮ hiện tại là: %d người.\n", num_female);
}

void print_number_unreturned_books() {
    int num_unreturned_books = 0;
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_CARD_IDS[i] != 0 && ACTUAL_RETURN_DATES[i][0] == 0) {
            for (int j = 0; j < 10; j++) {
                if (BORROWED_ISBNS[i][j] == 0) {
                    break;
                }
                num_unreturned_books++;
            }
        }
    }
    printf("Số sách đang được mượn nhưng chưa trả là: %d cuốn.",
           num_unreturned_books);
}

void print_late_return_user(int user_id) {
    int num_late_days = 0;
    int max_late_borrow_card_id = 0;
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_USER_IDS[i] != user_id) continue;
        int days_between = calculate_days_between(
            BORROW_DATES[i][0], BORROW_DATES[i][1], BORROW_DATES[i][2],
            CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY);
        if (days_between > 7 and days_between - 7 > num_late_days) {
            num_late_days = days_between - 7;
            max_late_borrow_card_id = BORROW_CARD_IDS[i];
        }
    }

    if (num_late_days > 0) {
        char username[100];
        get_user_name_by_id(user_id, username);
        printf(
            "Người dùng %s - CMND %d quá hạn %d ngày cho phiếu mượn sách ID "
            "%d.\n",
            username, user_id, num_late_days, max_late_borrow_card_id);
    }
}

void print_current_late_users() {
    printf("Danh sách người dùng đang mượn sách quá hạn:\n");
    for (int i = 0; i < MAX_BORROW_RECORDS; i++) {
        if (BORROW_CARD_IDS[i] != 0 && ACTUAL_RETURN_DATES[i][0] == 0) {
            int found = 0;
            int current_uid = BORROW_USER_IDS[i];
            for (int j = 0; j < i; j++) {
                if (BORROW_USER_IDS[j] == current_uid) {
                    found = 1;
                    break;
                }
            }
            if (found) continue;
            print_late_return_user(current_uid);
        }
    }
}