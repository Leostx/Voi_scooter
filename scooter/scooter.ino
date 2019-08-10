#include <SoftwareSerial.h>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"

#define BUZ   3

#define BT_RX 8
#define BT_TX 9

#define MC_RX 10
#define MC_TX 11
#define EN    12

#define HOLD  0.01

SoftwareSerial bt(BT_RX, BT_TX);
SoftwareSerial mc(MC_RX, MC_TX);

LSM6DS3 IMU;


byte standby[] = {0x60, 0x03, 0x00, 0x92, 0x00, 0x00, 0x56, 0xEC};

byte start_0[] = {0x60, 0x03, 0x01, 0xE2, 0x00, 0x01, 0x00, 0x1D, 0x71};
byte start_1[] = {0x60, 0x03, 0x01, 0xE1, 0x00, 0x01, 0xF1, 0xDD, 0xB0};

byte stop_0[] = {0x60, 0x03, 0x01, 0xE2, 0x00, 0x01, 0x01, 0xDD, 0xB0};
byte stop_1[] = {0x60, 0x03, 0x01, 0xE1, 0x00, 0x01, 0xF0, 0x1D, 0x71};
byte stop_2[] = {0x60, 0x03, 0x01, 0xE2, 0x00, 0x01, 0x00, 0x1D, 0x71};

bool state    = 0;
bool EnState  = 1;

//float param = {0, 0, 0};

void setup() {
  pinMode(BUZ, OUTPUT);
  pinMode(EN, OUTPUT);

  Serial.begin(9600);
  bt.begin(9600);
  mc.begin(9600);

  IMU.begin();

  //enable dlock and lock
  digitalWrite(EN, HIGH);
  mc.write(stop_1, 9);

  /*
  param[0] = IMU.readFloatAccelX();  
  param[1] = IMU.readFloatAccelY();
  param[2] = IMU.readFloatAccelZ();
  */
}

void loop() {
  //select bluetooth rx and look for command
  bt.listen();
  if (bt.available()) {
    String rec = bt.readString();
    rec.trim();
    
    if(rec.equals("Start") && !state){
      state = 1;
      
      Serial.println("START!");
      mc.write(start_1, 9);
      bt.println("started!");

      //make sound
      digitalWrite(BUZ, HIGH);
      delay(400);
      digitalWrite(BUZ, LOW);
      delay(200);
      digitalWrite(BUZ, HIGH);
      delay(100);
      digitalWrite(BUZ, LOW);
      
    }else if(rec.equals("Stop") && state){
      state = 0;
      
      Serial.println("STOP!");
      mc.write(stop_1, 9);
      bt.println("stoped!");

      //make sound
      digitalWrite(BUZ, HIGH);
      delay(100);
      digitalWrite(BUZ, LOW);
      delay(200);
      digitalWrite(BUZ, HIGH);
      delay(400);
      digitalWrite(BUZ, LOW);
      
    }else if(rec.equals("Enable") && !state){
      EnState = 1;
      
      Serial.println("ENABLE!");
      digitalWrite(EN, HIGH);
      bt.println("enabled!");
    }else if(rec.equals("Disable") && state){
      EnState = 0;
      
      Serial.println("DISABLE!");
      digitalWrite(EN, LOW);
      bt.println("disabled!");
    }
  }

}
