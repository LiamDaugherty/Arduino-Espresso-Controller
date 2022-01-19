void serialCommand() {
  if (Serial.available() > 0) {
    sComm = Serial.parseInt();
    Serial.print(sComm);
  }

  if (sComm == 4910) {
    powerState = HIGH;
    Serial.print("POOP");
  }

  if (sComm == 5010) {
    powerState = LOW;
  }
}
