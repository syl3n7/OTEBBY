#include "Arduino.h"
#include <SoftwareSerial.h>      // Library for software serial
#include "I2Cdev.h"              // for MPU6050
#include "MPU6050.h"             // for MPU6050
#include "Wire.h"                // for MPU6050
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
float babyHunger = 100; //if 0 hes very hungry, if 100 not hungry
float babyTemperature = 0; //if 18c or less he's cold, if 27 or more he's hot, the in between is the sweet spot.
float babyAttitude = 100; //the lower the number the heavier are the cries
int timeToSleep = 60000; // time to make the baby sleep each time he is ok :)
int defaultDelay = 35; 
int soundDelay = 10000; // 10 sec wait after playing a sound.
bool sleeping = false;
bool hungry = false;

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

  // Inicialize I2C IMU
  Wire.begin();        // 
  sensor.initialize(); // 
  Serial.print("IMU READY\n");

  // NFC
  SPI.begin();     // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.print("NFC READY\n");

  // pinMode(inPin, INPUT); //for eating //added a resistor to stop the short and read accurately from pin D2.
  pinMode(2, INPUT);
}

void loop()
{
  // Update the temperature and humidity
  // babyHumidity = dht2.readHumidity(); //no longer used
  babyTemperature = dht2.readTemperature();
  
  if(sleeping) 
  {
    sleep();
    checkAttitude();
    makehunger();
  }
  else
  {  
    wake();

    if (digitalRead(2) == HIGH)
    {
      eat();
      Serial.println("yummy! nrml");
    }
    else
    {
      makehunger();
      Serial.println("getting hungry! nrml");
    }
  
    if (rfid.PICC_IsNewCardPresent() && babyHunger > 75 || rfid.PICC_IsNewCardPresent() && babyAttitude > 65) 
    {
        sleeping = true;
        sleep();
    }
  }
}
