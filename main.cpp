#include <stdio.h>

#include "menu.h"
#include "users.h"

int main() {
    // Initialize the global arrays
    init_user_array();

    // Read user ID
    int user_id;
    printf("Hãy nhập CMND của bạn: ");
    scanf("%d", &user_id);

    int is_existing = is_existing_user(user_id);
    if (is_existing) {
        showMenu(user_id);
    } else {
        if (register_user(user_id)) {
            showMenu(user_id);
        } else {
            printf("Đăng ký người dùng thất bại.\n");
        }
    }
    
    return 0;
}
