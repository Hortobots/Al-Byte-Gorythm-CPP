// Definição dos pinos para a primeira ponte H
#define ENA_A 2  // PWM
#define IN1_A 3
#define IN2_A 4
#define IN3_A 5
#define IN4_A 6
#define ENB_A 7 // PWM

// Definição dos pinos para a segunda ponte H
#define ENA_B 8 // PWM
#define IN1_B 9
#define IN2_B 10
#define IN4_B 11
#define IN3_B 12
#define ENB_B 13 // PWM  

void setup() {
    // Configuração dos pinos como saída
    pinMode(IN1_A, OUTPUT);
    pinMode(IN2_A, OUTPUT);
    pinMode(ENA_A, OUTPUT);
    
    pinMode(IN3_A, OUTPUT);
    pinMode(IN4_A, OUTPUT);
    pinMode(ENB_A, OUTPUT);
    
    pinMode(IN1_B, OUTPUT);
    pinMode(IN2_B, OUTPUT);
    pinMode(ENA_B, OUTPUT);
    
    pinMode(IN3_B, OUTPUT);
    pinMode(IN4_B, OUTPUT);
    pinMode(ENB_B, OUTPUT);

    Serial.begin(9600);
}
void stopAll(){
    digitalWrite(IN1_A, LOW); // M1 FRENTE
    digitalWrite(IN2_A, LOW); // M1 TRÁS

    digitalWrite(IN4_A, LOW); // M2 FRENTE
    digitalWrite(IN3_A, LOW); // M2 TRÁS

    digitalWrite(IN1_B, LOW); // M3 FRENTE
    digitalWrite(IN2_B, LOW); // M3 TRÁS

    digitalWrite(IN4_B, LOW); // M4 FRENTE
    digitalWrite(IN3_B, LOW); // M4 TRÁS
}

void move_Fwd(int velocidade, int tempo){

    int saveSpeed = velocidade;
    velocidade = 0;

    digitalWrite(IN1_A, HIGH); // M1 FRENTE
    digitalWrite(IN4_A, HIGH); // M2 FRENTE
    digitalWrite(IN1_B, HIGH); // M3 FRENTE
    digitalWrite(IN4_B, HIGH); // M4 FRENTE

    digitalWrite(IN2_A, LOW); // M1 TRÁS
    digitalWrite(IN3_A, LOW); // M2 TRÁS
    digitalWrite(IN2_B, LOW); // M3 TRÁS
    digitalWrite(IN3_B, LOW); // M4 TRÁS
    

    for (int i = 0; i < saveSpeed; i++){
      velocidade++;
      Serial.println(velocidade);
      delay(5);
      analogWrite(ENB_B, velocidade - 10);
      analogWrite(ENA_B, velocidade - 10);
      analogWrite(ENB_A, velocidade + 20);
      analogWrite(ENA_A, velocidade + 20); 

    }

    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20);
    Serial.println("andando para frente...");

    delay((tempo * 1000) - 2500);

    for (int i = 50; i > 1; i--){
      velocidade--;
      Serial.println(velocidade);
      delay(40);
      analogWrite(ENB_B, velocidade - 10);
      analogWrite(ENA_B, velocidade - 10);
      analogWrite(ENB_A, velocidade + 20);
      analogWrite(ENA_A, velocidade + 20);
}

for (int i = 100; i > 1; i--){
      velocidade--;
      Serial.println(velocidade);
      delay(10);
      analogWrite(ENB_B, velocidade - 10);
      analogWrite(ENA_B, velocidade - 10);
      analogWrite(ENB_A, velocidade + 20);
      analogWrite(ENA_A, velocidade + 20);
}
    delay(100);
    stopAll();
    Serial.println("parei :D");
}

void move_Bwd(int velocidade){
    digitalWrite(IN2_A, HIGH); // M1 TRÁS
    digitalWrite(IN3_A, HIGH); // M2 TRÁS
    digitalWrite(IN2_B, HIGH); // M3 TRÁS
    digitalWrite(IN3_B, HIGH); // M4 TRÁS

    digitalWrite(IN1_A, LOW); // M1 FRENTE
    digitalWrite(IN4_A, LOW); // M2 FRENTE
    digitalWrite(IN1_B, LOW); // M3 FRENTE
    digitalWrite(IN4_B, LOW); // M4 FRENTE
    
    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20); 
}

void move_Left(int velocidade){
    digitalWrite(IN1_A, HIGH); // M1 FRENTE
    digitalWrite(IN3_A, HIGH); // M2 TRÁS
    digitalWrite(IN2_B, HIGH); // M3 TRÁS
    digitalWrite(IN4_B, HIGH); // M4 FRENTE

    digitalWrite(IN4_A, LOW); // M2 FRENTE
    digitalWrite(IN1_B, LOW); // M3 FRENTE
    digitalWrite(IN2_A, LOW); // M1 TRÁS
    digitalWrite(IN3_B, LOW); // M4 TRÁS

    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20); 
}

void move_Right(int velocidade){

    digitalWrite(IN2_A, HIGH); // M1 TRÁS
    digitalWrite(IN4_A, HIGH); // M2 FRENTE
    digitalWrite(IN1_B, HIGH); // M3 FRENTE
    digitalWrite(IN3_B, HIGH); // M4 TRÁS

    digitalWrite(IN1_A, LOW); // M1 FRENTE
    digitalWrite(IN3_A, LOW); // M2 TRÁS
    digitalWrite(IN2_B, LOW); // M3 TRÁS
    digitalWrite(IN4_B, LOW); // M4 FRENTE

    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20); 
}

void turnLeft(int velocidade, int degrees){
    int tempo = (degrees * 20) / velocidade;  // Ajuste experimental
    digitalWrite(IN1_A, HIGH); // M1 FRENTE
    digitalWrite(IN4_A, HIGH); // M2 FRENTE
    digitalWrite(IN1_B, LOW); // M3 FRENTE
    digitalWrite(IN4_B, LOW); // M4 FRENTE

    digitalWrite(IN2_A, LOW); // M1 TRÁS
    digitalWrite(IN3_A, LOW); // M2 TRÁS
    digitalWrite(IN2_B, HIGH); // M3 TRÁS
    digitalWrite(IN3_B, HIGH); // M4 TRÁS

    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20);

    delay(tempo);
    stopAll();
}

void turnRight(int velocidade, int degrees){
    int tempo = (degrees * 10) / velocidade;  // Ajuste experimental
    digitalWrite(IN1_A, LOW); // M1 FRENTE
    digitalWrite(IN4_A, LOW); // M2 FRENTE
    digitalWrite(IN1_B, HIGH); // M3 FRENTE
    digitalWrite(IN4_B, HIGH); // M4 FRENTE

    digitalWrite(IN2_A, HIGH); // M1 TRÁS
    digitalWrite(IN3_A, HIGH); // M2 TRÁS
    digitalWrite(IN2_B, LOW); // M3 TRÁS
    digitalWrite(IN3_B, LOW); // M4 TRÁS

    analogWrite(ENB_B, velocidade - 10);
    analogWrite(ENA_B, velocidade - 10);
    analogWrite(ENB_A, velocidade + 20);
    analogWrite(ENA_A, velocidade + 20); 

    delay(tempo * 140);
    stopAll();
}

void loop() {
  move_Fwd(175, 5);
  delay(5000);
}
