#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#define MPU_addr 0x68

int sd_init()
{
  if (!SD.begin(4))
  {
    Serial.println("Error initializing SD card");
    return 1;
  }
  Serial.println("SD card initialized.");

  String filename = "";
  for (int i=0; true ;++i)
  {
    filename = "test" + String(i) + ".txt";
    if (!SD.exists(filename))
    {
      break;
    }
  }
  File logFile = SD.open(filename, FILE_WRITE);
  if (!logFile)
  {
    Serial.println("Error creating file " + filename);
  //  return 2;
  }
  else
  {
    Serial.println("Created file " + filename + ".");
  }

  logFile.close();
}

void get_mpu_vals()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  accelx = Wire.read() << 8 | Wire.read();
  accely = Wire.read() << 8 | Wire.read();
  accelz = Wire.read() << 8 | Wire.read();
  gyx = Wire.read() << 8 | Wire.read();
  gyy = Wire.read() << 8 | Wire.read();
  gyz = Wire.read() << 8 | Wire.read();
}

void setup (void)
{
  Serial.begin(9600);
  while (!Serial);

  sd_init();

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop(){
  get_mpu_vals();
}
