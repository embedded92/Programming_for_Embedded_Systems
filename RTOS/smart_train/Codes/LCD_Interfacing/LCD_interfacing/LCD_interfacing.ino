/*
 *  created on: 30-Oct-2020 
 *      Author: Ramneet Kaur
 */
/*

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 if(Serial.available())
 {
  int val= Serial.read(); // read serial data from receiver pin
  if (val==65) // if A is received. ASCII value of A is 65
  {
    lcd.setCursor(0,0); // in line one of LCD
    lcd.print("Train"); // print Train 
    lcd.setCursor(0,1); // in secong line of LCD
    lcd.print("Arriving..."); // print arriving
    delay(500); // delay of 0.5 second
  }
  if(val==68) // if D(ASCII code 68) is received by serial pin
  {
    lcd.setCursor(0,0); //  first line of LCD
    lcd.print("Train"); // display train
    lcd.setCursor(0,1); // second line
    lcd.print("Departing..."); // display departing
    delay(500);
  }
  if(val==80) // if letter P (ASCII code 80)
  {
    lcd.setCursor(0,0); //1st line
    lcd.print("Alert!!"); // print Alert message
    lcd.setCursor(0,1); // 2nd line
    lcd.print("**Emergency**"); // print emergency
    delay(500); // delay of 0.5 second
  }  
  }     
}
