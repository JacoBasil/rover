#include <Arduino.h>
//motor PINS
#define MOTOR_1_A 2
#define MOTOR_1_B 3
#define MOTOR_2_A 4
#define MOTOR_2_B 5
#define MOTOR_3_A 8
#define MOTOR_3_B 9
#define MOTOR_4_A 10
#define MOTOR_4_B 11

//encoder PINS
#define ENCODER_1_A 12
#define ENCODER_1_B 13
#define ENCODER_2_A 30
#define ENCODER_2_B 31
#define ENCODER_3_A 40
#define ENCODER_3_B 41
#define ENCODER_4_A 48
#define ENCODER_4_B 49

//encoder ticks counter
volatile long enc_tick_1 = 0;
volatile long enc_tick_2 = 0;
volatile long enc_tick_3 = 0;
volatile long enc_tick_4 = 0;

//encoder signals state
volatile bool sig_enc_1_A = false;
volatile bool sig_enc_1_B = false;
volatile bool sig_enc_2_A = false;
volatile bool sig_enc_2_B = false;
volatile bool sig_enc_3_A = false;
volatile bool sig_enc_3_B = false;
volatile bool sig_enc_4_A = false;
volatile bool sig_enc_4_B = false;

enum MOTORS {MOTOR_1, MOTOR_2, MOTOR_3, MOTOR_4};

//Interrupt Service Routine for encoder #1
void encoderReadA1() {
  sig_enc_1_A = digitalRead(ENCODER_1_A);
  if(sig_enc_1_B != sig_enc_1_A) 
    enc_tick_1++;
  else enc_tick_1--;
}

void encoderReadB1() {
  sig_enc_1_B = digitalRead(ENCODER_1_B);
  if(sig_enc_1_B == sig_enc_1_A) enc_tick_1++;
  else enc_tick_1--;
}

//Interrupt Service Routine for encoder #2
void encoderReadA2() {
  sig_enc_2_A = digitalRead(ENCODER_2_A);
  if(sig_enc_2_B != sig_enc_2_A) enc_tick_2++;
  else enc_tick_2--;
}

void encoderReadB2() {
  sig_enc_2_B = digitalRead(ENCODER_2_B);
  if(sig_enc_2_B == sig_enc_2_A) enc_tick_2++;
  else enc_tick_2--;
}

//Interrupt Service Routine for encoder #3
void encoderReadA3() {
  sig_enc_3_A = digitalRead(ENCODER_3_A);
  if(sig_enc_3_B != sig_enc_3_A) enc_tick_3++;
  else enc_tick_3--;
}

void encoderReadB3() {
  sig_enc_3_B = digitalRead(ENCODER_3_B);
  if(sig_enc_3_B == sig_enc_3_A) enc_tick_3++;
  else enc_tick_3--;
}

//Interrupt Service Routine for encoder #4
void encoderReadA4() {
  sig_enc_4_A = digitalRead(ENCODER_4_A);
  if(sig_enc_4_B != sig_enc_4_A) enc_tick_4++;
  else enc_tick_4--;
}

void encoderReadB4() {
  sig_enc_4_B = digitalRead(ENCODER_4_B);
  if(sig_enc_4_B == sig_enc_4_A) enc_tick_4++;
  else enc_tick_4--;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  pinMode(MOTOR_1_A, OUTPUT);
  pinMode(MOTOR_1_B, OUTPUT);
  pinMode(MOTOR_2_A, OUTPUT);
  pinMode(MOTOR_2_B, OUTPUT);
  pinMode(MOTOR_3_A, OUTPUT);
  pinMode(MOTOR_3_B, OUTPUT);
  pinMode(MOTOR_4_A, OUTPUT);
  pinMode(MOTOR_4_B, OUTPUT);
  pinMode(ENCODER_1_A, INPUT);
  pinMode(ENCODER_1_B, INPUT);
  pinMode(ENCODER_2_A, INPUT);
  pinMode(ENCODER_2_B, INPUT);
  pinMode(ENCODER_3_A, INPUT);
  pinMode(ENCODER_3_B, INPUT);
  pinMode(ENCODER_4_A, INPUT);
  pinMode(ENCODER_4_B, INPUT);
  sig_enc_1_A = digitalRead(ENCODER_1_A);
  sig_enc_1_B = digitalRead(ENCODER_1_B);
  sig_enc_2_A = digitalRead(ENCODER_2_A);
  sig_enc_2_B = digitalRead(ENCODER_2_B);
  sig_enc_3_A = digitalRead(ENCODER_3_A);
  sig_enc_3_B = digitalRead(ENCODER_3_B);
  sig_enc_4_A = digitalRead(ENCODER_4_A);
  sig_enc_4_B = digitalRead(ENCODER_4_B);
  attachInterrupt(digitalPinToInterrupt(ENCODER_1_A), encoderReadA1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_1_B), encoderReadB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_2_A), encoderReadA2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_2_B), encoderReadB2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_3_A), encoderReadA3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_3_B), encoderReadB3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_4_A), encoderReadA4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_4_B), encoderReadB4, CHANGE);
}

void motorGo(MOTORS motor, String direct, uint16_t pwm) {
  switch (motor)
  {
  case MOTOR_1:
    if (direct == "CW") {
      analogWrite(MOTOR_1_A, pwm);
      digitalWrite(MOTOR_1_B, LOW);
    }
    else if (direct == "CWW")
    {
      analogWrite(MOTOR_1_B, pwm);
      digitalWrite(MOTOR_1_A, LOW);
    }
    else {
      digitalWrite(MOTOR_1_A, LOW);
      digitalWrite(MOTOR_1_B, LOW);
    }
    break;
  case MOTOR_2:
    if (direct == "CW") {
      analogWrite(MOTOR_2_A, pwm);
      digitalWrite(MOTOR_2_B, LOW);
    }
    else if (direct == "CWW")
    {
      analogWrite(MOTOR_2_B, pwm);
      digitalWrite(MOTOR_2_A, LOW);
    }
    else {
      digitalWrite(MOTOR_2_A, LOW);
      digitalWrite(MOTOR_2_B, LOW);
    }
    break;
  case MOTOR_3:
    if (direct == "CW") {
      analogWrite(MOTOR_3_A, pwm);
      digitalWrite(MOTOR_3_B, LOW);
    }
    else if (direct == "CWW")
    {
      analogWrite(MOTOR_3_B, pwm);
      digitalWrite(MOTOR_3_A, LOW);
    }
    else {
      digitalWrite(MOTOR_3_A, LOW);
      digitalWrite(MOTOR_3_B, LOW);
    }
    break;
  case MOTOR_4:
    if (direct == "CW") {
      analogWrite(MOTOR_4_A, pwm);
      digitalWrite(MOTOR_4_B, LOW);
    }
    else if (direct == "CWW")
    {
      analogWrite(MOTOR_4_B, pwm);
      digitalWrite(MOTOR_4_A, LOW);
    }
    else {
      digitalWrite(MOTOR_4_A, LOW);
      digitalWrite(MOTOR_4_B, LOW);
    }
    break;
  default:
    break;
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  motorGo(MOTOR_1, "CW", 200);
  Serial.println(enc_tick_1);  

}