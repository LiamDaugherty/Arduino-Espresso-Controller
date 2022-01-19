#include <LatchingButton.h>

#define RT0 10000   // Ω
#define B 3250     // K
#define VCC 3.3    //Supply voltage
#define R 10000  //R=10KΩ

int sComm = 0;
float shotTemp = 105.0; 
float steamTemp = 125.0;
float RT, VR, ln, TX, T0, VRT, setTemp;

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
  digitalWrite(readyLED, LOW);
}

void loop() { 
  if (boilerPowerState.pushed()) { //all powered on fuctions live inside this if statement
    digitalWrite(powerLED, HIGH);
    tempRead();
    Serial.print(TX);
    
    if (shotSteamState.pushed()) { //this is steam mode
      digitalWrite(steamLED, HIGH);
      digitalWrite(shotLED, LOW);
      setTemp = steamTemp;
    }
    
    else { //this is shot mode
      digitalWrite(shotLED, HIGH);
      digitalWrite(steamLED, LOW);
      setTemp = shotTemp;
    }


    if (TX < setTemp) { //checking temp reading against set temp
      digitalWrite(boiler, HIGH); //starts boiler heating up set temp
      digitalWrite(readyLED, LOW); //turns off ready LED
    }
    
    else {
      digitalWrite(boiler, LOW); //shuts off boiler
      digitalWrite(readyLED, HIGH); //turns on ready LED
    }


    if (pumpPowerState.pushed()) {
      digitalWrite(pump, HIGH);
    }
    
    else {
      digitalWrite(pump, LOW);
    }
  }
  
  else { //powered off state
    digitalWrite(powerLED, LOW); //turns off all lights
    digitalWrite(shotLED, LOW);
    digitalWrite(steamLED, LOW);
    digitalWrite(readyLED, LOW);

    digitalWrite(boiler, LOW); //turns off boiler and pump
    digitalWrite(pump, LOW);
  }

}
