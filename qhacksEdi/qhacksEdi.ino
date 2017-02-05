/* Sampson - The Pill dispenser of the future

Jonathon Malcolm
Nikita Lipski
Connor Sparling
Jordan O'Neill

*/

#include "Wire.h"
#include <rgb_lcd.h>
#include "Servo.h"

Servo drug1;
rgb_lcd lcd;

const int drug1Sens = 0;
const int drug1Servo = 9;
const int drop1Thresh = 70;
const int SERVOTIME = 10;
const int opene = 105; // open angle
const int closee = 30; // close angle

void setup() {
  Serial.begin(115200);
  drug1.attach(drug1Servo);
  toClose();
  lcd.begin(16, 2);
  lcd.setColor(0);
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(4,1);
  lcd.print("Sampson!");

  delay(1000);
}

void loop() {
//  displayTime();
  int test = dispense1(5);
  displayDispense(test);
  toClose();
  //displayInstruct("Please take with water");
  lcd.setColor(0);
  delay(5000);
  lcd.clear();
  
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
    int ang = closee;
    int retry = 0;
    while( trigger == 0 && retry < 2){
      drop1 = analogRead(drug1Sens);
      if (drop1Start - drop1 > drop1Thresh){
        trigger = 1;
        lcd.setColor(2);
      }
      if ((count % 250 == 0) && ang < opene){
        ang++;
      }
      if(ang >= opene){
        toClose();
        retry++;
        ang = drug1.read();
      }
      drug1.write(ang);
      count++;
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
  if( currentAng != opene){
    for (int i = currentAng; i < opene; i++){
      drug1.write(i);
      delay(SERVOTIME);
    }
    delay(1000);
  }
}

void toClose(){
  int currentAng = drug1.read();
  if( currentAng != closee){
    for (int i = currentAng; i > closee; i--){
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

*/




/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
