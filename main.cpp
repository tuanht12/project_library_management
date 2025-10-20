#include "menu.h"
#include "users.h"
#include "utils.h"

int main() {
    initialize_user_data();
    initialize_test_users();
    login();
    display_main_menu();
    return 0;
}
