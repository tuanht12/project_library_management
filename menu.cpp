#include <stdio.h>

#include "books.h"
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
        safe_scanf_int(choice);
        switch (choice) {
            case 1: {
                int user_id;
                printf("Nhập CMND của người dùng: ");
                safe_scanf_int(user_id);
                print_user_info(user_id);
            } break;
            case 2: {
                int new_user_id;
                printf("Nhập CMND của người dùng mới: ");
                safe_scanf_int(new_user_id);
                register_user(new_user_id);
            } break;
            case 3:
                print_all_users();
                break;
            case 4: {
                int edit_user_id;
                printf("Nhập CMND của người dùng cần chỉnh sửa: ");
                safe_scanf_int(edit_user_id);
                edit_user_info(edit_user_id);
            } break;
            case 5: {
                int delete_user_id;
                printf("Nhập CMND của người dùng cần xóa: ");
                safe_scanf_int(delete_user_id);
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

void show_book_management_menu() {
    int choice = 0;
    while (choice != 9) {
        printf("\n=== QUẢN LÝ SÁCH ===\n");
        printf("1. Xem tất cả sách\n");
        printf("2. Thêm sách mới / Cập nhật số lượng sách\n");
        printf("3. Chỉnh sửa thông tin sách\n");
        printf("4. Xóa sách\n");
        printf("5. Tìm kiếm sách theo ISBN\n");
        printf("6. Tìm kiếm sách theo tên sách\n");
        printf("9. Quay lại menu chính\n");
        printf("Hãy chọn một tùy chọn: ");
        safe_scanf_int(choice);
        switch (choice) {
            case 1:
                print_all_books();
                break;
            case 2: {
                int isbn, num_copies;
                printf("Nhập ISBN của sách: ");
                safe_scanf_int(isbn);
                printf("Nhập số lượng sách: ");
                safe_scanf_int(num_copies);
                add_book(isbn, num_copies);
            } break;
            case 3: {
                int isbn;
                printf("Nhập ISBN của sách cần chỉnh sửa: ");
                safe_scanf_int(isbn);
                edit_book_info(isbn);
            } break;
            case 4: {
                int isbn;
                printf("Nhập ISBN của sách cần xóa: ");
                safe_scanf_int(isbn);
                delete_book(isbn);
            } break;
            case 5: {
                int isbn;
                printf("Nhập ISBN của sách cần tìm: ");
                safe_scanf_int(isbn);
                print_book_info_by_isbn(isbn);
            } break;
            case 6: {
                char book_name[100];
                printf("Nhập tên sách cần tìm: ");
                safe_input_str(book_name, sizeof(book_name));
                print_book_info_by_name(book_name);
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
        safe_scanf_int(choice);
        switch (choice) {
            case 1:
                show_user_management_menu();
                break;
            case 2:
                show_book_management_menu();
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
