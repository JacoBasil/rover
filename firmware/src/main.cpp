#include <Arduino.h>
#define MOTOR_1_A 2
#define MOTOR_1_B 3
#define MOTOR_2_A 4
#define MOTOR_2_B 5
#define MOTOR_3_A 8
#define MOTOR_3_B 9
#define MOTOR_4_A 10
#define MOTOR_4_B 11
#define ENCODER_1_A 12
#define ENCODER_1_B 13
#define ENCODER_2_A 30
#define ENCODER_2_B 31
#define ENCODER_3_A 40
#define ENCODER_3_B 41
#define ENCODER_4_A 48
#define ENCODER_4_B 49

long enc_tick_1 = 0;
long enc_tick_2 = 0;
long enc_tick_3 = 0;
long enc_tick_4 = 0;

bool sig_enc_1_A = false;
bool sig_enc_1_B = false;
bool sig_enc_2_A = false;
bool sig_enc_2_B = false;
bool sig_enc_3_A = false;
bool sig_enc_3_B = false;
bool sig_enc_4_A = false;
bool sig_enc_4_B = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  // put your setup code here, to run once:
  pinMode(MOTOR_1_A, OUTPUT);
  pinMode(MOTOR_1_B, OUTPUT);
  pinMode(MOTOR_2_A, OUTPUT);
  pinMode(MOTOR_2_B, OUTPUT);
  pinMode(MOTOR_3_A, OUTPUT);
  pinMode(MOTOR_3_B, OUTPUT);
  pinMode(MOTOR_4_A, OUTPUT);
  pinMode(MOTOR_4_B, OUTPUT);
  attachInterrupt(ENCODER_1_A, encoder_A_Read(ENCODER_1_A, enc_tick_1, sig_enc_1_A, sig_enc_1_B), CHANGE);
  attachInterrupt(ENCODER_1_B, encoder_A_Read(ENCODER_1_B, enc_tick_1, sig_enc_1_A, sig_enc_1_B), CHANGE);
}

void encoder_A_Read(int16_t enc, long tick, bool sigA, bool sigB) {
  sigA = digitalRead(enc);
  if(sigB != sigA) tick++;
  else tick--;
}


void encoder_A_Read(int16_t enc, long tick, bool sigA, bool sigB) {
  sigB = digitalRead(enc);
  if(sigB == sigA) tick++;
  else tick--;
}

void motor_Go(int16_t motor, int16_t direct, uint16_t pwm) {

}
void loop() {
  // put your main code here, to run repeatedly:

}