#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "webpage.h"

// Motor control pins for Nano ESP32
// Using GPIO pins that are available and suitable for motor control
#define MOTOR_A_FWD 0
#define MOTOR_A_BWD 1
#define MOTOR_B_FWD 2
#define MOTOR_B_BWD 3

// WiFi credentials - CHANGE THESE TO YOUR NETWORK
const char* ssid = "Atrash Home";
const char* password = "microgrid2015";

// Create web server object on port 80
WebServer server(80);

// LED states
bool redState = false;
bool greenState = false;
bool blueState = false;

// Motor control variables
unsigned long motorStartTime = 0;
bool motorRunning = false;
const unsigned long MOTOR_DURATION = 500; // 500ms = 0.5 seconds

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(3000);
  
  Serial.println("Starting LED and Car Controller...");
  
  // Setup built-in RGB LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Setup motor control pins
  pinMode(MOTOR_A_FWD, OUTPUT);
  pinMode(MOTOR_A_BWD, OUTPUT);
  pinMode(MOTOR_B_FWD, OUTPUT);
  pinMode(MOTOR_B_BWD, OUTPUT);
  
  // Turn off all LEDs initially
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  
  // Initialize motors to stop position
  digitalWrite(MOTOR_A_FWD, LOW);
  digitalWrite(MOTOR_A_BWD, LOW);
  digitalWrite(MOTOR_B_FWD, LOW);
  digitalWrite(MOTOR_B_BWD, LOW);
  
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
  
  // Setup mDNS (allows accessing via hostname)
  if (MDNS.begin("car-controller")) {
    Serial.println("MDNS responder started");
    Serial.println("You can access the board at: http://car-controller.local");
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
  
  // Check if motors should be stopped
  if (motorRunning && (millis() - motorStartTime >= MOTOR_DURATION)) {
    stopMotors();
  }
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(MOTOR_A_FWD, LOW);
  digitalWrite(MOTOR_A_BWD, LOW);
  digitalWrite(MOTOR_B_FWD, LOW);
  digitalWrite(MOTOR_B_BWD, LOW);
  motorRunning = false;
  Serial.println("⏹️ Motors stopped automatically");
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
      digitalWrite(MOTOR_A_FWD, HIGH);
      digitalWrite(MOTOR_A_BWD, LOW);
      digitalWrite(MOTOR_B_FWD, HIGH);
      digitalWrite(MOTOR_B_BWD, LOW);
      motorStartTime = millis();
      motorRunning = true;
    } else if (direction == "BACKWARD") {
      Serial.println("🔴 Moving BACKWARD");
      digitalWrite(MOTOR_A_FWD, LOW);
      digitalWrite(MOTOR_A_BWD, HIGH);
      digitalWrite(MOTOR_B_FWD, LOW);
      digitalWrite(MOTOR_B_BWD, HIGH);
      motorStartTime = millis();
      motorRunning = true;
    } else if (direction == "LEFT") {
      Serial.println("🔵 Turning LEFT");
      digitalWrite(MOTOR_A_FWD, LOW);
      digitalWrite(MOTOR_A_BWD, LOW);
      digitalWrite(MOTOR_B_FWD, HIGH);
      digitalWrite(MOTOR_B_BWD, LOW);
      motorStartTime = millis();
      motorRunning = true;
    } else if (direction == "RIGHT") {
      Serial.println("🔵 Turning RIGHT");
      digitalWrite(MOTOR_A_FWD, HIGH);
      digitalWrite(MOTOR_A_BWD, LOW);
      digitalWrite(MOTOR_B_FWD, LOW);
      digitalWrite(MOTOR_B_BWD, LOW);
      motorStartTime = millis();
      motorRunning = true;
    } else if (direction == "STOP") {
      Serial.println("⏹️ STOPPING");
      stopMotors();
    }
    
    server.send(200, "text/plain", "Direction command executed");
  } else {
    server.send(400, "text/plain", "No direction specified");
  }
}
