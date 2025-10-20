#include <stdio.h>

#include "users.h"
#include "utils.h"

void show_user_management_menu() {
    int choice = 0;
    while (choice != 9) {
        printf("\n=== QUẢN LÝ NGƯỜI DÙNG ===\n");
        printf("1. Xem thông tin người dùng\n");
        printf("2. Đăng ký người dùng mới\n");
        printf("3. Xem tất cả người dùng\n");
        printf("4. Chỉnh sửa thông tin người dùng\n");
        printf("5. Xóa người dùng\n");
        printf("9. Quay lại menu chính\n");
        printf("Hãy chọn một tùy chọn: ");
        scanf("%d", &choice);
        cleanup_input_buffer();
        switch (choice) {
            case 1: {
                int user_id;
                printf("Nhập CMND của người dùng: ");
                scanf("%d", &user_id);
                cleanup_input_buffer();
                print_user_info(user_id);
            } break;
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
            case 4: {
                int edit_user_id;
                printf("Nhập CMND của người dùng cần chỉnh sửa: ");
                scanf("%d", &edit_user_id);
                cleanup_input_buffer();
                edit_user_info(edit_user_id);
            } break;
            case 5: {
                int delete_user_id;
                printf("Nhập CMND của người dùng cần xóa: ");
                scanf("%d", &delete_user_id);
                cleanup_input_buffer();
                delete_user(delete_user_id);
            } break;
            case 9:
                printf("Quay lại menu chính.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
                break;
        }
    }
}

void display_main_menu() {
    int choice = 0;
    while (choice != 9) {
        printf("\n=== MENU CHÍNH ===\n");
        printf("1. Quản lý người dùng\n");
        printf("2. Quản lý sách\n");
        printf("3. Quản lý mượn trả sách\n");
        printf("4. Thống kê\n");
        printf("9. Thoát\n");
        printf("Hãy chọn một tùy chọn: ");
        scanf("%d", &choice);
        cleanup_input_buffer();
        switch (choice) {
            case 1:
                show_user_management_menu();
                break;
            case 9:
                printf("Thoát chương trình. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
                break;
        }
    }
}
