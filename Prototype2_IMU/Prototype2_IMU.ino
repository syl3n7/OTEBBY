#include <SoftwareSerial.h>      // Library for bluetooth communication
#include "Wire.h"                // This library allows you to communicate with I2C devices.
#include <SPI.h>                 // for NFC
#include <MFRC522.h>             // for NFC
#include "DFRobotDFPlayerMini.h" // for DF Player MINI module

// DF Player Mini uses RX pin
static const uint8_t PIN_MP3_TX = 9; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 8; // Connects to module's TX
SoftwareSerial DFPlayerSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player; // create player objetct

// NFC pins 10, 11, 12, 13
#define SS_PIN 10
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

// BT
SoftwareSerial btserial(6, 7); // BT ports 6 for RX/ 7 for TX
int btIN;                      // variable to read info sent from bt

// IMU
const int MPU_ADDR = 0x68;                                 // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                            // variables for gyro raw data
int16_t temperature;                                       // variables for temperature data
char tmp_str[7];                                           // temporary variable used in convert function
char *convert_int16_to_str(int16_t i)
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

// Global Baby Variables
float TimeToEat = 500;
float TimeToPoop = 500;
float TimeToScream = 500;

#define ledp 2 // digital pin for the main LED

void setup()
{
  DFPlayerSerial.begin(9600); // Start communication with DFPlayer Mini
  if (player.begin(DFPlayerSerial))
  {
    player.volume(30);
    player.play(1);
  }
  else
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  // Sleep Button and LED
  pinMode(2, OUTPUT); // LED
  // pinMode(3, INPUT);  // Button

  // Normal Serial
  Serial.begin(9600);
  Serial.print("\nSerial READY\n");

  // BT Serial
  btserial.begin(9600);
  Serial.print("BT READY\n");

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


}
  void loop()
  {
    btRead();
    //delay(2000);
    Serial.print("\n");
    readNFC();
    //delay(2000);
    Serial.print("\n");
    readimu();
    //delay(2000);
    Serial.print("\n");
    sleepbutton();
  }
