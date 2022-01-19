#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "FD1-2";        // your network SSID (name)
char pass[] = "SpaghettiO";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

int powerState = LOW;
int pumpState = LOW;
int steamState = LOW;
int powerButtState = LOW;
int lastPowerButtState = LOW;
int pumpButtState = LOW;
int lastPumpButtState = LOW;
int steamButtState = LOW;
int lastSteamButtState = LOW;
int sComm = 0;

const int power = 2;  //main power relay
const int pump = 3; //pump relay
const int steam = 4; //steam relay
const int powerButt = 5;  //main power button
const int pumpButt = 6;  //pump button
const int steamButt = 7;  //steam button

void setup() {
//  Serial.begin(9600);
  delay(200);
  Serial.println("READY");
  
  pinMode(power, OUTPUT); //main power relay
  pinMode(pump, OUTPUT); //pump relay
  pinMode(steam, OUTPUT); //steam relay
  pinMode(powerButt, INPUT);  //main power button
  pinMode(pumpButt, INPUT);  //pump button
  pinMode(steamButt, INPUT);  //steam button
/*
   // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
*/
}

void loop() {

//code to toggle main power state variable from button
  lastPowerButtState = powerButtState;
  powerButtState = digitalRead(powerButt);

//code to toggle pump power state variable from button
  lastPumpButtState = pumpButtState;
  pumpButtState = digitalRead(pumpButt);

//code to toggle steam power state variable from button
  lastSteamButtState = steamButtState;
  steamButtState = digitalRead(steamButt);

  serialCommand();
  
  if(powerButtState == HIGH && lastPowerButtState == LOW){
    powerState = !powerState;
    Serial.print("Power state ");
    Serial.println(powerState);
    delay(350);
  }
  
  if(pumpButtState == HIGH && lastPumpButtState == LOW){
    pumpState = !pumpState;
    Serial.print("steam state ");
    Serial.println(pumpState);
    delay(350);
  }
  
  if(steamButtState == HIGH && lastSteamButtState == LOW){
    steamState = !steamState;
    digitalWrite(steam, steamState);
    Serial.print("Steam state ");
    Serial.println(steamState);
    delay(350);
  }

  digitalWrite(power, powerState);
  digitalWrite(pump, pumpState);
  digitalWrite(steam, steamState);
  
}
