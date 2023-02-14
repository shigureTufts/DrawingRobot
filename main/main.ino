// Motor 1
int motor1Pin1 = 2; 
int motor1Pin2 = 0; 
int enable1Pin = 4;
int enc1A = 16;
int enc1B = 17;
bool enc1Val;
bool enc1PrevVal;
int enc1Count;

// Motor 2
int motor2Pin1 = 5; 
int motor2Pin2 = 18; 
int enable2Pin = 19;
int enc2A = 22;
int enc2B = 23;
bool enc2Val;
bool enc2PrevVal;
int enc2Count;

//Servo
int servoPWM = 34;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;

//initialize state and target encoder position
int currentState = 0;
int targetEnc1 = 0;
int targetEnc2 = 0;

#include "time.h"

void setup() {
  
  // sets the pins as outputs:
  //m1
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enc1A, INPUT);
  pinMode(enc1B, INPUT);
  //m2
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(enc2A, INPUT);
  pinMode(enc2B, INPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);

  //start serial
  Serial.begin(115200);

  // H-Bridge direction selection, never needs to change due to our one directional motion. 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH); 

  //inititalize encoder states
  enc1PrevVal = digitalRead(enc1A);
  enc2PrevVal = digitalRead(enc2A);

}

void loop() {
  while(currentState == 1){
     //readEnc(enc1A, enc1B, &enc1Val, &enc1Count, &enc1PrevVal); //THIS IS FOR CALLING ENCODER READ For 1 of the encoders
     readEnc_all(enc1A, enc1B, &enc1Val, &enc1Count, &enc1PrevVal, enc2A, enc2B, &enc2Val, &enc2Count, &enc2PrevVal);  //big function :)
     Serial.print("enc1count: ");
     Serial.print(enc1Count);
     Serial.print("   Target : ");
     Serial.println(targetEnc1);

     Serial.print("enc2count: ");
     Serial.print(enc2Count);
     Serial.print("   Target : ");
     Serial.println(targetEnc2);
     
     //MOTOR 1
     Serial.print("\n\n ---------Setting line 1---------------- \n\n");
     driveMotor(1, 160);
     while(!((enc1Count == (targetEnc1 -1)) || (enc1Count == (targetEnc1 + 1)) || (enc1Count == targetEnc1))){
        readEnc(enc1A, enc1B, &enc1Val, &enc1Count, &enc1PrevVal);
        Serial.print("enc1count: ");
        Serial.println(enc1Count);
        if(enc1Count > 102){
          enc1Count = enc1Count%102;
         }
     }
     driveMotor(1, 0);
     
     // MOTOR 2
     Serial.print("\n\n ---------Setting line 2---------------- \n\n");
     driveMotor(2, 180);
     while(!((enc2Count == (targetEnc2 -2)) || (enc2Count == (targetEnc2 + 2)) || (enc2Count == targetEnc2))){
        readEnc(enc2A, enc2B, &enc2Val, &enc2Count, &enc2PrevVal);
        Serial.print("enc2count: ");
        Serial.println(enc2Count);
        if(enc2Count > 102){
          enc2Count = enc2Count%102;
         }
     }
     driveMotor(2, 0);
  }
}

//motor function
void driveMotor(int motor_id, int duty){
  int chan = getChannel(motor_id);
  if(chan == -1){
    return;
  }
  ledcWrite(chan, duty);
}
​
//motor channel function
int getChannel(int motor_id){
  if(motor_id == 1) return pwmChannel1;
  else if(motor_id == 2) return pwmChannel2;
  else if(motor_id == 3) return pwmChannel3;
  else return -1;
}


// after this resolves, encPrev is populated w/ enc, and encCount is incremented
// call with readEnc(&enc1Val, &enc1Count, &enc1PrevVal)
void readEnc(int encA_pin, int encB_pin, bool* encVal, int* encCount, bool* encPrev){
  *encVal = digitalRead(encA_pin); //update encoder value

  //NEED TO SOMETHING HERE WITH ENC2B
  (void) encB_pin; //putting this here so compiler doesnt get mad

  if(*encVal != *encPrev){
    *encCount = *encCount + 1;
  }
  else{
    //*encCount = *encCount -1;  UPDATED WUTH DIRECtion stuff
  }

  *encPrev = *encVal;
}

//call readEnc for all the encoders
void readEnc_all(int enc1A_pin, int enc1B_pin, bool* enc1Val, int* enc1Count, bool* enc1Prev, int enc2A_pin, int enc2B_pin, bool* enc2Val, int* enc2Count, bool* enc2Prev)
{
  readEnc(enc1A_pin, enc1B_pin, enc1Val, enc1Count, enc1Prev);
  readEnc(enc2A_pin, enc2B_pin, enc2Val, enc2Count, enc2Prev);
}

//target position calculation fucntions
//We don't know how exactly many encoder counts there are per output shaft revolution, and there is little to no documentation for this online. Which is very fun and nice. 
//As a result, the values of 102 and 1020 are both calculated using values provided by the manufacturer for their 150RPM motor in the same line.
//This may necesitate a fudge factor for manual tuning.




//end