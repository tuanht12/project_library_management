#include <stdio.h>

#include "book_ops.h"
#include "books.h"
#include "configs.h"
#include "csv_utils.h"
#include "datetime_utils.h"
#include "menu.h"
#include "users.h"
#include "utils.h"
int main() {
    // Đọc dữ liệu từ file CSV
    int num_current_books = read_books_from_csv();
    int num_current_users = read_users_from_csv();
    int num_current_borrows = read_borrows_from_csv();
    if (SHOULD_INIT_DATA_FOR_TESTING &&
        (num_current_books == 0 || num_current_users == 0 ||
         num_current_borrows == 0)) {
        printf("Khởi tạo dữ liệu mẫu cho mục đích testing...\n");
        if (!num_current_books) initialize_test_books();
        if (!num_current_users) initialize_test_users();
        if (!num_current_borrows) initialize_test_borrows();
    }
    initialize_current_date();
    display_main_menu();
    // Lưu dữ liệu vào file CSV khi thoát chương trình
    write_books_to_csv();
    write_users_to_csv();
    write_borrows_to_csv();
    return 0;
}
