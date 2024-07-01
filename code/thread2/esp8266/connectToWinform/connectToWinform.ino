#include <ESP8266WiFi.h>
#define Button_PIN 0 // D3

void setup()
{
  Serial.begin(115200);
  pinMode(Button_PIN, INPUT);
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
      }
      else if (received == 'a')
      {
        String studentID = Serial.readStringUntil(';');
        String studentName = Serial.readStringUntil('\n');
        Serial.println("Tên sinh viên: " + studentName);
        Serial.println("Đang nhập vân tay cho sinh viên có mã số: " + studentID);
        Serial.println("DONE");
      }
      else if (received == 'g')
      {
        // Collect to google sheet
      }
    }
  }
}