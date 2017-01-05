#include <SD.h>

#define FILE_NAME "test"
#define CS_PIN 53

class Sd
{
  String filename;

  public:
    void sd_init();
    void write_int(int x);
    void write_long(long x);
    void write_str(String s);
};
