#include "books.h"

#include <stdio.h>
#include <string.h>

#include "configs.h"
#include "utils.h"

Book BOOKS[MAX_BOOKS];

void initialize_one_book_data(int index) {
    BOOKS[index].isbn = 0;
    BOOKS[index].year = 0;
    BOOKS[index].count = 0;
    BOOKS[index].price = 0;
    BOOKS[index].name[0] = '\0';
    BOOKS[index].author[0] = '\0';
    BOOKS[index].publisher[0] = '\0';
    BOOKS[index].genre[0] = '\0';
}

void initialize_book_data() {
    for (int i = 0; i < MAX_BOOKS; i++) {
        initialize_one_book_data(i);
    }
}

void initialize_test_books() {
    // Mảng dữ liệu mẫu cục bộ
    int test_isbns[10] = {1001, 1002, 1003, 1004, 1005,
                          1006, 1007, 1008, 1009, 1010};

    char test_names[10][MAX_STR_LEN] = {"So Do",
                                        "Sapiens: Luoc Su Loai Nguoi",
                                        "Nha Gia Kim",
                                        "De Men Phieu Luu Ky",
                                        "Dac Nhan Tam",
                                        "Lap Trinh Huong Doi Tuong voi C++",
                                        "Harry Potter va Hon Da Phu Thuy",
                                        "Kinh Te Hoc Vui Ve",
                                        "Viet Nam Su Luoc",
                                        "Sherlock Holmes Toan Tap"};

    char test_authors[10][MAX_STR_LEN] = {
        "Vu Trong Phung",    "Yuval Noah Harari",     "Paulo Coelho",
        "To Hoai",           "Dale Carnegie",         "Pham Hung",
        "J.K. Rowling",      "S. Levitt & S. Dubner", "Tran Trong Kim",
        "Arthur Conan Doyle"};

    char test_publishers[10][MAX_STR_LEN] = {
        "NXB Van hoc",  "NXB Tri Thuc",        "NXB Hoi Nha Van",
        "NXB Kim Dong", "NXB Tong hop TP.HCM", "NXB Khoa hoc va Ky thuat",
        "NXB Tre",      "NXB The Gioi",        "NXB Hong Duc",
        "NXB Van Hoc"};

    int test_years[10] = {2018, 2017, 2013, 2015, 2016,
                          2020, 2014, 2019, 2017, 2018};

    char test_genres[10][MAX_STR_LEN] = {
        "Hien thuc phe phan", "Khoa hoc",     "Tieu thuyet",
        "Thieu nhi",          "Ky nang song", "Cong nghe thong tin",
        "Gia tuong",          "Kinh te",      "Lich su",
        "Trinh tham"};

    int test_prices[10] = {120000, 200000, 150000, 80000,  100000,
                           250000, 180000, 220000, 160000, 140000};

    int test_counts[10] = {5, 3, 7, 10, 8, 4, 6, 2, 3, 5};

    // Vòng lặp để gán dữ liệu vào mảng struct
    for (int i = 0; i < 10; i++) {
        BOOKS[i].isbn = test_isbns[i];
        strcpy(BOOKS[i].name, test_names[i]);
        strcpy(BOOKS[i].author, test_authors[i]);
        strcpy(BOOKS[i].publisher, test_publishers[i]);
        BOOKS[i].year = test_years[i];
        strcpy(BOOKS[i].genre, test_genres[i]);
        BOOKS[i].price = test_prices[i];
        BOOKS[i].count = test_counts[i];
    }

    printf("Da khoi tao 10 cuon sach mau cho testing!\n");
    printf("ID cua cac cuon sach: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", BOOKS[i].isbn);
        if (i < 9) printf(", ");
    }
    printf("\n");
}

void print_all_books() {
    printf("\n===== Danh sách tất cả sách =====\n");
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn != 0) {
            print_book_info_by_isbn(BOOKS[i].isbn, 0);
            printf("-----------------------------\n");
        }
    }
}

void add_book(int isbn, int num_copies) {
    if (num_copies <= 0) {
        printf("Số lượng sách phải lớn hơn 0.\n");
        return;
    }
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            BOOKS[i].count += num_copies;
            printf(
                "Đã thêm %d bản cho sách ISBN %d. Tổng số lượng hiện tại: %d\n",
                num_copies, isbn, BOOKS[i].count);
            return;
        }
    }
    int new_book_index = -1;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == 0) {
            new_book_index = i;
            break;
        }
    }

    if (new_book_index == -1) {
        printf("Thêm sách thất bại: Đã đạt giới hạn lưu trữ sách.\n");
        return;
    }

    BOOKS[new_book_index].isbn = isbn;
    BOOKS[new_book_index].count = num_copies;
    printf("Nhập tên sách: ");
    safe_input_str(BOOKS[new_book_index].name,
                   sizeof(BOOKS[new_book_index].name));
    printf("Nhập tác giả: ");
    safe_input_str(BOOKS[new_book_index].author,
                   sizeof(BOOKS[new_book_index].author));
    printf("Nhập nhà xuất bản: ");
    safe_input_str(BOOKS[new_book_index].publisher,
                   sizeof(BOOKS[new_book_index].publisher));
    printf("Nhập năm xuất bản: ");
    safe_scanf_int(BOOKS[new_book_index].year);
    while (BOOKS[new_book_index].year <= 0) {
        printf("Năm xuất bản không hợp lệ. Vui lòng nhập lại: ");
        safe_scanf_int(BOOKS[new_book_index].year);
    }

    printf("Nhập thể loại: ");
    safe_input_str(BOOKS[new_book_index].genre,
                   sizeof(BOOKS[new_book_index].genre));
    printf("Nhập giá sách: ");
    safe_scanf_int(BOOKS[new_book_index].price);
    while (BOOKS[new_book_index].price < 0) {
        printf("Giá sách không hợp lệ. Vui lòng nhập lại: ");
        safe_scanf_int(BOOKS[new_book_index].price);
    }
    printf("Đã thêm sách mới với ISBN %d và số lượng %d\n", isbn, num_copies);
}

