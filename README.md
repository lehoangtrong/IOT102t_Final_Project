# IOT102t_Final_Project

Dự án Smart Classroom (Phòng học thông minh) là một dự án hỗ trợ sinh viên và giảng viên về sự an toàn cũng như tiện lợi trong cuộc sống.
Là một thiết bị nhỏ trong việc điểm danh sinh viên cũng như hỗ trợ về vấn đề an toàn trong phòng học.

## Lưu ý

Với board Arduino Uno R3 chính hãng sẽ không chạy ổn định, nhất là trên Windows 8.1 (nghe vô lý không?). Để tránh lỗi vui lòng không rút dây USB trong quá trình ứng dụng chạy. Chỉ rút sau khi đã hoàn tất công việc trên ứng dụng. Tất nhiên rồi. Board clone sử dụng CH340G sẽ ổn định hơn, nhưng yêu cầu cài driver. Trường hợp sử dụng clone CH340G vui lòng chọn cài CH34X Driver khi cài ứng dụng, rồi ấn nút Install trong ô cửa sổ hiện lên.

Nếu sử dụng Arduino chính hãng nhưng máy không nhận, vui lòng chọn cài Arduino Driver, và làm theo hướng dẫn trong ô cửa sổ hiện lên.

Trong dự án này, sử dụng 2 luồng dữ liệu là đăng kí và điểm danh cũng như là các vấn đề an toàn trong phòng học hiện nay.

## Cách tạo mạch Arduino UNO

## Cách tạo mạch ESP8266

## Upload sketch

- GitHub repo này có chứa đầy đủ tất cả code, trong đó có sketch để Arduino làm việc
- Tải thư mục code/\* trong GitHub repo này về máy. Có thể clone repo về hoặc tìm file thẳng trên web
- Mở file arduino.ino và esp8266.ino bằng Arduino IDE, rồi upload Sketch vào board.

## Các thư viện dùng trong project

- Adafruit_Fingerprint
- SoftwareSerial
- LiquidCrystal_I2C
- Adafruit_GFX
- Adafruit_SSD1306
- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
