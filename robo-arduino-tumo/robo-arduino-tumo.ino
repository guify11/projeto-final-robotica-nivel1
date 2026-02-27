#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

#define PIN_ENA A0
#define PIN_IN1 16
#define PIN_IN2 17
#define PIN_IN3 18
#define PIN_IN4 19
#define PIN_ENB A5

uint32_t corbranca; // Definida no setup após o carrier.begin()

// Notas Musicais para o Mario
#define NOTE_E7  2637
#define NOTE_C7  2093
#define NOTE_G7  3136
#define NOTE_G6  1568

void setup() {
  Serial.begin(9600);
  delay(2000);
  carrier.noCase();
  if (!carrier.begin()) {
    Serial.println("Erro ao iniciar o Carrier!");
    while (1);
  }
  
  corbranca = carrier.leds.Color(255, 255, 255);
  carrier.leds.fill(corbranca, 0, 5);
  carrier.leds.setBrightness(255);
  carrier.leds.show();

  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
}

// Função para tocar o tema curto do Mario
void tocarMario() {
  // Nota, Duração (ms)
  int melodia[] = {NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, NOTE_G6};
  int duracoes[] = {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150};

  for (int i = 0; i < 11; i++) {
    if (melodia[i] == 0) {
      delay(duracoes[i]);
    } else {
      carrier.Buzzer.beep(melodia[i], duracoes[i]);
      delay(duracoes[i] * 1.3); // Pequena pausa entre notas
    }
  }
}

void andaTras() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, 255);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENB, 255);
}

void andaFrente() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, 255);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENB, 255);
}

void direita() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, 180);
  analogWrite(PIN_ENB, 0);
}

void esquerda() {
  analogWrite(PIN_ENA, 0);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENB, 150);
}

void parar() {
  analogWrite(PIN_ENA, 0);
  analogWrite(PIN_ENB, 0);
}

int r, g, b;

void loop() {
  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(r, g, b);
    Serial.println(String("r:") + r + String(" g:") + g + String(" b:") + b);

    if (r >= 135 && g >= 135 && b >= 135) {
      Serial.println("estou no branco");
      esquerda();
    } 
    else if (r > 150 && r < 170 && g > 30 && g < 60 && b > 50 && b < 80) {
      Serial.println("TO NO VERMELHO - Toca Mario!");
      parar();        // Para o robô para tocar a música
      tocarMario();   // Chamei a função aqui!
    } 
    else {
      direita();
      Serial.println("estou no preto");
    }
  }
}
