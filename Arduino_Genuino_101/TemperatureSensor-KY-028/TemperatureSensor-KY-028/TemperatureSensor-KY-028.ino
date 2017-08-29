/*
  Name:     TemperatureSensor-KY-028
  Author:   Sampreet Kalita
  Created:  2017/08/18 
*/

// include the lcd library
#include<math.h>
#include<LiquidCrystal.h>

// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temperature for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    

// initialize the library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initialize the pin numbers used for the sensor
const int analogIn = A0;  // X-axis signal
const int digitalIn = 7; // button signal

// declare the variables
double analogTemp;
int digitalTemp;
int i;

// code for initial setup
void setup()
{
  // set the serail communication baud
  Serial.begin(9600);
  // set up the number of columns and rows
  lcd.begin(16, 2);

  // display the welcome message with the custom character
  lcd.print("Temperature ");
  lcd.setCursor(0, 1);
  lcd.print("Sensor");
  
  // declare the signal pin from sensor as input 
  pinMode(analogIn, INPUT);
  pinMode(digitalIn, INPUT); 

  Serial.println("Initialized.");
  delay (1000);
}

// code to run repeatedly
void loop()
{
  // get the pooled value of readings
  double average = 0;
  for (i=0; i<5; i++)
  {
    average += analogRead(analogIn);
    delay(10);
  }
  average /= 5;
  Serial.print("Average analog reading "); 
  Serial.println(average);
  
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");
  
  analogTemp = steinhart;
  digitalTemp = digitalRead(digitalIn);
  
  PrintTemperature();
  delay(1000);  
}

// function to print the heart beat message
void PrintTemperature()
{
  lcd.clear();
  lcd.print("Analog: ");
  lcd.print(analogTemp);
  lcd.setCursor(0, 1);
  lcd.print("Digital: ");
  lcd.print(digitalTemp);
}
