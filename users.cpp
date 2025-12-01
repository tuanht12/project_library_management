#include "users.h"

#include <stdio.h>
#include <string.h>

#include <iostream>

#include "configs.h"
#include "datetime_utils.h"
#include "utils.h"

User USERS[MAX_USERS];

void initialize_one_user_data(int index) {
    USERS[index].id = 0;
    USERS[index].name[0] = '\0';
    USERS[index].gender = -1;
    USERS[index].email[0] = '\0';
    USERS[index].address[0] = '\0';
    USERS[index].birthdate[0] = 0;
    USERS[index].birthdate[1] = 0;
    USERS[index].birthdate[2] = 0;
    USERS[index].creation_date[0] = 0;
    USERS[index].creation_date[1] = 0;
    USERS[index].creation_date[2] = 0;
    USERS[index].expiration_date[0] = 0;
    USERS[index].expiration_date[1] = 0;
    USERS[index].expiration_date[2] = 0;
}

void initialize_user_data() {
    for (int i = 0; i < MAX_USERS; i++) {
        initialize_one_user_data(i);
    }
}

void initialize_test_users() {
    // Sample user data arrays
    int test_ids[10] = {123456, 234567, 345678, 456789, 567890,
                        678901, 789012, 890123, 901234, 012345};

    char test_names[10][MAX_STR_LEN] = {
        "Nguyen Van An", "Tran Thi Binh", "Le Van Cuong", "Pham Thi Dung",
        "Hoang Van Em",  "Vu Thi Phuong", "Do Van Giang", "Bui Thi Hoa",
        "Ngo Van Inh",   "Ly Thi Khanh"};

    int test_genders[10] = {1, 0, 1, 0, 1,
                            0, 1, 0, 1, 0};  // Alternating male/female

    char test_emails[10][MAX_STR_LEN] = {
        "an.nguyen@email.com", "binh.tran@email.com", "cuong.le@email.com",
        "dung.pham@email.com", "em.hoang@email.com",  "phuong.vu@email.com",
        "giang.do@email.com",  "hoa.bui@email.com",   "inh.ngo@email.com",
        "khanh.ly@email.com"};

    char test_addresses[10][MAX_STR_LEN] = {
        "123 Nguyen Trai, Q1, TP.HCM",
        "456 Le Loi, Q3, TP.HCM",
        "789 Tran Hung Dao, Q5, TP.HCM",
        "101 Vo Van Tan, Q3, TP.HCM",
        "202 Cach Mang Thang 8, Q10, TP.HCM",
        "303 Nguyen Dinh Chieu, Q3, TP.HCM",
        "404 Pham Ngu Lao, Q1, TP.HCM",
        "505 Hai Ba Trung, Q1, TP.HCM",
        "606 Le Van Sy, Phu Nhuan, TP.HCM",
        "707 Truong Chinh, Tan Binh, TP.HCM"};

    // Birth dates (year, month, day)
    int test_birthdates[10][3] = {{1990, 5, 15}, {1985, 8, 22}, {1992, 12, 3},
                                  {1988, 3, 18}, {1995, 7, 9},  {1987, 11, 27},
                                  {1993, 4, 14}, {1989, 9, 6},  {1991, 6, 30},
                                  {1994, 10, 12}};

    // Creation dates (all created in 2025)
    int test_creation_dates[10][3] = {
        {2025, 1, 15}, {2025, 2, 20}, {2025, 3, 10}, {2025, 4, 5},
        {2025, 5, 18}, {2025, 6, 25}, {2025, 7, 8},  {2025, 8, 14},
        {2025, 9, 22}, {2025, 10, 1}};

    // Initialize each test user
    for (int i = 0; i < 10; i++) {
        USERS[i].id = test_ids[i];
        strcpy(USERS[i].name, test_names[i]);
        USERS[i].gender = test_genders[i];
        strcpy(USERS[i].email, test_emails[i]);
        strcpy(USERS[i].address, test_addresses[i]);

        // Set birthdate
        USERS[i].birthdate[0] = test_birthdates[i][0];
        USERS[i].birthdate[1] = test_birthdates[i][1];
        USERS[i].birthdate[2] = test_birthdates[i][2];

        // Set creation date
        USERS[i].creation_date[0] = test_creation_dates[i][0];
        USERS[i].creation_date[1] = test_creation_dates[i][1];
        USERS[i].creation_date[2] = test_creation_dates[i][2];

        // Calculate and set expiration date (48 months later)
        int exp_year, exp_month, exp_day;
        get_expiration_date(
            test_creation_dates[i][0], test_creation_dates[i][1],
            test_creation_dates[i][2], exp_year, exp_month, exp_day);
        USERS[i].expiration_date[0] = exp_year;
        USERS[i].expiration_date[1] = exp_month;
        USERS[i].expiration_date[2] = exp_day;
    }

    printf("Đã khởi tạo 10 người dùng mẫu cho testing!\n");
    printf("CMND của các người dùng: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", test_ids[i]);
        if (i < 9) printf(", ");
    }
    printf("\n");
}

