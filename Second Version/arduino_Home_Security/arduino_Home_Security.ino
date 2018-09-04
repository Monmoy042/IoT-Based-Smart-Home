#include<Servo.h>
#define REC 2 // pin 2 is used for recording
#define PLAY_E 3 // pin 3 is used for playback-edge trigge
#define PLAY_L 4 // pin 4 is used for playback  
#define FT 5 // pin 5 is used for feed through
#define playTime 5000 // playback time 5 seconds
#define recordTime 3000 // recording time 3 seconds
#define playLTime 900 // press and release playback time 0.9 seconds

const int analogPin = A0;    // Flame Sensor (A0) to Arduino analog input pin A0
//const int BuzzerPin = 13;
const int motorPin1  = 9;  // Pin 14 of L293
const int motorPin2  = 10; // Buzzer output pin
const int threshold = 720;// Flame level threshold (You can vary the value depends on your need)

Servo servo1;
int pos1=0;

void setup() 
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT); 
  pinMode(REC,OUTPUT);// set the REC pin as output
  pinMode(PLAY_L,OUTPUT);// set the PLAY_L pin as output
  pinMode(PLAY_E,OUTPUT);// set the PLAY_e pin as output
  pinMode(FT,OUTPUT);// set the FT pin as output  
  servo1.attach(8);
  Serial.begin(9600);// set up Serial monitor   
}

void loop() {
  recorder();
  
  exhaustFan();
 
  largeServo();
}
//Recorder
void recorder(){
  while (Serial.available() > 0) {
          char inChar = (char)Serial.read();
            if(inChar =='p' || inChar =='P'){
            digitalWrite(PLAY_E, HIGH);
            digitalWrite(PLAY_E, LOW);  
              //Serial.println("Playbak Started");  
            delay(playTime);
            
              //Serial.println("Playbak Ended");
            break; 
            }// if          
            else if(inChar =='r' || inChar =='R'){
              digitalWrite(REC, HIGH);
              //Serial.println("Recording started");
              delay(recordTime);
              digitalWrite(REC, LOW);
              //Serial.println("Recording Stopped ");              
            } 
            else if(inChar =='l' || inChar =='L'){
            digitalWrite(PLAY_L, HIGH); 
              //Serial.println("Playbak L Started");  
            delay(playLTime);
            digitalWrite(PLAY_L, LOW);
              //Serial.println("Playbak L Ended");            
            }             
            
      //Serial.println("**** Serial Monitor Exited");      
    }// wihile
    //Serial.println("**** Enter r to record, p to play");
  }
//Exhaust Fan
void exhaustFan(){
  int analogValue = analogRead(analogPin);
 Serial.println(analogValue);
  
  if (analogValue>threshold) {
    //digitalWrite(BuzzerPin, HIGH);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(500);
    Serial.println(analogValue);
  } 
  else if (analogValue = threshold){
    
    //digitalWrite(BuzzerPin, LOW);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    //Serial.println(analogValue);
    delay(400);
    //digitalWrite(BuzzerPin, LOW);
  }
  else {
    //digitalWrite(BuzzerPin, LOW);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW); 
  }
  }

//Large Servo

void largeServo(){
  for(pos1==0;pos1<180;pos1+=1)
  {
    servo1.write(pos1);
    delay(50);
    }
    
    for(pos1==180;pos1>=1;pos1-=1)
  {
    servo1.write(pos1);
    delay(50);
    }
  }
