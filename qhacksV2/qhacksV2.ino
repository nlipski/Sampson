/*
  Hello World.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include <Servo.h>

Servo drug1;

rgb_lcd lcd;

const int colorR = 125;
const int colorG = 125;
const int colorB = 125;
const int drug1Sens = 0;
const int drug1Servo = 9;
const int drop1Thresh = 70;
const int SERVOTIME = 10;
int open = 105; // open angle
int close = 30; // close angle

void setup() {
  Serial.begin(115200);
  drug1.attach(drug1Servo);
  drug1.write(close);
  lcd.begin(16, 2);
  lcd.setColor(0);
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(4,1);
  lcd.print("Sampson!");
  delay(1000);
}

void loop() {
  int test = dispense1(5);
  displayDispense(test);
  toClose();
  //displayInstruct("Please take with water");
  lcd.clear();
  lcd.setColor(0);
  delay(5000);
  
}

int dispense1(int amount){ // returns -1 if dispensed correctly
  for(int i = 1; i <= amount; i++){
    toClose();
    lcd.clear();
    lcd.setColor(3);  
    lcd.setCursor(2,0);
    lcd.print("Dispensing ");
    lcd.print(i);
    lcd.setCursor(4,1);
    lcd.print("........");
    int drop1 = analogRead(drug1Sens);
    int drop1Start = drop1;
    int trigger = 0;
    int count = 0;
    int ang = close;
    int retry = 0;
    while( trigger == 0 && retry < 2){
      drop1 = analogRead(drug1Sens);
      if (drop1Start - drop1 > drop1Thresh){
        trigger = 1;
        lcd.setColor(2);
      }
      if ((count % 250 == 0) && ang < open){
        ang++;
      }
      if(ang >= open){
        toClose();
        retry++;
        ang = drug1.read();
      }
      drug1.write(ang);
      count++;
      //Serial.println(count);

    }
    if (trigger == 0){
      return(amount + 1 - i);
    }
    toClose();
  }
  return(-1);
}

void displayDispense( int val){
  lcd.clear();
  if (val == -1){
    lcd.setColor(2);
    lcd.setCursor(4,0);
    lcd.print("Success!");
    delay(4000);
  }  else{
    lcd.setColor(1);
    for (int i=0; i<5; i++){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Error: ");
      delay(500);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Error: ");
      lcd.setCursor(1,1);
      lcd.print(val);
      lcd.setCursor(3,1);
      lcd.print("pills");
      lcd.setCursor(9,1);
      lcd.print("missed");
      delay(1000);
    }
  }
}

void toOpen(){
  int currentAng = drug1.read();
  if( currentAng != open){
    for (int i = currentAng; i < open; i++){
      drug1.write(i);
      delay(SERVOTIME);
    }
    delay(1000);
  }
}

void toClose(){
  int currentAng = drug1.read();
  if( currentAng != close){
    for (int i = currentAng; i > close; i--){
      drug1.write(i);
      delay(SERVOTIME);
    }
    delay(1000);
  }
}
/*
void displayInstruct(String text){
  lcd.clear();
  delay(500);
  lcd.setCursor(16,0);
  lcd.setColor(0);
  lcd.print(text + "     ");
  for (int scrollCounter = 0; scrollCounter < text.length(); scrollCounter++) 
  { 
    lcd.scrollDisplayLeft(); 
    delay(250);
  }
  lcd.clear();
}



void displayTime(){
  int curHour = hour();
  Serial.print(curHour);
  Serial.print("  ");
  int curDay = day();
  Serial.println(curDay);
}

*/
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
