#include <BluetoothSerial.h>
#include <MPU9250_WE.h>
#include <Wire.h>
#define MPU9250_ADDR 0x68

BluetoothSerial SerialBT; //Initialise BT object
MPU9250_WE sensor = MPU9250_WE(MPU9250_ADDR); //Initialise sensor object 
long int refTime = millis(); //Start time
int idx = 0; //index
int sampleRate = 50;
int calibration = 100;

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

  //Start i2c bus
  Wire.begin(); // Default values are SCL: P22, SDA: P21
  Wire.setClock(400000);
  if (!sensor.init()) {
      Serial.println("Error connected to MPU9250");
  } else {
      Serial.println("MPU9250 connected succesfully");   
  }
  if(!sensor.initMagnetometer()){
    Serial.println("Magnetometer does not respond");
  }
  else{
    Serial.println("Magnetometer is connected");
  }

  // Start auto calibration
  Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
  delay(1000);
  sensor.autoOffsets();
  Serial.println("Internal calibration done!");

  sensor.setSampleRateDivider(5); // Sample rate = internal rate/(divider + 1)
  sensor.setAccRange(MPU9250_ACC_RANGE_4G); //Can be changed to 2G, 4G, 8G, 16G
  sensor.enableAccDLPF(true); // Enable the digital low pass filter. Wow
  sensor.setAccDLPF(MPU9250_DLPF_6);
  sensor.enableGyrDLPF(); // Wow
  sensor.setGyrDLPF(MPU9250_DLPF_6); // Lowest noise level apparently
  sensor.setGyrRange(MPU9250_GYRO_RANGE_500); // Can be changed to 250, 500, 1000, 2000 deg per sec
  sensor.setMagOpMode(AK8963_CONT_MODE_100HZ);
  delay(200);
  
  pinMode(LED_BUILTIN, OUTPUT); // Initialise Inbuilt LED 
  Serial.println("\nLet us begin");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  //idx = idx + 1;
  xyzFloat aValue = sensor.getGValues();
  xyzFloat gyr = sensor.getGyrValues();
  xyzFloat magValue = sensor.getMagValues();
  float temp = sensor.getTemperature();
  float resultantG = sensor.getResultantG(aValue);
  long int currentTime = (millis() - refTime);

  //SerialBT.print(idx);
  //SerialBT.print(" ");
  
  SerialBT.print(currentTime);
  SerialBT.print(" ");
  
  SerialBT.print(gyr.x);
  SerialBT.print(" ");
  SerialBT.print(gyr.y);
  SerialBT.print(" ");
  SerialBT.print(gyr.z);
  SerialBT.print(" ");
  
  SerialBT.print(aValue.x);
  SerialBT.print(" ");
  SerialBT.print(aValue.y);
  SerialBT.print(" ");
  SerialBT.print(aValue.z);
  SerialBT.print(" ");
  
  SerialBT.print(magValue.x);
  SerialBT.print(" ");
  SerialBT.print(magValue.y);
  SerialBT.print(" ");
  SerialBT.print(magValue.z);
  SerialBT.print("\r");
  
  digitalWrite(LED_BUILTIN, LOW);
  
  delay(sampleRate - 3); // Adjustment for lag
}
