#include "Arduino.h"
#include <SoftwareSerial.h>      // Library for bluetooth communication
#include "Wire.h"                // This library allows you to communicate with I2C devices.
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
const int MPU_ADDR = 0x68;                                 // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                            // variables for gyro raw data
char tmp_str[7];                                           // temporary variable used in convert function
char *convert_int16_to_str(int16_t i)
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

// CSJL DHT11
#define DHTPIN A2      // what pin dht11 is connected to
#define DHTMODEL DHT11 // what model of dht sensor
DHT dht2 = DHT(DHTPIN, DHTMODEL);

// Global Baby Variables
float babyHunger = 0;
float babyThirst = 0;
float babyFatigue = 0;
float babyTemperature = 0;
float babyHumidity = 0;
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
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.print("IMU READY\n");

  // NFC
  SPI.begin();     // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.print("NFC READY\n");

  myDFPlayer.volume(100); // Set volume value. From 0 to 30
  myDFPlayer.play(3);     // Play the first mp3
}
void loop()
{
  readTempHum();
  readNFC();
  readimu();
}
