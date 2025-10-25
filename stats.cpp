#include <stdio.h>
#include <string.h>

#include "books.h"
#include "users.h"
void print_total_number_of_books() {
    int total_books = 0;
    for (int i = 0; i < 100; i++) {
        total_books += BOOKCOUNTS[i];
    }
    printf("Tổng số  cuốn sách trong thư viện: %d cuốn.\n", total_books);
}

void print_number_books_by_genre() {
    char current_genre[100];

    for (int i = 0; i < 100; i++) {
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
    for (int i = 0; i < 100; i++) {
        if (USERIDS[i] > 0) user_counts++;
    }
    printf("Số lượng người dùng hiện tại là: %d người.", user_counts);
}

void print_number_users_by_gender() {
    int num_male = 0;
    int num_female = 0;
    for (int i = 0; i < 100; i++) {
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