//Important Libries
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

char ssid[] = "anirban-wifi"; //Your Wifi Network Name
char wifiPassword[] = "amijanina"; //Your Wifi Password

char username[] = "a60212f0-deff-11e7-b67f-67bba9556416"; //This User Name From Cayenne Website
char password[] = "6072d05a87444f2217f11bd7f002dd7a5057f621"; //This Password From Cayenne Website
char clientID[] = "c1970cf0-a9ca-11e8-9207-895fcb08b269"; //This Client ID From Cayenne Website

//Motion
int ledpin1 = 12;// Digital pin n D6
int ledpin2 =14;//digital pin D5
int pir1;
int pir2;
int sensor1 = 13;//motion senson1 on D7
int sensor2 =15; //motion sensor2 on D8;

//Vibration
int vibration = 16; //vibration sensor D0
int LedPin3 =5;  //vibration in led D1

//Smoke Sensor
const int smoke = A0;
const int Buzzerpin = 2; //bUZZ PIN D4

const int threshold = 190;//gas sensor

//Panic button

int button = 10; // panic on D3
int button_value = 0;
int ledpin4 =4;//digital pin D2

void setup() {

  //Motion
  pinMode(sensor1, INPUT);   // declare sensor as input
  pinMode(sensor2, INPUT);
  pinMode(ledpin1, OUTPUT);  // declare LED as output
  pinMode(ledpin2, OUTPUT);

  //Smoke
  pinMode(smoke, INPUT);
  pinMode(Buzzerpin, OUTPUT); //Buzzpin for fire alarm

  //Vibration
  pinMode(vibration, INPUT);
  pinMode(LedPin3, OUTPUT);

  //Panic button
  pinMode(ledpin4, OUTPUT);
  pinMode(button, INPUT);

  
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
  
  gasSensor();
  
  vibration_sensor();
}

//gas sensor
void gasSensor(){ 
  int analogValue = analogRead(smoke);

   Serial.println("\n gas = ");
  Serial.println(analogValue);
  
  if (analogValue > threshold) {
    digitalWrite(Buzzerpin, HIGH);
  }
  else if (analogValue == threshold) {

    digitalWrite(Buzzerpin, LOW);
    delay(400);
    digitalWrite(Buzzerpin, LOW);
  }
  else {
    digitalWrite(Buzzerpin, LOW);
  }

  Cayenne.virtualWrite(0, analogRead(A0));
  Serial.println(analogRead(A0));
  delay(500);
}

////Motion Sensor Detection
//void motionDetected1(){
//  pir1 = digitalRead (sensor1);
//  digitalWrite(ledpin1, pir1);
//  Serial.println("\n motion 1 = ");
//  Serial.println(pir1);
//  Cayenne.virtualWrite(1, digitalRead(13));
//  //Serial.println(digitalRead(13));
//  delay(500);
//}

//void motionDetected2(){  
//  pir2=digitalRead(sensor2);
//  digitalWrite(ledpin2, pir2);
//  Serial.println("\n motion 2 = ");
//  Serial.println(pir2);
//  Cayenne.virtualWrite(2, digitalRead(15));
//  //Serial.println(digitalRead(15));
//  delay(500);
//  }

////Panic Button
//void Panic_Button(){
//  button_value = digitalRead(button);
//
//  Serial.println("\n Panic = ");
//  Serial.println(button_value);
//  
//  if (button_value == 1)
//  {
//    digitalWrite(ledpin4, HIGH);
//
//    //Serial.println("\n Panic = ");
//    //Serial.println(button_value);
//    delay(200);
//    digitalWrite(ledpin4, LOW);
//  }
//
//  else if (button_value == 0)
//  {
//    digitalWrite(ledpin4, LOW);
//
//    //Serial.println("\n Panic = ");
//    //Serial.println(button_value);
//    delay(200);
//  }
//
//  Cayenne.virtualWrite(3, digitalRead(10));
//  Serial.println(digitalRead(10));
//  delay(500);
//}


// Vibration Sensor
 void vibration_sensor(){
  int vibrationvalue = digitalRead(vibration);

  if (vibrationvalue == HIGH)  {
    digitalWrite(LedPin3, HIGH);
    Serial.print("\n Vibration");
    delay(1000);
  } 

  else {
    digitalWrite(LedPin3, LOW);
    Serial.print("\n NO Vibration");
    delay(1000);
    }
  Cayenne.virtualWrite(4, digitalRead(16));
  //Serial.println(digitalRead(16));
  delay(500);
}


//CAYENNE_IN(1)
//{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//
//  int i = getValue.asInt();
//  digitalWrite(13, i);
//}
//
//
//CAYENNE_IN(2)
//{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//
//  int j = getValue.asInt();
//  digitalWrite(15, j);
//}
//
//
//CAYENNE_IN(3)
//{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//
//  int k = getValue.asInt();
//  digitalWrite(10, k);
//}
 
//CAYENNE_IN(4)
//{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//
//  int l = getValue.asInt();
//  digitalWrite(16, l);
//}

CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");

   int i = getValue.asInt();
   digitalWrite(16, i);
 
}
