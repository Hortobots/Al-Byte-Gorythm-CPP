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

void setup() {
  Serial.begin(9600);

  pinMode(IN1_A, OUTPUT); pinMode(IN2_A, OUTPUT); pinMode(ENA_A, OUTPUT);
  pinMode(IN3_A, OUTPUT); pinMode(IN4_A, OUTPUT); pinMode(ENB_A, OUTPUT);
  pinMode(IN1_B, OUTPUT); pinMode(IN2_B, OUTPUT); pinMode(ENA_B, OUTPUT);
  pinMode(IN3_B, OUTPUT); pinMode(IN4_B, OUTPUT); pinMode(ENB_B, OUTPUT);

  stopAll();
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    processarComando(comando);
  }
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

// ========== FUNÇÕES DE MOVIMENTO ========== //

void stopAll() {
  digitalWrite(IN1_A, LOW); digitalWrite(IN2_A, LOW);
  digitalWrite(IN3_A, LOW); digitalWrite(IN4_A, LOW);
  digitalWrite(IN1_B, LOW); digitalWrite(IN2_B, LOW);
  digitalWrite(IN3_B, LOW); digitalWrite(IN4_B, LOW);
}

// MOVER PARA FRENTE //

void move_Fwd(int velocidade, int tempo){

    int saveSpeed = velocidade;
    velocidade = 100;

    digitalWrite(IN1_A, HIGH); // M1 FRENTE
    digitalWrite(IN4_A, HIGH); // M2 FRENTE
    digitalWrite(IN1_B, HIGH); // M3 FRENTE
    digitalWrite(IN4_B, HIGH); // M4 FRENTE

    digitalWrite(IN2_A, LOW); // M1 TRÁS
    digitalWrite(IN3_A, LOW); // M2 TRÁS
    digitalWrite(IN2_B, LOW); // M3 TRÁS
    digitalWrite(IN3_B, LOW); // M4 TRÁS
    
    for (int i = 100; i < saveSpeed; i++){
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

// MOVER PARA TRÁS //

void move_Bwd(int velocidade, int tempo){

    int saveSpeed = velocidade;
    velocidade = 100;

    digitalWrite(IN2_A, HIGH); // M1 TRÁS
    digitalWrite(IN3_A, HIGH); // M2 TRÁS
    digitalWrite(IN2_B, HIGH); // M3 TRÁS
    digitalWrite(IN3_B, HIGH); // M4 TRÁS

    digitalWrite(IN1_A, LOW); // M1 FRENTE
    digitalWrite(IN4_A, LOW); // M2 FRENTE
    digitalWrite(IN1_B, LOW); // M3 FRENTE
    digitalWrite(IN4_B, LOW); // M4 FRENTE
    
        
    for (int i = 100; i < saveSpeed; i++){
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
    Serial.println("andando para trás...");

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

// MOVER PARA A ESQUERDA //

void move_Left(int velocidade, int tempo){

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
    Serial.println("andando para a esquerda...");

    delay(tempo * 1000);

    stopAll();
    Serial.println("parei :D");

}

// MOVER PARA A DIREITA //

void move_Right(int velocidade, int tempo){
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
    Serial.println("andando para a direita...");

    delay(tempo * 1000);

    stopAll();
    Serial.println("parei :D");

}

// GIRAR PARA A ESQUERDA //

void turnLeft(int velocidade, int degrees){
    int tempo = (degrees * 10) / velocidade;  // Ajuste experimental
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

    delay(tempo * 140);
    stopAll();
}

// GIRAR PARA A DIREITA //

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
