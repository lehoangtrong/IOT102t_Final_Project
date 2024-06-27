#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "defind.h"
// #include <LiquidCrystal_I2C.h>

#define PIN_FIRE_SENSOR 6
#define PIN_PIR_SENSOR 7
#define PIN_AIR_SENSOR A0
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

uint8_t fireSensorValue = 0;
uint8_t pirSensorValue = 0;
uint8_t airSensorValue = 0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(4);

// LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(4, 5);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void displayOled(uint8_t choice);

bool checkSensorFire();  // Kiểm tra cảm biến cháy
void fingerSystem();     // Hệ thống vân tay

void setup() {
  // lcd.init();
  // lcd.backlight();

  pinMode(PIN_FIRE_SENSOR, INPUT);
  pinMode(PIN_PIR_SENSOR, INPUT);
  pinMode(PIN_AIR_SENSOR, INPUT);

  Serial.begin(115200);

  // text display tests
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  Serial.println("Adafruit finger detect test");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1)
      ;
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains ");
  Serial.print(finger.templateCount);
  Serial.println(" templates");
  Serial.println("Waiting for valid finger...");

  display.clearDisplay();
}

void loop() {
  // Read sensor values
  fireSensorValue = digitalRead(PIN_FIRE_SENSOR);
  pirSensorValue = digitalRead(PIN_PIR_SENSOR);
  airSensorValue = analogRead(PIN_AIR_SENSOR);

  if (!checkSensorValue()) {
    fingerSystem();
  } else {
    Serial.println("System is safe!!!!!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("System is safe");
    display.println("Fire sensor: " + String(fireSensorValue));
    display.println("PIR sensor: " + String(pirSensorValue));
    display.println("Air sensor: " + String(airSensorValue));
    display.display();
    // Alarm system here
  }
}

bool checkSensorValue() {
  bool check = false;
  if (fireSensorValue == 1 || airSensorValue > 400) {
    if (pirSensorValue == 1) {
      check = true;
    } else {
      check = false;
    }
  }
  return check;
}

void fingerSystem() {
  // get finger ID
  uint8_t p = finger.getImage();

  displayOled(4);

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
  displayOled(6);

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
    Serial.println("Found a print match!");
    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);

    displayOled(7);

    // show id fingerprint
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Finger ID: " + String(finger.fingerID));
    display.display();

    // Wait esp8266 uart read fingerprint id and check in database

    delay(1000);
  } else if (p == FINGERPRINT_NOTFOUND) {
    displayOled(5);
    Serial.println("Did not find a match");
    delay(1000);
    return;
  } else {
    Serial.println("Unknown error");
    return;
  }

  // delay(1000);

  // Check if the ID is in the database
  // for (int i = 0; i < 3; i++)
  // {
  //     if (finger.fingerID == students[i].studentFingerID)
  //     {
  //         Serial.println("Welcome " + students[i].studentName);
  //         break;
  //     }
  // }
  // delay(1000);
}

void displayOled(uint8_t choice) {
  if (choice == 1) {
    String ssid = "FPT_Students";
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
  if (choice == 6) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_start_bits, FinPr_start_width, FinPr_start_height, WHITE);
    display.display();
    delay(1000);
    return;
  }

  if (choice == 7) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_valid_bits, FinPr_valid_width, FinPr_valid_height, WHITE);
    display.display();
    delay(1000);
    return;
  }

  if (choice == 8) {
    display.clearDisplay();
    display.drawBitmap(32, 0, FinPr_invalid_bits, FinPr_invalid_width, FinPr_invalid_height, WHITE);
    display.display();
    delay(1000);
    return;
  }
}