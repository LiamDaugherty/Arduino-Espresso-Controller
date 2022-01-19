#include <LatchingButton.h>

#define RT0 10000   // Ω
#define B 3250     // K
#define VCC 3.3    //Supply voltage
#define R 10000  //R=10KΩ

int sComm = 0;
float shotTemp = 105.0; 
float steamTemp = 125.0;
float RT, VR, ln, TX, T0, VRT;

const int boiler = 2;  //boiler power relay
const int pump = 3; //pump relay
const int powerButt = 4; //main boiler power button
const int pumpButt = 5;  //pump button
const int shotSteamButt = 6;  //shot steam button
const int powerLED = 7;  //power LED
const int shotLED = 8;  // shot mode LED
const int steamLED = 9; // steam mode LED
const int readyLED = 10; // ready LED

LatchingButton boilerPowerState(powerButt); //creates internal latching button for toggling and reading boiler power state
LatchingButton pumpPowerState(pumpButt); // creates internal latching button for toggling and reading water pump state
LatchingButton shotSteamState(shotSteamButt); // creates interal latching button for toggling and reading shot/steam mode state

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("READY");

  pinMode(boiler, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(powerButt, INPUT);
  pinMode(pumpButt, INPUT);
  pinMode(shotSteamButt, INPUT);
  pinMode(powerLED, OUTPUT);
  pinMode(shotLED, OUTPUT);
  pinMode(steamLED, OUTPUT);
  pinMode(readyLED, OUTPUT);

  digitalWrite(powerLED, LOW);
  digitalWrite(shotLED, LOW);
  digitalWrite(steamLED, LOW);
}

void loop() {
  if (boilerPowerState.pushed())
  {
    digitalWrite(powerLED, HIGH);
    
  }
  else
  {
    digitalWrite(powerLED, LOW);
    digitalWrite(shotLED, LOW);
    digitalWrite(steamLED, LOW);
    digitalWrite(readyLED, LOW);
    
  }

}
