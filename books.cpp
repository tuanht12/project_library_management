#include "books.h"

#include <stdio.h>
#include <string.h>

#include "utils.h"
int ISBNS[100];
char BOOKNAMES[100][100];
char BOOKAUTHORS[100][100];
char BOOKPUBLISHERS[100][100];
int BOOKYEARS[100];
char BOOKGENRES[100][100];
char BOOKSHELVES[100][50];
int BOOKCOUNTS[100];

void initialize_one_book_data(int index) {
    ISBNS[index] = 0;
    BOOKYEARS[index] = 0;
    BOOKCOUNTS[index] = 0;
    BOOKNAMES[index][0] = '\0';
    BOOKAUTHORS[index][0] = '\0';
    BOOKPUBLISHERS[index][0] = '\0';
    BOOKGENRES[index][0] = '\0';
    BOOKSHELVES[index][0] = '\0';
}

void initialize_book_data() {
    for (int i = 0; i < 100; i++) {
        initialize_one_book_data(i);
    }
}

#include <string.h>  // Cần thiết cho hàm strcpy()

/**
 * @brief Khởi tạo dữ liệu mẫu cho 10 cuốn sách để phục vụ việc testing.
 * * Hàm này điền thông tin cho 10 cuốn sách đầu tiên trong các mảng dữ liệu
 * toàn cục.
 */
void initialize_test_books() {
    // Mảng dữ liệu mẫu cục bộ
    int test_isbns[10] = {1001, 1002, 1003, 1004, 1005,
                          1006, 1007, 1008, 1009, 1010};

    char test_names[10][100] = {"So Do",
                                "Sapiens: Luoc Su Loai Nguoi",
                                "Nha Gia Kim",
                                "De Men Phieu Luu Ky",
                                "Dac Nhan Tam",
                                "Lap Trinh Huong Doi Tuong voi C++",
                                "Harry Potter va Hon Da Phu Thuy",
                                "Kinh Te Hoc Vui Ve",
                                "Viet Nam Su Luoc",
                                "Sherlock Holmes Toan Tap"};

    char test_authors[10][100] = {"Vu Trong Phung", "Yuval Noah Harari",
                                  "Paulo Coelho",   "To Hoai",
                                  "Dale Carnegie",  "Pham Hung",
                                  "J.K. Rowling",   "S. Levitt & S. Dubner",
                                  "Tran Trong Kim", "Arthur Conan Doyle"};

    char test_publishers[10][100] = {
        "NXB Van hoc",  "NXB Tri Thuc",        "NXB Hoi Nha Van",
        "NXB Kim Dong", "NXB Tong hop TP.HCM", "NXB Khoa hoc va Ky thuat",
        "NXB Tre",      "NXB The Gioi",        "NXB Hong Duc",
        "NXB Van Hoc"};

    int test_years[10] = {2018, 2017, 2013, 2015, 2016,
                          2020, 2014, 2019, 2017, 2018};

    char test_genres[10][100] = {
        "Hien thuc phe phan", "Khoa hoc",     "Tieu thuyet",
        "Thieu nhi",          "Ky nang song", "Cong nghe thong tin",
        "Gia tuong",          "Kinh te",      "Lich su",
        "Trinh tham"};

    char test_shelves[10][50] = {"A1", "B2", "C3", "D4", "E5",
                                 "F1", "G2", "H3", "I4", "J5"};

    int test_counts[10] = {5, 3, 7, 10, 8, 4, 6, 2, 3, 5};

    // Vòng lặp để gán dữ liệu vào các mảng toàn cục
    for (int i = 0; i < 10; i++) {
        ISBNS[i] = test_isbns[i];
        strcpy(BOOKNAMES[i], test_names[i]);
        strcpy(BOOKAUTHORS[i], test_authors[i]);
        strcpy(BOOKPUBLISHERS[i], test_publishers[i]);
        BOOKYEARS[i] = test_years[i];
        strcpy(BOOKGENRES[i], test_genres[i]);
        strcpy(BOOKSHELVES[i], test_shelves[i]);
        BOOKCOUNTS[i] = test_counts[i];
    }

    printf("Da khoi tao 10 cuon sach mau cho testing!\n");
    printf("ID cua cac cuon sach: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", ISBNS[i]);
        if (i < 9) printf(", ");
    }
    printf("\n");
}

void print_all_books() {
    printf("\n===== Danh sách tất cả sách =====\n");
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] != 0) {
            print_book_info_by_isbn(ISBNS[i], 0);
            printf("-----------------------------\n");
        }
    }
}

