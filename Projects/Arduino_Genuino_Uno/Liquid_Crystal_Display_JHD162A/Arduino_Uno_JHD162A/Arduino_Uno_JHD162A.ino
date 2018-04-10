/* 
  Name:     LiquidCrystalDisplay-JHD162A
  Author:   Sampreet Kalita
  Created:  2017/08/18 
*/

// include the lcd library
#include<LiquidCrystal.h>

// initialize the library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// define a custom character
// in this case, it a smiling emoji
unsigned char customChar[8] =
{
	0x00,   //0b00000
	0x0A,   //0b01010
	0x0A,   //0b01010
	0x00,   //0b00000
	0x11,   //0b10001
	0x0E,   //0b01110
	0x00,   //0b00000
	0x00    //0b00000
};

// code for initial setup
void setup() 
{
  // create the custom character
  lcd.createChar(0, customChar);

  // set up the number of columns and rows
  lcd.begin(16, 2);

  // display the title
  lcd.print("LCD - JHD 162A");
  // move cursor to second row
  lcd.setCursor(0, 1);

  // display the custom character
  lcd.print("Welcome ");
  lcd.write((uint8_t)0);

  // wait for 1s before entering the loop
  delay(1000);
}

// code to run repeatedly
void loop() 
{

}
