#include <LiquidCrystal_I2C.h>

#define MQ2_ANA 15
#define LDR 4
#define buzzer 25
#define rele 0

float MQ2_leitura, LDR_leitura;
int GAS, FOGO;
int LIM_GAS = 60;
int LIM_FOGO = 80;

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {

  Serial.begin(115200);

  pinMode(buzzer, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(MQ2_ANA, INPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(rele, LOW);

  LCD.init();
  LCD.backlight();
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Iniciando");
  LCD.setCursor(0, 1);
  LCD.print("Sistemas");

  for (int i = 0; i < 3; i++) {
    delay(500);
    LCD.print(".");
    delay(500);
  }
  LCD.clear();

}

void loop() {
  //Leitura dos dados
  MQ2_leitura = analogRead(MQ2_ANA);
  LDR_leitura = analogRead(LDR);
 // Conversão dos dados
  GAS = map(MQ2_leitura, 0, 4095, 0, 100);
  FOGO = map(LDR_leitura, 0, 4095, 100, 0);

  // Impressão dos dados no sistema
  Serial.print("Smoke/Gás: ");
  Serial.print(GAS, 0);
  Serial.println("%");

  Serial.print("Chama: ");
  Serial.print(FOGO, 0);
  Serial.println("%");
  Serial.println("---");

  //Condição de incendio
  if(GAS >= LIM_GAS){
    LCD.clear();
    digitalWrite(rele, HIGH);
    tone(buzzer, 663, 500);
    tone(buzzer, 701, 500);
    LCD.setCursor(0, 0);
    LCD.print("GAS/FUMACA     ");
    LCD.setCursor(0,1);
    LCD.print("DETECTADO!");
    delay(1000);
  }if(FOGO >= LIM_FOGO){
    LCD.clear();
    digitalWrite(rele, HIGH);
    tone(buzzer, 557, 500);
    tone(buzzer, 625, 500);
    LCD.setCursor(0, 0);
    LCD.print("TA PEGANDO FOGO");
    LCD.setCursor(0, 1);
    LCD.print("BIXO!");
    delay(1000);
  }if(FOGO < LIM_FOGO && GAS < LIM_GAS){
    //Impressão dos dados do LCD
    LCD.setCursor(0, 0);
    LCD.print("GAS:  ");
    LCD.setCursor(0, 1);
    LCD.print("Fogo: ");

    LCD.setCursor(6, 0);
    LCD.print(GAS, 0);
    LCD.print("%         ");
    LCD.setCursor(6, 1);
    LCD.print(FOGO, 0);
    LCD.print("%         ");
    digitalWrite(rele, LOW);
    delay(500);
  }
}