void add_book(int isbn, int num_copies) {
    if (num_copies <= 0) {
        printf("Số lượng sách phải lớn hơn 0.\n");
        return;
    }
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] == isbn) {
            BOOKCOUNTS[i] += num_copies;
            printf(
                "Đã thêm %d bản cho sách ISBN %d. Tổng số lượng hiện tại: %d\n",
                num_copies, isbn, BOOKCOUNTS[i]);
            return;
        }
    }
    int new_book_index = -1;
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] == 0) {
            new_book_index = i;
            break;
        }
    }

    if (new_book_index == -1) {
        printf("Thêm sách thất bại: Đã đạt giới hạn lưu trữ sách.\n");
        return;
    }

    ISBNS[new_book_index] = isbn;
    BOOKCOUNTS[new_book_index] = num_copies;
    printf("Nhập tên sách: ");
    safe_input_str(BOOKNAMES[new_book_index],
                   sizeof(BOOKNAMES[new_book_index]));
    printf("Nhập tác giả: ");
    safe_input_str(BOOKAUTHORS[new_book_index],
                   sizeof(BOOKAUTHORS[new_book_index]));
    printf("Nhập nhà xuất bản: ");
    safe_input_str(BOOKPUBLISHERS[new_book_index],
                   sizeof(BOOKPUBLISHERS[new_book_index]));
    printf("Nhập năm xuất bản: ");
    safe_scanf_int(BOOKYEARS[new_book_index]);
    while (BOOKYEARS[new_book_index] <= 0) {
        printf("Năm xuất bản không hợp lệ. Vui lòng nhập lại: ");
        safe_scanf_int(BOOKYEARS[new_book_index]);
    }

    printf("Nhập thể loại: ");
    safe_input_str(BOOKGENRES[new_book_index],
                   sizeof(BOOKGENRES[new_book_index]));
    printf("Nhập giá sách: ");
    safe_input_str(BOOKSHELVES[new_book_index],
                   sizeof(BOOKSHELVES[new_book_index]));
    printf("Đã thêm sách mới với ISBN %d và số lượng %d\n", isbn, num_copies);
}

void delete_book(int isbn) {
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] == isbn) {
            initialize_one_book_data(i);
            printf("Đã xóa sách với ISBN %d khỏi hệ thống.\n", isbn);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d để xóa.\n", isbn);
}

void print_book_info_by_isbn(int isbn, int with_header) {
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] == isbn) {
            if (with_header) {
                printf("\n--- Thông tin sách ---\n");
            }
            printf("ISBN: %d\n", ISBNS[i]);
            printf("Tên sách: %s\n", BOOKNAMES[i]);
            printf("Tác giả: %s\n", BOOKAUTHORS[i]);
            printf("Nhà xuất bản: %s\n", BOOKPUBLISHERS[i]);
            printf("Năm xuất bản: %d\n", BOOKYEARS[i]);
            printf("Thể loại: %s\n", BOOKGENRES[i]);
            printf("Giá sách: %s\n", BOOKSHELVES[i]);
            printf("Số lượng hiện có: %d\n", BOOKCOUNTS[i]);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d trong hệ thống.\n", isbn);
}

void print_book_info_by_name(const char book_name[100]) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(BOOKNAMES[i], book_name) == 0) {
            int isbn = ISBNS[i];
            print_book_info_by_isbn(isbn);
            return;
        }
    }
    printf("Không tìm thấy sách với tên \"%s\" trong hệ thống.\n", book_name);
}

void edit_book_info(int isbn) {
    for (int i = 0; i < 100; i++) {
        if (ISBNS[i] == isbn) {
            printf("Chỉnh sửa thông tin cho sách với ISBN %d\n", isbn);
            printf("Nhấn Enter để bỏ qua trường không muốn chỉnh sửa.\n");

            printf("Tên sách hiện tại: %s\n", BOOKNAMES[i]);
            if (ask_to_edit_field()) {
                printf("Nhập tên sách mới: ");
                safe_input_str(BOOKNAMES[i], sizeof(BOOKNAMES[i]));
            }

            printf("Tác giả hiện tại: %s\n", BOOKAUTHORS[i]);
            if (ask_to_edit_field()) {
                printf("Nhập tác giả mới: ");
                safe_input_str(BOOKAUTHORS[i], sizeof(BOOKAUTHORS[i]));
            }

            printf("Nhà xuất bản hiện tại: %s\n", BOOKPUBLISHERS[i]);
            if (ask_to_edit_field()) {
                printf("Nhập nhà xuất bản mới: ");
                safe_input_str(BOOKPUBLISHERS[i], sizeof(BOOKPUBLISHERS[i]));
            }

            printf("Năm xuất bản hiện tại: %d\n", BOOKYEARS[i]);
            if (ask_to_edit_field()) {
                printf("Nhập năm xuất bản mới: ");
                safe_scanf_int(BOOKYEARS[i]);
                while (BOOKYEARS[i] <= 0) {
                    printf("Năm xuất bản không hợp lệ. Vui lòng nhập lại: ");
                    safe_scanf_int(BOOKYEARS[i]);
                }
            }

            printf("Thể loại hiện tại: %s\n", BOOKGENRES[i]);
            if (ask_to_edit_field()) {
                printf("Nhập thể loại mới: ");
                safe_input_str(BOOKGENRES[i], sizeof(BOOKGENRES[i]));
            }

            printf("Giá sách hiện tại: %s\n", BOOKSHELVES[i]);
            if (ask_to_edit_field()) {
                printf("Nhập giá sách mới: ");
                safe_input_str(BOOKSHELVES[i], sizeof(BOOKSHELVES[i]));
            }

            printf("Số lượng hiện tại: %d\n", BOOKCOUNTS[i]);
            if (ask_to_edit_field()) {
                printf("Nhập số lượng mới: ");
                safe_scanf_int(BOOKCOUNTS[i]);
                while (BOOKCOUNTS[i] < 0) {
                    printf("Số lượng không hợp lệ. Vui lòng nhập lại: ");
                    safe_scanf_int(BOOKCOUNTS[i]);
                }
            }

            printf("Đã cập nhật thông tin cho sách với ISBN %d\n", isbn);
            return;
        }
    }
    printf("Không tìm thấy sách với ISBN %d để chỉnh sửa.\n", isbn);
}
