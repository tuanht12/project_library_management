/**
 * @brief Xóa bỏ tất cả ký tự còn lại trong buffer đầu vào
 *
 * Hàm này loại bỏ các ký tự thừa trong input buffer, thường được sử dụng
 * sau các lệnh scanf() để tránh việc các ký tự thừa (đặc biệt là '\n')
 * ảnh hưởng đến các lần nhập liệu tiếp theo.
 *
 * @note Nên gọi hàm này sau mỗi lần sử dụng scanf()
 * @warning Không nên gọi trước khi sử dụng fgets() vì có thể gây treo chương
 * trình
 */
void cleanup_input_buffer();

/**
 * @brief Nhập chuỗi ký tự an toàn từ người dùng
 *
 * Hàm này sử dụng fgets() để đọc một dòng văn bản từ stdin một cách an toàn,
 * tự động loại bỏ ký tự xuống dòng '\n' ở cuối chuỗi.
 *
 * @param buffer Mảng ký tự để lưu trữ chuỗi nhập vào (tối đa 100 ký tự)
 * @param size Kích thước tối đa của chuỗi có thể đọc (bao gồm null terminator)
 *
 * @note Hàm này an toàn hơn gets() vì tránh được buffer overflow
 * @note Ký tự '\n' sẽ được tự động loại bỏ khỏi chuỗi kết quả
 */
void safe_input_str(char buffer[100], int size);

/**
 * @brief Nhập một số nguyên an toàn từ người dùng
 *
 * Hàm này sử dụng scanf() để đọc một số nguyên từ stdin và sau đó
 * gọi cleanup_input_buffer() để loại bỏ các ký tự thừa trong buffer đầu vào.
 *
 * @param var Biến tham chiếu để lưu trữ số nguyên nhập vào
 *
 * @example
 * int age;
 * printf("Mời bạn nhập tuổi: ");
 * safe_scanf_int(age);
 * // Biến 'age' bây giờ chứa một giá trị số nguyên hợp lệ.
 */
void safe_scanf_int(int& var);

/**
 * @brief Hỏi người dùng có muốn chỉnh sửa trường thông tin hay không
 *
 * Hàm này sẽ yêu cầu người dùng nhập vào "y" để xác nhận, Enter để bỏ qua.
 *
 * @return 1 nếu người dùng muốn chỉnh sửa, 0 nếu không muốn
 */
int ask_to_edit_field();

/**
 * @brief Nhập một số nguyên dài an toàn từ người dùng
 *
 * Hàm này sử dụng scanf() để đọc một số nguyên dài từ stdin và sau đó
 * gọi cleanup_input_buffer() để loại bỏ các ký tự thừa trong buffer đầu vào.
 *
 * @param var Biến tham chiếu để lưu trữ số nguyên dài nhập vào
 *
 * @example
 * long age;
 * printf("Mời bạn nhập giá tiền: ");
 * safe_scanf_long(price);
 * // Biến 'price]' bây giờ chứa một giá trị số nguyên hợp lệ.
 */
void safe_scanf_long(long& var);