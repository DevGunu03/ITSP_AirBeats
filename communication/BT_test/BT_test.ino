#include <BluetoothSerial.h>

BluetoothSerial SerialBT; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("Shobhit_ESP32");
  Serial.println("Device is ready to connect");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
   if (Serial.available()) {
      digitalWrite(LED_BUILTIN, HIGH);
      SerialBT.write(Serial.read());
      digitalWrite(LED_BUILTIN, LOW);
   }
   if (SerialBT.available()) {
      Serial.write(SerialBT.read());
   }
   delay(50);
}
