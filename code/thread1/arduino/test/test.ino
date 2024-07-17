
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.flush();
    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n');
        Serial.println(data);
        if (data.indexOf("OPEN") >= 0)
        {
            Serial.println("OPEN DOOR SUCCESS");
        }
    }
}