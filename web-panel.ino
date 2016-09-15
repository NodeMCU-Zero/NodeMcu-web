#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "TP";
const char* password = "12345678";

ESP8266WebServer server(80);

const int led = 16;
const int fan = 4;

String con = "LED"; // to check condition 

void handleRoot() {

  String page = "<h1> NodeMcu-Power Panel</h1>";
  page += "<p>(PIN:DO) <a href=\"?pin=ON1\"><button>LAMP-ON</button></a>&nbsp;<a href=\"?pin=OFF1\"><button>LAMP-OFF</button></a></p>";
  page += "<p>(PIN:D2) <a href=\"?pin=ON2\"><button>FAN-ON</button></a>&nbsp;<a href=\"?pin=OFF2\"><button>FAN-OFF</button></a></p>";
  page += "<p>(PIN:D1) <a href=\"?pin=ON3\"><button>LAMP-ON-2</button></a>&nbsp;<a href=\"?pin=OFF3\"><button>LAMP-OFF-2</button></a></p>";
  page += "<p>(PIN:D4) <a href=\"?pin=ON4\"><button>LAMP-ON-3</button></a>&nbsp;<a href=\"?pin=OFF4\"><button>LAMP-OFF-3</button></a></p>";
  page += "<p>(PIN:D5) <a href=\"?pin=ON5\"><button>LAMP-ON-4</button></a>&nbsp;<a href=\"?pin=OFF5\"><button>LAMP-OFF-4</button></a></p>";
  page += "<p>(PIN:D6) <a href=\"?pin=ON6\"><button>LAMP-ON-5</button></a>&nbsp;<a href=\"?pin=OFF6\"><button>LAMP-OFF-5</button></a></p>";
  page += "<p><center>Status <a href=\"?details\"><button>DETAILS</button></a><center>";
  page += "<h2> Algobel Team : Free to Use </h2>";
  page += "<h3> Warning !!!!! </h3>";
  page +="<font color=\"red\">Before Connecting to the :Relay board: please follow the proper instructions!</font>";
 // page += "<p> Before Connect to Relay board please follow the proper instructions </p>";
  server.send(200, "text/html", page);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(led, 0);
  digitalWrite(fan, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
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

  server.on("/pin=ON1", []() {
    digitalWrite(led, 1);
    Serial.println("LED-1 ON");
    con = "LED-1-ON";
  });
  server.on("/pin=OFF1", []() {
    digitalWrite(led, 0);
    Serial.println("LED-1 OFF");
    con = "LED-1-OFF";
  });
  server.on("/pin=ON2", []() {
    digitalWrite(fan, 1);
    Serial.println("LED-2 ON");
    con = "LED-2-ON";
  });
  server.on("/pin=OFF2", []() {
    digitalWrite(fan, 0);
    Serial.println("LED-2 OFF");
    con = "LED-2-OFF";
  });
  server.on("/pin=ON3", []() {    
    Serial.println("LED-3 ON");
    con = "LED-3-ON";
    });
  server.on("/pin=OFF3", []() {   
    Serial.println("LED-3 OFF");
    con = "LED-3-OFF";
  });
server.on("/pin=ON4", []() {    
    Serial.println("LED-4 ON");
    con = "LED-4-ON";
   }); 
  server.on("/pin=OFF4", []() {   
    Serial.println("LED-4 OFF");
    con = "LED-4-OFF";
  });
  server.on("/pin=ON5", []() {    
    Serial.println("LED-5 ON");
    con = "LED-5-ON";
    });
    
  server.on("/pin=OFF5", []() {   
    Serial.println("LED-5 OFF");
    con = "LED-5-OFF";
  });
 server.on("/details", []() {   
    Serial.println("details");
    server.send(200, "text/plain", con);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  Serial.setDebugOutput(true);

  WiFi.printDiag(Serial);
}

void loop(void) {
  server.handleClient();

}

