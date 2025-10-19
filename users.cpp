#include "users.h"

#include <stdio.h>
#include <string.h>

#include <iostream>

// Define the global arrays

// CMND của người dùng
int USERIDS[100];

// Tên người dùng
char USERNAMES[100][100];

// Ngày sinh của người dùng
char USER_BIRTHDATES[100][100];

// Giới tính của người dùng, 0: Nữ, 1: Nam
int USER_GENDERS[100];

// Email của người dùng
char USER_EMAILS[100][100];

// Địa chỉ của người dùng
char USER_ADDRESSES[100][100];

// Ngày tạo tài khoản của người dùng
char USER_CREATION_DATES[100][100];
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Khởi tạo mảng người dùng
void init_user_array() {
    for (int i = 0; i < 100; i++) {
        USERIDS[i] = 0;
        USERNAMES[i][0] = '\0';
        USER_BIRTHDATES[i][0] = '\0';
        USER_GENDERS[i] = -1;
        USER_EMAILS[i][0] = '\0';
        USER_ADDRESSES[i][0] = '\0';
        USER_CREATION_DATES[i][0] = '\0';
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
    clear_input_buffer();
    int user_index = -1;
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
    fgets(USERNAMES[user_index], sizeof(USERNAMES[user_index]), stdin);
    printf("Mời bạn nhập ngày sinh (DD/MM/YYYY): ");
    fgets(USER_BIRTHDATES[user_index], sizeof(USER_BIRTHDATES[user_index]),
          stdin);
    printf("Mời bạn nhập giới tính (0: Nữ, 1: Nam): ");
    fgets(gender_input, sizeof(gender_input), stdin);
    USER_GENDERS[user_index] = atoi(gender_input);
    printf("Mời bạn nhập email: ");
    fgets(USER_EMAILS[user_index], sizeof(USER_EMAILS[user_index]), stdin);
    printf("Mời bạn nhập địa chỉ: ");
    fgets(USER_ADDRESSES[user_index], sizeof(USER_ADDRESSES[user_index]),
          stdin);

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
    if (USER_GENDERS[index] == 1) {
        strcpy(gender_str, "Nam\n");
    } else {
        strcpy(gender_str, "Nữ\n");
    }
    printf("===== Thông tin người dùng =====\n");
    printf("CMND: %d\n", USERIDS[index]);
    printf("Tên: %s", USERNAMES[index]);
    printf("Ngày sinh: %s", USER_BIRTHDATES[index]);
    printf("Giới tính: %s", gender_str);
    printf("Email: %s", USER_EMAILS[index]);
    printf("Địa chỉ: %s", USER_ADDRESSES[index]);
}