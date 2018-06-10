#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "FS.h"

const char* SSID = "reza";

int i = 0;
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

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long before = millis();
  int32_t rssi = getRSSI(SSID);
  batch[i] = rssi;
  i++;
  if(i==5)
    i = 0;
  int32_t wrssi = winsorise();
  
  unsigned long after = millis();
  Serial.print("Signal strength: ");
  Serial.print(wrssi);
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
//  delay(1000);
}



