#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// WiFi credentials - CHANGE THESE TO YOUR NETWORK
const char* ssid = "Atrash Home";
const char* password = "microgrid2015";

// Create web server object on port 80
WebServer server(80);

// LED pins (change these to your actual LED pins)
const int RED_LED = 2;    // Built-in LED on most ESP32 boards
const int GREEN_LED = 4;  // Change to your green LED pin
const int BLUE_LED = 5;   // Change to your blue LED pin

// LED states
bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(3000);
  
  Serial.println("Starting LED and Car Controller...");
  
  // Setup LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  // Turn off all LEDs initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
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
  String html = R"html(
<!DOCTYPE html>
<html>
<head>
    <title>LED and Car Controller</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
            text-align: center;
            margin-bottom: 30px;
        }
        .section {
            margin-bottom: 30px;
        }
        .section h2 {
            color: #555;
            margin-bottom: 15px;
            text-align: center;
        }
        .led-button {
            width: 100%;
            padding: 15px;
            margin: 5px 0;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.2s;
            color: white;
        }
        .led-button:hover {
            transform: scale(1.02);
        }
        .led-button:active {
            transform: scale(0.98);
        }
        .red { background-color: #f44336; }
        .red:hover { background-color: #d32f2f; }
        .green { background-color: #4CAF50; }
        .green:hover { background-color: #388e3c; }
        .blue { background-color: #2196F3; }
        .blue:hover { background-color: #1976d2; }
        
        .direction-controls {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
            gap: 10px;
            max-width: 300px;
            margin: 0 auto;
        }
        .direction-btn {
            padding: 20px;
            border: none;
            border-radius: 10px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.2s;
            color: white;
        }
        .direction-btn:hover {
            transform: scale(1.05);
        }
        .direction-btn:active {
            transform: scale(0.95);
        }
        .up { grid-column: 2; grid-row: 1; background-color: #4CAF50; }
        .left { grid-column: 1; grid-row: 2; background-color: #2196F3; }
        .right { grid-column: 3; grid-row: 2; background-color: #2196F3; }
        .down { grid-column: 2; grid-row: 3; background-color: #FF9800; }
        
        .wifi-info {
            background-color: #e8f5e8;
            padding: 15px;
            border-radius: 8px;
            margin-bottom: 20px;
            text-align: center;
        }
        .wifi-info.connected {
            background-color: #d4edda;
            border: 1px solid #c3e6cb;
        }
        .wifi-info.disconnected {
            background-color: #f8d7da;
            border: 1px solid #f5c6cb;
        }
        .status {
            margin-top: 20px;
            padding: 10px;
            border-radius: 5px;
            text-align: center;
        }
        .success {
            background-color: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
        }
        .error {
            background-color: #f8d7da;
            color: #721c24;
            border: 1px solid #f5c6cb;
        }
        .info {
            background-color: #d1ecf1;
            color: #0c5460;
            border: 1px solid #bee5eb;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎛️ LED and Car Controller</h1>
        
        <div class="wifi-info" id="wifi-status">
            <strong>WiFi Status:</strong> <span id="wifi-text">Checking...</span><br>
            <strong>IP Address:</strong> <span id="ip-address">Loading...</span><br>
            <strong>Signal Strength:</strong> <span id="signal-strength">Loading...</span>
        </div>
        
        <div class="section">
            <h2>🚗 Car Controls</h2>
            <div class="direction-controls">
                <button class="direction-btn up" onclick="sendDirection('FORWARD')">⬆️ FORWARD</button>
                <button class="direction-btn left" onclick="sendDirection('LEFT')">⬅️ LEFT</button>
                <button class="direction-btn right" onclick="sendDirection('RIGHT')">➡️ RIGHT</button>
                <button class="direction-btn down" onclick="sendDirection('BACKWARD')">⬇️ BACKWARD</button>
            </div>
        </div>
        
        <div class="section">
            <h2>💡 LED Controls</h2>
            <button class="led-button red" onclick="toggleLED('red')">🔴 RED LED</button>
            <button class="led-button green" onclick="toggleLED('green')">🟢 GREEN LED</button>
            <button class="led-button blue" onclick="toggleLED('blue')">🔵 BLUE LED</button>
        </div>
        
        <div id="status"></div>
    </div>

    <script>
        function toggleLED(color) {
            fetch('/toggle', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: 'led=' + color
            })
            .then(response => response.text())
            .then(data => {
                showStatus('Toggled ' + color.toUpperCase() + ' LED', 'success');
            })
            .catch(error => {
                showStatus('Error: ' + error, 'error');
            });
        }
        
        function sendDirection(direction) {
            fetch('/direction', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: 'direction=' + direction
            })
            .then(response => response.text())
            .then(data => {
                showStatus('Car command: ' + direction, 'info');
            })
            .catch(error => {
                showStatus('Error: ' + error, 'error');
            });
        }
        
        function showStatus(message, type) {
            const statusDiv = document.getElementById('status');
            statusDiv.innerHTML = message;
            statusDiv.className = 'status ' + type;
            setTimeout(() => {
                statusDiv.innerHTML = '';
                statusDiv.className = 'status';
            }, 2000);
        }
        
        function updateWiFiStatus() {
            const wifiDiv = document.getElementById('wifi-status');
            const wifiText = document.getElementById('wifi-text');
            const ipAddress = document.getElementById('ip-address');
            const signalStrength = document.getElementById('signal-strength');
            
            // Simulate WiFi status (in real app, you'd get this from server)
            const isConnected = true; // This would come from server
            const ip = window.location.hostname;
            const signal = '-45 dBm'; // This would come from server
            
            if (isConnected) {
                wifiDiv.className = 'wifi-info connected';
                wifiText.textContent = 'Connected';
                ipAddress.textContent = ip;
                signalStrength.textContent = signal;
            } else {
                wifiDiv.className = 'wifi-info disconnected';
                wifiText.textContent = 'Disconnected';
                ipAddress.textContent = 'N/A';
                signalStrength.textContent = 'N/A';
            }
        }
        
        // Update WiFi status on page load
        updateWiFiStatus();
        
        // Keyboard controls for car
        document.addEventListener('keydown', function(event) {
            switch(event.key) {
                case 'ArrowUp':
                case 'w':
                case 'W':
                    event.preventDefault();
                    sendDirection('FORWARD');
                    break;
                case 'ArrowDown':
                case 's':
                case 'S':
                    event.preventDefault();
                    sendDirection('BACKWARD');
                    break;
                case 'ArrowLeft':
                case 'a':
                case 'A':
                    event.preventDefault();
                    sendDirection('LEFT');
                    break;
                case 'ArrowRight':
                case 'd':
                case 'D':
                    event.preventDefault();
                    sendDirection('RIGHT');
                    break;
            }
        });
    </script>
</body>
</html>
)html";
  
  server.send(200, "text/html", html);
}

// Handle LED toggle
void handleToggle() {
  if (server.hasArg("led")) {
    String led = server.arg("led");
    
    if (led == "red") {
      redState = !redState;
      digitalWrite(RED_LED, redState ? HIGH : LOW);
      Serial.println("🔴 RED LED: " + String(redState ? "ON" : "OFF"));
    } else if (led == "green") {
      greenState = !greenState;
      digitalWrite(GREEN_LED, greenState ? HIGH : LOW);
      Serial.println("🟢 GREEN LED: " + String(greenState ? "ON" : "OFF"));
    } else if (led == "blue") {
      blueState = !blueState;
      digitalWrite(BLUE_LED, blueState ? HIGH : LOW);
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
