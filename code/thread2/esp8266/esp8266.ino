#include <ESP8266WiFi.h>
// Finger print library
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
// OLED display library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "defind.h"

// Wifi library
#include <WiFiClientSecure.h>

const char *host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbziXksUeubaKHlDtbA1ktCBU7BpTTEOtgBh5-AyCyKGpm-bGYcwXGpSUqxjrG6eR2tnfw";

// Fingerprint scanner Pins
#define Finger_Rx 14 // D5
#define Finger_Tx 12 // D6
// Declaration for SSD1306 display connected using software I2C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 0     // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial mySerial(Finger_Rx, Finger_Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const char *ssid = "FPT_Error";
const char *password = "nonepassword";

WiFiClientSecure client;

void displayOled(uint8_t choice); // display oled
void clearBuffer();               // clear buffer
String addFingerPrint();          // add fingerprint

void setup()
{
    Serial.begin(115200);
    delay(10);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();

    Serial.println("Adafruit finger detect test");
    finger.begin(57600);
    if (finger.verifyPassword())
    {
        Serial.println("Found fingerprint sensor!");
    }
    else
    {
        Serial.println("Did not find fingerprint sensor :(");
        while (1)
            ;
    }

    finger.getTemplateCount();
    Serial.print("Sensor contains ");
    Serial.print(finger.templateCount);
    Serial.println(" templates");
    Serial.println("Waiting for valid finger...");

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        displayOled(wifi_connect_icon);
        delay(500);
        Serial.print(".");
    }
    displayOled(wifi_connected_icon);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setInsecure(); // set client to use http
}

void loop()
{
    while (true)
    {
        if (Serial.available() > 0)
        {
            char received = Serial.read();
            if (received == 'c')
            {
                Serial.println("Connected");
                break;
            }
            else if (received == "a")
            {
                String studentID = Serial.readStringUntil(';');
                String studentName = Serial.readStringUntil('\n');
                Serial.println("Tên sinh viên: " + studentName);
                Serial.println("Đang nhập vân tay cho sinh viên có mã số: " + studentID);
                String fingerID = addFingerPrint();
                Serial.println("Chờ xác nhận từ server");
                if (sendGoogleSheet(name, studentID, fingerID))
                {
                    Serial.println("Thêm sinh viên thành công");
                }
                else
                {
                    Serial.println("Thêm sinh viên thất bại");
                }
                Serial.println("DONE");
                break;
            }
        }
    }
}

string addFingerPrint()
{
    uint8_t p = finger.getImage();
    displayOled(fingerprint_scan_icon);
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Vân tay đã được lấy");
        break;
    case FINGERPRINT_NOFINGER:
        Serial.print(".");
        return;
    default:
        Serial.println("Lỗi không xác định");
        return;
    }

    displayOled(fingerprint_icon);
    Serial.println("Đang chuyển đổi vân tay");
    p = finger.image2Tz();
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Vân tay đã được chuyển đổi");
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Vân tay quá mờ");
        return;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Lỗi truyền thông");
        return;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Không thể tìm thấy đặc điểm vân tay");
        return;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Không thể tìm thấy đặc điểm vân tay");
        return;
    default:
        Serial.println("Lỗi không xác định");
        return;
    }

    p = finger.createModel();
    Serial.println("Đang tạo mẫu vân tay");
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Đã tạo mẫu vân tay");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Lỗi truyền thông");
        return;
    }
    else if (p == FINGERPRINT_ENROLLMISMATCH)
    {
        Serial.println("Vân tay không khớp");
        return;
    }
    else
    {
        Serial.println("Lỗi không xác định");
        return;
    }
    p = finger.storeModel();
    Serial.println("Đang lưu vân tay");
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Đã lưu vân tay thành công");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Lỗi truyền thông");
        return;
    }
    else if (p == FINGERPRINT_BADLOCATION)
    {
        Serial.println("Vị trí lưu không hợp lệ");
        return;
    }
    else if (p == FINGERPRINT_FLASHERR)
    {
        Serial.println("Lỗi lưu trữ");
        return;
    }
    else
    {
        Serial.println("Lỗi không xác định");
        return;
    }
    return finger.fingerID;
}