int get_user_internal_id(int user_id) {
    if (user_id == 0) {
        return 0;
    }
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id == user_id) {
            return i + 1;
        }
    }
    return 0;  // User not found
}

int is_existing_user(int user_id) {
    if (user_id == 0) {
        return 0;
    }
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id == user_id) {
            return 1;  // User exists
        }
    }
    return 0;  // User does not exist
}

int is_user_expired(int user_id) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        return 1;  // Non-existing users are considered expired
    }
    int index = internal_id - 1;
    int exp_year = USERS[index].expiration_date[0];
    int exp_month = USERS[index].expiration_date[1];
    int exp_day = USERS[index].expiration_date[2];

    if (CURRENT_YEAR > exp_year ||
        (CURRENT_YEAR == exp_year && CURRENT_MONTH > exp_month) ||
        (CURRENT_YEAR == exp_year && CURRENT_MONTH == exp_month &&
         CURRENT_DAY > exp_day)) {
        return 1;  // Expired
    }
    return 0;  // Not expired
}

void register_user(int user_id) {
    if (is_existing_user(user_id)) {
        printf("Người dùng với CMND %d đã tồn tại.\n", user_id);
        return;
    }

    int user_index = -1;
    int input_year, input_month, input_day;
    char gender_input[10];
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id == 0) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf(
            "Đăng ký thất bại. Hệ thống đã đạt đến số lượng người dùng tối "
            "đa.\n");
        return;
    }
    printf(
        "Người dùng mới! Vui lòng cung cấp thông tin để đăng ký tài khoản.\n");
    USERS[user_index].id = user_id;
    printf("Mời bạn nhập tên: ");
    safe_input_str(USERS[user_index].name, sizeof(USERS[user_index].name));
    printf("Mời bạn nhập ngày sinh\n");
    input_date(input_year, input_month, input_day);
    USERS[user_index].birthdate[0] = input_year;
    USERS[user_index].birthdate[1] = input_month;
    USERS[user_index].birthdate[2] = input_day;
    printf("Mời bạn nhập giới tính (0: Nữ, 1: Nam): ");
    safe_input_str(gender_input, sizeof(gender_input));
    USERS[user_index].gender = atoi(gender_input);
    printf("Mời bạn nhập email: ");
    safe_input_str(USERS[user_index].email, sizeof(USERS[user_index].email));
    printf("Mời bạn nhập địa chỉ: ");
    safe_input_str(USERS[user_index].address,
                   sizeof(USERS[user_index].address));

    // Set creation date & expiration date
    USERS[user_index].creation_date[0] = CURRENT_YEAR;
    USERS[user_index].creation_date[1] = CURRENT_MONTH;
    USERS[user_index].creation_date[2] = CURRENT_DAY;
    int exp_year, exp_month, exp_day;
    get_expiration_date(CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY, exp_year,
                        exp_month, exp_day);
    USERS[user_index].expiration_date[0] = exp_year;
    USERS[user_index].expiration_date[1] = exp_month;
    USERS[user_index].expiration_date[2] = exp_day;
    printf("Tạo tài khoản thành công!\n");
}

