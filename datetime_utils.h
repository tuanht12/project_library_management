extern int CURRENT_YEAR;
extern int CURRENT_MONTH;
extern int CURRENT_DAY;

void get_expiration_date(int creation_year, int creation_month,
                         int creation_day, int& exp_year, int& exp_month,
                         int& exp_day);

void input_date(int& year, int& month, int& day);
void get_date_string(char date_str[11], int year, int month, int day);
void initialize_current_date();
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
int calculate_days_between(int from_year, int from_month, int from_day,
                              int to_year, int to_month, int to_day);
int is_record_returned(int record_index);
