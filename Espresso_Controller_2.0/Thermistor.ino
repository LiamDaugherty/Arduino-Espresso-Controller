void tempRead() {
  VRT = analogRead(A0); //Acquisition analog value of VRT
  VRT = (3.3 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + 0.00335401643)); //Temperature from thermistor

  TX = (TX - 273.15) * 9/5 + 32; //Conversion to Fahrenheit

  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(TX);
  Serial.println("F");
  delay(250);

}
