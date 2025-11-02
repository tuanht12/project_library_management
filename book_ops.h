#include "configs.h"
/** @brief Mảng chứa ID của các phiếu mượn sách */
extern int BORROW_CARD_IDS[MAX_BORROW_RECORDS];

/** @brief Mảng chứa CMND của người mượn tương ứng với mỗi phiếu mượn */
extern int BORROW_USER_IDS[MAX_BORROW_RECORDS];

/** @brief Mảng chứa ngày mượn sách của mỗi phiếu mượn
 * Định dạng: [năm, tháng, ngày]
 */
extern int BORROW_DATES[MAX_BORROW_RECORDS][3];

/** @brief Mảng chứa ngày dự kiến trả sách của mỗi phiếu mượn
 * Định dạng: [năm, tháng, ngày]
 */
extern int EXPECTED_RETURN_DATES[MAX_BORROW_RECORDS][3];

/** @brief Mảng chứa ngày trả thực tế của mỗi phiếu mượn
 *
 * Định dạng: [năm, tháng, ngày]. Nếu chưa trả, giá trị là [0, 0, 0]
 */
extern int ACTUAL_RETURN_DATES[MAX_BORROW_RECORDS][3];

/** @brief Mảng chứa ISBN các sách được mượn trong mỗi phiếu mượn */
extern int BORROWED_ISBNS[MAX_BORROW_RECORDS][MAX_BORROWED_BOOKS];

/** @brief Mảng chứa phí phạt trễ hạn cho mỗi phiếu mượn */
extern long LATE_PENALTIES[MAX_BORROW_RECORDS];

/** @brief Mảng chứa phí phạt mất sách cho mỗi sách trong mỗi phiếu mượn */
extern long LOST_PENALTIES[MAX_BORROW_RECORDS][MAX_BORROWED_BOOKS];

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