void delete_book(int isbn) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            initialize_one_book_data(i);
            printf("Đã xóa sách với ISBN %d khỏi hệ thống.\n", isbn);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d để xóa.\n", isbn);
}

void print_book_info_by_isbn(int isbn, int with_header) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            if (with_header) {
                printf("\n--- Thông tin sách ---\n");
            }
            printf("ISBN: %d\n", BOOKS[i].isbn);
            printf("Tên sách: %s\n", BOOKS[i].name);
            printf("Tác giả: %s\n", BOOKS[i].author);
            printf("Nhà xuất bản: %s\n", BOOKS[i].publisher);
            printf("Năm xuất bản: %d\n", BOOKS[i].year);
            printf("Thể loại: %s\n", BOOKS[i].genre);
            printf("Giá sách: %d VND\n", BOOKS[i].price);
            printf("Số lượng hiện có: %d\n", BOOKS[i].count);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d trong hệ thống.\n", isbn);
}

void print_book_info_by_name(const char book_name[MAX_STR_LEN]) {
    int found = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (strcmp(BOOKS[i].name, book_name) == 0) {
            int isbn = BOOKS[i].isbn;
            print_book_info_by_isbn(isbn);
            found = 1;
        }
    }
    if (!found) {
        printf("Không tìm thấy sách với tên \"%s\" trong hệ thống.\n",
               book_name);
    }
}

void edit_book_info(int isbn) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            printf("Chỉnh sửa thông tin cho sách với ISBN %d\n", isbn);
            printf("Nhấn Enter để bỏ qua trường không muốn chỉnh sửa.\n");

            printf("Tên sách hiện tại: %s\n", BOOKS[i].name);
            if (ask_to_edit_field()) {
                printf("Nhập tên sách mới: ");
                safe_input_str(BOOKS[i].name, sizeof(BOOKS[i].name));
            }

            printf("Tác giả hiện tại: %s\n", BOOKS[i].author);
            if (ask_to_edit_field()) {
                printf("Nhập tác giả mới: ");
                safe_input_str(BOOKS[i].author, sizeof(BOOKS[i].author));
            }

            printf("Nhà xuất bản hiện tại: %s\n", BOOKS[i].publisher);
            if (ask_to_edit_field()) {
                printf("Nhập nhà xuất bản mới: ");
                safe_input_str(BOOKS[i].publisher, sizeof(BOOKS[i].publisher));
            }

            printf("Năm xuất bản hiện tại: %d\n", BOOKS[i].year);
            if (ask_to_edit_field()) {
                printf("Nhập năm xuất bản mới: ");
                safe_scanf_int(BOOKS[i].year);
                while (BOOKS[i].year <= 0) {
                    printf("Năm xuất bản không hợp lệ. Vui lòng nhập lại: ");
                    safe_scanf_int(BOOKS[i].year);
                }
            }

            printf("Thể loại hiện tại: %s\n", BOOKS[i].genre);
            if (ask_to_edit_field()) {
                printf("Nhập thể loại mới: ");
                safe_input_str(BOOKS[i].genre, sizeof(BOOKS[i].genre));
            }

            printf("Giá sách hiện tại: %d VND\n", BOOKS[i].price);
            if (ask_to_edit_field()) {
                printf("Nhập giá sách mới: ");
                safe_scanf_int(BOOKS[i].price);
                while (BOOKS[i].price < 0) {
                    printf("Giá sách không hợp lệ. Vui lòng nhập lại: ");
                    safe_scanf_int(BOOKS[i].price);
                }
            }

            printf("Số lượng hiện tại: %d\n", BOOKS[i].count);
            if (ask_to_edit_field()) {
                printf("Nhập số lượng mới: ");
                safe_scanf_int(BOOKS[i].count);
                while (BOOKS[i].count < 0) {
                    printf("Số lượng không hợp lệ. Vui lòng nhập lại: ");
                    safe_scanf_int(BOOKS[i].count);
                }
            }

            printf("Đã cập nhật thông tin cho sách với ISBN %d\n", isbn);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d để chỉnh sửa.\n", isbn);
}

int borrow_book(int isbn) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            if (BOOKS[i].count > 0) {
                BOOKS[i].count--;
                printf("Đã mượn sách với ISBN %d thành công.\n", isbn);
                return 1;
            } else {
                printf("Sách với ISBN %d hiện không còn trong kho.\n", isbn);
                return 0;
            }
        }
    }
    printf("Không tìm thấy sách với ISBN %d trong hệ thống.\n", isbn);
    return 0;
}

int return_book(int isbn) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            BOOKS[i].count++;
            printf("Đã trả sách với ISBN %d thành công.\n", isbn);
            return 1;
        }
    }
    printf("Không tìm thấy sách với ISBN %d trong hệ thống.\n", isbn);
    return 0;
}

int get_price_by_isbn(int isbn) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            return BOOKS[i].price;
        }
    }
    return 0;
}

void get_book_name_by_isbn(int isbn, char book_name[MAX_STR_LEN]) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (BOOKS[i].isbn == isbn) {
            strcpy(book_name, BOOKS[i].name);
            return;
        }
    }
    strcpy(book_name, "Unknown Book");
}
