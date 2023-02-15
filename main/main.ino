// Motor A (Top)
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;
int enc1A = 18;
int enc1B = 19;
bool enc1Val;
bool enc1PrevVal;
int enc1Count;

// Motor B (Bottom)
int motor2Pin1 = 33;
int motor2Pin2 = 32;
int enable2Pin = 25;
int enc2A = 12;
int enc2B = 13;
bool enc2Val;
bool enc2PrevVal;
int enc2Count;

// Servo
int servoPWM = 34;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 200;

//initialize state and target encoder position
int currentState = 0;
int targetEnc1 = 0;
int targetEnc2 = 0;

void setup() {
  // sets the pins as outputs:
  // Motor A (Top)
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enc1A, INPUT);
  pinMode(enc1B, INPUT);

  // Motor 2 (Bottom)
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

  // attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  Serial.begin(115200);
}

void loop() {

  readEnc_all(enc1A, enc1B, &enc1Val, &enc1Count, &enc1PrevVal, enc2A, enc2B, &enc2Val, &enc2Count, &enc2PrevVal);  //big function :)
  Serial.print("enc1count: ");
  Serial.print(enc1Count);
  Serial.println(" ");
  Serial.print("encoder2count: ");
  Serial.print(enc2Count);
  Serial.println(" ");

}

void readEnc(int encA_pin, int encB_pin, bool* encVal, int* encCount, bool* encPrev){
  *encVal = digitalRead(encA_pin); //update encoder value

  //NEED TO SOMETHING HERE WITH ENC2B
  (void) encB_pin; //putting this here so compiler doesnt get mad

  if(*encVal != *encPrev){
    *encCount = *encCount + 1;
  }
  else{
    //*encCount = *encCount -1;  // does nothing
  }

  *encPrev = *encVal;
}

//call readEnc for all the encoders
void readEnc_all(int enc1A_pin, int enc1B_pin, bool* enc1Val, int* enc1Count, bool* enc1Prev, int enc2A_pin, int enc2B_pin, bool* enc2Val, int* enc2Count, bool* enc2Prev)
{
  readEnc(enc1A_pin, enc1B_pin, enc1Val, enc1Count, enc1Prev);
  readEnc(enc2A_pin, enc2B_pin, enc2Val, enc2Count, enc2Prev);
}