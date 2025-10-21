extern int ISBNS[100];
extern char BOOKNAMES[100][100];
extern char BOOKAUTHORS[100][100];
extern char BOOKPUBLISHERS[100][100];
extern int BOOKYEARS[100];
extern char BOOKGENRES[100][100];
extern int BOOKPRICES[100];
extern int BOOKCOUNTS[100];

void initialize_book_data();
void initialize_test_books();

void print_all_books();
void add_book(int isbn, int num_copies);
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
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, nó sẽ in ra tất cả thông tin liên quan đến cuốn sách đó,
 * bao gồm tên sách, tác giả, nhà xuất bản, năm xuất bản, thể loại,
 * giá sách và số lượng hiện có.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 * @param isbn Mã ISBN của cuốn sách cần in thông tin.
 */
void print_book_info_by_isbn(int isbn, int with_header = 1);

/**
 * @brief In thông tin chi tiết của một cuốn sách dựa trên tên sách.
 * Hàm này tìm kiếm cuốn sách trong mảng `BOOKNAMES` dựa trên tên sách được cung
 * cấp. Nếu tìm thấy, nó sẽ in ra tất cả thông tin liên quan đến cuốn sách đó,
 * bao gồm mã ISBN, tác giả, nhà xuất bản, năm xuất bản, thể loại,
 * giá sách và số lượng hiện có.
 * Nếu không tìm thấy cuốn sách với tên đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 * @param book_name Tên của cuốn sách cần in thông tin.
 */
void print_book_info_by_name(const char book_name[100]);

/**
 * @brief Chỉnh sửa thông tin của một cuốn sách dựa trên mã ISBN.
 * Hàm này tìm kiếm cuốn sách trong mảng `ISBNS` dựa trên mã ISBN được cung cấp.
 * Nếu tìm thấy, nó sẽ cho phép người dùng chỉnh sửa các thông tin liên quan
 * đến cuốn sách đó, bao gồm tên sách, tác giả, nhà xuất bản, năm xuất bản,
 * thể loại, giá sách và số lượng hiện có.
 * Nếu không tìm thấy cuốn sách với mã ISBN đã cho, hàm sẽ in ra
 * một thông báo rằng cuốn sách không tồn tại trong hệ thống.
 * @param isbn Mã ISBN của cuốn sách cần chỉnh sửa.
 */
void edit_book_info(int isbn);
