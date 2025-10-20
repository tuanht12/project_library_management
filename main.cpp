#include <stdio.h>

#include "users.h"
#include "utils.h"
// TEST
#include "datetime_utils.h"

void run() {
    // Initialize the global arrays
    initialize_user_data();
    initialize_test_users();
    // Read user ID
    int user_id;
    printf("Hãy nhập CMND của bạn: ");
    scanf("%d", &user_id);
    cleanup_input_buffer();
    if (!is_existing_user(user_id) && !register_user(user_id)) {
        printf("Đăng ký người dùng thất bại. Vui lòng thử lại sau.\n");
        return;
    }

    int choice = 0;
    while (choice != 9) {
        printf("\n=== MENU CHÍNH ===\n");
        printf("1. Xem thông tin người dùng\n");
        printf("2. Đăng ký người dùng mới\n");
        printf("3. Xem tất cả người dùng\n");
        printf("4. Chỉnh sửa thông tin người dùng\n");
        printf("5. Xóa người dùng\n");
        printf("9. Thoát\n");
        printf("Hãy chọn một tùy chọn: ");
        scanf("%d", &choice);
        cleanup_input_buffer();
        printf("Bạn đã chọn: %d\n", choice);
        switch (choice) {
            case 1:
                int user_id;
                printf("Nhập CMND của người dùng: ");
                scanf("%d", &user_id);
                cleanup_input_buffer();
                print_user_info(user_id);
                break;
            case 2: {
                int new_user_id;
                printf("Nhập CMND của người dùng mới: ");
                scanf("%d", &new_user_id);
                cleanup_input_buffer();
                register_user(new_user_id);
            } break;
            case 3:
                print_all_users();
                break;
            case 4:
                int edit_user_id;
                printf("Nhập CMND của người dùng cần chỉnh sửa: ");
                scanf("%d", &edit_user_id);
                cleanup_input_buffer();
                edit_user_info(edit_user_id);
                break;
            case 5:
                int delete_user_id;
                printf("Nhập CMND của người dùng cần xóa: ");
                scanf("%d", &delete_user_id);
                cleanup_input_buffer();
                delete_user(delete_user_id);
                break;
            case 9:
                printf("Thoát khỏi hệ thống. Hẹn gặp lại!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
                break;
        }
    }
}

int main() {
    run();
    // char date_str[11];
    // get_date_string(date_str, 2025, 10, 2);
    // printf("Expiration Date: %s\n", date_str);
    return 0;
}
