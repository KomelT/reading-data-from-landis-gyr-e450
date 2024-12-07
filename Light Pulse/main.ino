unsigned long timems = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(4, INPUT);

  timems = millis();
}

void loop()
{
  int val = analogRead(4);
  if (val != 0 && (millis() - timems) > 500)
  {
    unsigned long delta = millis() - timems;

    float timeh = (float)delta / 1000.0 / 3600.0;

    float wattage = 1.0 / timeh;
    
    Serial.printf("Delta time: %lu ms\n", delta);
    Serial.printf("Wattage: %.6f W\n", wattage);

    timems = millis(); // Reset the time marker
  }
  delay(1);
}
