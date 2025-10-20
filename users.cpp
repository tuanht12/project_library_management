#include <stdio.h>
#include <string.h>

#include <iostream>

#include "datetime_utils.h"
#include "utils.h"

// Define the global arrays

// CMND của người dùng
int USERIDS[100];

// Tên người dùng
char USERNAMES[100][100];

// Giới tính của người dùng, 0: Nữ, 1: Nam
int USER_GENDERS[100];

// Email của người dùng
char USER_EMAILS[100][100];

// Địa chỉ của người dùng
char USER_ADDRESSES[100][100];

// Ngày tạo tài khoản của người dùng
int USER_CREATION_DATES[100][3];

// Ngày hết hạn tài khoản của người dùng
int USER_EXPIRATION_DATES[100][3];

// Ngày sinh của người dùng
int USER_BIRTHDATES[100][3];

// Khởi tạo mảng người dùng
void initialize_user_data() {
    for (int i = 0; i < 100; i++) {
        USERIDS[i] = 0;
        USERNAMES[i][0] = '\0';
        USER_GENDERS[i] = -1;
        USER_EMAILS[i][0] = '\0';
        USER_ADDRESSES[i][0] = '\0';
        USER_CREATION_DATES[i][0] = 0;
        USER_CREATION_DATES[i][1] = 0;
        USER_CREATION_DATES[i][2] = 0;
        USER_EXPIRATION_DATES[i][0] = 0;
        USER_EXPIRATION_DATES[i][1] = 0;
        USER_EXPIRATION_DATES[i][2] = 0;
        USER_BIRTHDATES[i][0] = 0;
        USER_BIRTHDATES[i][1] = 0;
        USER_BIRTHDATES[i][2] = 0;
    }
}

int get_user_internal_id(int user_id) {
    for (int i = 0; i < 100; i++) {
        if (USERIDS[i] == user_id) {
            return i + 1;  // Return internal index
        }
    }
    return 0;  // User not found
}

int is_existing_user(int user_id) { return get_user_internal_id(user_id) != 0; }

// Register a new user
int register_user(int user_id) {
    if (is_existing_user(user_id)) {
        printf("Người dùng với CMND %d đã tồn tại.\n", user_id);
        return 0;
    }

    clear_input_buffer();
    int user_index = -1;
    int input_year, input_month, input_day;
    char gender_input[10];
    for (int i = 0; i < 100; i++) {
        if (USERIDS[i] == 0) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("User registration failed: User limit reached.\n");
        return 0;
    }
    printf(
        "Người dùng mới! Vui lòng cung cấp thông tin để đăng ký tài khoản.\n");
    USERIDS[user_index] = user_id;
    printf("Mời bạn nhập tên: ");
    input_str(USERNAMES[user_index], sizeof(USERNAMES[user_index]));
    printf("Mời bạn nhập ngày sinh\n");
    input_date(input_year, input_month, input_day);
    USER_BIRTHDATES[user_index][0] = input_year;
    USER_BIRTHDATES[user_index][1] = input_month;
    USER_BIRTHDATES[user_index][2] = input_day;
    printf("Mời bạn nhập giới tính (0: Nữ, 1: Nam): ");
    input_str(gender_input, sizeof(gender_input));
    USER_GENDERS[user_index] = atoi(gender_input);
    printf("Mời bạn nhập email: ");
    input_str(USER_EMAILS[user_index], sizeof(USER_EMAILS[user_index]));
    printf("Mời bạn nhập địa chỉ: ");
    input_str(USER_ADDRESSES[user_index], sizeof(USER_ADDRESSES[user_index]));
    printf("Nhập ngày tạo tài khoản\n");
    input_date(input_year, input_month, input_day);
    USER_CREATION_DATES[user_index][0] = input_year;
    USER_CREATION_DATES[user_index][1] = input_month;
    USER_CREATION_DATES[user_index][2] = input_day;
    int exp_year, exp_month, exp_day;
    get_expiration_date(input_year, input_month, input_day, exp_year, exp_month,
                        exp_day);
    USER_EXPIRATION_DATES[user_index][0] = exp_year;
    USER_EXPIRATION_DATES[user_index][1] = exp_month;
    USER_EXPIRATION_DATES[user_index][2] = exp_day;
    printf("Tạo tài khoản thành công!\n");
    return 1;
}

// In thông tin người dùng
void print_user_info(int user_id) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        printf("Người dùng với CMND %d không tồn tại.\n", user_id);
        return;
    }
    int index = internal_id - 1;
    char gender_str[10];
    char date_str[11];
    if (USER_GENDERS[index] == 1) {
        strcpy(gender_str, "Nam");
    } else {
        strcpy(gender_str, "Nữ");
    }
    printf("===== Thông tin người dùng =====\n");
    printf("CMND: %d\n", USERIDS[index]);
    printf("Tên: %s\n", USERNAMES[index]);
    get_date_string(date_str, USER_CREATION_DATES[index][0],
                    USER_CREATION_DATES[index][1],
                    USER_CREATION_DATES[index][2]);
    printf("Ngày sinh: %s\n", date_str);
    printf("Giới tính: %s\n", gender_str);
    printf("Email: %s\n", USER_EMAILS[index]);
    printf("Địa chỉ: %s\n", USER_ADDRESSES[index]);
    get_date_string(date_str, USER_CREATION_DATES[index][0],
                    USER_CREATION_DATES[index][1],
                    USER_CREATION_DATES[index][2]);
    printf("Ngày tạo tài khoản: %s\n", date_str);
    get_date_string(date_str, USER_EXPIRATION_DATES[index][0],
                    USER_EXPIRATION_DATES[index][1],
                    USER_EXPIRATION_DATES[index][2]);
    printf("Ngày hết hạn tài khoản: %s\n", date_str);
}
