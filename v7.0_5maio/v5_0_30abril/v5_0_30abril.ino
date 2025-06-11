#include <Servo.h>
//#include "mpu6050.h"

// DEFINIÇÃO DOS PINOS //
#define ENA_A 2
#define IN1_A 3
#define IN2_A 4
#define IN3_A 5
#define IN4_A 6
#define ENB_A 7

#define ENA_B 8
#define IN1_B 9
#define IN2_B 10
#define IN4_B 11
#define IN3_B 12
#define ENB_B 13

// AJUSTE INDIVIDUAL DE FORÇA DOS MOTORES (compensação manual)
int motorM1_ajuste = -35;   // IN1_A/IN2_A
int motorM2_ajuste = -35;   // IN3_A/IN4_A
int motorM3_ajuste = -20;   // IN1_B/IN2_B
int motorM4_ajuste = 0;     // IN3_B/IN4_B

Servo servo;
int angle;

void setup() {
  Serial.begin(9600);
  servo.attach(45);  // Pino do servo
  servo.write(90);   // Posição central

  pinMode(IN1_A, OUTPUT); pinMode(IN2_A, OUTPUT); pinMode(ENA_A, OUTPUT);
  pinMode(IN3_A, OUTPUT); pinMode(IN4_A, OUTPUT); pinMode(ENB_A, OUTPUT);
  pinMode(IN1_B, OUTPUT); pinMode(IN2_B, OUTPUT); pinMode(ENA_B, OUTPUT);
  pinMode(IN3_B, OUTPUT); pinMode(IN4_B, OUTPUT); pinMode(ENB_B, OUTPUT);

  stopAll();
}

void loop() {
}

void processarComando(String comando) {
  String nome = getToken(comando, 0);
  int val1 = getToken(comando, 1).toInt();
  int val2 = getToken(comando, 2).toInt();

  if (nome == "move_Fwd") move_Fwd(val1, val2);
  else if (nome == "move_Bwd") move_Bwd(val1, val2);
  else if (nome == "move_Left") move_Left(val1, val2);
  else if (nome == "move_Right") move_Right(val1, val2);
  else if (nome == "turnLeft") turnLeft(val1, val2);
  else if (nome == "turnRight") turnRight(val1, val2);
  else Serial.println("Comando inválido!");
}

String getToken(String data, int index) {
  int start = 0, end = -1;
  for (int i = 0; i <= index; i++) {
    start = end + 1;
    end = data.indexOf(' ', start);
    if (end == -1) end = data.length();
  }
  return data.substring(start, end);
}

// ========== UTILITÁRIO ========== //

void aplicarPWM(int baseVelocidade) {
  analogWrite(ENA_A, constrain(baseVelocidade + motorM1_ajuste, 0, 255)); // M1
  analogWrite(ENB_A, constrain(baseVelocidade + motorM2_ajuste, 0, 255)); // M2
  analogWrite(ENA_B, constrain(baseVelocidade + motorM3_ajuste, 0, 255)); // M3
  analogWrite(ENB_B, constrain(baseVelocidade + motorM4_ajuste, 0, 255)); // M4
}

void stopAll() {
  digitalWrite(IN1_A, LOW); digitalWrite(IN2_A, LOW);
  digitalWrite(IN3_A, LOW); digitalWrite(IN4_A, LOW);
  digitalWrite(IN1_B, LOW); digitalWrite(IN2_B, LOW);
  digitalWrite(IN3_B, LOW); digitalWrite(IN4_B, LOW);
}

// ========== FUNÇÕES DE MOVIMENTO ========== //

void move_Fwd(int velocidade, int tempo){
  digitalWrite(IN2_A, HIGH); digitalWrite(IN1_A, LOW); // M1
  digitalWrite(IN3_A, HIGH); digitalWrite(IN4_A, LOW); // M2
  digitalWrite(IN2_B, HIGH); digitalWrite(IN1_B, LOW); // M3
  digitalWrite(IN4_B, HIGH); digitalWrite(IN3_B, LOW); // M4

  aplicarPWM(velocidade);
  Serial.println("andando para frente...");
  delay(tempo * 1000);
  stopAll();
  Serial.println("parei :D");
}

void move_Bwd(int velocidade, int tempo){
  digitalWrite(IN2_A, LOW); digitalWrite(IN1_A, HIGH); // M1
  digitalWrite(IN3_A, LOW); digitalWrite(IN4_A, HIGH); // M2
  digitalWrite(IN2_B, LOW); digitalWrite(IN1_B, HIGH); // M3
  digitalWrite(IN4_B, LOW); digitalWrite(IN3_B, HIGH); // M4

  aplicarPWM(velocidade);
  Serial.println("andando para trás...");
  delay(tempo * 1000);
  stopAll();
  Serial.println("parei :D");
}

void move_Left(int velocidade, int tempo){
  digitalWrite(IN2_A, HIGH); digitalWrite(IN1_A, LOW);  // M1
  digitalWrite(IN3_A, LOW);  digitalWrite(IN4_A, HIGH); // M2
  digitalWrite(IN2_B, LOW);  digitalWrite(IN1_B, HIGH); // M3
  digitalWrite(IN4_B, HIGH); digitalWrite(IN3_B, LOW);  // M4

  aplicarPWM(velocidade);
  Serial.println("andando para a esquerda...");
  delay(tempo * 1000);
  stopAll();
  Serial.println("parei :D");
}

void move_Right(int velocidade, int tempo){
  digitalWrite(IN2_A, LOW);  digitalWrite(IN1_A, HIGH); // M1
  digitalWrite(IN3_A, HIGH); digitalWrite(IN4_A, LOW);  // M2
  digitalWrite(IN2_B, HIGH); digitalWrite(IN1_B, LOW);  // M3
  digitalWrite(IN4_B, LOW);  digitalWrite(IN3_B, HIGH); // M4

  aplicarPWM(velocidade);
  Serial.println("andando para a direita...");
  delay(tempo * 1000);
  stopAll();
  Serial.println("parei :D");
}

void turnLeft(int velocidade, int degrees){
  int tempo = (degrees * 10) / velocidade;

  digitalWrite(IN2_A, HIGH); digitalWrite(IN1_A, LOW);  // M1
  digitalWrite(IN3_A, HIGH); digitalWrite(IN4_A, LOW);  // M2
  digitalWrite(IN2_B, LOW);  digitalWrite(IN1_B, HIGH); // M3
  digitalWrite(IN4_B, LOW);  digitalWrite(IN3_B, HIGH); // M4

  aplicarPWM(velocidade);
  delay(tempo * 140);
  stopAll();
}

void turnRight(int velocidade, int degrees){
  int tempo = ((degrees * 10) / velocidade) * 2;

  digitalWrite(IN2_A, LOW);  digitalWrite(IN1_A, HIGH); // M1
  digitalWrite(IN3_A, LOW);  digitalWrite(IN4_A, HIGH); // M2
  digitalWrite(IN2_B, HIGH); digitalWrite(IN1_B, LOW);  // M3
  digitalWrite(IN4_B, HIGH); digitalWrite(IN3_B, LOW);  // M4

  aplicarPWM(velocidade);
  delay(tempo * 140);
  stopAll();
}