void print_user_info(int user_id, int with_header) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        printf("Người dùng với CMND %d không tồn tại.\n", user_id);
        return;
    }
    int index = internal_id - 1;
    char gender_str[10];
    char date_str[11];
    if (USERS[index].gender == 1) {
        strcpy(gender_str, "Nam");
    } else {
        strcpy(gender_str, "Nữ");
    }
    if (with_header) {
        printf("\n===== Thông tin người dùng =====\n");
    }
    printf("CMND: %d\n", USERS[index].id);
    printf("Mã số bạn đọc: %d\n", internal_id);
    printf("Tên: %s\n", USERS[index].name);
    get_date_string(date_str, USERS[index].birthdate[0],
                    USERS[index].birthdate[1], USERS[index].birthdate[2]);
    printf("Ngày sinh: %s\n", date_str);
    printf("Giới tính: %s\n", gender_str);
    printf("Email: %s\n", USERS[index].email);
    printf("Địa chỉ: %s\n", USERS[index].address);
    get_date_string(date_str, USERS[index].creation_date[0],
                    USERS[index].creation_date[1],
                    USERS[index].creation_date[2]);
    printf("Ngày tạo tài khoản: %s\n", date_str);
    get_date_string(date_str, USERS[index].expiration_date[0],
                    USERS[index].expiration_date[1],
                    USERS[index].expiration_date[2]);
    printf("Ngày hết hạn tài khoản: %s\n", date_str);
}

void print_all_users() {
    printf("\n===== Danh sách tất cả người dùng =====\n");
    for (int i = 0; i < MAX_USERS; i++) {
        if (USERS[i].id != 0) {
            print_user_info(USERS[i].id, 0);
            printf("-----------------------------\n");
        }
    }
}

void edit_user_info(int user_id) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        printf("Người dùng với CMND %d không tồn tại.\n", user_id);
        return;
    }
    int index = internal_id - 1;
    int input_year, input_month, input_day;
    char gender_input[10];
    printf("Chỉnh sửa thông tin cho người dùng với CMND %d\n", user_id);
    printf("Nhấn Enter để bỏ qua trường không muốn chỉnh sửa.\n");

    printf("Tên hiện tại: %s\n", USERS[index].name);
    if (ask_to_edit_field()) {
        printf("Nhập tên mới: ");
        safe_input_str(USERS[index].name, sizeof(USERS[index].name));
    }

    printf("Ngày sinh hiện tại: ");
    char date_str[11];
    get_date_string(date_str, USERS[index].birthdate[0],
                    USERS[index].birthdate[1], USERS[index].birthdate[2]);
    printf("%s\n", date_str);
    if (ask_to_edit_field()) {
        printf("Nhập ngày sinh mới\n");
        input_date(input_year, input_month, input_day);
        USERS[index].birthdate[0] = input_year;
        USERS[index].birthdate[1] = input_month;
        USERS[index].birthdate[2] = input_day;
    }

    printf("Giới tính hiện tại: %s\n", USERS[index].gender == 1 ? "Nam" : "Nữ");
    if (ask_to_edit_field()) {
        printf("Nhập giới tính mới (0: Nữ, 1: Nam): ");
        safe_input_str(gender_input, sizeof(gender_input));
        USERS[index].gender = atoi(gender_input);
    }

    printf("Email hiện tại: %s\n", USERS[index].email);
    if (ask_to_edit_field()) {
        printf("Nhập email mới: ");
        safe_input_str(USERS[index].email, sizeof(USERS[index].email));
    }

    printf("Địa chỉ hiện tại: %s\n", USERS[index].address);
    if (ask_to_edit_field()) {
        printf("Nhập địa chỉ mới: ");
        safe_input_str(USERS[index].address, sizeof(USERS[index].address));
    }

    printf("Cập nhật thông tin thành công!\n");
}

void delete_user(int user_id) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        printf("Người dùng với CMND %d không tồn tại.\n", user_id);
        return;
    }
    int index = internal_id - 1;
    while (index < MAX_USERS - 1 && USERS[index + 1].id != 0) {
        USERS[index] = USERS[index + 1];
        index++;
    }
    initialize_one_user_data(index);  // Khởi tạo lại slot cuối cùng
    printf("Xóa người dùng với CMND %d thành công.\n", user_id);
}

void get_user_name_by_id(int user_id, char username[MAX_STR_LEN]) {
    int internal_id = get_user_internal_id(user_id);
    if (internal_id == 0) {
        printf("Người dùng với CMND %d không tồn tại.\n", user_id);
        return;
    }

    strcpy(username, USERS[internal_id - 1].name);
}
