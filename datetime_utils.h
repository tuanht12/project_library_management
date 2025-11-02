/** @brief Năm hiện tại của hệ thống */
extern int CURRENT_YEAR;
/** @brief Tháng hiện tại của hệ thống */
extern int CURRENT_MONTH;
/** @brief Ngày hiện tại của hệ thống */
extern int CURRENT_DAY;

/**
 * @brief Khởi tạo ngày hiện tại từ hệ thống
 *
 * Lấy ngày hiện tại từ hệ thống và gán vào các biến toàn cục
 */
void initialize_current_date();

/**
 * @brief Tính ngày hết hạn tài khoản dựa trên ngày tạo
 *
 * Tài khoản có hạn sử dụng là 48 tháng kể từ ngày tạo.
 *
 * @param creation_year Năm tạo tài khoản
 * @param creation_month Tháng tạo tài khoản
 * @param creation_day Ngày tạo tài khoản
 * @param exp_year Tham chiếu để lưu năm hết hạn
 * @param exp_month Tham chiếu để lưu tháng hết hạn
 * @param exp_day Tham chiếu để lưu ngày hết hạn
 */
void get_expiration_date(int creation_year, int creation_month,
                         int creation_day, int& exp_year, int& exp_month,
                         int& exp_day);

/**
 * @brief Kiểm tra năm nhuận
 *
 * @param year Năm cần kiểm tra
 * @return 1 nếu là năm nhuận, 0 nếu không
 */
int check_leap_year(int year);

/**
 * @brief Kiểm tra tính hợp lệ của một ngày tháng năm
 *
 * @param year Năm
 * @param month Tháng
 * @param day Ngày
 * @return 1 nếu ngày hợp lệ, 0 nếu không hợp lệ
 */
int check_valid_date(int year, int month, int day);

/**
 * @brief Nhập ngày tháng năm từ người dùng
 *
 * Yêu cầu người dùng nhập ngày tháng năm theo định dạng DD/MM/YYYY.
 * Hàm sẽ lặp lại yêu cầu nhập cho đến khi nhận được ngày hợp lệ.
 *
 * @param year Tham chiếu để lưu năm
 * @param month Tham chiếu để lưu tháng
 * @param day Tham chiếu để lưu ngày
 */
void input_date(int& year, int& month, int& day);

/**
 * @brief Chuyển đổi ngày tháng năm thành chuỗi định dạng "DD/MM/YYYY"
 *
 * @param date_str Mảng ký tự để lưu chuỗi kết quả (phải đủ lớn để chứa 11 ký
 * tự)
 * @param year Năm
 * @param month Tháng
 * @param day Ngày
 */
void get_date_string(char date_str[11], int year, int month, int day);

/**
 * @brief Tính ngày trả sách dự kiến dựa trên ngày mượn
 * Hàm này cộng thêm 7 ngày vào ngày mượn để tính ngày trả dự kiến.
 *
 * @param borrow_year Năm mượn sách
 * @param borrow_month Tháng mượn sách
 * @param borrow_day Ngày mượn sách
 * @param return_year Tham chiếu để lưu năm trả dự kiến
 * @param return_month Tham chiếu để lưu tháng trả dự kiến
 * @param return_day Tham chiếu để lưu ngày trả dự kiến
 */
void get_expected_return_date(int borrow_year, int borrow_month, int borrow_day,
                              int& return_year, int& return_month,
                              int& return_day);

/**
 * @brief Tính số ngày giữa hai ngày
 * @param from_year Năm của ngày bắt đầu
 * @param from_month Tháng của ngày bắt đầu
 * @param from_day Ngày của ngày bắt đầu
 * @param to_year Năm của ngày kết thúc
 * @param to_month Tháng của ngày kết thúc
 * @param to_day Ngày của ngày kết thúc
 * @return Số ngày giữa hai ngày
 */
int calculate_days_between(int from_year, int from_month, int from_day,
                           int to_year, int to_month, int to_day);
