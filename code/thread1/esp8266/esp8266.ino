#include <ESP8266WiFi.h>
// Finger print library
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
// OLED display library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "defind.h"
// FONT vi

// Wifi library
#include "HTTPSRedirect.h"
#include <WiFiClientSecure.h>

const char *host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbwrPlg8llnoHhIu_0dLCJ6fINCWptultwJGdIlPefFAJxLHR-EpWe-NsNVuNgdRNNdOXQ";

// Fingerprint scanner Pins
#define Finger_Rx 14  // D5
#define Finger_Tx 12  // D6
// Declaration for SSD1306 display connected using software I2C
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET 0      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial mySerial(Finger_Rx, Finger_Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const char *ssid = "FPT_Error";
const char *password = "nonepassword";
String takeAttendant = String("/macros/s/") + GAS_ID + "/exec?type=takeAttendant&";
String getStudentByFingerID = String("/macros/s/") + GAS_ID + "/exec?type=getStudentByFingerPrint&";

HTTPSRedirect *client = nullptr;

void fingerSystem();                 // take attendance by fingerprint
void displayOled(uint8_t choice);    // display oled
String checkStudent(int fingerID);   // check student by fingerID
void connectToGoogleSheet();         // connect to google sheet
String sendGoogleSheet(String url);  // send data to google sheet

void setup() {
  Serial.begin(115200);
  delay(10);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();

  Serial.println("Adafruit finger detect test");
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    for (;;)
      ;
  }

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    displayOled(wifi_connect_icon);
    delay(500);
    Serial.print(".");
  }
  displayOled(wifi_connected_icon);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}

void loop() {
  fingerSystem();  // take attendance by fingerprint
  yield();
}

void fingerSystem() {
  uint8_t p = finger.getImage();

  displayOled(fingerprint_scan_icon);

  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  // OK success!
  displayOled(fingerprint_icon);

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  // OK converted!
  p = finger.fingerFastSearch();

  if (p == FINGERPRINT_OK) {

    Serial.print("  OPEN\r\n");
    delay(500);
    Serial.print("  OPEN\r\n");
    Serial.println("Found a print match!");
    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);

    displayOled(fingerprint_valid_icon);
    String response = checkStudent(finger.fingerID);

    if (response.indexOf("studentID") != -1) {
      Serial.println("Attendant taken");
      String student = response;
      // {"studentID":"QE180205","studentName":"Vũ Thị Kim Liên","fingerID":21}
      String studentID = student.substring(student.indexOf("studentID") + 12, student.indexOf("studentName") - 3);
      String studentName = student.substring(student.indexOf("studentName") + 15, student.indexOf("fingerID") - 3);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print(F("Student ID: "));
      display.setCursor(0, 10);
      display.print(studentID);
      display.setCursor(0, 20);
      display.print(F("Student Name: "));
      display.setCursor(0, 30);
      display.print(studentName);  // TODO: Encode UTF-8 not working
      display.display();

    } else {
      Serial.println("Attendant not taken");
    }
    delay(1000);
  } else if (p == FINGERPRINT_NOTFOUND) {
    displayOled(fingerprint_invalid_icon);
    Serial.println("Did not find a match");
    delay(1000);
    return;
  } else {
    Serial.println("Unknown error");
    return;
  }
}

void displayOled(uint8_t choice) {
  if (choice == 1) {
    // show username of wifi
    display.clearDisplay();
    display.setTextSize(1);       // Normal 1:1 pixel scale
    display.setTextColor(WHITE);  // Draw white text
    display.setCursor(0, 0);      // Start at top-left corner
    display.print(F("Connecting to \n"));
    display.setCursor(0, 50);
    display.setTextSize(2);
    display.print(ssid);
    display.drawBitmap(73, 10, Wifi_start_bits, Wifi_start_width, Wifi_start_height, WHITE);
    display.display();
    delay(1000);
    return;
  }
  if (choice == 2) {
    display.clearDisplay();
    display.setTextSize(2);       // Normal 1:1 pixel scale
    display.setTextColor(WHITE);  // Draw white text
    display.setCursor(8, 0);      // Start at top-left corner
    display.print(F("Connected \n"));
    display.drawBitmap(33, 15, Wifi_connected_bits, Wifi_connected_width, Wifi_connected_height, WHITE);
    display.display();
    delay(1000);
    return;
  }
  if (choice == 3) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_failed_bits, FinPr_failed_width, FinPr_failed_height, WHITE);
    display.display();
    delay(1000);
    return;
  }

  if (choice == 4) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_scan_bits, FinPr_scan_width, FinPr_scan_height, WHITE);
    display.display();
    delay(1000);
    return;
  }
  if (choice == 5) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_start_bits, FinPr_start_width, FinPr_start_height, WHITE);
    display.display();
    delay(1000);
    return;
  }

  if (choice == 6) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_valid_bits, FinPr_valid_width, FinPr_valid_height, WHITE);
    display.display();
    delay(1000);
    return;
  }

  if (choice == 7) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_invalid_bits, FinPr_invalid_width, FinPr_invalid_height, WHITE);
    display.display();
    delay(1000);
    return;
  }
}

String checkStudent(int fingerID) {
  bool check = false;
  // Serial.print("connecting to ");
  // Serial.println(host);
  String url = takeAttendant + "fingerID=" + fingerID;
  String response = sendGoogleSheet(url);
  if (response.indexOf("studentID") != -1) {
    check = true;
  } else if (response.indexOf("FingerID not found") != -1) {
    check = false;
  } else {
    checkStudent(fingerID);
  }

  return check ? response : "";
}

String sendGoogleSheet(String url) {
  connectToGoogleSheet();
  String respone = "";
  if (client->GET(url, host)) {
    // Serial.println("Yêu cầu GET thành công");
    // Serial.println("Respone:");
    // Serial.println(client->getResponseBody());
    respone = client->getResponseBody();
  } else {
    // Serial.println("Yêu cầu GET thất bại");
  }
  return respone;
}

void connectToGoogleSheet() {
  if (client == nullptr) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();

    client->setPrintResponseBody(false);
    client->setContentTypeHeader("application/json");
  }
  if (!client->connected()) {
    client->connect(host, httpsPort);
  }
}
