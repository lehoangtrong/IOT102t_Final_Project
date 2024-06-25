// // // include i2c library
// // #include <LiquidCrystal_I2C.h>
// // #define sensorAirPIN A0
// // #define sensorPirPIN 3
// // int sensorAirValue = 0;
// // int sensorPirValue = 0;

// // LiquidCrystal_I2C lcd(0x27, 16, 2);

// // void setup()
// // {
// //   lcd.init();
// //   lcd.backlight();
// //   lcd.setCursor(0, 0);
// //   Serial.begin(9600);
// // }

// // void loop()
// // {
// //   sensorAirValue = analogRead(sensorAirPIN);
// //   sensorPirValue = digitalRead(sensorPirPIN);
// //   lcd.setCursor(0, 0);
// //   lcd.print("Air Quality: ");
// //   lcd.print(sensorAirValue);

// //   Serial.print("Pir value: ");
// //   Serial.println(sensorPirValue);
// //   // Sensor air quality about 100 - 250 is good
// //   // Serial.print("Air Quality: ");
// //   // Serial.println(sensorAirValue);

// //   // delay(1000);
// // }
// /*
// Kết nối:
//   oled                  Uno                 Mega
//  * GND                  GND                  GND
//  * VCC                  5V                   5V
//  * SCL                  A5                   SCL
//  * SDA                  A4                   SDA
// */

// #include <LiquidCrystal_I2C.h>

// #include <Adafruit_GFX.h>             // Include core graphics library for the display
// #include <Adafruit_SSD1306.h>         // Include Adafruit_SSD1306 library to drive the display
// Adafruit_SSD1306 display;             // Create display
// #include <Fonts/FreeMonoBold12pt7b.h> // Add a custom font
// #include <Fonts/FreeMono9pt7b.h>      // Add a custom font
// int Variable1;                        // Create a variable to have something dynamic to show on the display

// LiquidCrystal_I2C lcd(0x27, 16, 2);

// int sensorAirPIN = A0;
// int sensorAirValue = 0;
// void setup() // Start of setup
// {
//     delay(100);                                // This delay is needed to let the display to initialize
//     display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize display with the I2C address of 0x3C
//     display.clearDisplay();                    // Clear the buffer
//     display.setTextColor(WHITE);               // Set color of the text
//     display.setRotation(0);                    // Set orientation. Goes from 0, 1, 2 or 3
//     display.setTextWrap(false);                // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
//                                                // To override this behavior (so text will run off the right side of the display - useful for
//                                                // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
//                                                // with setTextWrap(true).
//     display.dim(0);                            // Set brightness (0 is maximun and 1 is a little dim)

//     lcd.init();
//     lcd.backlight();
//     lcd.setCursor(0, 0);
//     Serial.begin(9600);
// } // End of setup

// void loop() // Start of loop
// {
//     lcd.setCursor(0, 0);
//     sensorAirValue = analogRead(sensorAirPIN);
//     Serial.print("Air Quality: ");
//     Serial.println(sensorAirValue);
//     lcd.print("Air Quality: ");
//     lcd.print(sensorAirValue);

//     Variable1++;         // Increase variable by 1
//     if (Variable1 > 150) // If Variable1 is greater than 150
//     {
//         Variable1 = 0; // Set Variable1 to 0
//     }
//     char string[10]; // Create a character array of 10 characters
//     // Convert float to a string:
//     dtostrf(Variable1, 3, 0, string); // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)
//     display.clearDisplay();           // Clear the display so we can refresh
//     display.setFont(&FreeMono9pt7b);  // Set a custom font
//     display.setTextSize(0);           // Set text size. We are using a custom font so you should always use the text size of 0
//     // Print text:
//     display.setCursor(0, 10); // (x,y)
//     display.println("Trong"); // Text or value to print
//     // Draw triangle:
//     display.drawTriangle(40, 40, 50, 20, 60, 40, WHITE); // Draw triangle. X, Y coordinates for three corner points defining the triangle, followed by a color
//     // Draw filled triangle:
//     display.fillTriangle(0, 63, 15, 45, 30, 63, WHITE); // Draw filled triangle. X, Y coordinates for three corner points defining the triangle, followed by a color
//     // Draw line:
//     display.drawLine(40, 63, 70, 63, WHITE); // Draw line (x0,y0,x1,y1,color)
//     // Draw circle:
//     display.drawCircle(47, 36, 20, WHITE); //  Draw circle (x,y,radius,color). X and Y are the coordinates for the center point
//     // Draw a filled circle:
//     display.fillCircle(12, 27, 10, WHITE);          // Draw filled circle (x,y,radius,color). X and Y are the coordinates for the center point
//                                                     // Draw rounded rectangle and fill:
//     display.fillRoundRect(58, 0, 18, 18, 5, WHITE); // Draw filled rounded rectangle (x,y,width,height,color)
//                                                     // It draws from the location to down-right
//     // Draw rectangle:
//     display.drawRect(79, 0, 49, 27, WHITE); // Draw rectangle (x,y,width,height,color)
//                                             // It draws from the location to down-right
//     display.setFont(&FreeMonoBold12pt7b);   // Set a custom font
//     // Print variable with left alignment:
//     display.setCursor(83, 20);  // (x,y)
//     display.println(Variable1); // Text or value to print
//     // Draw rounded rectangle:
//     display.drawRoundRect(79, 37, 49, 27, 8, WHITE); // Draw rounded rectangle (x,y,width,height,radius,color)
//                                                      // It draws from the location to down-right
//     display.setCursor(83, 57);                       // (x,y)
//     display.println(string);                         // Text or value to print
//     display.display();                               // Print everything we set previously
// } // End of loop

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

