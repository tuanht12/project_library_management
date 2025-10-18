#include <stdio.h>
#include <iostream>
#include <string>
#include "nguoi_dung.h"

int USERS[100];
char USERNAMES[100][100]; // Assuming max 100 users with max 100 char names

void initUsers()
{
    for (int i = 0; i < 100; i++)
    {
        USERS[i] = 0;
    }
}

int readUserId()
{
    int user_id;
    char username[100];
    printf("Mời bạn nhập ID: ");
    scanf("%d", &user_id);

    for (int i = 0; i < 100; i++)
    {
        if (USERS[i] == user_id)
        {
            std::cout << "Chào mừng trở lại, người dùng với ID " << user_id << "!\n";
            findUserNameById(user_id, username);
            std::cout << "Tên người dùng của bạn là: " << username << "\n";
            return user_id;
        }
    }

    for (int i = 0; i < 100; i++)
    {
        if (USERS[i] == 0)
        {
            USERS[i] = user_id;
            readUserName(username);
            break;
        }
    }
    std::cout << "Người dùng mới được tạo với ID " << user_id << "!\n";
    std::cout << "Tên người dùng của bạn là: " << username << "\n";

    return user_id;
}

void readUserName(char username[100])
{
    printf("Mời bạn nhập tên người dùng: ");
    std::cin.ignore();
    std::cin.getline(username, 100);
}

void findUserNameById(int user_id, char username[100])
{
    for (int i = 0; i < 100; i++)
    {
        if (USERS[i] == user_id)
        {
            username = USERNAMES[i];
            return;
        }
    }
    printf("Không tìm thấy người dùng với ID %d\n", user_id);
}
