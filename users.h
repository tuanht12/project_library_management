#include "configs.h"

/**
 * @brief Mảng chứa CMND của tất cả người dùng trong hệ thống
 *
 * Giá trị 0 biểu thị slot trống, các giá trị khác là CMND hợp lệ
 *
 * @note Index của mảng này tương ứng với index của các mảng người dùng khác
 */
extern int USERIDS[MAX_USERS];

/**
 * @brief Mảng chứa tên đầy đủ của người dùng
 *
 * Chuỗi rỗng ("") biểu thị slot trống
 *
 * @note Độ dài tối đa mỗi tên là MAX_STR_LEN ký tự
 */
extern char USERNAMES[MAX_USERS][MAX_STR_LEN];

/**
 * @brief Mảng chứa giới tính của người dùng
 *
 * 0: Nữ, 1: Nam, -1: Slot trống
 */
extern int USER_GENDERS[MAX_USERS];

/**
 * @brief Mảng chứa địa chỉ email của người dùng
 *
 * Chuỗi rỗng ("") biểu thị slot trống hoặc không có email
 */
extern char USER_EMAILS[MAX_USERS][MAX_STR_LEN];

/**
 * @brief Mảng chứa địa chỉ thường trú của người dùng
 *
 * Chuỗi rỗng ("") biểu thị slot trống hoặc không có địa chỉ
 */
extern char USER_ADDRESSES[MAX_USERS][MAX_STR_LEN];

/**
 * @brief Mảng chứa ngày sinh của người dùng
 *
 * Định dạng: [năm, tháng, ngày]. VD: [1990, 5, 15] = 15/5/1990
 *
 * @note [0, 0, 0] biểu thị slot trống hoặc ngày sinh chưa được thiết lập
 */
extern int USER_BIRTHDATES[MAX_USERS][3];

/**
 * @brief Mảng chứa ngày tạo tài khoản của người dùng
 *
 * Định dạng: [năm, tháng, ngày]. Tự động thiết lập khi đăng ký
 *
 * @note [0, 0, 0] biểu thị slot trống
 */
extern int USER_CREATION_DATES[MAX_USERS][3];

/**
 * @brief Mảng chứa ngày hết hạn tài khoản của người dùng
 *
 * Định dạng: [năm, tháng, ngày]. Tài khoản hết hạn không thể mượn sách
 *
 * @note [0, 0, 0] biểu thị tài khoản không có hạn sử dụng
 */
extern int USER_EXPIRATION_DATES[MAX_USERS][3];

/**
 * @brief Khởi tạo một người dùng về trạng thái rỗng
 * @param index Chỉ số người dùng cần khởi tạo
 */
void initialize_one_user_data(int index);

/**
 * @brief Khởi tạo tất cả mảng dữ liệu người dùng về trạng thái rỗng
 */
void initialize_user_data();

/**
 * @brief Tạo dữ liệu người dùng mẫu để test hệ thống
 *
 * Tạo một số tài khoản người dùng giả với thông tin đầy đủ
 */
void initialize_test_users();

/**
 * @brief Lấy mã số bạn đọc từ CMND là chỉ số nội bộ trong mảng + 1
 * @param user_id CMND của người dùng
 * @return Mã số bạn đọc nếu tìm thấy, 0 nếu không tìm thấy
 */
int get_user_internal_id(int user_id);

/**
 * @brief Kiểm tra xem người dùng có tồn tại trong hệ thống hay không
 * @param user_id CMND của người dùng cần kiểm tra
 * @return 1 nếu người dùng tồn tại, 0 nếu không tồn tại
 */
int is_existing_user(int user_id);

/**
 * @brief Kiểm tra xem tài khoản người dùng đã hết hạn hay chưa
 * @param user_id CMND của người dùng cần kiểm tra
 * @return 1 nếu tài khoản đã hết hạn, 0 nếu còn hạn hoặc không có hạn
 */
int is_user_expired(int user_id);

/**
 * @brief Đăng ký người dùng mới vào hệ thống
 * @param user_id CMND của người dùng mới (phải là duy nhất)
 * @note Nếu CMND đã tồn tại hoặc hệ thống đã đầy người dùng,
 * hàm sẽ in thông báo lỗi và không thực hiện đăng ký
 */
void register_user(int user_id);

/**
 * @brief In thông tin chi tiết của một người dùng
 * @param user_id CMND của người dùng cần in thông tin
 * @param with_header Có in header với tiêu đề hay không (mặc định là có)
 */
void print_user_info(int user_id, int with_header = 1);

/**
 * @brief In danh sách tất cả người dùng trong hệ thống
 *
 * In thông tin cơ bản của tất cả người dùng đã đăng ký
 */
void print_all_users();

/**
 * @brief Chỉnh sửa thông tin của người dùng đã tồn tại
 * @param user_id CMND của người dùng cần chỉnh sửa
 * @note Không thể thay đổi CMND, ngày tạo và ngày hết hạn tài khoản
 */
void edit_user_info(int user_id);

/**
 * @brief Xóa người dùng khỏi hệ thống
 *
 * Thiết lập lại tất cả thông tin về trạng thái rỗng
 *
 * @param user_id CMND của người dùng cần xóa
 *
 * @warning Không thể khôi phục sau khi xóa
 */
void delete_user(int user_id);

/**
 * @brief Lấy tên người dùng theo CMND
 *
 * Sao chép tên người dùng vào buffer username
 *
 * @param user_id CMND của người dùng
 * @param username Buffer để lưu tên người dùng
 * @note Nếu người dùng không tồn tại, username sẽ là chuỗi rỗng
 */
void get_user_name_by_id(int user_id, char username[MAX_STR_LEN]);