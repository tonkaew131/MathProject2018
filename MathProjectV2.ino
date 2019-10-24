#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   5 //SDA_D1(5)
#define OLED_CLK   16 //SCL_D0(16)
#define OLED_DC    0 //D/C_D3(0)
#define OLED_CS    2 //N/A_D4(2)
#define OLED_RESET 4 //RST_D2(4)
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define MAX_DISTANCE 400 //MAX
#define TRIGGER_PIN_BASE  14 //BASE_TRIG_D5(14)
#define ECHO_PIN_BASE     12 //BASE_ECHO_D6(12)
NewPing sonarbase(TRIGGER_PIN_BASE, ECHO_PIN_BASE, MAX_DISTANCE);
#define TRIGGER_PIN_SLOBE  13 //SLOBE_TRIG_D7(13)
#define ECHO_PIN_SLOBE     15 //SLOBE_ECHO_D8(15)
NewPing sonarslobe(TRIGGER_PIN_SLOBE, ECHO_PIN_SLOBE, MAX_DISTANCE);

int basepower;
int slobepower;
double heightpower;
double height;

void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  delay(500);
  display.display();
  delay(500);
  display.clearDisplay();  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1, 0);
  display.print("Mathematics");
  display.setCursor(0, 10);
  display.print("Project 2018");
  display.display();
  delay(2000);
  display.fillScreen(BLACK);
  display.display();
}

void loop() {
  delay(1000);
  display.clearDisplay();
  display.fillScreen(BLACK);
  display.display();
  basepower = pow(sonarbase.ping_cm(), 2);
  slobepower = pow(sonarslobe.ping_cm(), 2);
  heightpower = slobepower-basepower;
  height = sqrt(heightpower);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("         info");
  display.print("Base   : "); display.print(sonarbase.ping_cm()); display.println(" cm");
  display.print("Slobe  : "); display.print(sonarslobe.ping_cm()); display.println(" cm");
  display.print("Height : "); display.print(height); display.println(" cm");
  display.display();
}
