#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

#define PIN_ENA A0
#define PIN_IN1 16
#define PIN_IN2 17
#define PIN_IN3 18
#define PIN_IN4 19
#define PIN_ENB A5

uint32_t corbranca = carrier.leds.Color(255,255,255);
// bool meta_alcançada = false


void setup() {
  Serial.begin(9600);
  delay(2000);
  carrier.noCase();
  carrier.begin();
  carrier.leds.fill(corbranca, 0 ,5);
  carrier.leds.setBrightness(255);
  carrier.leds.show();
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
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

void direita(){
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, 180);
  analogWrite(PIN_ENB, 0);
}

void esquerda(){
  analogWrite(PIN_ENA, 0);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENB, 150);
}

void parar(){
  analogWrite(PIN_ENA, 0);
  analogWrite(PIN_ENB, 0);
}

int r, g, b;

void loop(){

    if (carrier.Light.colorAvailable()){
     carrier.Light.readColor(r, g, b); //read rgb color values
      Serial.println(String("r:")+r+String("g:")+g+String("b:")+b);

      if (r > 150 && r < 170 && g > 30 && g < 60 & b > 50 && b < 80) {
        Serial.println("to in red");
        parar();
        carrier.Buzzer.beep();
      }
      else
        if (r >= 135 && g >= 135 && b >= 135){
          Serial.println("estou no branco");
          esquerda();
       }
       else {
          direita();
          Serial.println("estou no preto");
       }
    }
  }
