#include <stdio.h>

#include "utils.h"

// 48 months expiration from creation date
// Example: Creation Date: 2025-10-20 -> Expiration Date: 2029-10-20
void get_expiration_date(int creation_year, int creation_month,
                         int creation_day, int& exp_year, int& exp_month,
                         int& exp_day) {
    exp_year = creation_year + 4;
    exp_month = creation_month;
    exp_day = creation_day;

    if (creation_month == 2 && creation_day == 29) {
        bool exp_is_leap =
            (exp_year % 4 == 0 && exp_year % 100 != 0) || (exp_year % 400 == 0);
        if (!exp_is_leap) {
            exp_day = 28;
        }
    }
}

int check_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int check_valid_date(int year, int month, int day) {
    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;
    } else {
        int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Check for leap year in February
        if (month == 2) {
            if (check_leap_year(year)) {
                days_in_month[1] = 29;
            }
        }
        if (day > days_in_month[month - 1]) {
            return 0;
        }
    }
    return 1;
}

void input_date(int& year, int& month, int& day) {
    printf("Nhập ngày (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day, &month, &year);
    clear_input_buffer();
    int is_valid = 0;
    while (!is_valid) {
        if (check_valid_date(year, month, day)) {
            is_valid = 1;
        } else {
            printf("Ngày không hợp lệ. Vui lòng nhập lại (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &day, &month, &year);
            clear_input_buffer();
        }
    }
}

// Get a date string based on year, month, day
void get_date_string(char date_str[11], int year, int month, int day) {
    snprintf(date_str, 11, "%02d/%02d/%04d", day, month, year);
}
