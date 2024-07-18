#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SerialCommand.h>

#define PIN_FIRE_SENSOR 6
#define PIN_PIR_SENSOR 7
#define PIN_AIR_SENSOR A0
#define PIN_SERVO_MOTOR 9

uint8_t fireSensorValue = 0;
uint8_t pirSensorValue = 0;
uint8_t airSensorValue = 0;

SerialCommand sCmd;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor;

bool checkSensorFire(); // Kiểm tra cảm biến cháy
void UARTReceive();     // Nhận dữ liệu từ esp8266

void setup()
{
  lcd.init();
  lcd.backlight();

  pinMode(PIN_FIRE_SENSOR, INPUT);
  pinMode(PIN_PIR_SENSOR, INPUT);
  pinMode(PIN_AIR_SENSOR, INPUT);
  pinMode(PIN_SERVO_MOTOR, OUTPUT);

  Serial.begin(115200);
  sCmd.addCommand("Open", UARTReceive);
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
    servoMotor.attach(PIN_SERVO_MOTOR);
    servoMotor.write(90);
  }
  else
  {
    Serial.println("System is safe!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System is safe!");
    lcd.setCursor(0, 1);
    lcd.print("Welcome FPT classroom!");

    // Close door
    servoMotor.attach(PIN_SERVO_MOTOR);
    servoMotor.write(0);
  }

  sCmd.readSerial();
}

bool checkSensorValue()
{
  bool check = false;
  if (fireSensorValue == 1 || airSensorValue > 400)
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

void UARTReceive()
{
  char *arg;
  arg = sCmd.next();
  // command is Open 90
  if (arg != NULL)
  {
    if (strcmp(arg, "Open") == 0)
    {
      arg = sCmd.next();
      if (arg != NULL)
      {
        int angle = atoi(arg);
        servoMotor.attach(PIN_SERVO_MOTOR);
        servoMotor.write(angle);

        // Delay 2s
        delay(2000);
        servoMotor.write(0);
      }
    }
  }
}