#include <Arduino.h>
#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;

void setup() {
  Wire.begin(21, 22);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(115200);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  accX = Wire.read() << 8 | Wire.read();
  accY = Wire.read() << 8 | Wire.read();
  accZ = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  gyroX = Wire.read() << 8 | Wire.read();
  gyroY = Wire.read() << 8 | Wire.read();
  gyroZ = Wire.read() << 8 | Wire.read();

  float pitch = atan2(accY, accZ) * 180.0 / PI;
  float roll  = atan2(accX, accZ) * 180.0 / PI;

  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" | Roll: ");
  Serial.println(roll);

  delay(500);
}