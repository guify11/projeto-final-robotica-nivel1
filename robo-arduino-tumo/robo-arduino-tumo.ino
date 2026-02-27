#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

#define PIN_ENA A0
#define PIN_IN1 16
#define PIN_IN2 17
#define PIN_IN3 18
#define PIN_IN4 19
#define PIN_ENB A5

// Frequências das Notas
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_C6  1047

void setup() {
  Serial.begin(9600);
  delay(2000);
  carrier.noCase();
  if (!carrier.begin()) {
    while (1);
  }
  
  uint32_t corbranca = carrier.leds.Color(255, 255, 255);
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

// Função para tocar a música completa
void tocarMarioCompleto() {
  int melodia[] = {
    NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5, 0, NOTE_G4, 0, 
    NOTE_C5, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
    NOTE_C5, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3
  };

  int duracoes[] = {
    125, 125, 125, 125, 125, 125, 125, 125, 125, 250, 125, 250,
    250, 250, 250, 250, 250, 250, 125,
    125, 125, 125, 125, 125, 125, 125, 125, 125,
    250, 250, 250, 250, 250, 250, 125,
    125, 125, 125, 125, 125, 125, 125, 125, 125
  };

  for (int i = 0; i < sizeof(melodia)/sizeof(int); i++) {
    if (melodia[i] == 0) {
      delay(duracoes[i]);
    } else {
      carrier.Buzzer.beep(melodia[i], duracoes[i]);
      delay(duracoes[i] * 1.2); 
    }
  }
}

// Funções de movimento
void parar() { analogWrite(PIN_ENA, 0); analogWrite(PIN_ENB, 0); }
void direita() { digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, HIGH); analogWrite(PIN_ENA, 180); analogWrite(PIN_ENB, 0); }
void esquerda() { analogWrite(PIN_ENA, 0); digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, HIGH); analogWrite(PIN_ENB, 150); }

int r, g, b;

void loop() {
  if (carrier.Light.colorAvailable()) {
    carrier.Light.readColor(r, g, b);

    if (r >= 135 && g >= 135 && b >= 135) {
      esquerda();
    } 
    else if (r > 150 && r < 170 && g > 30 && g < 60 && b > 50 && b < 80) {
      Serial.println("Mario Time!");
      parar();               // Para o robô para não bater enquanto toca
      tocarMarioCompleto();  // Toca a música toda
      delay(1000);           // Espera um pouco antes de continuar
    } 
    else {
      direita();
    }
  }
}
