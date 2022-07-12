#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Saurabh-2.4G_EXT";
const char* password = "abcd*123";

//The broker and port are provided by http://www.mqtt−dashboard.com/
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

//Replace these 3 with the strings of your choice
const char* mqtt_client_name = "Shobhit_ESP-32";
const char* mqtt_pub_topic = "/ys/randomPub"; //The topic to which our client will publish
const char* mqtt_sub_topic = "/ys/randomSub"; //The topic to which our client will subscribe

int count = random(500); //This is the information we will be publishing

WiFiClient client;
PubSubClient mqttClient(client);

//This fucntion defines what to do when we receive a message
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received from: "); Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

  pinMode(LED_BUILTIN, OUTPUT); // Im using LED to denote writing to the server instead of writing to the serial port

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mqttClient.connected()) {
    while (!mqttClient.connected()) {
      if (mqttClient.connect(mqtt_client_name)) {
        Serial.println("MQTT Connected!");
        mqttClient.subscribe(mqtt_sub_topic);
      }
      else {
        Serial.print(".");
      }
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);
  mqttClient.publish(mqtt_pub_topic, "0.9 0.882 -0.9 45 32 54 88 9.5 23 hi kartik");
  mqttClient.loop();
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
