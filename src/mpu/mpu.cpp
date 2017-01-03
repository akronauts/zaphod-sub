#include "mpu.h"
#include <Wire.h>

void Mpu::init()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void Mpu::get_values()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  data.accX = Wire.read() << 8 | Wire.read();
  data.accY = Wire.read() << 8 | Wire.read();
  data.accZ = Wire.read() << 8 | Wire.read();
  data.gyX = Wire.read() << 8 | Wire.read();
  data.gyY = Wire.read() << 8 | Wire.read();
  data.gyZ = Wire.read() << 8 | Wire.read();
}
