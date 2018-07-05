#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   13
#define OLED_CLK   14
#define OLED_DC    2
#define OLED_CS    12
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

const int trigPin1 = D1;
const int echoPin1 = D2;
const int trigPin2 = D3;
const int echoPin2 = D6;
long duration1;
double distance1;
long duration2;
double distance2;
int distance1pow;
int distance2pow;
double heightpow;
double height;
int Base; 
int Slant;

void setup()   {     
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);     
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(3,3);
  display.println("Hello T.Carlo");
  display.display();
  delay(3000);
  display.clearDisplay();
}

void loop() {
  
  delay(1000);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= duration2*0.034/2;

  Base= distance2+2;
  Slant= distance1+11;

  distance1pow= pow(Slant, 2);
  distance2pow= pow(Base, 2);
  heightpow= distance1pow-distance2pow;
  height= sqrt(heightpow);
  
  Serial.print(" Base Duration: ");  Serial.print(duration2);
  Serial.print(" Slant Duration: ");  Serial.print(duration1);
  Serial.print(" HeightPow: ");  Serial.println(heightpow);
  Serial.print(" Base: ");  Serial.print(Base);  Serial.print("cm ");
  Serial.print(" Slant: ");  Serial.print(Slant);  Serial.print("cm ");
  Serial.print(" Height: "); Serial.print(height);  Serial.println("cm");
  
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Base: "); display.print(Base); display.println("cm");
  display.print("Slant: "); display.print(Slant); display.println("cm");
  display.print("Height: "); display.print(height); display.println("cm");
  display.display();
  display.clearDisplay();
}
