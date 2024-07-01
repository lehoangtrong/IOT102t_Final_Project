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

const char *ssid = "LeHoangTrong_EXT";
const char *password = "Lehoangtrong1905";

WiFiClientSecure client;

void fingerSystem();              // take attendance by fingerprint
void displayOled(uint8_t choice); // display oled
bool checkStudent(int fingerID);  // check student by fingerID

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

  // Set client to connect to google sheet with https
  client.setInsecure();
  client.setNoDelay(true);

  delay(1000);
}

void loop()
{
  fingerSystem(); // take attendance by fingerprint
}

void fingerSystem()
{
  uint8_t p = finger.getImage();

  displayOled(fingerprint_scan_icon);

  switch (p)
  {
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
  switch (p)
  {
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

  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);

    displayOled(fingerprint_valid_icon);

    if (checkStudent(finger.fingerID))
    {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("Finger ID: " + String(finger.fingerID));
      display.setCursor(0, 32);
      display.println("Welcome");
      display.display();
    }
    delay(1000);
  }
  else if (p == FINGERPRINT_NOTFOUND)
  {
    displayOled(fingerprint_invalid_icon);
    Serial.println("Did not find a match");
    delay(1000);
    return;
  }
  else
  {
    Serial.println("Unknown error");
    return;
  }
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

bool checkStudent(int fingerID)
{
  bool check = false;

  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort))
  {
    Serial.println("connection failed");
  }
  else
  {
    Serial.println("Connected to Google Sheets");
    String url = "/macros/s/" + GAS_ID + "/exec?type=takeAttendant&fingerID=" + fingerID;
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
    while (client.connected())
    {
      String line = client.readStringUntil('\n');
      if (line == "\r")
      {
        Serial.println("Headers received");
        break;
      }
    }
    client.stop();
    Serial.println("OPEN");
    delay(500);
    Serial.println("OPEN"); // double check
    check = true;
  }
  return check;
}