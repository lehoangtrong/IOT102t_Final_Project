#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_FIRE_SENSOR 6
#define PIN_PIR_SENSOR 7
#define PIN_AIR_SENSOR A0
int fireSensorValue = 0;
int pirSensorValue = 0;
int airSensorValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Adafruit_SSD1306 display; // Create display

void cleanSerialBuffer(); // Xóa bộ đệm của Serial
bool checkSensorFire();   // Kiểm tra cảm biến cháy

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    lcd.setCursor(0, 1);
    lcd.print("Hello, world!");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    Serial.begin(9600);
    while (!Serial)
        ;
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
}

void loop()
{
    // Read sensor values
    fireSensorValue = digitalRead(PIN_FIRE_SENSOR);
    pirSensorValue = digitalRead(PIN_PIR_SENSOR);
    airSensorValue = analogRead(PIN_AIR_SENSOR);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Fire sensor: " + String(fireSensorValue));
    display.println("PIR sensor: " + String(pirSensorValue));
    display.println("Air sensor: " + String(airSensorValue));
    display.display();

    Serial.println("PIR sensor: " + String(pirSensorValue));
    // Serial.println("=====================================");
    // Serial.println("Fingerprint system");
    // Serial.println("Choose a number from the following list:");
    // Serial.println("1. Enroll a new fingerprint");
    // Serial.println("2. Update a fingerprint");
    // Serial.println("3. Delete a fingerprint");

    // int choice = 0;
    // while (Serial.available() == 0)
    //     ;
    // choice = Serial.parseInt();
    // clearSerialBuffer();

    // switch (choice)
    // {
    // case 1:
    //     Serial.println("Enroll a new fingerprint");
    //     break;
    // case 2:
    //     Serial.println("Update a fingerprint");
    //     break;
    // case 3:
    //     Serial.println("Delete a fingerprint");
    //     break;
    // default:
    //     Serial.println("Invalid choice");
    //     break;
    // }

    // delay(50);
}

void clearSerialBuffer()
{
    while (Serial.available() > 0)
    {
        char t = Serial.read();
    }
}