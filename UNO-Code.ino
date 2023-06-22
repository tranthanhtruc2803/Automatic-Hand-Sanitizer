/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

/* 

If you do not have an LCD library, follow the instructions here : xxxxxxxxxxxxxxxxxxxxx

*/

#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int RELAY_PIN = 9;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*
   TRIG : 11
   Echo : 12
*/
UltraSonicDistanceSensor distanceSensor(11, 12);  // Initialize sensor that uses digital pins 11 and 12.

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(13, OUTPUT);  //Buzzer
  pinMode(RELAY_PIN, OUTPUT);
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
}


void loop()
{
  //  Do a measurement using the sensor and print the distance in centimeters.
  
  float distance = distanceSensor.measureDistanceCm();
  float temp=0;
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println(distance);
  if (distance > 0 & distance < 8)
  {
    
    {
      lcd.clear();
      for(int i=0;i<3;i++)
      {
        lcd.setCursor(5, 1);
        temp = temp + ((mlx.readObjectTempC()+2.25)); 
        lcd.print("HOLD ON");
        
        delay(300);
      }
      
      temp=temp/3;
      
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print(temp); 
      lcd.print(" C");
      if(temp<38)
      {
      tone(13, 2803); 
      delay(200);
      tone(13, 300); 
      delay(100);
      noTone(13);
      delay(500);
      }
      else
      {
        for(int j=0;j<3;j++)
        {
          tone(13, 100); 
          delay(300);
          tone(13, 3000); 
          delay(300);
        }
      noTone(13);
      }
      digitalWrite(RELAY_PIN, LOW);
      delay(1000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(1000);
    }
  } 
  else {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("GET CLOSER");
    delay(300);
  }
}
