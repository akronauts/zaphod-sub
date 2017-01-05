#include "sd/sd.h"
#include "mpu/mpu.h"
#include <Wire.h>
#include <SD.h>
#include <TimerOne.h>

#define MPU_addr 0x68
#define STRAT1_PIN 2
#define STRAT2_PIN 3
#define STRAT3_PIN 4

File logFile;
Mpu mpu;
//TimerOne timer;
Sd sd;
bool strat1fired = false;
bool strat2fired = false;
bool strat3fired = false;

long _clock = 0;

void update_clk()
{
  _clock = _clock + 1;
}

void setup (void)
{
  //Serial.begin(115200);
  //while (!Serial);

  // initialize the sd card
  sd.sd_init();

  // initialize the mpu module
  mpu.init();

  // initialize the timer
  Timer1.initialize(10000);
  Timer1.attachInterrupt(update_clk);

  // set up the pins for detecting the stratalogger
  pinMode(STRAT1_PIN, INPUT);
  pinMode(STRAT2_PIN, INPUT);
  pinMode(STRAT3_PIN, INPUT);
}

void loop()
{
    mpu.get_values();
    Serial.println("Writing");
    sd.write_long(_clock);
    sd.write_str(",");
    sd.write_int(mpu.data.accX);
    sd.write_str(",");
    sd.write_int(mpu.data.accY);
    sd.write_str(",");
    sd.write_int(mpu.data.accZ);
    sd.write_str(",");
    sd.write_int(mpu.data.gyX);
    sd.write_str(",");
    sd.write_int(mpu.data.gyY);
    sd.write_str(",");
    sd.write_int(mpu.data.gyZ);
    sd.write_str("\n");

    if (digitalRead(STRAT1_PIN) == HIGH)
    {
      if (!strat1fired)
      {
          sd.write_str("Stratalogger 1 fired!");
          strat1fired = true;
      }
    }
    if (digitalRead(STRAT2_PIN) == HIGH)
    {
      if (!strat2fired)
      {
          sd.write_str("Stratalogger 2 fired!");
          strat2fired = true;
      }
    }
    if (digitalRead(STRAT3_PIN) == HIGH)
    {
      if (!strat3fired)
      {
          sd.write_str("Stratalogger 3 fired!");
          strat3fired = true;
      }
    }
}
