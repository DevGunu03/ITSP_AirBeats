#include <WiFi.h>
String apiKey = "KHZX5VPZ4FU4QWOR";                  //  Enter your Write API key from ThingSpeak
const char *ssid =  "Saurabh-2.4G_EXT";                                    // replace with your wifi ssid and wpa2 key
const char *pass =  "abcd*123";
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup() 
{
    Serial.begin(115200);
    delay(10);
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
 
}
void loop() 
{
  
int h = 0;
float t =0;

 if (client.connect(server,80))                                 //   "184.106.153.149" or api.thingspeak.com
    {  
                            
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(h);
    postStr += "&field2=";
    postStr += String(t);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Hall: ");
    Serial.println(h);
    Serial.print("Temperature:");
    Serial.print(t);
    Serial.println(" C");
                             
    Serial.println("%. Send to Thingspeak.");
}
    client.stop();
    Serial.println("Waiting...");
    delay(1000);
}
