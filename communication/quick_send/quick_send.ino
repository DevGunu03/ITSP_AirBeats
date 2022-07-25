#include <BluetoothSerial.h>
BluetoothSerial SerialBT; //Initialise BT object
float gx = 6.9;
float gy = 6.9;
float gz = 6.9;
float ax = 4.2;
float ay = 4.2;
float az = 4.2;
float mx = 8.6;
float my = 8.6;
float mz = 8.6;
long int refTime = millis(); //Start time
int sampleRate = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial){} // Wait for serial to begin

  //Bluetooth is connected first
  SerialBT.begin("Shobhit_ESP32");
  Serial.println("Device is ready to connect");
  Serial.println("Waiting for response");
    while(!SerialBT.available()){ // Wait for response from receiver
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nDevice connected and verified!");

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  long int currentTime = (millis() - refTime);
  digitalWrite(LED_BUILTIN, HIGH);
  SerialBT.print(currentTime);
  SerialBT.print(" ");
  SerialBT.print(gx);
  SerialBT.print(" ");
  SerialBT.print(gy);
  SerialBT.print(" ");
  SerialBT.print(gz);
  SerialBT.print(" ");
  SerialBT.print(ax);
  SerialBT.print(" ");
  SerialBT.print(ay);
  SerialBT.print(" ");
  SerialBT.print(az);
  SerialBT.print(" ");
  SerialBT.print(mx);
  SerialBT.print(" ");
  SerialBT.print(my);
  SerialBT.print(" ");
  SerialBT.print(mz);
  SerialBT.print(" ");
  SerialBT.print("\r");
  digitalWrite(LED_BUILTIN, LOW);
  delay(sampleRate - 3); //Adjustment for lag
}
