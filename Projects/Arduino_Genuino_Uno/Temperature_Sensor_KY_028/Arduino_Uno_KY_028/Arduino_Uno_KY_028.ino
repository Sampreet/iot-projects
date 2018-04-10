/*
  Name:     TemperatureSensor-KY-028
  Author:   Sampreet Kalita
  Created:  2017/08/29 
*/

// include the lcd library
#include<math.h>

// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temperature for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000

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
  steinhart = average / THERMISTORNOMINAL;          // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert to C
  
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");
  
  analogTemp = steinhart;
  digitalTemp = digitalRead(digitalIn);
  delay(1000);  
}
