#include <Wire.h>
#include <Servo.h>

template <typename T, typename... Args>
void print(T val, Args... args)
{
    Serial.print(val);
    print(args...);
}
template <typename T>
void print(T val)
{
    Serial.print(val);
}
template <typename T, typename... Args>
void println(T val, Args... args)
{
    print(val, args...);
    Serial.print("\n");
}

// servos should be digital
namespace constants
{
    const int sda = 4; // a4
    const int scl = 5; // a5

    const int servoPort = 1; // d1
}

// based on datasheet from 
// https://cdn.sparkfun.com/datasheets/Sensors/Accelerometers/RM-MPU-6000A.pdf
namespace mpu6050{
  const char address = 0x68;

  char read8(char reg){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    int available = Wire.requestFrom(address, 1);
    if (available != 1){
      println("ERROR: unable to request");
      return '\0';
    }
    return Wire.read();
  }

  short read16(char reg){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    int available = Wire.requestFrom(0x68, 2);
    println("num available: ", available);
    
  }
  void verifyDetectable(){
    Wire.beginTransmission(address);
    int ret =  Wire.endTransmission();

    if (ret == 0){
      println("mpu6050 is detectable");
    }
    else{
      println("mpu6050 is not detectable, please make sure it is wired correctly. Failed detecting with error ", address);
    }
  }

  void verifyWhoAmI(){
    // select the chip and the register
    char identity = read8(117);
    if (identity == 0x68){
      println("mpu6050 identified itself correctly");
    }
    else{
      Serial.println(identity, BIN);
      println("something went wrong; got ", (int)identity, " instead of 0x68");
    }
    while (Wire.available()){
      Wire.read();
    }
  }
};

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin();

    mpu6050::verifyDetectable();
    mpu6050::verifyWhoAmI();
}

void loop()
{
    // format for reading / writing is write the address you want to request from
    // and then read
    // mpu6050::read16(59);
}
