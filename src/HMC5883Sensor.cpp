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

    // Calculate heading in degrees
    float heading = atan2(y, x) * 180.0 / PI;

    // Adjust for negative heading values
    if (heading < 0) {
      heading += 360.0;
    }

    // Determine cardinal direction
    String direction;
    if (heading >= 45.0 && heading < 135.0) {
      direction = "E"; // East
    } else if (heading >= 135.0 && heading < 225.0) {
      direction = "S"; // South
    } else if (heading >= 225.0 && heading < 315.0) {
      direction = "W"; // West
    } else {
      direction = "N"; // North
    }

    // Print results
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.print(z);
    Serial.print(" Heading: ");
    Serial.print(heading);
    Serial.print(" Direction: ");
    Serial.println(direction);
  }

  delay(1000); // Delay for 1 second before reading again
}