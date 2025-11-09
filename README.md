# 📚 Hệ Thống Quản Lý Thư Viện

Một hệ thống quản lý thư viện đơn giản được viết bằng C++, hỗ trợ quản lý người dùng, sách và các thao tác mượn/trả sách.

## 🚀 Tính Năng Chính

### 👥 Quản Lý Người Dùng
- ✅ Đăng ký người dùng mới
- ✅ Xem thông tin người dùng
- ✅ Chỉnh sửa thông tin người dùng
- ✅ Xóa người dùng
- ✅ Kiểm tra tài khoản hết hạn
- ✅ Xem danh sách tất cả người dùng

### 📖 Quản Lý Sách
- ✅ Thêm sách mới vào thư viện
- ✅ Xem thông tin chi tiết sách
- ✅ Chỉnh sửa thông tin sách
- ✅ Xóa sách khỏi thư viện
- ✅ Tìm kiếm sách theo tên/tác giả/thể loại
- ✅ Xem danh sách tất cả sách

### 🔄 Quản Lý Mượn/Trả Sách
- ✅ Mượn sách (hỗ trợ mượn nhiều sách cùng lúc)
- ✅ Trả sách
- ✅ Xem lịch sử mượn sách của người dùng
- ✅ Tính phí phạt trễ hạn
- ✅ Xử lý sách bị mất
- ✅ Gia hạn thời gian mượn

### 📊 Thống Kê
- ✅ Tổng số sách trong thư viện
- ✅ Số lượng sách theo thể loại
- ✅ Số lượng người dùng
- ✅ Phân loại người dùng theo giới tính
- ✅ Số sách đang được mượn

## 🛠️ Yêu Cầu Hệ Thống

- **Compiler**: GCC 7.0+ hoặc Clang 5.0+ (hỗ trợ C++17)
- **Hệ điều hành**: Linux, macOS, Windows (với MinGW)
- **RAM**: Tối thiểu 512MB
- **Dung lượng**: 50MB trống

## 📦 Cài Đặt và Biên Dịch

### Trên Linux/macOS:

```bash
# Clone repository
git clone https://github.com/tuanht12/project_library_management.git
cd project_library_management

# Biên dịch dự án
chmod +x build.sh
./build.sh

# Chạy ứng dụng
./library_app
```

### Trên Windows:

```bash
# Với MinGW hoặc MSYS2
g++ *.cpp -o library_app.exe -Wall -std=c++17

# Chạy ứng dụng
library_app.exe
```

### Biên dịch thủ công:

```bash
g++ main.cpp users.cpp books.cpp book_ops.cpp menu.cpp stats.cpp datetime_utils.cpp utils.cpp -o library_app -Wall -std=c++17
```

## 🎮 Cách Sử Dụng

### Khởi động ứng dụng:
```bash
./library_app
```

### Menu chính:
```
========== HỆ THỐNG QUẢN LÝ THỦ VIỆN ==========
1. Quản lý người dùng
2. Quản lý sách
3. Mượn/Trả sách
4. Thống kê
5. Thoát
================================================
```

### Dữ liệu mẫu:
Hệ thống tự động tạo dữ liệu mẫu khi khởi động (có thể tắt trong `configs.h`):
- 5 người dùng mẫu
- 10 cuốn sách mẫu
- Một số bản ghi mượn sách mẫu

## ⚙️ Cấu Hình

Chỉnh sửa file `configs.h` để thay đổi các thông số:

```cpp
#define MAX_USERS 100              // Số người dùng tối đa
#define MAX_STR_LEN 100           // Độ dài chuỗi tối đa
#define MAX_BOOKS 100             // Số sách tối đa
#define MAX_BORROW_RECORDS 500    // Số bản ghi mượn tối đa
#define MAX_BORROWED_BOOKS 10     // Số sách mượn cùng lúc tối đa
#define LATE_FINE_PER_DAY 5000    // Phí phạt mỗi ngày (VND)
#define MAX_BORROW_DAYS 7         // Số ngày mượn tối đa
#define LOST_PENALTY_FACTOR 2     // Hệ số phạt mất sách
```

## 📁 Cấu Trúc Dự Án

```
project_library_management/
├── main.cpp              # File chính
├── configs.h             # Cấu hình hệ thống
├── users.h/.cpp          # Quản lý người dùng
├── books.h/.cpp          # Quản lý sách  
├── book_ops.h/.cpp       # Thao tác mượn/trả sách
├── menu.h/.cpp           # Giao diện menu
├── stats.h/.cpp          # Thống kê
├── datetime_utils.h/.cpp # Xử lý ngày tháng
├── utils.h/.cpp          # Tiện ích chung
├── build.sh              # Script biên dịch
└── README.md             # Tài liệu này
```

## 💾 Cấu Trúc Dữ Liệu

### Người dùng:
- CMND (ID duy nhất)
- Tên đầy đủ
- Ngày sinh
- Giới tính
- Email
- Địa chỉ
- Ngày tạo tài khoản
- Ngày hết hạn

### Sách:
- ISBN (ID duy nhất)
- Tên sách
- Tác giả
- Thể loại
- Nhà xuất bản
- Năm xuất bản
- Số lượng
- Giá bìa

### Bản ghi mượn:
- ID bản ghi
- CMND người mượn
- Danh sách ISBN sách mượn
- Ngày mượn
- Ngày dự kiến trả
- Ngày trả thực tế
- Trạng thái

## 🔍 Ví Dụ Sử Dụng

### Đăng ký người dùng mới:
```
Chọn: 1 -> 1 -> Nhập CMND -> Nhập thông tin
```

### Thêm sách mới:
```
Chọn: 2 -> 1 -> Nhập ISBN -> Nhập thông tin sách
```

### Mượn sách:
```
Chọn: 3 -> 1 -> Nhập CMND -> Nhập ISBN sách cần mượn
```

### Xem thống kê:
```
Chọn: 4 -> Chọn loại thống kê muốn xem
```

## 🐛 Xử Lý Lỗi

Hệ thống xử lý các trường hợp lỗi phổ biến:
- ✅ Kiểm tra dữ liệu đầu vào
- ✅ Xử lý người dùng/sách không tồn tại
- ✅ Kiểm tra số lượng sách khả dụng
- ✅ Xác thực ngày tháng
- ✅ Xử lý tài khoản hết hạn

## 🤝 Đóng Góp

1. Fork dự án
2. Tạo branch cho tính năng mới (`git checkout -b feature/AmazingFeature`)
3. Commit thay đổi (`git commit -m 'Add some AmazingFeature'`)
4. Push lên branch (`git push origin feature/AmazingFeature`)
5. Tạo Pull Request

## 📜 Giấy Phép

Dự án này được phát hành dưới giấy phép MIT. Xem file `LICENSE` để biết thêm chi tiết.

## 👨‍💻 Tác Giả

- **TuanHT** - *Developer* - [tuanht12](https://github.com/tuanht12)

## 🙏 Lời Cảm Ơn

- Giảng viên môn Nhập Môn Lập Trình
- Các bạn sinh viên đã đóng góp ý kiến

## 📞 Liên Hệ

- Email: [thanhtuan97dn@gmail.com]
- GitHub: [@tuanht12](https://github.com/tuanht12)

---

⭐ **Nếu dự án này hữu ích, hãy cho một Star nhé!** ⭐