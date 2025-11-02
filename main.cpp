#include <stdio.h>

#include "book_ops.h"
#include "books.h"
#include "configs.h"
#include "datetime_utils.h"
#include "menu.h"
#include "users.h"
#include "utils.h"
int main() {
    if (SHOULD_INIT_DATA_FOR_TESTING) {
        printf("Khởi tạo dữ liệu mẫu cho mục đích testing...\n");
        initialize_user_data();
        initialize_test_users();

        initialize_book_data();
        initialize_test_books();

        initialize_borrow_data();
        initialize_test_borrows();
    }
    initialize_current_date();
    display_main_menu();
    return 0;
}
