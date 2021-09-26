#include <EEPROM.h>
#define r A0 //rgb red
#define g A1 //rgb green
#define b A2 //rgb blue 
#define b1 2 //button-1
#define b2 3 //button-2
#define b3 4 //button-3
#define l1 5 //led1
#define v1 6 //voice-1
#define v2 7 //voice-2
#define v3 8 //voice-3
#define v4 9 //voice-4
#define v5 10 //voice-5
#define v6 11 //voice-6
#define v7 12 //voice-7
int vsel,val;
const unsigned long interval=300,bdel=1000;   
unsigned long previoustime=0,count=0,pt1=0,pt2=0;
void setup() {
pinMode(b1,INPUT);
pinMode(b2,INPUT);
pinMode(r,OUTPUT);
pinMode(g,OUTPUT);
pinMode(b,OUTPUT);
pinMode(l1,OUTPUT);
pinMode(v1,OUTPUT);
pinMode(v2,OUTPUT);
pinMode(v3,OUTPUT);
pinMode(v4,OUTPUT);
pinMode(v5,OUTPUT);
pinMode(v6,OUTPUT);
pinMode(v7,OUTPUT);
val=EEPROM.read(0);
 digitalWrite(v1,HIGH);
  digitalWrite(v2,HIGH);
  digitalWrite(v3,HIGH);
  digitalWrite(v4,HIGH);
  digitalWrite(v5,HIGH);
  digitalWrite(v6,HIGH);
  digitalWrite(v7,HIGH);
}
void inc(){
  unsigned long currenttime=millis(); 
  if(digitalRead(b1)==HIGH and currenttime - previoustime >= interval){
   previoustime=currenttime;
   val++; if(val >7){val=1;}
  }}
  void rgb_vsel(){
    if(val==1){
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(b,LOW);
      EEPROM.write(0,1);
      vsel=v1;
      }
       else  if(val==2){
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(b,LOW);
      EEPROM.write(0,2);
      vsel=v2;
      }
       else  if(val==3){
      digitalWrite(r,LOW);
      digitalWrite(g,LOW);
      digitalWrite(b,HIGH);
      EEPROM.write(0,3);
      vsel=v3;
      }
       else  if(val==4){
      digitalWrite(r,HIGH);
      digitalWrite(g,HIGH);
      digitalWrite(b,LOW);
      EEPROM.write(0,4);
      vsel=v4;
      }
      else  if(val==5){
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(b,HIGH);
      EEPROM.write(0,5);
      vsel=v5;
      }
     else  if(val==6){
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(b,HIGH);
      EEPROM.write(0,6);
      vsel=v6;
      }
     else  if(val==7){
      digitalWrite(r,HIGH);
      digitalWrite(g,HIGH);pt1=currenttime;
      digitalWrite(b,HIGH);
      EEPROM.write(0,7);
      vsel=v7;
      }
    }
void play(){
  unsigned long currenttime=millis(); 
  inc();
  rgb_vsel();
  if(digitalRead(b2)==HIGH){
    digitalWrite(vsel,LOW);
    digitalWrite(l1,HIGH);
    }
 else{
  if(currenttime-pt1 >= bdel){
 digitalWrite(l1,LOW); 
 digitalWrite(vsel,HIGH);
 pt1=currenttime;  
      }
  }
}
void rec(){
  unsigned long currenttime=millis(); 
   val=EEPROM.read(1);
    rgb_vsel();
  if(digitalRead(b2)==HIGH){
    digitalWrite(vsel,LOW);
    digitalWrite(l1,HIGH);
    count++;
    }
    else{
      if(currenttime - pt2 >= bdel){
      if(count>0){
        count=0;
          val++;
           if(val>7){
          val=1;
           }
           EEPROM.write(1,val);
        }
 digitalWrite(l1,LOW); 
 digitalWrite(vsel,HIGH); 
 pt2=currenttime;   
      }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(b3)==HIGH){
   play();
  }
  else{
    rec();
    }
}
