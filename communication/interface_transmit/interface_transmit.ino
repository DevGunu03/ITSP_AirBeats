#include <BluetoothSerial.h>
#include "mpu9250.h"

BluetoothSerial SerialBT; //Initialise BT object
bfs::Mpu9250 imu; //Initialise mpu object

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
  Serial.println("Device connected and verified!");

  //Start i2c bus
  Wire.begin(); // Default values are SCL: P22, SDA: P21
  Wire.setClock(400000);
  imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM); // Default address is 0x68
  
  /* Initialize and configure IMU */
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  
  /* Set the sample rate divider */
  if (!imu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }
  
  pinMode(LED_BUILTIN, OUTPUT); // Initialise Inbuilt LED 
  long int refTime = millis(); //Start time
}

void loop() {
   if (imu.Read()) {
      // read and transmit sensor data
      long int currentTime = millis() - refTime;
      digitalWrite(LED_BUILTIN, HIGH);
      SerialBT.print(currentTime);
      SerialBT.print("\t");
      SerialBT.print(imu.new_imu_data());
      SerialBT.print("\t");
      SerialBT.print(imu.new_mag_data());
      SerialBT.print("\t");
      SerialBT.print(imu.accel_x_mps2());
      SerialBT.print("\t");
      SerialBT.print(imu.accel_y_mps2());
      SerialBT.print("\t");
      SerialBT.print(imu.accel_z_mps2());
      SerialBT.print("\t");
      SerialBT.print(imu.gyro_x_radps());
      SerialBT.print("\t");
      SerialBT.print(imu.gyro_y_radps());
      SerialBT.print("\t");
      SerialBT.print(imu.gyro_z_radps());
      SerialBT.print("\t");
      SerialBT.print(imu.mag_x_ut());
      SerialBT.print("\t");
      SerialBT.print(imu.mag_y_ut());
      SerialBT.print("\t");
      SerialBT.print(imu.mag_z_ut());
      SerialBT.print("\t");
      SerialBT.print(imu.die_temp_c());
      SerialBT.print("\n");
      digitalWrite(LED_BUILTIN, LOW);
   }
   
   delay(50);
}
