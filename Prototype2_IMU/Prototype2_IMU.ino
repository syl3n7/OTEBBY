#include "Arduino.h"
#include <SoftwareSerial.h>      // Library for bluetooth communication
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h" // This library allows you to communicate with I2C devices, in this case, the IMU
#include <SPI.h>                 // for NFC
#include <MFRC522.h>             // for NFC
#include "DFRobotDFPlayerMini.h" // for DF Player MINI module
#include "DHT.h"                 // for DHT11

//IMU New Method
MPU6050 sensor;
int ax, ay, az;
int gx, gy, gz;

//Filter
long f_ax,f_ay, f_az;
int p_ax, p_ay, p_az;
long f_gx,f_gy, f_gz;
int p_gx, p_gy, p_gz;
int counter=0;

//Offsets
int ax_o,ay_o,az_o;
int gx_o,gy_o,gz_o;

// DF Player Mini uses pin 4 for RX and 3 for TX
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/3);
#define FPSerial softSerial
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// NFC pins 10, 11, 12, 13
#define SS_PIN 10
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

// CSJL DHT11
#define DHTPIN A2       // what pin dht11 is connected to
#define DHTMODEL DHT11 // what model of dht sensor
DHT dht2 = DHT(DHTPIN, DHTMODEL); //create an object with the pin and model of DHT.

// Global Baby Variables
float babyHunger = 0;
float babyThirst = 0;
float babyFatigue = 0;
float babyTemperature = 0;
float babyHumidity = 0;
float babyAttitude = 0;

void setup()
{
  // IMU NEW METHOD
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  if (sensor.testConnection()) Serial.println("IMU OK");
  
  //read previous offsets
  ax_o=sensor.getXAccelOffset();
  ay_o=sensor.getYAccelOffset();
  az_o=sensor.getZAccelOffset();
  gx_o=sensor.getXGyroOffset();
  gy_o=sensor.getYGyroOffset();
  gz_o=sensor.getZGyroOffset();

  Serial.println("Press a key on the serial console to calibrate.");
  while (true){if (Serial.available()) break;}  
  Serial.println("Calibrating IMU");

  // Normal Serial
  Serial.begin(9600);
  Serial.print("Serial READY\n");

  // Temperature and humidity sensor
  dht2.begin();
  Serial.print("Temp READY\n");

  // DFPlayer Serial
  FPSerial.begin(9600);
  myDFPlayer.begin(FPSerial);
  Serial.println("DFPlayer READY\n");

  // NFC
  SPI.begin();     // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.print("NFC READY\n");

  //Baby stuff
  babyHunger = random(0, 100);
  babyThirst = random(0, 100);
  babyFatigue = random(0, 100);
  babyTemperature = dht2.readTemperature();
  babyHumidity = dht2.readHumidity();
  babyAttitude = random(0, 100);

}

void loop()
{
  Serial.println("hello");
  readTempHum();
  readNFC();
  readimu();
}
