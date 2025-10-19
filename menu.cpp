#include <iostream>

#include "users.h"
// Function to display the main menu
void showMenu(int user_id) {
    printf("\nChào mừng bạn đến với hệ thống quản lý thư viện!\n");
    print_user_info(user_id);

    printf("=== MENU CHÍNH ===\n");
    printf("1. Xem thông tin người dùng\n");
    printf("2. Thoát\n");
    printf("Hãy chọn một tùy chọn: ");
}
