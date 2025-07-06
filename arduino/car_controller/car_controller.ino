#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "webpage.h"

// WiFi credentials - CHANGE THESE TO YOUR NETWORK
const char* ssid = "Atrash Home";
const char* password = "microgrid2015";

// Create web server object on port 80
WebServer server(80);

// LED states
bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(3000);
  
  Serial.println("Starting LED and Car Controller...");
  
  // Setup built-in RGB LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Turn off all LEDs initially
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_RED, redState);
    redState=!redState;
    Serial.print(".");
  }
  greenState=true;

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Setup mDNS (optional - allows accessing via hostname)
  if (MDNS.begin("arduino")) {
    Serial.println("MDNS responder started");
  }
  
  // Setup server routes
  server.on("/", handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.on("/direction", HTTP_POST, handleDirection);
  
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

// Handle root page (main interface)
void handleRoot() {
  server.send(200, "text/html", WEBPAGE_HTML);
}

// Handle LED toggle
void handleToggle() {
  if (server.hasArg("led")) {
    String led = server.arg("led");
    
    if (led == "red") {
      redState = !redState;
      digitalWrite(LED_RED, !redState);
      Serial.println("🔴 RED LED: " + String(redState ? "ON" : "OFF"));
    } else if (led == "green") {
      greenState = !greenState;
      digitalWrite(LED_GREEN, !greenState);
      Serial.println("🟢 GREEN LED: " + String(greenState ? "ON" : "OFF"));
    } else if (led == "blue") {
      blueState = !blueState;
      digitalWrite(LED_BLUE, !blueState);
      Serial.println("🔵 BLUE LED: " + String(blueState ? "ON" : "OFF"));
    }
    
    server.send(200, "text/plain", "LED toggled");
  } else {
    server.send(400, "text/plain", "No LED specified");
  }
}

// Handle car direction commands
void handleDirection() {
  if (server.hasArg("direction")) {
    String direction = server.arg("direction");
    
    Serial.println("🚗 Car Command: " + direction);
    
    if (direction == "FORWARD") {
      Serial.println("🟢 Moving FORWARD");
      // Add your motor control code here
      // digitalWrite(MOTOR_A_FWD, HIGH);
      // digitalWrite(MOTOR_A_BWD, LOW);
      // digitalWrite(MOTOR_B_FWD, HIGH);
      // digitalWrite(MOTOR_B_BWD, LOW);
    } else if (direction == "BACKWARD") {
      Serial.println("🔴 Moving BACKWARD");
      // digitalWrite(MOTOR_A_FWD, LOW);
      // digitalWrite(MOTOR_A_BWD, HIGH);
      // digitalWrite(MOTOR_B_FWD, LOW);
      // digitalWrite(MOTOR_B_BWD, HIGH);
    } else if (direction == "LEFT") {
      Serial.println("🔵 Turning LEFT");
      // digitalWrite(MOTOR_A_FWD, LOW);
      // digitalWrite(MOTOR_A_BWD, HIGH);
      // digitalWrite(MOTOR_B_FWD, HIGH);
      // digitalWrite(MOTOR_B_BWD, LOW);
    } else if (direction == "RIGHT") {
      Serial.println("🔵 Turning RIGHT");
      // digitalWrite(MOTOR_A_FWD, HIGH);
      // digitalWrite(MOTOR_A_BWD, LOW);
      // digitalWrite(MOTOR_B_FWD, LOW);
      // digitalWrite(MOTOR_B_BWD, HIGH);
    }
    
    server.send(200, "text/plain", "Direction command executed");
  } else {
    server.send(400, "text/plain", "No direction specified");
  }
}
