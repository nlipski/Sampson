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

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  lcd.begin(16, 2);
  lcd.setColor(0);
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(4,1);
  lcd.print("Sampson!");
  delay(3000);
}

void loop() {
//  displayTime();
  int test = dispense1(1);
  Serial.println("adflkjhadafg.,dskjfhlkdjghlsdkjfghlsdkfjgsdklhasdjasd");
  displayDispense(test);
  //toClose();
  //displayInstruct("Please take with water");
  lcd.setColor(0);
  delay(50000);
  lcd.clear();
  
}

int dispense1(int amount){ // returns -1 if dispensed correctly
  Direction = true; // forward
  for(int i = 1; i <= amount; i++){
    lcd.clear();
    lcd.setColor(3);  
    lcd.setCursor(2,0);
    lcd.print("Dispensing ");
    lcd.print(i);
    lcd.setCursor(4,1);
    lcd.print("........");
    int drop1 = analogRead(drug1Sens); //--------------------------------------------------------------
    int drop1Start = drop1;
    int trigger = 0;
    int retry = 0;
    steps_left = 0; // 0 is back fully, STEP is forward fully
    while( trigger == 0 && retry < 2){ // if a pin deosn't drop and it hasn't tried twice already
      Direction = true; // forward ?
      drop1 = analogRead(drug1Sens); // check if drop
      currentMillis = micros();
      if(currentMillis-last_time>=1000){
        stepper(1); //step forward
        time=time+micros()-last_time;
        last_time=micros();
        steps_left++;
      }
      if (drop1Start - drop1 > drop1Thresh){ // if dropped .....shold?
        trigger = 1;
        lcd.setColor(2);
        while(steps_left > 0){ // go  back fully 
          Direction = false; // go back
          currentMillis = micros();
          if(currentMillis-last_time>=1000){
            stepper(1); 
            time=time+micros()-last_time;
            last_time=micros();
            steps_left--;
          }
        } // NOW fully back
      }
      if(steps_left >= STEP){ // fully forward
        Direction = false; // go back
        retry++;
        Serial.print(steps_left);
        while(steps_left>0){
          currentMillis = micros();
          if(currentMillis-last_time>=1000){
            stepper(1); 
            time=time+micros()-last_time;
            last_time=micros();
            steps_left--;
          }
        } // NOW fully back
      }
    }
    if (trigger == 0){
      return(amount + 1 - i);
    }
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
  }}


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
