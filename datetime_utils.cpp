#include "datetime_utils.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <iostream>

#include "utils.h"
int CURRENT_YEAR;
int CURRENT_MONTH;
int CURRENT_DAY;

void initialize_current_date() {
    char time_str[26];
    time_t current_time = time(NULL);
    ctime_r(&current_time, time_str);

    char month_str[4];
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    month_str[0] = time_str[4];
    month_str[1] = time_str[5];
    month_str[2] = time_str[6];
    month_str[3] = '\0';
    int month = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_str, months[i]) == 0) {
            month = i + 1;
            break;
        }
    }

    int day = 0;
    char day_str[3];
    day_str[0] = time_str[8];
    day_str[1] = time_str[9];
    day_str[2] = '\0';
    day = atoi(day_str);

    char year_str[5];
    year_str[0] = time_str[20];
    year_str[1] = time_str[21];
    year_str[2] = time_str[22];
    year_str[3] = time_str[23];
    year_str[4] = '\0';
    int year = atoi(year_str);
    printf("Current Date: %02d/%02d/%04d\n", day, month, year);
    CURRENT_YEAR = year;
    CURRENT_MONTH = month;
    CURRENT_DAY = day;
}

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
    cleanup_input_buffer();
    int is_valid = 0;
    while (!is_valid) {
        if (check_valid_date(year, month, day)) {
            is_valid = 1;
        } else {
            printf("Ngày không hợp lệ. Vui lòng nhập lại (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &day, &month, &year);
            cleanup_input_buffer();
        }
    }
}

void get_date_string(char date_str[11], int year, int month, int day) {
    snprintf(date_str, 11, "%02d/%02d/%04d", day, month, year);
}

void get_expected_return_date(int borrow_year, int borrow_month, int borrow_day,
                              int& return_year, int& return_month,
                              int& return_day) {
    // Add 7 days
    return_day = borrow_day + 7;
    return_month = borrow_month;
    return_year = borrow_year;

    // Days in each month
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year in February
    if (borrow_month == 2) {
        if (check_leap_year(borrow_year)) {
            days_in_month[1] = 29;
        }
    }

    // Adjust day and month/year if day exceeds month length
    if (return_day > days_in_month[borrow_month - 1]) {
        return_day -= days_in_month[borrow_month - 1];
        return_month += 1;
        if (return_month > 12) {
            return_month = 1;
            return_year += 1;
        }
    }
}

int calculate_days_between(int from_year, int from_month, int from_day,
                           int to_year, int to_month, int to_day) {
    if (from_year > to_year ||
        (from_year == to_year && from_month > to_month) ||
        (from_year == to_year && from_month == to_month && from_day > to_day)) {
        printf("Invalid date range for difference calculation.\n");
        return 0;
    }
    long total_days = 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int year = from_year; year < to_year; year++) {
        total_days += 365;
        if (check_leap_year(year)) {
            total_days += 1;
        }
    }

    for (int month = 1; month < from_month; month++) {
        total_days -= days_in_month[month - 1];
    }
    total_days -= from_day;

    for (int month = 1; month < to_month; month++) {
        total_days += days_in_month[month - 1];
    }
    total_days += to_day;

    return total_days;
}
