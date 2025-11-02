#include "configs.h"
/**
 * @brief Mảng chứa mã ISBN của tất cả cuốn sách trong hệ thống
 *
 * Giá trị 0 biểu thị slot trống, các giá trị khác là mã ISBN hợp lệ
 *
 * @note Index của mảng này tương ứng với index của các mảng sách khác
 */
extern int ISBNS[MAX_BOOKS];

/**
 * @brief Mảng chứa tên của các cuốn sách
 *
 * Chuỗi rỗng ("") biểu thị slot trống
 *
 * @note Độ dài tối đa mỗi tên sách là MAX_STR_LEN ký tự
 */
extern char BOOKNAMES[MAX_BOOKS][MAX_STR_LEN];

/**
 * @brief Mảng chứa tác giả của các cuốn sách
 *
 * Chuỗi rỗng ("") biểu thị slot trống hoặc không có tác giả
 */
extern char BOOKAUTHORS[MAX_BOOKS][MAX_STR_LEN];

/**
 * @brief Mảng chứa nhà xuất bản của các cuốn sách
 *
 * Chuỗi rỗng ("") biểu thị slot trống hoặc không có nhà xuất bản
 */
extern char BOOKPUBLISHERS[MAX_BOOKS][MAX_STR_LEN];

/**
 * @brief Mảng chứa năm xuất bản của các cuốn sách
 *
 * Giá trị 0 biểu thị slot trống hoặc không có năm xuất bản
 */
extern int BOOKYEARS[MAX_BOOKS];

/**
 * @brief Mảng chứa thể loại của các cuốn sách
 *
 * Chuỗi rỗng ("") biểu thị slot trống hoặc không có thể loại
 */
extern char BOOKGENRES[MAX_BOOKS][MAX_STR_LEN];

/**
 * @brief Mảng chứa giá của các cuốn sách
 *
 * Giá trị 0 biểu thị slot trống hoặc không có giá
 */
extern int BOOKPRICES[MAX_BOOKS];

/**
 * @brief Mảng chứa số lượng bản sao hiện có của các cuốn sách
 *
 * Giá trị 0 biểu thị slot trống hoặc không còn bản sao nào
 */

/**
 * @brief Mảng chứa số lượng bản sao hiện có của các cuốn sách
 *
 * Giá trị 0 biểu thị slot trống hoặc không còn bản sao nào
 */
extern int BOOKCOUNTS[MAX_BOOKS];

/**
 * @brief Khởi tạo một cuốn sách về trạng thái rỗng
 * @param index Chỉ số cuốn sách cần khởi tạo trong mảng
 */
void initialize_one_book_data(int index);

/**
 * @brief Khởi tạo tất cả mảng dữ liệu sách về trạng thái rỗng
 */
void initialize_book_data();

/**
 * @brief Tạo dữ liệu sách mẫu để test hệ thống
 *
 * Tạo 10 cuốn sách giả với thông tin đầy đủ
 */
void initialize_test_books();

/**
 * @brief In danh sách tất cả sách trong hệ thống
 */
void print_all_books();

/**
 * @brief Thêm một cuốn sách mới vào hệ thống.
 *
 * Nếu cuốn sách với mã ISBN đã tồn tại, số lượng bản sao sẽ được
 * cập nhật bằng cách cộng thêm `num_copies`.
 * Ngược lại, thêm cuốn sách mới với thông tin chi tiết được nhập từ người dùng.
 *
 * @param isbn Mã ISBN của cuốn sách
 * @param num_copies Số lượng bản sao của cuốn sách
 * @note Nếu số lượng bản sao không hợp lệ (<= 0),
 * hoặc hệ thống đã đầy, hàm sẽ in thông báo lỗi và không thực hiện thêm sách.
 */
void add_book(int isbn, int num_copies);

/**
 * @brief Chỉnh sửa thông tin của một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, nó sẽ cho phép người dùng chỉnh sửa các thông tin liên quan
 * đến cuốn sách đó.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 *
 * @param isbn Mã ISBN của cuốn sách cần chỉnh sửa.
 */
