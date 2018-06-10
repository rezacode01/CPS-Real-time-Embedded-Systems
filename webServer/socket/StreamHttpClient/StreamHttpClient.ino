





w#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "reza";
const char* password = "1r2e3z4a";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = 13;
void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);http://arduino.esp8266.com/stable/package_esp8266com_index.json
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());http://arduino.esp8266.com/stable/package_esp8266com_index.json
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}


//#include <ESP8266WiFi.h>
//
//#define MAX_SRV_CLIENTS 3
//const char* ssid = "reza";
//const char* password = "1r2e3z4a";
//
//WiFiServer server(21);
//WiFiClient serverClients[MAX_SRV_CLIENTS];
//
//void setup() {
//  Serial.begin(115200);
//  Serial.println("reza");
//  Serial1.begin(115200);
//  //Serial1.setDebugOutput(true);
//  WiFi.begin(ssid, password);
//  Serial1.print("\nConnecting to "); Serial1.println(ssid);
//  uint8_t i = 0;
//  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
//  if(i == 21){
//    Serial1.print("Could not connect to"); Serial1.println(ssid);
//    while(1) delay(500);
//  }
////  Serial.begin(115200);
//  server.begin();
//  server.setNoDelay(true);
//  Serial1.print("Ready! Use 'telnet ");
//  Serial1.print(WiFi.localIP());
//  Serial1.println(" 21' to connect");
//}
//
//void loop() {
//  Serial.println("reza");
//  uint8_t i;
//  if (server.hasClient()){
//    for(i = 0; i < MAX_SRV_CLIENTS; i++){
//      if (!serverClients[i] || !serverClients[i].connected()){
//        if(serverClients[i]) serverClients[i].stop();
//        serverClients[i] = server.available();
//        continue;
//      }
//    }
//    //no free spot
//    WiFiClient serverClient = server.available();
//    serverClient.stop();
//  }
//  for(i = 0; i < MAX_SRV_CLIENTS; i++){
//    if (serverClients[i] && serverClients[i].connected()){
//      if(serverClients[i].available()){
//        while(serverClients[i].available()) Serial.write(serverClients[i].read());
//        //you can reply to the client here
//      }
//    }
//  }
//  if(Serial.available()){
//    size_t len = Serial.available();
//    uint8_t sbuf[len];
//    Serial.readBytes(sbuf, len);
//    //bello is a broadcast to all clients
//    for(i = 0; i < MAX_SRV_CLIENTS; i++){
//      if (serverClients[i] && serverClients[i].connected()){
//        serverClients[i].write(sbuf, len);
//        delay(1);
//      }
//    }
//  }
//}
