#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

#include "TopSecret.h"    // contains 'const char* ssid = ""' & 'const char* password = ""'
/* Or, do it here instead */
// const char* ssid = "ChangeMe";
// const char* password = "ChangeMeToo";

char WebPage[] =
  "<html>\n\
  <head><title>ESP8266 Testing</title></head>\n\
  <body><h1>Ooga Booga!</h1>\n\
  <br><br><br><br>\n\
  <p>Yup...  It works.</p>\n\
  </body>\n\
  </html>";

char WebPage404[] =
  "<html>\n\
  <head><title>ESP8266 Testing (404!)</title></head>\n\
  <body>\n\
  <h1>Say Wut\?\?\?</h1>\n\
  <br><br><br><br>\n\
  <a href=\"/\">Run Away!</a>\n\
  </body>\n\
  </html>";

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

              // function prototypes for HTTP handlers
void handleRoot();
void handleNotFound();

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(100);
  Serial.println();
  Serial.println(F("+----------------------------------------+"));
  Serial.println(F("| Welcome to the ESP8266 Test WebServer  |"));
  Serial.println(F("+----------------------------------------+"));
  Serial.println("");
  Serial.print("ssid: ");
  Serial.println(ssid);
  Serial.print("pass: ");
  Serial.println(password);

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

  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  server.handleClient();

}

void handleRoot() {
  String message = WebPage;
  server.send(200, "text/html", message);
  // server.send(200, "text/html", WebPage0);
}

void handleNotFound() {
  String message = WebPage404;
  message += "<br><br>URI: ";
  message += server.uri();
  message += "<br>Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "<br>Arguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}
