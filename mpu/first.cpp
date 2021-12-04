// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
 
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU9250.h"

#include "SensorFusion.h" //SF
SF fusion;
 
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU9250 accelgyro;
 
int16_t gx, gy, gz, ax, ay, az, mx, my, mz;
float pitch, roll, yaw;
float deltat, x, y, z;
 
#define LED_PIN 2
bool blinkState = false;
 
void setup() {
// join I2C bus (I2Cdev library doesn't do this automatically)
Wire.begin();
 
// initialize serial communication
// (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
// it's really up to you depending on your project)
Serial.begin(9600);
 
// initialize device
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
 
// verify connection
Serial.println("Testing device connections...");
Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 
// configure Arduino LED for
pinMode(LED_PIN, OUTPUT);
}
 
void loop() {
// read raw accel/gyro measurements from device
accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
 
  deltat = fusion.deltatUpdate(); //this have to be done before calling the fusion update
  //choose only one of these two:
  fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow
  //fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);  //else use the magwick, it is slower but more accurate

  pitch = fusion.getPitchRadians();
  roll = fusion.getRollRadians();    //you could also use getRollRadians() ecc
  yaw = fusion.getYawRadians();

  x = cos(yaw)*cos(pitch);
  y = sin(yaw)*cos(pitch);
  z = sin(pitch);

  Serial.print("x:\t"); Serial.println(x);
  Serial.print("y:\t"); Serial.println(y);
  Serial.print("z:\t"); Serial.println(z);
  Serial.println();
}