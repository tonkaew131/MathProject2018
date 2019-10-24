#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MAX_DISTANCE 400 //MAX
#define TRIGGER_PIN_BASE  2 //BASE_TRIG_D5(14)
#define ECHO_PIN_BASE     3 //BASE_ECHO_D6(12)
NewPing sonarbase(TRIGGER_PIN_BASE, ECHO_PIN_BASE, MAX_DISTANCE);
#define TRIGGER_PIN_SLOBE  4 //SLOBE_TRIG_D7(13)
#define ECHO_PIN_SLOBE     5 //SLOBE_ECHO_D8(15)
NewPing sonarslobe(TRIGGER_PIN_SLOBE, ECHO_PIN_SLOBE, MAX_DISTANCE);

int basepower;
int slobepower;
double heightpower;
double height;

void setup()   {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Mathematics");
  lcd.setCursor(0,1);
  lcd.print("Project 2018");
  delay(1000);
  lcd.clear();
}

void loop() {
  basepower = pow(sonarbase.ping_cm(), 2);
  slobepower = pow(sonarslobe.ping_cm(), 2);
  heightpower = slobepower-basepower;
  height = sqrt(heightpower);
  lcd.setCursor(0,0);
  lcd.print("B:"); lcd.print(sonarbase.ping_cm()); lcd.print("cm");
  lcd.setCursor(8,0);
  lcd.print("S:"); lcd.print(sonarslobe.ping_cm()); lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("H:"); lcd.print(height); lcd.print("cm");
  Serial.println("-----------------------");
  Serial.print("BASE   : "); Serial.print(sonarbase.ping_cm()); Serial.println("cm");
  Serial.print("SLOBE  : "); Serial.print(sonarbase.ping_cm()); Serial.println("cm");
  Serial.print("HEIGHT : "); Serial.print(height); Serial.println("cm");
  Serial.println("-----------------------");
  delay(800);
  lcd.clear();
}
