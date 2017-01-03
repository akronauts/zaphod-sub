#include "sd/sd.h"
#include "mpu/mpu.h"
#include <Wire.h>
#include <SD.h>
#include <TimerOne.h>

#define MPU_addr 0x68

File logFile;
Mpu mpu;
TimerOne timer;

void setup (void)
{
  Serial.begin(9600);
  while (!Serial);

  logFile = sd_init();
  mpu.init();
  timer.initialize();
}

void loop(){
  mpu.get_values();

  logFile.write(timer.read());
  logFile.write(",");
  logFile.write(mpu.data.accX);
  logFile.write(",");
  logFile.write(mpu.data.accY);
  logFile.write(",");
  logFile.write(mpu.data.accZ);
  logFile.write(",");
  logFile.write(mpu.data.gyX);
  logFile.write(",");
  logFile.write(mpu.data.gyY);
  logFile.write(",");
  logFile.write(mpu.data.gyZ);
  logFile.write("\n");
}
