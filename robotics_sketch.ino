#include <Wire.h>
#include <Servo.h>

template <typename T, typename ...Args>
void print(T val, Args... args){
  Serial.print(val);
  print(args...);
}
template <typename T>
void print(T val){
  Serial.print(val);
}
template <typename T, typename ...Args>
void println(T val, Args... args){
  print(val, args...);
  Serial.print("\n");
}

// servos should be digital
namespace constants{
  const int sda = 4; // a4
  const int scl = 5; // a5

  const int servoPort = 1; // d1
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  // so the mpu6050 is 0x68
  Wire.beginTransmission(0x68);
  int ret= Wire.endTransmission();
  if (ret== 0){
    println("we were able to detect it!");
  }
  else{
    println("We failed to detect the mpu6050 with the val: ", ret);
  }

  // check to make sure we got the ack byte
  Wire.beginTransmission(0x68);
  Wire.write(117);
  ret = Wire.endTransmission();
  if (ret == 0){
    println("wooh");
  }
  else{
    println("failed...");
  }
  println("num bytes available is ", Wire.requestFrom(0x68, 1));
  char a = Wire.read();
  Serial.println(a, BIN);
  println("is it equal to what we expected? ", a == 0x68);
}

void loop() {
  // format for reading / writing is write the address you want to request from
  // and then read
  
}
