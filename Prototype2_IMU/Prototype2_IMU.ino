#include "Arduino.h"
#include <SoftwareSerial.h> // Library for bluetooth communication
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SPI.h>                 // for NFC
#include <MFRC522.h>             // for NFC
#include "DFRobotDFPlayerMini.h" // for DF Player MINI module
#include "DHT.h"                 // for DHT11

// DF Player Mini uses pin 4 for RX and 3 for TX
SoftwareSerial softSerial(4, 3);
#define FPSerial softSerial
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// NFC pins 10, 11, 12, 13
#define SS_PIN 10
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

// IMU
MPU6050 sensor(0x69);
int ax, ay, az;
int gx, gy, gz;
float total = 0;

// CSJL DHT11
#define DHTPIN A2      // what pin dht11 is connected to
#define DHTMODEL DHT11 // what model of dht sensor
DHT dht2 = DHT(DHTPIN, DHTMODEL);

// Global Baby Variables
float babyHunger = 0;
float babyThirst = 0;
float babyFatigue = 0;
float babyTemperature = 0;
// float babyHumidity = 0;
float babyAttitude = 100;

void setup()
{
  // Normal Serial
  Serial.begin(9600);
  Serial.print("Serial READY\n");

  // Temperature and humidity sensor
  dht2.begin();
  Serial.print("Temp READY");

  // DFPlayer Serial
  FPSerial.begin(9600);
  myDFPlayer.begin(FPSerial);
  Serial.println("DFPlayer READY\n");

  // IMU
  Wire.begin();        // Iniciando I2C
  sensor.initialize(); // Iniciando el sensor
  Serial.print("IMU READY\n");

  // NFC
  SPI.begin();     // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.print("NFC READY\n");

  // pinMode(inPin, INPUT); //for eating
  pinMode(2, INPUT);
}

void loop()
{

  // update the temperature
  // babyHumidity = dht2.readHumidity();
  babyTemperature = dht2.readTemperature();

  checkAttitude();

  if (digitalRead(2) == LOW)
  {
    makehunger();
    Serial.println("getting hungry!");
  }
  else
  {
    eat();
    Serial.println("yummy!");
  }

  sleep();

  readimu();
}
