#include <SD.h>
#include "sd.h"
#include <SPI.h>

void Sd::sd_init()
{
  // start SPI with CS on the appropriate pin
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Error initializing SD card");
  }
  Serial.println("SD card initialized.");

  // get a unique filename
  filename = "";
  for (int i=0; true ;++i)
  {
    filename = FILE_NAME + String(i) + ".txt";
    if (!SD.exists(filename))
    {
      break;
    }
  }

  // get a file handle
  File logFile = SD.open(filename, FILE_WRITE);
  if (!logFile)
  {
    Serial.println("Error creating file " + filename);
  }
  else
  {
    Serial.println("Created file " + filename + ".");
  }
}

void Sd::write_str(String s)
{
  File logFile = SD.open(filename, FILE_WRITE);

  char cbuff[50];
  s.toCharArray(cbuff, 50);
  logFile.write(cbuff);
  logFile.flush();
  logFile.close();
}

void Sd::write_int(int x)
{
  File logFile = SD.open(filename, FILE_WRITE);
  char cbuff[50];

  String(x).toCharArray(cbuff, 50);
  logFile.write(cbuff);
  logFile.flush();
  logFile.close();
}

void Sd::write_long(long x)
{
  File logFile = SD.open(filename, FILE_WRITE);

  char cbuff[50];

  String(x).toCharArray(cbuff, 50);
  logFile.write(cbuff);
  logFile.flush();
  logFile.close();
}
