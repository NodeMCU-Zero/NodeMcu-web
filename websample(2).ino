#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
int led = 16;
const char* ssid = "TP";
const char* password = "12345678";
int con; 
ESP8266WebServer server(80);


void handleRoot() {
  con =0;
   
  server.send(200, "text/plain", "Welcome to the IoT world");
}
void handleon() {
  con =2;
   
  server.send(200, "text/plain", "LED is keep On");
}

void handleNotFound() {
 
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
  
}

void setup(void) {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
pinMode(led, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("algobel-webled", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/on", handleon);

  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.println("HTTP server started");
  
  Serial.setDebugOutput(true);

  WiFi.printDiag(Serial);
}

void loop(void) {
  server.handleClient();
  if (con==0){
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
  }

}
