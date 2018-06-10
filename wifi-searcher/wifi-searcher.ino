#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "FS.h"

//Initialize Digital Pins
const int MOTOR_ON = 1000;

const int leftForward = 5;
const int leftBackward = 4;
const int rightForward = 0;
const int rightBackward = 2;

const int left = 14;
const int top = 12;
const int right = 13;

int ls = 0;
int ts = 0;
int rs = 0;

int prevDirection = 0;
const int LEFT = 0;
const int RIGHT = 1;

int motorTimeSlice = 1000;
const int rotationTimeSlice = 1300;
const int LOOP_TIME_SLICE = 500;

int32_t prevRSSI = 0;
int i = 0;


void stopp() {
  analogWrite(leftForward,0);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,0);

  delay(motorTimeSlice);
}

void goForward() {
  // run forward
  analogWrite(leftForward,MOTOR_ON);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,MOTOR_ON);
  analogWrite(rightBackward,0);

  Serial.println("forward");
//  delay(motorTimeSlice);  
}

void goBackward() {  
  // run backward
  analogWrite(leftForward,0);
  analogWrite(leftBackward,MOTOR_ON);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,MOTOR_ON);

  Serial.println("backward");
//  delay(motorTimeSlice);
}

void turnRight() {
  // run right
  analogWrite(leftForward,MOTOR_ON);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,0);
  analogWrite(rightBackward,0);

  Serial.println("right");
  delay(rotationTimeSlice);
  
}

void turnLeft() {
  // run left
  analogWrite(leftForward,0);
  analogWrite(leftBackward,0);
  analogWrite(rightForward,MOTOR_ON);
  analogWrite(rightBackward,0);

  Serial.println("left");
  delay(rotationTimeSlice);
}




// **********************************************************************************************************************************************
// Wifi

const char* SSID = "reza";

const int b = 2;
const int s = 5;
int32_t batch[s];
const double percentile = 0.6;

// Return RSSI or 0 if target SSID not found
int32_t getRSSI(const char* target_ssid) {
  byte available_networks = WiFi.scanNetworks();

  for (int network = 0; network < available_networks; network++) {
    if (strcmp(WiFi.SSID(network).c_str(), target_ssid) == 0) {
      return WiFi.RSSI(network);
    }
  }
  return 0;
}

int32_t winsorise() {
    Serial.print("batch: ");
  for(int j =0; j< s;j++){
    Serial.print(batch[j]);
    Serial.print(" ");
  }
   Serial.println("");
  //winsorisation
  int32_t nb[s];
  for(int j = 0; j < s; j++)
    nb[j] = batch[j]  ;    
  double interval_dbs;
  //sotring
  for(int j =0; j < s; j++)
    for(int k = 0; k < s-1; k++)
        if(nb[k]>nb[k+1])
        {
            long temp = nb[k];
            nb[k] = nb[k+1];
            nb[k+1] = temp;
        }
  //winsorisation
  int index_low = (int) (((1.0-percentile)/2.0)*s);
  int index_high = (int) ((1-((1.0-percentile)/2.0))*s)-1;
  for(int j = 0; j < index_low; j++)
      nb[j] = nb[index_low];
  for(int j = index_high+1; j < s; j++)
      nb[j] = nb[index_high];
  interval_dbs = 0;
  for(int j = 0; j < s; j++)
    interval_dbs += double(nb[j]);
  interval_dbs /= double(s);
  return interval_dbs;
}


// ******************************************************************************************************************************************

void setup() {
  // set motor pins as Output
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);


  // sensor control pin as input
  pinMode(left,INPUT);
  pinMode(top,INPUT);
  pinMode(right,INPUT);

  Serial.begin(9600);
}



int dir = 0;

void loop() {
  unsigned long before = millis();
  int32_t rssi = getRSSI(SSID);
  batch[i] = rssi;

  int32_t wrssi = winsorise();
  i++;
  if(i == 5){
    i = 0;
  }
  else if(i>1){
    stopp();
  }

  if(wrssi > prevRSSI){
      if(dir == 0)
        goForward();
      else
        goBackward();
    }
    else if(prevRSSI == wrssi)
      stopp();
    else{
      if(dir == 0){
        goBackward();
        dir = 1;
      }
      else{
        goForward();
        dir = 0;
      }
    } 
    prevRSSI = wrssi;

  
  unsigned long after = millis();
  
  Serial.print("Signal strength: ");
  Serial.print(wrssi);
  Serial.println(" dbm ");
  Serial.print(prevRSSI);
  Serial.println(" dbm ");
//  double pWatts = pow( 10.0, (wrssi + 60.0) / 10.0);
//  Serial.print(pWatts);
//  Serial.println("nWatts");

//  double distance = pow(10.0, (-16.6 - wrssi) / 20) / 20;
//  Serial.print(distance);
//  Serial.println("meter");
//  Serial.println("");

  Serial.print("Took ");
  Serial.print(after - before);
  Serial.println("ms");
 
}



