#include <Wire.h>

#define HMC5883_ADDR 0x1E // I2C address of HMC5883

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(HMC5883_ADDR);
  Wire.write(0x03); // Set the register pointer to the beginning of the data
  Wire.endTransmission();

  Wire.requestFrom(HMC5883_ADDR, 6);

  if (Wire.available() >= 6) {
    int x = Wire.read() << 8 | Wire.read();
    int z = Wire.read() << 8 | Wire.read();
    int y = Wire.read() << 8 | Wire.read();

    // Do something with the x, y, and z values
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.println(z);
  }

  delay(2000); // Delay for 1 second before reading again
}