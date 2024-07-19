#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define PIN_FIRE_SENSOR A1
#define PIN_PIR_SENSOR 7
#define PIN_AIR_SENSOR A0
#define PIN_SERVO_MOTOR 9
#define PIN_BUZZER 8

uint8_t fireSensorValue = 0;
uint8_t pirSensorValue = 0;
uint8_t airSensorValue = 0;
const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;
int duration, distance;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor;

bool checkSensorFire(); // Kiểm tra cảm biến cháy

void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(PIN_FIRE_SENSOR, INPUT);
  pinMode(PIN_PIR_SENSOR, INPUT);
  pinMode(PIN_AIR_SENSOR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(PIN_SERVO_MOTOR);
}

void loop()
{
  if (checkSensorValue())
  {
    Serial.println("System is not safe!!!!!");

    Serial.println("====================================");
    Serial.println("Fire sensor: " + String(fireSensorValue));
    Serial.println("PIR sensor: " + String(pirSensorValue));
    Serial.println("Air sensor: " + String(airSensorValue));
    Serial.println("====================================");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System not safe!");
    lcd.setCursor(0, 1);
    lcd.print("F:    A:    P:");
    lcd.setCursor(2, 1);
    lcd.print(String(fireSensorValue));
    lcd.setCursor(8, 1);
    lcd.print(String(airSensorValue));
    lcd.setCursor(14, 1);
    lcd.print(String(pirSensorValue));

    // Warning
    while (checkSensorValue())
    {
      tone(PIN_BUZZER, 1000);
      delay(500);
      noTone(PIN_BUZZER);

      // Open door
      servoMotor.write(0);
    }

    delay(4000);
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
    lcd.print("System safe!");
    lcd.setCursor(0, 1);
    lcd.print("F:    A:    P:");
    lcd.setCursor(2, 1);
    lcd.print(String(fireSensorValue));
    lcd.setCursor(8, 1);
    lcd.print(String(airSensorValue));
    lcd.setCursor(14, 1);
    lcd.print(String(pirSensorValue));

    // Close door
    servoMotor.write(150);
  }

  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    if (data.indexOf("OPEN") >= 0)
    {
      servoMotor.write(0);
      delay(3000); // maybe can change read sensor value to check door is open or close

      servoMotor.write(150);
    }
  }

  if (distance < 6)
  {
    Serial.println("Door is opening");
    servoMotor.write(0);
    delay(2000);
    servoMotor.write(150);
  }

  delay(1000);
}

bool checkSensorValue()
{
  // Read sensor values
  fireSensorValue = analogRead(PIN_FIRE_SENSOR);
  pirSensorValue = digitalRead(PIN_PIR_SENSOR);
  airSensorValue = analogRead(PIN_AIR_SENSOR);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  bool check = false;
  if (fireSensorValue < 200 || airSensorValue > 400 || airSensorValue < 40)
  {
    check = true;
  }
  return check;
}