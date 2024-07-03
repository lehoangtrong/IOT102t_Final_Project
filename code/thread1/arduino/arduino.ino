#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define PIN_FIRE_SENSOR 6
#define PIN_PIR_SENSOR 7
#define PIN_AIR_SENSOR A0
#define PIN_SERVO_MOTOR 9

uint8_t fireSensorValue = 0;
uint8_t pirSensorValue = 0;
uint8_t airSensorValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor;

bool checkSensorFire(); // Kiểm tra cảm biến cháy

void setup()
{
  lcd.init();
  lcd.backlight();

  pinMode(PIN_FIRE_SENSOR, INPUT);
  pinMode(PIN_PIR_SENSOR, INPUT);
  pinMode(PIN_AIR_SENSOR, INPUT);
  servoMotor.attach(PIN_SERVO_MOTOR);
  Serial.begin(115200);
}

void loop()
{
  // Read sensor values
  fireSensorValue = digitalRead(PIN_FIRE_SENSOR);
  pirSensorValue = digitalRead(PIN_PIR_SENSOR);
  airSensorValue = analogRead(PIN_AIR_SENSOR);

  if (checkSensorValue())
  {
    Serial.println("System is not safe!!!!!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System not safe!");
    lcd.setCursor(0, 1);
    lcd.print("Please call 911");

    // Open door
    servoMotor.write(90);
    delay(3000);
  }
  else
  {
    Serial.println("System is safe!");

    Serial.println("====================================");
    Serial.println("Fire sensor: " + String(fireSensorValue));
    Serial.println("PIR sensor: " + String(pirSensorValue));
    Serial.println("Air sensor: " + String(airSensorValue));
    Serial.println("====================================");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System is safe!");
    lcd.setCursor(0, 1);
    lcd.print("Welcome FPT classroom!");

    // Close door
    servoMotor.write(0);
  }
  if (Serial.available() > 0)
  { // read from esp8266
    String data = Serial.readString().substring(0, 4);
    Serial.println(data);
    if (data.equals("OPEN"))
    {
      servoMotor.write(90);
      delay(3000); // maybe can change read sensor value to check door is open or close

      servoMotor.write(0);
    }
  }
  delay(1000);
}

bool checkSensorValue()
{
  bool check = false;
  if (fireSensorValue == 1 || airSensorValue > 400 || airSensorValue < 40)
  {
    if (pirSensorValue == 1)
    {
      check = true;
    }
    else
    {
      check = false;
    }
  }
  return check;
}
