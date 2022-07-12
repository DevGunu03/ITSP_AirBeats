#include <WiFi.h>

const char* ssid = "Saurabh-2.4G_EXT";
const char* pass = "abcd*123";

const char* server = "httpbin.org";
const int port = 80;

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Set esp32 to station mode
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      Serial.print("."); // Ah yes fancy loading screen
    }
  Serial.println(""); Serial.print("WiFi connected to "); Serial.println(ssid); Serial.print("IP address: ");Serial.println(WiFi.localIP());
  
}

void loop() {
  int  conn;
  int chip_id = ESP.getEfuseMac();;
  Serial.printf("  Flash Chip id = %08X\t", chip_id);
  Serial.println();
  Serial.println();
  String body = "ChipId=" + String(chip_id) + "&SentBy=" + "your_name";
  int body_len = body.length();
  
  Serial.println(".....");
  Serial.println(); Serial.print("For sending parameters, connecting to ");      Serial.println(server);
  conn = client.connect(server, port);
