#include "datetime_utils.h"
#include "menu.h"
#include "users.h"
#include "utils.h"
int main() {
    initialize_user_data();
    initialize_test_users();
    initialize_current_date();

    display_main_menu();
    return 0;
}
