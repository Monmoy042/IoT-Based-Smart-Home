//Important Libries
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

char ssid[] = "SSID Name"; //Your Wifi Network Name
char wifiPassword[] = "Password"; //Your Wifi Password

char username[] = "MQTT Username"; //This User Name From Cayenne Website
char password[] = "MQTT Password"; //This Password From Cayenne Website
char clientID[] = "Client ID"; //This Client ID From Cayenne Website

int Light1 = 16;
int Light2 = 5;
int Light3 = 4;
int Light4 = 0;

int motorA = 2;
int motorB = 14;

const int smoke = A0;
const int Buzzerpin = 13;

const int threshold = 150;

void setup() {
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(Light4, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(Buzzerpin, OUTPUT);

  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

}

void loop() {
  Cayenne.loop();

  int analogValue = analogRead(smoke);
  Serial.println(analogValue);
  if (analogValue > threshold) {
    digitalWrite(Buzzerpin, HIGH);
  }
  else if (analogValue = threshold) {

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

//Channels for Showing Home Appliances

CAYENNE_IN(1)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int i = getValue.asInt();
  digitalWrite(16, i);
}
CAYENNE_IN(2)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int j = getValue.asInt();
  digitalWrite(5, j);
}
CAYENNE_IN(3)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int k = getValue.asInt();
  digitalWrite(4, k);
}

CAYENNE_IN(4)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int l = getValue.asInt();
  digitalWrite(0, l);
}

CAYENNE_IN(5)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int m = getValue.asInt();
  digitalWrite(0, m);
}

CAYENNE_IN(6)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int n = getValue.asInt();
  digitalWrite(2, n);
}

CAYENNE_IN(6)
{ CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());

  int o = getValue.asInt();
  digitalWrite(14, o);
}

