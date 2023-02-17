#include <Wire.h>
 
// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>
 
// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);
 
// Define maximum and minimum number of "ticks" for the servo motors
// Range from 0 to 4095
// This determines the pulse width
 
#define SERVOMIN 110  // Minimum value 
#define SERVOMAX 500  // Maximum value
 
// Define servo motor connections (expand as required)
#define SER0 12 //Servo Motor 0 top servo
#define SER1 13 //Servo Motor 1 lower servo
#define SER2 14 //Servo Motor 2 pen servo
 
// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;
int pwm2;
 
void setup() 
{
  // Serial monitor setup
  Serial.begin(115200);
 
  // Initialize PCA9685
  pca9685.begin();
 
  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);
 
}
 
void loop() 
{
  Orangen_klauer();
  delay(3000);

  shigure();
  delay(3000);

}

void home()
{
  pwm0 = map(50, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
}

void lift_pen()
{
  pwm2 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
}

void drop_pen()
{
  pwm2 = map(60, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
}

void draw_random()
{
  for(int angle = 0; angle < 60; angle++)
  {
    pwm0 = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pca9685.setPWM(SER0, 0, pwm0);
    pwm1 = map(60 - angle, 0, 180, SERVOMIN, SERVOMAX);
    pca9685.setPWM(SER1, 0, pwm1);
    delay(30);
  }
  for(int angle = 60; angle > 0; angle--)
  {
    pwm0 = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pca9685.setPWM(SER0, 0, pwm0);
    pwm1 = map(60 - angle, 0, 180, SERVOMIN, SERVOMAX);
    pca9685.setPWM(SER1, 0, pwm1);
    delay(30);
  }
}

void draw_straight()
{
  pwm0 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
}

void draw_infinity()
{

  pwm0 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
}

void Orangen_klauer()
{
  // move to T :)
  lift_pen();
  delay(1000);
  pwm0 = map(40, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(5, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  drop_pen();
  delay(1000);
  
  //top of T
  pwm0 = map(35, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);
  pwm0 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);

  //bottm of T
  pwm0 = map(35, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);

  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm1 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
  lift_pen();


  // move to M and drop pen :)
  pwm0 = map(25, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  drop_pen();
  delay(1000);

  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm1 = map(5, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(5, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm1 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm1 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  lift_pen();
  delay(1000);

}

void shigure()
{
  //move to J
  pwm0 = map(35, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
  drop_pen();
  delay(1000);

  //draw top of J
  pwm0 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);
  pwm0 = map(25, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);
  lift_pen();
  delay(1000);

  //draw bottom of J
  pwm0 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);
  drop_pen();
  delay(1000);

  pwm1 = map(25, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm1 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(35, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
  lift_pen();
  delay(1000);

  //move to C

  pwm0 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
  drop_pen();
  delay(1000);

  //draw C
  pwm0 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);

  pwm0 = map(20, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pwm1 = map(25, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(15, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pwm1 = map(30, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);

  pwm0 = map(10, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  delay(1000);
  lift_pen();
  delay(1000);




}