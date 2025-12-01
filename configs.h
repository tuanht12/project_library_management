/** Số lượng người dùng tối đa */
#define MAX_USERS 100
/** Độ dài tối đa của chuỗi */
#define MAX_STR_LEN 100
/** Cờ hiệu khởi tạo dữ liệu mẫu cho mục đích testing */
#define SHOULD_INIT_DATA_FOR_TESTING 1
/** Số lượng sách tối đa */
#define MAX_BOOKS 100
/** Số lượng bản ghi mượn tối đa */
#define MAX_BORROW_RECORDS 500
/** Số lượng sách mượn tối đa trong một bản ghi mượn */
#define MAX_BORROWED_BOOKS 10
/** Giá bìa tối đa của một cuốn sách (đơn vị: VND) */
#define LATE_FINE_PER_DAY 5000
/** Số ngày mượn tối đa không bị phạt */
#define MAX_BORROW_DAYS 7
/** Hệ số tính phí phạt mất sách */
#define LOST_PENALTY_FACTOR 2
/** Ký tự phân tách trong file CSV */
#define CSV_DELIMITER "|"
/**Ký tự phân tách con*/
#define CSV_SUB_DELIMITER ";"
/** Đường dẫn tới file CSV chứa dữ liệu sách */
#define BOOKS_CSV_PATH "books.csv"
/** Đường dẫn tới file CSV chứa dữ liệu người dùng */
#define USERS_CSV_PATH "users.csv"
/** Đường dẫn tới file CSV chứa dữ liệu phiếu mượn */
#define BORROWS_CSV_PATH "borrows.csv"
/** Kích thước bộ đệm đọc/ghi file CSV */
#define CSV_BUFFER_SIZE 1024