void displayOled(uint8_t choice)
{
    if (choice == 1)
    {
        // show username of wifi
        display.clearDisplay();
        display.setTextSize(1);      // Normal 1:1 pixel scale
        display.setTextColor(WHITE); // Draw white text
        display.setCursor(0, 0);     // Start at top-left corner
        display.print(F("Connecting to \n"));
        display.setCursor(0, 50);
        display.setTextSize(2);
        display.print(ssid);
        display.drawBitmap(73, 10, Wifi_start_bits, Wifi_start_width, Wifi_start_height, WHITE);
        display.display();
        delay(1000);
        return;
    }
    if (choice == 2)
    {
        display.clearDisplay();
        display.setTextSize(2);      // Normal 1:1 pixel scale
        display.setTextColor(WHITE); // Draw white text
        display.setCursor(8, 0);     // Start at top-left corner
        display.print(F("Connected \n"));
        display.drawBitmap(33, 15, Wifi_connected_bits, Wifi_connected_width, Wifi_connected_height, WHITE);
        display.display();
        delay(1000);
        return;
    }
    if (choice == 3)
    {
        display.clearDisplay();
        display.drawBitmap(32, 0, FinPr_failed_bits, FinPr_failed_width, FinPr_failed_height, WHITE);
        display.display();
        delay(1000);
        return;
    }

    if (choice == 4)
    {
        display.clearDisplay();
        display.drawBitmap(32, 0, FinPr_scan_bits, FinPr_scan_width, FinPr_scan_height, WHITE);
        display.display();
        delay(1000);
        return;
    }
    if (choice == 5)
    {
        display.clearDisplay();
        display.drawBitmap(32, 0, FinPr_start_bits, FinPr_start_width, FinPr_start_height, WHITE);
        display.display();
        delay(1000);
        return;
    }

    if (choice == 6)
    {
        display.clearDisplay();
        display.drawBitmap(32, 0, FinPr_valid_bits, FinPr_valid_width, FinPr_valid_height, WHITE);
        display.display();
        delay(1000);
        return;
    }

    if (choice == 7)
    {
        display.clearDisplay();
        display.drawBitmap(32, 0, FinPr_invalid_bits, FinPr_invalid_width, FinPr_invalid_height, WHITE);
        display.display();
        delay(1000);
        return;
    }
}

bool sendGoogleSheet(String name, String studentID, String fingerID)
{
    bool result = false;
    if (Serial.available() > 0)
    {
        char received = Serial.read();
        if (received == 'c')
        {
            Serial.println("Đang kết nối tới Google Sheets");
            if (!client.connect(host, httpsPort))
            {
                Serial.println("Kết nối thất bại vui lòng thử lại sau");
                return;
            }
            Serial.println("Kết nối thành công tới Google Sheets");
            String url = "/macros/s/" + GAS_ID + "/exec?type=enrollStudent&studentID=" + studentID + "&studentName=" + name + "&fingerID=" + fingerID;
            Serial.print("Đang gửi yêu cầu: ");
            Serial.println(url);
            client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
            Serial.println("Yêu cầu đã được gửi đi");
            while (client.connected())
            {
                String line = client.readStringUntil('\n');
                if (line == "\r")
                {
                    Serial.println("Đã nhận được phản hồi từ server");
                    break;
                }
            }
            String line = client.readStringUntil('\n');
            if (line == "enroll success")
            {
                Serial.println("Thêm sinh viên thành công");
                result = true;
            }
            else
            {
                Serial.println("Thêm sinh viên thất bại");
                result = false;
            }
            client.stop();
        }
    }
    return result;
}