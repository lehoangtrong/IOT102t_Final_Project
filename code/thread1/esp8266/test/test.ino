#include <ESP8266WiFi.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Hello world!");
    delay(1000);
    Serial.println("OPEN");
}