#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
Adafruit_SSD1306 display; // Create display

void cleanSerialBuffer();              // Xóa bộ đệm của Serial
uint8_t enrollFingerprint();           // Đăng ký vân tay
String readSensorFire();               // Đọc cảm biến cháy
String readIDStudent();                // Đọc ID sinh viên
String checkContainStudent(String id); // Kiểm tra xem sinh viên đã tồn tại chưa

#define sensorFirePin 4
int sensorFireValue = 0;



void setup()
{

  // LOAD student data from file data.txt



  lcd.init();
  lcd.backlight();
  // printLcd("Fingerprint test print long text to see if it scrolls or not");

  Serial.begin(115200);
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

struct students
{
  String id;
  String fingerID;
  String hexID;
};

void loop()
{

  // printLcd("Wait to read fire sensor...");
  // printLcd(readSensorFire());
  // Serial.println(readSensorFire());
  // delay(1000);

  printLcd("Fingerprint system");

  Serial.println("=====================================");
  Serial.println("Choose a number from the following list:");
  Serial.println("1. Enroll a new fingerprint");
  Serial.println("2. Delete a fingerprint");
  Serial.println("3. Delete all fingerprints");
  Serial.println("4. Verify a fingerprint");
  Serial.println("5. Total number of fingerprints");
  Serial.println("Enter the number: ");
  while (Serial.available() == 0)
    ;
  int choice = Serial.parseInt();

  cleanSerialBuffer();
  switch (choice)
  {
  case 1:
    enrollFingerprint(checkContainStudent(readIDStudent()));
    break;

  default:
    Serial.println("Invalid choice");
    break;
  }
  delay(50);
}

void cleanSerialBuffer()
{
  while (Serial.available() > 0)
  {
    char c = Serial.read();
  }
}

void printLcd(String str)
{
  // if str is longer than 16 characters, scroll it to the left
  lcd.setCursor(0, 0);
  if (str.length() > 16)
  {
    str = "     " + str;
    for (int i = 0; i < str.length() - 15; i++)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(str.substring(i, i + 16));
      delay(500);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(str);
  }
}

String readIDStudent()
{
  Serial.println("Enter student ID: ");
  while (Serial.available() == 0)
    ;
  String id = Serial.readString();
  cleanSerialBuffer();
  return id;
}

String checkContainStudent(String studentID){
  // Check if student is already in the system
  // If not, add student to the system
  // If yes, return student ID
  return studentID;
}

uint8_t enrollFingerprint(String studentID)
{
  int id = 0;
  finger.getTemplateCount();
  id = finger.templateCount + 1;
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  Serial.println(id);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image converted");
    break;
  case FINGERPRINT_IMAGEMESS:
    Serial.println("Image too messy");
    return p;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return p;
  case FINGERPRINT_FEATUREFAIL:
    Serial.println("Could not find fingerprint features");
    return p;
  case FINGERPRINT_INVALIDIMAGE:
    Serial.println("Could not find fingerprint features");
    return p;
  default:
    Serial.println("Unknown error");
    return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image converted");
    break;
  case FINGERPRINT_IMAGEMESS:
    Serial.println("Image too messy");
    return p;
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return p;
  case FINGERPRINT_FEATUREFAIL:
    Serial.println("Could not find fingerprint features");
    return p;
  case FINGERPRINT_INVALIDIMAGE:
    Serial.println("Could not find fingerprint features");
    return p;
  default:
    Serial.println("Unknown error");
    return p;
  }

  // OK converted!
  Serial.print("Creating model for #");
  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Prints matched!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return p;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH)
  {
    Serial.println("Fingerprints did not match");
    return p;
  }
  else
  {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID ");
  Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Stored!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return p;
  }
  else if (p == FINGERPRINT_BADLOCATION)
  {
    Serial.println("Could not store in that location");
    return p;
  }
  else if (p == FINGERPRINT_FLASHERR)
  {
    Serial.println("Error writing to flash");
    return p;
  }
  else
  {
    Serial.println("Unknown error");
    return p;
  }

  return true;
}

String readSensorFire()
{
  sensorFireValue = digitalRead(sensorFirePin);
  if (sensorFireValue == HIGH)
  {
    return "Fire detected!";
  }
  else
  {
    return "No fire detected!";
  }
}
