#define MPU_addr 0x68

struct Data
{
  int accX;
  int accY;
  int accZ;
  int gyX;
  int gyY;
  int gyZ;
};

class Mpu
{
  public:
    Data data;

    void init();
    void get_values();
};