void edit_book_info(int isbn);

/**
 * @brief Xóa một cuốn sách khỏi hệ thống dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm trong mảng `ISBNS` để tìm một cuốn sách có mã ISBN
 * trùng khớp. Khi tìm thấy, nó sẽ gọi hàm `initialize_one_book_data()` để
 * đặt lại tất cả thông tin của cuốn sách tại vị trí đó về giá trị mặc định.
 * Đây là một phương pháp "xóa mềm" (soft delete).
 *
 * @param isbn Mã ISBN của cuốn sách cần xóa.
 *
 * @example
 * // Giả sử sách có ISBN 1001 tồn tại
 * delete_book(1001); // In ra: "Đã xóa sách với ISBN 1001 khỏi hệ thống."
 *
 * // Giả sử sách có ISBN 9999 không tồn tại
 * delete_book(9999); // In ra: "Không tìm thấy sách với ISBN 9999 để xóa."
 */
void delete_book(int isbn);

/**
 * @brief In thông tin chi tiết của một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, nó sẽ in ra tất cả thông tin liên quan đến cuốn sách đó
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 *
 * @param isbn Mã ISBN của cuốn sách cần in thông tin.
 */
void print_book_info_by_isbn(int isbn, int with_header = 1);

/**
 * @brief In thông tin chi tiết của một cuốn sách dựa trên tên sách.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `BOOKNAMES` dựa trên tên sách được cung
 * cấp. Nếu tìm thấy, nó sẽ in ra tất cả thông tin liên quan đến cuốn sách đó.
 * Nếu không tìm thấy cuốn sách với tên đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 *
 * @param book_name Tên của cuốn sách cần in thông tin.
 */
void print_book_info_by_name(const char book_name[MAX_STR_LEN]);

/**
 * @brief Chỉnh sửa thông tin của một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, nó sẽ cho phép người dùng chỉnh sửa các thông tin liên quan
 * đến cuốn sách đó.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 *
 * @param isbn Mã ISBN của cuốn sách cần chỉnh sửa.
 */
void edit_book_info(int isbn);

/**
 * @brief Mượn một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy và số lượng sách hiện có lớn hơn 0, hàm sẽ giảm số lượng
 * sách đi 1 và in ra thông báo mượn sách thành công.
 * Nếu số lượng sách hiện có bằng 0 hoặc không tìm thấy cuốn sách với mã ISBN đã
 * cho, hàm sẽ in ra thông báo mượn sách không thành công.
 *
 * @param isbn Mã ISBN của cuốn sách cần mượn.
 *
 * @return Trả về 1 nếu mượn sách thành công, 0 nếu không thành công.
 */
int borrow_book(int isbn);

/**
 * @brief Trả một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, hàm sẽ tăng số lượng sách hiện có lên 1 và in ra
 * thông báo trả sách thành công.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 *
 * @param isbn Mã ISBN của cuốn sách cần trả.
 * @return Trả về 1 nếu trả sách thành công, 0 nếu không thành công.
 */
int return_book(int isbn);

/**
 * @brief Lấy giá của một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, hàm sẽ trả về giá của cuốn sách từ mảng `BOOKPRICES`.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ trả về 0.
 *
 * @param isbn Mã ISBN của cuốn sách cần lấy giá.
 *
 * @return Giá của cuốn sách nếu tìm thấy, 0 nếu không tìm thấy.
 */
int get_price_by_isbn(int isbn);

/**
 * @brief Lấy tên của một cuốn sách dựa trên mã ISBN.
 *
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, hàm sẽ sao chép tên của cuốn sách từ mảng `BOOKNAMES`
 * vào biến `book_name`.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ
 * gán chuỗi "Unknown Book" vào biến `book_name`.
 *
 * @param isbn Mã ISBN của cuốn sách cần lấy tên.
 * @param book_name Biến để lưu tên của cuốn sách.
 */
void get_book_name_by_isbn(int isbn, char book_name[MAX_STR_LEN]);
