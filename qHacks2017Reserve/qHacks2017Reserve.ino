/* Sampson - The Pill dispenser of the future

Jonathon Malcolm
Nikita Lipski
Connor Sparling
Jordan O'Neill

*/

#include <Wire.h>
#include "rgb_lcd.h"
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define STEP 600

rgb_lcd lcd;

const int drug1Sens = 0;
const int drop1Thresh = 70;
const int opene = 105; // open angle
const int closee = 30; // close angle



int Steps = 0;
boolean Direction = true;// gre
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=STEP;
long time;
byte pillIden = 0;
byte pillNum = 0;
byte GlobalEmpty = 0;

byte bit0 = 1, bit1 = 0, bit2 = 0, bit3 = 0, bit4 = 0, bit5 = 0, bit6 = 0, bit7 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.setColor(0);
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(4,1);
  lcd.print("Sampson!");
  delay(3000);
}

void loop() {
  lcd.setColor(3);
  lcd.setCursor(3,0);
  lcd.clear();
  lcd.print("WAITING");
  delay(3000);
  lcd.setRGB(0,0,0);
  while(!digitalRead(6)){
      delay(1);
  }
  lcd.setColor(0);
  lcd.setCursor(1,0);
  lcd.clear();
  lcd.print("INCOMING DATA");
  delay(1500);


  
 
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Time to take");
    lcd.setCursor(2,1);
    lcd.print("your pills.");
    delay(5000);
    int testing = dispense1(1);
    displayDispense(testing, 1);
    if (testing >= 0)
      GlobalEmpty = 1;
  
}

int dispense1(int amount){ // returns -1 if dispensed correctly
  int success = 0;
  int i = 1;
  for(i = 1; i <= amount; i++){
    int retry = 0;
    success = 0;
    lcd.clear();
    lcd.setColor(3);  
    lcd.setCursor(2,0);
    lcd.print("Dispensing ");
    lcd.print(i);
    lcd.setCursor(4,1);
    lcd.print("........");
    while(retry <= 2 && success == 0){
      success = tryy();
      delay(1000);
      retry++;
    }
    if(!success){
      return(amount + 1 - i);
    }
  }
  if(success)
    return(-1);
  else
    return(0);
}

int tryy(){
  Direction = false;
  int drop1 = analogRead(drug1Sens); 
  int drop1Start = drop1;
  int trigger = 0;
  while( steps_left < STEP){
    drop1 = analogRead(drug1Sens);
    delayMicroseconds(1000);
    stepper(1);
    steps_left++;
    if (drop1Start - drop1 > drop1Thresh){
      trigger = 1;
      lcd.setColor(2);
    }
  }
  Direction = true;
  while(steps_left > 0){
    drop1 = analogRead(drug1Sens);
    delayMicroseconds(1000);
    stepper(1);
    steps_left--;
    if (drop1Start - drop1 > drop1Thresh){
      trigger = 1;
      lcd.setColor(2);
    }
  }
  return(trigger);
}


void displayDispense(int val, int pill){
  lcd.clear();
  if (val == -1){
    lcd.setColor(2);
    lcd.setCursor(3,0);
    lcd.print("Dispensed");
    lcd.setCursor(3,1);
    lcd.print("pill ID ");
    lcd.print(pill);
    lcd.print("!");
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


void stepper(int xw){
  for (int x=0;x<xw;x++){
    switch(Steps){
     case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     break; 
     case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
     break; 
     case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     break; 
     case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     break; 
     case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
     break; 
     case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
     break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
     break; 
     case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     break; 
     default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
     break; 
   }
   SetDirection();
 }
} 
void SetDirection(){
  if(Direction==1){ Steps++;}
  if(Direction==0){ Steps--; }
  if(Steps>7){Steps=0;}
  if(Steps<0){Steps=7; }
}


