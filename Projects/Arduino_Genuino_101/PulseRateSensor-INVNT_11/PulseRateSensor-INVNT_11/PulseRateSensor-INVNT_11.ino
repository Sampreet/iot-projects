/*
  Name:     PulseRateSensor-INVNT_11
  Author:   Sampreet Kalita
  Created:  2017/08/18 
*/

// include the lcd library
#include<LiquidCrystal.h>

// initialize the library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// define the pin number for sensor
const int beatIn = 8;

// declare the count variables
int i, k, rate;

// array to store the times of the last five beats
unsigned long time[6];

// define a custom character
// in this case, it is the symbol for heartbeat
byte heart[8] =
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

// code for initial setup
void setup()
{
  // create the custom character
  lcd.createChar(0, heart);

  // set up the number of columns and rows
  lcd.begin(16, 2);

  k = -1;

  // display the welcome message with the custom character
  lcd.print("Heart Beat ");
  lcd.write((uint8_t)0);
  lcd.setCursor(0, 1);
  lcd.print("Sensor");
  
  // declare the signal pin from sensor as input 
  pinMode(beatIn, INPUT);
}

// code to run repeatedly
void loop()
{
  // if the rate is uninitailized
  if (k == -1 && digitalRead(beatIn))
  {
    // loop for a specific count
    while (k < 100)
    {
      // initialize rate
      while (k < 5)
      {
        if (digitalRead(beatIn))
        {
          k++;
          InitializeRate();
          while (digitalRead(beatIn)) 
          {
            // wait for the input signal
          }
        }
      }
      // update rate
      if (digitalRead(beatIn))
      {
        k++;
        UpdateRate();
        while (digitalRead(beatIn)) 
        {
          // wait for the input signal
        }
      }
    }
    // reset after count
    if (k == 100)
    {
      lcd.clear();
      lcd.print("Resetting...");
      delay(1000);
    }
    k = -1;
  }
}

// function to initialize rate
void InitializeRate()
{
  // add the current time to time array
  time[k] = millis();
  // if minimum count for initialization is fulfilled
  if (k == 5)
  {
    // calculate rate and print it
    rate = 60000 * 5 / (time[5] - time[0]);
    PrintRate();
  }
  else
  {
    // print initializing message
    lcd.clear();
    lcd.print("Initializing...");
    lcd.setCursor(0, 1);
    lcd.print("Ready in ");
    lcd.print(5 - k);
    lcd.print(" ");
    lcd.write((uint8_t)0);
  }
}

// function to print the heart beat message
void PrintRate()
{
  lcd.clear();
  lcd.print("Heart Beat ");
  lcd.write((uint8_t)0);
  lcd.setCursor(0, 1);
  lcd.print("Rate: ");
  lcd.print(rate);
  lcd.print(" bpm");
}

// function to update rate
void UpdateRate()
{
  // update the array elements
  for (i = 0; i < 5; i++)
  {
    time[i] = time[i + 1];
  }
  time[5] = millis();

  // calculate rate and print it
  rate = 60000 * 5 / (time[5] - time[0]);
  PrintRate();
}
