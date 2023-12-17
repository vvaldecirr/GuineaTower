/**
 * Autor: Valdecir (Black Chan) - 03/AGO/2021
 * Código Arduino para automação do apartamento do Shyp
 * vvaldecirr@hotmail.com
 */

// Declaração das lâmpadas
const int pinoLuzAndar1      = 5; //Lâmpada do primeiro andar
const int pinoLuzAndar2      = 6; //Lâmpada do segundo andar
const int pinoLuzAndar3      = 9; //Lâmpada do terceiro andar
const int pinoLuzEscadaBaixo = 10; //Lâmpada da escada de baixo
const int pinoLuzEscadaCima  = 11; //Lâmpada da escada de cima

// Declaração dos sensores
const int pinoSensorAndar1  = 4; //Sensor do primeiro andar
const int pinoSensorAndar2  = 7; //Sensor do segundo andar
const int pinoSensorAndar3  = 8; //Sensor do terceiro andar

// Auxiliares do milis()
unsigned long lastLuzAndar1Time  = 0;
unsigned long lastLuzAndar2Time  = 0;
unsigned long lastLuzAndar3Time  = 0;
unsigned long luzAndarDelay      = 60000; // Tempo padrão de luz de andar acesa

int acionaAndar1; //Guardar valor do sensor do primeiro andar
int acionaAndar2; //Guardar valor do sensor do segundo andar
int acionaAndar3; //Guardar valor do sensor do terceiro andar

bool f1a1 = false;
bool f2a1 = false;
bool f3a1 = false;
bool f1a2 = false;
bool f2a2 = false;
bool f3a2 = false;
bool f1a3 = false;
bool f2a3 = false;
bool f3a3 = false;

void setup() {
  pinMode(pinoLuzAndar1, OUTPUT);
  pinMode(pinoLuzAndar2, OUTPUT);
  pinMode(pinoLuzAndar3, OUTPUT);
  pinMode(pinoLuzEscadaBaixo, OUTPUT);
  pinMode(pinoLuzEscadaCima, OUTPUT);
  
  pinMode(pinoSensorAndar1, INPUT);
  pinMode(pinoSensorAndar2, INPUT);
  pinMode(pinoSensorAndar3, INPUT);
  
  Serial.begin(9600);
}
 
void loop() {
  //Lendo sensores
  acionaAndar1 = digitalRead(pinoSensorAndar1);
  acionaAndar2 = digitalRead(pinoSensorAndar2);
  acionaAndar3 = digitalRead(pinoSensorAndar3);

  //Acionamento da rotina do primeiro andar
  if (acionaAndar1 == HIGH && f1a1 == false && f2a1 == false && f3a1 == false) {
    f1a1 = true;
  }
  
  //Acionamento da rotina do segundo andar
  if (acionaAndar2 == HIGH && f1a2 == false && f2a2 == false && f3a2 == false) {
    f1a2 = true;
  }
  
  //Acionamento da rotina do terceiro andar  
  if (acionaAndar3 == HIGH && f1a3 == false && f2a3 == false && f3a3 == false) {
    f1a3 = true;
  }

  //Andar1
  //fase 1
  if (f1a1) {
    for (int i = 0; i < 32; i++) {
      analogWrite(pinoLuzAndar1, i);
      delay(300);
    }
    for (int i = 33; i < 255; i++) {
      analogWrite(pinoLuzAndar1, i);
      analogWrite(pinoLuzEscadaBaixo, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar1, HIGH);
    digitalWrite(pinoLuzEscadaBaixo, HIGH);
    lastLuzAndar1Time = millis();
    f1a1 = false;
    f2a1 = true;
  }
  //fase 2
  if (f2a1) {
    if (millis() - lastLuzAndar1Time > luzAndarDelay) {
      f2a1 = false;
      f3a1 = true;
    }
  }
  //fase 3
  if (f3a1) {
    for (int i = 255; i > 0; i--) {
      analogWrite(pinoLuzAndar1, i);
      analogWrite(pinoLuzEscadaBaixo, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar1, LOW);
    digitalWrite(pinoLuzEscadaBaixo, LOW);
    f3a1 = false;
  }


  //Andar2
  //fase 1
  if (f1a2) {
    for (int i = 0; i < 32; i++) {
      analogWrite(pinoLuzAndar2, i);
      delay(300);
    }
    for (int i = 33; i < 255; i++) {
      analogWrite(pinoLuzAndar2, i);
      analogWrite(pinoLuzEscadaBaixo, i);
      analogWrite(pinoLuzEscadaCima, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar2, HIGH);
    digitalWrite(pinoLuzEscadaBaixo, HIGH);
    digitalWrite(pinoLuzEscadaCima, HIGH);
    lastLuzAndar2Time = millis();
    f1a2 = false;
    f2a2 = true;
  }
  //fase 2
  if (f2a2) {
    if (millis() - lastLuzAndar2Time > luzAndarDelay) {
      f2a2 = false;
      f3a2 = true;
    }
  }
  //fase 3
  if (f3a2) {
    for (int i = 255; i > 0; i--) {
      analogWrite(pinoLuzAndar2, i);
      analogWrite(pinoLuzEscadaBaixo, i);
      analogWrite(pinoLuzEscadaCima, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar2, LOW);
    digitalWrite(pinoLuzEscadaBaixo, LOW);
    digitalWrite(pinoLuzEscadaCima, LOW);
    f3a2 = false;
  }


  //Andar3
  //fase 1
  if (f1a3) {
    for (int i = 0; i < 32; i++) {
      analogWrite(pinoLuzAndar3, i);
      delay(300);
    }
    for (int i = 33; i < 255; i++) {
      analogWrite(pinoLuzAndar3, i);
      analogWrite(pinoLuzEscadaCima, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar3, HIGH);
    digitalWrite(pinoLuzEscadaCima, HIGH);
    lastLuzAndar3Time = millis();
    f1a3 = false;
    f2a3 = true;
  }
  //fase 2
  if (f2a3) {
    if (millis() - lastLuzAndar3Time > luzAndarDelay) {
      f2a3 = false;
      f3a3 = true;
    }
  }
  //fase 3
  if (f3a3) {
    for (int i = 255; i > 0; i--) {
      analogWrite(pinoLuzAndar3, i);
      analogWrite(pinoLuzEscadaCima, i);
      delay(10);
    }
    digitalWrite(pinoLuzAndar3, LOW);
    digitalWrite(pinoLuzEscadaBaixo, LOW);
    digitalWrite(pinoLuzEscadaCima, LOW);
    f3a3 = false;
  }
}
