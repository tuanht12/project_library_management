#!/bin/bash

echo "Đang biên dịch dự án..."

g++ *.cpp -o library_app -Wall -std=c++17

echo "Biên dịch hoàn tất! Chạy bằng lệnh: ./library_app"