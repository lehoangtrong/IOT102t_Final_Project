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

void displayOled(uint8_t choice);                                       // display oled
void clearBuffer();                                                     // clear buffer
String addFingerPrint();                                                // add fingerprint

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
                // read name and studentID
                String name = UARTRead();
                String studentID = UARTRead();
                String fingerID = addFingerPrint();
                // send data to server
                if (sendGoogleSheet(name, studentID, fingerID))
                {
                    Serial.println("Thêm sinh viên thành công");
                }
                else
                {
                    Serial.println("Thêm sinh viên thất bại");
                }
                break;
            }
            else if (received == "u")
            {
                // read name and studentID
                String name = UARTRead();
                String studentID = UARTRead();
                String fingerID = addFingerPrint();
                // send data to server
                if (updateGoogleSheet(name, studentID, fingerID))
                {
                    Serial.println("Cập nhật sinh viên thành công");
                }
                else
                {
                    Serial.println("Cập nhật sinh viên thất bại");
                }
                break;
            }
        }
    }
}

string addFingerPrint(){
    displayOled(finger_scan_icon);
    String fingerID = "";
    while (true)
    {
        uint8_t p = finger.getImage();
        switch (p)
        {
        case FINGERPRINT_OK:
            Serial.println("Image taken");
            break;
        case FINGERPRINT_NOFINGER:
            Serial.println("No finger detected");
            continue;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            continue;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Imaging error");
            continue;
        default:
            Serial.println("Unknown error");
            continue;
        }

        p = finger.image2Tz(1);
        switch (p)
        {
        case FINGERPRINT_OK:
            Serial.println("Image converted");
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println("Image too messy");
            continue;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            continue;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            continue;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            continue;
        default:
            Serial.println("Unknown error");
            continue;
        }

        p = finger.fingerFastSearch();
        if (p == FINGERPRINT_OK)
        {
            Serial.println("Found a print match!");
            fingerID = finger.fingerID;
            break;
        }
        else if (p == FINGERPRINT_PACKETRECIEVEERR)
        {
            Serial.println("Communication error");
            continue;
        }
        else if (p == FINGERPRINT_NOTFOUND)
        {
            Serial.println("Did not find a match");
            continue;
        }
        else
        {
            Serial.println("Unknown error");
            continue;
        }
    }
    return fingerID;
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
    if (!client.connect(host, httpsPort))
    {
        Serial.println("Connection failed");
        return false;
    }
    String url = "/macros/s/" + googleSheetID + "/exec?name=" + name + "&studentID=" + studentID + "&fingerID=" + fingerID;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    if (client.connected() || client.available())
    {
        while (client.connected() || client.available())
        {
            String line = client.readStringUntil('\n');
            if (line == "\r")
            {
                break;
            }
        }
        String line = client.readStringUntil('\n');
        if (line == "Success")
        {
            result = true;
        }
    }
    return result;
}