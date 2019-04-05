// EGT/CHT Monitor for my aircraft engine
// Hardware: Arduino Nano, AVR ISP
// 2017-07-27 Last revision (Rewrote startup message)

#include <max6675.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//DEFINE CHIP SELECT PINS ON THERMOCOUPLES
#define cs1 10
#define cs2 9
#define cs3 8
#define cs4 7
#define cs5 6
#define cs6 5
#define cs7 4

int thermoDO = 11;
int thermoCLK = 12;
int caution = 0;
int threshold = 400;

MAX6675 thermocouple1(thermoCLK, cs1, thermoDO);
MAX6675 thermocouple2(thermoCLK, cs2, thermoDO);
MAX6675 thermocouple3(thermoCLK, cs3, thermoDO);
MAX6675 thermocouple4(thermoCLK, cs4, thermoDO);
MAX6675 thermocouple5(thermoCLK, cs5, thermoDO);
MAX6675 thermocouple6(thermoCLK, cs6, thermoDO);
MAX6675 thermocouple7(thermoCLK, cs7, thermoDO);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

float t;

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  //pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  //pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  
  // THERMOCOUPLE SELECTS
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  // CAUTION INDICATOR
  pinMode(3, OUTPUT);
  
  // THERMOCOUPLE SELECTS, ACTIVE LOW
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  
  // CAUTION INDICATOR
  digitalWrite(3, HIGH);

// initialize the LCD
  lcd.begin();

 lcd.backlight();
 
 lcd.setCursor(0,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peter's EGT/CHT");
  lcd.setCursor(0,1);
  lcd.print("Computer July'17");
  delay(3000);
  // wait for MAX chip to stabilize
  delay(500);
  digitalWrite(3, LOW);
  }

void loop() { 

  lcd.clear();
  
  lcd.setCursor(0,0);
  
  t = thermocouple1.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  if ( t > threshold ) caution = 1;
  lcd.print(t,0);
  
  lcd.setCursor(4,0);
  t = thermocouple2.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  if ( t > threshold ) caution = 2;
  lcd.print(t,0);
  
  lcd.setCursor(8,0);
  t = thermocouple3.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  if ( t > threshold ) caution = 3;
  lcd.print(t,0);
  
  lcd.setCursor(12,0);
  t = thermocouple4.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  if ( t > threshold ) caution = 4;
  lcd.print(t,0);
  
  lcd.setCursor(0,1);
  t = thermocouple5.readFahrenheit();
    if ( t < 100 )
    lcd.print(" ");
   lcd.print(t,0);
  
  lcd.setCursor(4,1);
  t = thermocouple6.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  lcd.print(t,0);
  
  lcd.setCursor(8,1);
  t = thermocouple7.readFahrenheit();
  if ( t < 100 )
    lcd.print(" ");
  lcd.print(t,0);
  
  delay(1000);

  if (caution > 0) digitalWrite(3, HIGH);
}
