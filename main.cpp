#include "books.h"
#include "datetime_utils.h"
#include "menu.h"
#include "users.h"
#include "utils.h"
int main() {
    initialize_current_date();

    initialize_user_data();
    initialize_test_users();

    initialize_book_data();
    initialize_test_books();

    display_main_menu();
    return 0;
}
