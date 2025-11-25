#include "configs.h"

/**
 * @brief Cấu trúc dữ liệu chứa thông tin phiếu mượn sách
 *
 * Giá trị card_id = 0 biểu thị slot trống
 */
struct BorrowRecord {
    int card_id;                  // ID phiếu mượn (0 = slot trống)
    int user_id;                  // CMND người mượn
    int borrow_date[3];           // Ngày mượn [năm, tháng, ngày]
    int expected_return_date[3];  // Ngày dự kiến trả [năm, tháng, ngày]
    int actual_return_date[3];  // Ngày trả thực tế [năm, tháng, ngày] (0,0,0 =
                                // chưa trả)
    int borrowed_isbns[MAX_BORROWED_BOOKS];   // Danh sách ISBN sách được mượn
    long late_penalty;                        // Phí phạt trễ hạn (VND)
    long lost_penalties[MAX_BORROWED_BOOKS];  // Phí phạt mất sách cho từng cuốn
                                              // (VND)
};

/**
 * @brief Mảng chứa tất cả phiếu mượn sách trong hệ thống
 */
extern BorrowRecord BORROW_RECORDS[MAX_BORROW_RECORDS];

/**
 * @brief Khởi tạo một phiếu mượn sách về trạng thái rỗng
 * @param index Chỉ số phiếu mượn cần khởi tạo
 */
void initialize_one_borrow_card(int index);

/**
 * @brief Khởi tạo tất cả mảng dữ liệu phiếu mượn về trạng thái rỗng
 */
void initialize_borrow_data();

/**
 * @brief Khởi tạo dữ liệu mẫu cho 5 phiếu mượn sách để testing.
 * Hàm này tạo ra các kịch bản khác nhau: đang mượn, đã trả, trễ hạn...
 */
void initialize_test_borrows();

/**
 * @brief Tạo phiếu mượn sách mới
 *
 * Yêu cầu nhập CMND người mượn và danh sách ISBN các sách cần mượn.
 * Thiết lập ngày mượn là ngày hiện tại và tính toán ngày dự kiến trả.
 *
 * @note Nếu người dùng không tồn tại hoặc đã hết hạn, phiếu mượn sẽ không được
 * tạo.
 * @note Nếu không có sách nào được mượn, phiếu mượn sẽ bị hủy.
 * @note Nếu hệ thống đã đạt giới hạn tối đa phiếu mượn, không thể tạo phiếu
 * mới.
 */
void create_borrow_card();

/**
 * @brief Tạo phiếu trả sách
 *
 * Yêu cầu nhập ID phiếu mượn để trả sách.
 * Cập nhật ngày trả thực tế là ngày hiện tại.
 * Yêu cầu nhập thông tin về việc mất sách và tính toán phí phạt nếu có.
 *
 * @note Nếu phiếu mượn không tồn tại hoặc đã được trả trước đó, không thể tạo
 * phiếu trả.
 */
void create_return_card();

/**
 * @brief Tính toán phí phạt trễ hạn dựa trên ngày mượn và ngày trả
 *
 * Phí phạt trễ hạn được tính là `LATE_FINE_PER_DAY` VND
 * cho mỗi ngày trễ hạn sau `MAX_BORROW_DAYS` ngày mượn.
 *
 * @param borrow_year Năm mượn sách
 * @param borrow_month Tháng mượn sách
 * @param borrow_day Ngày mượn sách
 * @param return_year Năm trả sách
 * @param return_month Tháng trả sách
 * @param return_day Ngày trả sách
 * @return Số tiền phạt trễ hạn (nếu có), 0 nếu không trễ hạn
 */
long calculate_late_penalty(int borrow_year, int borrow_month, int borrow_day,
                            int return_year, int return_month, int return_day);
/**
 * @brief Tính toán phí phạt mất sách dựa trên ISBN của sách
 * @param isbn ISBN của cuốn sách bị mất
 * @return Số tiền phạt mất sách
 */
long calculate_lost_penalty_by_isbn(int isbn);

/**
 * @brief In chi tiết một bản ghi mượn sách dựa trên ID phiếu mượn
 * @param card_id ID của phiếu mượn cần in
 */
void print_a_borrow_record(int card_id);

/**
 * @brief In danh sách tất cả bản ghi mượn sách chưa trả
 */
void print_unreturned_borrows();

/**
 * @brief In danh sách tất cả bản ghi mượn sách đã trả
 */
void print_finished_returns();

/**
 * @brief In danh sách tất cả bản ghi mượn sách
 */
void print_all_borrow_records();

/**
 * @brief In danh sách sách đã mượn của người dùng theo tên
 *
 * @param username Tên người dùng
 */
void print_borrowed_books_by_username(char username[MAX_STR_LEN]);
