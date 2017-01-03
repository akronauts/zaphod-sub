#include <SD.h>
#include "sd.h"
#include <SPI.h>

File sd_init()
{
  // start SPI with CS on pin 4
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Error initializing SD card");
  }
  Serial.println("SD card initialized.");

  // get a unique filename
  String filename = "";
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

  return logFile;
}
