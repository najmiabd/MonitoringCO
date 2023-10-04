#include "MQ7.h"
#define A1PIN 0
#define A2PIN 1
#define A3PIN 2
#define A4PIN 3
#define VOLTAGE 5

#include <SoftwareSerial.h>
SoftwareSerial serial(10, 11);

// init MQ7 device
MQ71 mq71(A1PIN, VOLTAGE);
MQ72 mq72(A2PIN, VOLTAGE);
MQ73 mq73(A3PIN, VOLTAGE);
MQ74 mq74(A4PIN, VOLTAGE);

void setup()
{
  Serial.begin(19200);
  serial.begin(19200);
  while (!Serial)
  {
    ; // wait for serial connection
  }



  mq71.calibrate(); // calculates R0
  mq72.calibrate();
  mq73.calibrate();
  mq74.calibrate();

  // Menampilkan nilai R0 setelah proses kalibrasi
  Serial.print("Nilai R0 MQ71: ");
  Serial.println(mq71.getR0());
  Serial.print("Nilai R0 MQ72: ");
  Serial.println(mq72.getR0());
  Serial.print("Nilai R0 MQ73: ");
  Serial.println(mq73.getR0());
  Serial.print("Nilai R0 MQ74: ");
  Serial.println(mq74.getR0());

  Serial.println("Calibration done!");

}

void loop()
{
  String data = "";

  float ppm1 = mq71.readPpm();
  float ppm2 = mq72.readPpm();
  float ppm3 = mq73.readPpm();
  float ppm4 = mq74.readPpm();

  Serial.print("PPM1 = ");
  Serial.println(ppm1, 2);
  Serial.print("PPM2 = ");
  Serial.println(ppm2, 2);
  Serial.print("PPM3 = ");
  Serial.println(ppm3, 2);
  Serial.print("PPM4 = ");
  Serial.println(ppm4, 2);

  delay(10000);

  String datakirim = "PPM1: " + String(ppm1, 2) + ", PPM2: " + String(ppm2, 2) + ", PPM3: " +
                     String(ppm3, 2) + ", PPM4: " + String(ppm4, 2);
  data += datakirim + ",";

  Serial.println(datakirim);
  serial.println(datakirim);
}
