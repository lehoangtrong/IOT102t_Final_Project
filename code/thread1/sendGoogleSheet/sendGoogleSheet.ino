#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char *host = "script.google.com";
const int httpsPort = 443;
String GAS_ID = "AKfycbziXksUeubaKHlDtbA1ktCBU7BpTTEOtgBh5-AyCyKGpm-bGYcwXGpSUqxjrG6eR2tnfw";

const char *ssid = "LeHoangTrong_EXT";
const char *password = "Lehoangtrong1905";

WiFiClientSecure client;

void setup()
{
    Serial.begin(115200);
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    client.setInsecure();
}
void loop()
{
    if (Serial.available() > 0)
    {
        char received = Serial.read();
        if (received == 'c')
        {
            Serial.println("Connected to the WiFi network");
            Serial.println("Connecting to Google Sheets");
            if (!client.connect(host, httpsPort))
            {
                Serial.println("Connection failed");
                return;
            }
            Serial.println("Connected to Google Sheets");
            int fingerIDRand = random(1, 21);
            String url = "/macros/s/" + GAS_ID + "/exec?type=takeAttendant&fingerID=" + fingerIDRand;
            Serial.print("Requesting URL: ");
            Serial.println(url);
            client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
            Serial.println("Request sent");
            while (client.connected())
            {
                String line = client.readStringUntil('\n');
                if (line == "\r")
                {
                    Serial.println("Headers received");
                    break;
                }
                else
                {
                    Serial.println(line);
                }
            }
            String line = client.readStringUntil('\n');
            Serial.println("Reply was:");
            Serial.println("==========");
            Serial.println(line);
            Serial.println("==========");
            Serial.println("Closing connection");
            Serial.println();
            client.stop();
        }
    }
}