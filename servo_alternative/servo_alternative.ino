#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ezButton.h>

// Serco stuff
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

// Encoder stuff
#define ROTARY_ENCODER_A_PIN 17
#define ROTARY_ENCODER_B_PIN 16
#define ROTARY_ENCODER_BUTTON_PIN 4
#define MODE_BUTTON_PIN 0
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

// Button stuff
ezButton buttonE(MODE_BUTTON_PIN);

int axis = 1;

void rotary_loop()
{
  if (rotaryEncoder.encoderChanged())
  {
    Serial.print("Value: ");
    Serial.println(rotaryEncoder.readEncoder());
    if(axis % 2 == 1)
    {
      pwm0 = map(rotaryEncoder.readEncoder(), 0, 180, SERVOMIN, SERVOMAX);
      pca9685.setPWM(SER0, 0, pwm0);
    }
    else
    {
      pwm1 = map(rotaryEncoder.readEncoder(), 0, 180, SERVOMIN, SERVOMAX);
      pca9685.setPWM(SER1, 0, pwm1);
    }
  }

  if (rotaryEncoder.isEncoderButtonClicked())
  {
    axis ++;
    Serial.println("Switching servo...");
  }
}

void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}

void setup()
{
  Serial.begin(115200);

  //encoder stuff
  //we must initialize rotary encoder
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  //set boundaries and if values should cycle or not
  //in this example we will set possible values between 0 and 1000;
  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 50, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration

  // servo stuff
  pca9685.begin();
  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);

  // button stuff
  buttonE.setDebounceTime(50);
}

void loop()
{
  buttonE.loop();

  if (buttonE.isPressed())
  {
    Serial.println("The mode button is pressed");
    //auto draw
    Orangen_klauer();
    delay(3000);

    shigure();
    delay(3000);
  }
  else
  {
    rotary_loop();
    delay(50);
  }
}

void lift_pen()
{
  pwm2 = map(160, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
  delay(1000);
}

void drop_pen()
{
  pwm2 = map(180, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(SER2, 0, pwm2);
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