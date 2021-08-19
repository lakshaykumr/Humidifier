
#define analogPin A0
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27,16,2);  

void setup()
{
    Serial.begin(9600);
    pinMode(analogPin,0);
    lcd.begin();                    
  lcd.backlight();
  lcd.setBacklight(HIGH);
}

void loop()
{
    float r = 10000;
float logrt, rt, T, F;
float a = 0.9059557119e-03, b = 2.484884034e-04, c = 2.040119886e-07;
float adcVal, i, numSamples = 50;

   adcVal = 0;
  for (i = 0; i < numSamples; i++)
  {
    adcVal = adcVal + analogRead(analogPin);
  }
  adcVal = adcVal / 50;
  rt = r * (1023.0 / (float)adcVal - 1.0);
  logrt = log(rt);
  T = (1.0 / (a + b*logrt + c*logrt*logrt*logrt));
  T = T - 273.15;
  F = (T * 9.0)/ 5.0 + 32.0; 
                           
  Serial.println("Temperature in Celcius=" + String(T));
    lcd.setCursor(0,0);
    lcd.print("Temp: "); 
    lcd.print(T);
    lcd.print(" C");
     lcd.setCursor(0,1);
    lcd.print("Temp: "); 
    lcd.print(F);
    lcd.print(" F");
    delay(1000); 
}
