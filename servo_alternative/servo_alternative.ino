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
  shigure();
  delay(1000);
  orangen_klauer();
  delay(3000);
}

void home()
{
  lift_pen();
  delay(1000);
  pwm0 = map(50, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
}

void lift_pen()
{
  pwm2 = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
  delay(1000);
}

void drop_pen()
{
  pwm2 = map(60, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
  delay(1000);
}

// start point, end point for top servo and start point , end point for lower servo
int draw_something(int angle0_start, int angle0_end, int angle1_start, int angle1_end)
{
  drop_pen();
  delay(300);
  int angle0;
  int angle1;

  // if drawing vertical, only moves lower servo
  if(angle0_start == angle0_end)
  {
    //moving forward
    if(angle1_start < angle1_end)
    {
      for(angle1 = angle1_start; angle1 <= angle1_end; angle1++)
      {
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER1, 0, pwm1);
        delay(30);
      }
    }

    //moving backward
    else
    {
      for(angle1 = angle1_start; angle1 >= angle1_end; angle1--)
      {
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER1, 0, pwm1);
        delay(30);
      }
    }
  }

  //if drawing horizontal, only moves top servo
  else if(angle1_start == angle1_end)
  {
    //moving down
    if(angle0_start < angle0_end)
    {
      for(angle0 = angle0_start; angle0 <= angle0_end; angle0++)
      {
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER1, 0, pwm1);
        delay(30);
      }
    }

    //moving up
    else
    {
      for(angle0 = angle0_start; angle0 >= angle0_end; angle0--)
      {
        pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER0, 0, pwm0);
        delay(30);
      }
    }
  }

  //drawing diagonal, need to determin ratio of moving
  else
  {
    //setting moving ratio of the angle
    int ratio = abs((angle1_start - angle1_end) / (angle0_start - angle0_end));

    if(angle0_start > angle0_end && angle1_start > angle1_end)
    {
      for(angle0 = angle0_start; angle0 <= angle0_end; angle0++)
      {
        int angle1 = angle1_start;
        pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER0, 0, pwm0);
        pca9685.setPWM(SER1, 0, pwm1);
        angle1 += ratio;
        delay(30);
      }
    }

    else if(angle0_start < angle0_end && angle1_start > angle1_end)
    {
      for(angle0 = angle0_start; angle0 >= angle0_end; angle0--)
      {
        angle1 = angle1_start;
        pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER0, 0, pwm0);
        pca9685.setPWM(SER1, 0, pwm1);
        angle1 += ratio;
        delay(30);
      }
    }

    else if(angle0_start > angle0_end && angle1_start < angle1_end)
    {
      for(angle0 = angle0_start; angle0 <= angle0_end; angle0++)
      {
        angle1 = angle1_start;
        pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER0, 0, pwm0);
        pca9685.setPWM(SER1, 0, pwm1);
        angle1 -= ratio;
        delay(30);
      }
    }
    else
    {
      for(angle0 = angle0_start; angle0 >= angle0_end; angle0--)
      {
        angle1 = angle1_start;
        pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
        pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
        pca9685.setPWM(SER0, 0, pwm0);
        pca9685.setPWM(SER1, 0, pwm1);
        angle1 -= ratio;
        delay(30);
      }
    }
  }

}

// move to coordinate
int go_to(int angle0, int angle1)
{
  lift_pen();
  delay(1000);
  pwm0 = map(angle0, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(angle1, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  delay(1000);
}

void orangen_klauer()
{
  // move to T :)
  go_to(40, 5);
  
  //top of T
  draw_something(40, 30, 5, 5);

  //bottm of T
  go_to(35, 5);
  draw_something(35, 35, 5, 15);

  // move to M :)
  go_to(25, 5);

  draw_something(25, 25, 5, 15);
  draw_something(20, 15, 10, 5);
  draw_something(15, 15, 5, 15);

  delay(1000);

}

void shigure()
{
  //move to J
  go_to(35, 20);

  //draw top of J
  draw_something(35, 25, 20, 20);


  //draw bottom of J
  go_to(30, 20);
  draw_something(30, 30, 20, 30);
  draw_something(30, 35, 30, 30);

  //move to C
  go_to(10, 20);

  //draw C
  draw_something(10, 15, 20, 20);
  draw_something(15, 20, 20 ,25);
  draw_something(20, 15, 25, 30);
  draw_something(15, 10, 30, 30);
}

void cr()
{
  //move to C
  go_to(0, 5);

  //draw C
  draw_something(0, 5, 5, 5);
  draw_something(5, 10, 5, 10);
  draw_something(10, 5, 10, 15);
  draw_something(5, 0, 15, 15);

  //move to R
  go_to(5, 30);

  //draw R
  draw_something(5, 5, 30, 20);
  draw_something(5, 0, 20, 20);
  draw_something(0, 0, 20, 25);
  draw_something(0, 5, 25, 25);
  draw_something(5, 0, 25, 30);



}