bool testSensor();
uint8_t GetFingerprintEnroll();
uint8_t FingerprintVerify();
uint8_t GetFingerprintDelete();
uint8_t GetFingerprintDeleteAll();
uint8_t GetFingerprintList();
void downloadTemplate();
void removeSerialBuffer();
void printHex(int num, int precision);

int successTemplateCount = 0;

void setup()
{
    Serial.begin(9600); // initialize serial communication
    Serial.println();
    Serial.println("Fingerprint sensor test");
    while (testSensor() == false)
    {
        testSensor();
        delay(1000);
    }
}

void loop()
{
    uint8_t choice;
    Serial.println("1. Enroll");
    Serial.println("2. Verify");
    Serial.println("3. Delete");
    Serial.println("4. Delete All");
    Serial.println("5. Download Template");

    while (!Serial.available())
    {
    }

    choice = Serial.parseInt();
    removeSerialBuffer();

    switch (choice)
    {
    case 1:
        GetFingerprintEnroll();
        break;
    case 2:
        FingerprintVerify();
        break;
    case 3:
        GetFingerprintDelete();
        break;
    case 4:
        GetFingerprintDeleteAll();
        break;
    case 5:
        downloadTemplate();
        break;
    default:
        Serial.println("Invalid choice");
        break;
    }

    removeSerialBuffer();
}

void removeSerialBuffer()
{
    while (Serial.available())
    {
        Serial.read();
    }
}

bool testSensor()
{
    bool result = false;
    finger.begin(57600);

    if (finger.verifyPassword())
    {
        Serial.println("Found fingerprint sensor!");
        result = true;
    }
    else
    {
        Serial.println("Did not find fingerprint sensor :(");
    }
    return result;
}

uint8_t GetFingerprintEnroll()
{
    // Lấy id từ serial
    Serial.println("Nhập ID: ");
    while (!Serial.available())
    {
    }
    int id = Serial.parseInt();

    int p = -1;
    Serial.println("Đặt tay lên cảm biến.");
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();
    }

    p = finger.image2Tz(1);
    Serial.println("Lấy tay ra khỏi cảm biến.");

    Serial.println("Đặt tay lên cảm biến lần 2.");
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();
    }

    p = finger.image2Tz(2);
    Serial.println("Lấy tay ra khỏi cảm biến.");

    p = finger.createModel();
    if (p == FINGERPRINT_OK)
    {
        p = finger.storeModel(id);
        if (p == FINGERPRINT_OK)
        {
            Serial.println("Đã lưu");
        }
        else
        {
            Serial.println("Không thể lưu");
        }
    }
    else
    {
        Serial.println("Không thể tạo mẫu");
    }
    return p;
}

uint8_t FingerprintVerify()
{
    // Lấy id từ serial
    Serial.println("Nhập ID: ");
    while (!Serial.available())
    {
    }
    int id = Serial.parseInt();

    int p = -1;
    Serial.println("Đặt tay lên cảm biến.");
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();
    }

    p = finger.image2Tz(1);
    Serial.println("Lấy tay ra khỏi cảm biến.");

    Serial.println("Đang so sánh...");

    p = finger.fingerFastSearch();
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Trùng khớp");
    }
    else
    {
        Serial.println("Không trùng khớp");
    }
    return p;
}

uint8_t GetFingerprintDelete()
{
    // Lấy id từ serial
    Serial.println("Nhập ID: ");
    while (!Serial.available())
    {
    }
    int id = Serial.parseInt();

    int p = finger.deleteModel(id);
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Đã xóa");
    }
    else
    {
        Serial.println("Không thể xóa");
    }
    return p;
}

uint8_t GetFingerprintDeleteAll()
{
    int p = finger.emptyDatabase();
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Đã xóa");
    }
    else
    {
        Serial.println("Không thể xóa");
    }
    return p;
}

void printHex(int num, int precision)
{
    char tmp[16];
    char format[128];

    sprintf(format, "%%.%dX", precision);

    sprintf(tmp, format, num);
    Serial.print(tmp);
}

void downloadTemplate()
{
    finger.getTemplateCount();
    Serial.print("Template count: ");
    Serial.println(finger.templateCount);

    if (finger.templateCount == 0)
    {
        Serial.println("No templates found");
        return;
    }

    int success = 0;
    int index = 0;
    while (success != finger.templateCount)
    {
        finger.getTemplate(index);
        success++;
        index++;
    }
}

void getTemplate(uint8_t id)
{

    int p = finger.loadModel(id);
    if (p == FINGERPRINT_OK)
    {
        Serial.print("Template ID: ");
        Serial.println(id);
        Serial.print("Template data: ");
        p = finger.getModel();

        if (p == FINGERPRINT_OK)
        {
            // Show hex data
        }
        else
        {
            Serial.println("Không thể load template data");
        }
        Serial.println();
    }
    else
    {
        Serial.println("Không thể load template");
    }
}