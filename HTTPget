// Tools > Board: Generic 8266 Module
#include <ESP8266WiFi.h>
#include <WiFiClient.h>   // https://goo.gl/B3CRB3
 
// WiFi information, Connect to HotSpot
const char ssid[] = "ssid";
const char password[] = "password";
 
// Remote site information
const char site[] = "example.com";
const int port = 80; 
 
// Onboard 8266 LED pin
const int LED_PIN = 5;
 
// Initialize default client library
WiFiClient client;


// ------------------------------------------------------------------------------ Setup

void setup() {
  
  // Set up serial console to read web page
  Serial.begin(115200);
  Serial.print("Attempting to connect to WPA network...");
  Serial.println();
  
  
  // Set up LED for debugging
  pinMode(LED_PIN, OUTPUT);
  
  // Connect to WiFi
  connectWiFi();
  
  // Attempt to connect to website
  if ( !getPage() ) {
    Serial.println("GET request failed");
  }

  // Connecting to
  Serial.println("Connected: ");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP addy
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
 
  // Signal Strength.
  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");
  
}


// ------------------------------------------------------------------------------ Loop

void loop() {

  // As long as there are bytes from the server in the client buffer, read the bytes and print them to the serial monitor. Repeat every 5 seconds.
  // If there are incoming bytes, print them
  if ( client.available() ) {
    char c = client.read();
    Serial.print(c);
  }
  
  // If the server has disconnected, stop the client and WiFi
  if ( !client.connected() ) {
    //Serial.println();
    
    // Close socket and wait for disconnect from WiFi
    // WL_CONNECTED == return when WiFi connected to network
    client.stop();
    if ( WiFi.status() != WL_DISCONNECTED ) {
      WiFi.disconnect();
    }
    
    // Turn off LED
    digitalWrite(LED_PIN, LOW);
    
    // Do nothing
    Serial.println();
    Serial.println();
    Serial.println("... Disconnected from WEP network");  // ("Finished Thing GET Webapp Data Test");
    while(true) {
      delay(1000);
    }

  }
}


// ------------------------------------------------------------------------------ connectWiFi

// Attempt to connect to WiFi
void connectWiFi() {
  
  byte led_status = 0;
  
  // Set WiFi mode to station (client)
  WiFi.mode(WIFI_STA);
  
  // Initiate connection with SSID and PSK
  WiFi.begin(ssid, password);
  
  // Blink LED while we wait for WiFi connection
  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(LED_PIN, led_status);
    led_status ^= 0x01;
    delay(100);
    Serial.print("."); // prints between ln 22 ("GET Webapp Data ") and 98 ("GET /index.html HTTP/1.1")
    //Serial.println();
  }
  
  // Turn LED on when we are connected
  digitalWrite(LED_PIN, HIGH);
}


// ------------------------------------------------------------------------------ getPage

// Perform an HTTP GET request to a remote page
bool getPage() {
  
  // Attempt to make a connection to the remote server
  if ( !client.connect(site, port) ) {
    return false;
  }
  
  // Make an HTTP GET request
  
  //  Serial.println();
  //  IPAddress ip(172, 20, 10, 7);   // Assign IP to 8266
  //  Serial.println("IP: ");
  //  Serial.println(IPAddress());
  
  Serial.println(); 
  client.println("GET /index.html HTTP/1.1");
  client.print("Host: ");
  client.println(site);
  client.println("Connection: close");
  client.println();

  return true;
}
