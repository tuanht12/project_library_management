#include <stdio.h>

#include "menu.h"
#include "users.h"
#include "utils.h"

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

    show_main_menu();
}

int main() {
    run();
    return 0;
}
