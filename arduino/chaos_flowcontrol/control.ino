
void setAirPressure(int channel, float value) {
  airPressure[channel] = value;
  analogWrite(airRegulatorPins[channel], map(value, 0, 1, 0, 255));
}

void setWaterPressure(int channel, float value) {
  waterPressure[channel] = value;
  analogWrite(pumpPins[channel], map(value, 0, 1, 0, 255));
}

void openWater(int channel) {
  waterValveOpen[channel] = true;
  digitalWrite(waterValvePins[channel], HIGH);
}

void closeWater(int channel) {
  waterValveOpen[channel] = false;
  digitalWrite(waterValvePins[channel], LOW);
}

void openAir(int channel) {
  airValveOpen[channel] = true;
  digitalWrite(airValvePins[channel], HIGH);
}

void closeAir(int channel) {
  airValveOpen[channel] = false;
  digitalWrite(airValvePins[channel], LOW);
}


