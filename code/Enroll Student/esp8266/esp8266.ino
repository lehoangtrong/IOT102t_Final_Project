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
#include "HTTPSRedirect.h"
#include <WiFiClientSecure.h>

const char *host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbwrPlg8llnoHhIu_0dLCJ6fINCWptultwJGdIlPefFAJxLHR-EpWe-NsNVuNgdRNNdOXQ";

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
String enrollStudent = String("/macros/s/") + GAS_ID + "/exec?type=enrollStudent&";

HTTPSRedirect *client = nullptr;

void displayOled(uint8_t choice);   // display oled
void clearBuffer();                 // clear buffer
uint8_t addFingerPrint();           // add fingerprint
void connectToGoogleSheet();        // connect to google sheet
String sendGoogleSheet(String url); // send data to google sheet

void setup()
{
  Serial.begin(115200);
  delay(10);
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
    }
  }
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
    Serial.println(".");
  }
  displayOled(wifi_connected_icon);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("DONE");
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
        Serial.println("DONE");
        break;
      }
      else if (received == 'a')
      {
        String studentID = Serial.readStringUntil(';');
        String studentName = Serial.readStringUntil('\n');
        Serial.println("Tên sinh viên: " + studentName);
        Serial.println("Đang nhập vân tay cho sinh viên có mã số: " + studentID);
        uint8_t fingerID = addFingerPrint();
        finger.getTemplateCount();
        uint8_t total = finger.templateCount;
        if (fingerID == total)
        {
          Serial.println("Chờ xác nhận từ server");
          if (sendGoogleSheet(studentName, studentID, String(fingerID)))
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
}

uint8_t addFingerPrint()
{
  bool check = true;
  finger.getTemplateCount();
  uint8_t id = finger.templateCount + 1;

  int p = -1;
  displayOled(fingerprint_scan_icon);
  Serial.println("Đặt tay lên cảm biến.");
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
  }

  finger.image2Tz(1);
  Serial.println("Lấy tay ra khỏi cảm biến.");
  p = 0;
  displayOled(fingerprint_icon);
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
  }

  p = -1;
  displayOled(fingerprint_scan_icon);
  Serial.println("Đặt tay lên cảm biến lần nữa.");
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
  }

  p = finger.image2Tz(2);
  Serial.print("Đang tạo mô hình #");
  Serial.println(id);
  p = finger.createModel();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Trùng khớp");
    break;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Lỗi nhận gói vân tay");
    check = false;
    break;
  case FINGERPRINT_ENROLLMISMATCH:
    Serial.println("Không trùng khớp");
    check = false;
    break;
  default:
    Serial.println("Không rõ lỗi");
    check = false;
    break;
  }
  if (!check)
  {
    Serial.println("DONE");
    return p;
  }

  Serial.print("Finger ID: ");
  Serial.println(id);
  // Save model to memory
  p = finger.storeModel(id);
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Đã hoàn tất.");
    break;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Lỗi giao tiếp");
    check = false;
    break;
  case FINGERPRINT_BADLOCATION:
    Serial.println("Không thể lưu trữ");
    check = false;
    break;
  case FINGERPRINT_FLASHERR:
    Serial.println("Lỗi viết bộ nhớ");
    check = false;
    break;
  default:
    Serial.println("Lỗi không rõ");
    check = false;
    break;
  }
  if (!check)
  {
    Serial.println("DONE");
    return p;
  }
  return id;
}

void displayOled(uint8_t choice)
{
  if (choice == 1)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
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
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 0);
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

String urlEncode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (unsigned int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += '+';
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

bool sendGoogleSheet(String name, String studentID, String fingerID)
{
  bool result = false;
  Serial.println("Đang kết nối tới Google Sheets");
  connectToGoogleSheet();
  Serial.println("Đã kết nối tới Google Sheets");
  String url = enrollStudent + "studentID=" + studentID + "&studentName=" + urlEncode(name) + "&fingerID=" + fingerID;
  Serial.println("Đang gửi yêu cầu tới Google Sheets" + url);
  String response = sendGoogleSheet(url);
  if (response.indexOf("enroll success") != -1)
  {
    result = true;
  }
  else if (response.indexOf("studentID exist") != -1)
  {
    result = false;
  }
  else
  {
    sendGoogleSheet(name, studentID, fingerID);
  }
  return result;
}

String sendGoogleSheet(String url)
{
  String respone = "";
  if (client->GET(url, host))
  {
    Serial.println("Yêu cầu GET thành công");
    Serial.println("Respone:");
    Serial.println(client->getResponseBody());
    respone = client->getResponseBody();
  }
  else
  {
    Serial.println("Yêu cầu GET thất bại");
  }
  return respone;
}

void connectToGoogleSheet()
{
  if (client == nullptr)
  {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();

    client->setPrintResponseBody(false);
    client->setContentTypeHeader("application/json");
  }
  if (!client->connected())
  {
    client->connect(host, httpsPort);
  }
}