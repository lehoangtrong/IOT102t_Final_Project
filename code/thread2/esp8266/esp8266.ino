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
void UARTSend(String data);       // send data to arduino uno
void clearBuffer();

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
    clearBuffer();
    // Serial show fingerprint system
    Serial.println("Fingerprint system");
    Serial.println("1. Add new student fingerprint");
    Serial.println("2. Update student fingerprint");
    Serial.println("3. Delete student fingerprint");
    Serial.println("Choose: ");
    while (Serial.available() == 0)
        ;
    int choice = Serial.parseInt();
    switch (choice)
    {
    case 1:
        // Add new student fingerprint
        // Collect student information and send to server (use c#)
        break;
    case 2:
        // Update student fingerprint
        // Collect student information and send to server (use c#)
        break;
    case 3:
        // Delete student fingerprint
        // Collect student information and send to server (use c#)
        break;
    default:
        break;
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

void UARTSend(String data)
{
    Serial.print(data);
}