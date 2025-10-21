extern int BORROW_CARD_IDS[1000];
extern int BORROW_USER_IDS[1000];
extern int BORROW_DATES[1000][3];
extern int EXPECTED_RETURN_DATES[1000][3];
extern int ACTUAL_RETURN_DATES[1000][3];
extern int BORROWED_ISBNS[1000][10];
extern long LATE_PENALTIES[1000];
extern long LOST_PENALTIES[1000][10];

void initialize_borrow_data();
/**
 * @brief Khởi tạo dữ liệu mẫu cho 5 phiếu mượn sách để testing.
 * Hàm này tạo ra các kịch bản khác nhau: đang mượn, đã trả, trễ hạn...
 * Nó cũng tự động cập nhật số lượng sách trong kho cho các sách đang được mượn.
 */
void initialize_test_borrows();

void create_borrow_card();

void create_return_card();

long calculate_late_penalty(int borrow_year, int borrow_month, int borrow_day,
                            int return_year, int return_month, int return_day);
long calculate_lost_penalty_by_isbn(int isbn);
void print_unreturned_borrows();
void print_finished_returns();
void print_a_borrow_record(int card_id);
void print_all_borrow_records();
