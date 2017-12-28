#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // https://goo.gl/hvc4L8
 
// WiFi information, Connect to HotSpot
const char ssid[] = "Moric";
const char password[] = "pmwtf5vrju7et";

// Onboard 8266 LED pin
const int LED_PIN = 5;


// ------------------------------------------------------------------------------ Setup

void setup(void) { 

  // Set up serial console
  Serial.begin(115200);
  Serial.print("Attempting to connect to WPA network...");

  // Set up LED for debugging
  pinMode(LED_PIN, OUTPUT);
  
  // Attempt to connect to WiFi
  WiFi.begin(ssid, password); 
 
  // while wifi not connected yet, print '.'
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");

     // Turn on LED
    digitalWrite(LED_PIN, HIGH);
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
 
void loop() {

 // Check WiFi status
 if(WiFi.status() == WL_CONNECTED) { 
  
   // Declare object of class HTTPClient
   HTTPClient http; 

   // Post destination
   http.begin("http://jsonplaceholder.typicode.com/posts/1"); 

   // Content-type header define
   http.addHeader("Content-Type", "text/plain"); 

   // Send request
   int httpCode = http.GET(); 

   // Get the response payload
   String payload = http.getString();  

   // Print HTTP return code
   Serial.println("HTTP Code: " + httpCode); 

   // Print payload request response
   Serial.println("Payload: " + payload); 

   // End connection
   http.end();  
   
  } 
  
  else {
    Serial.println("Error in WiFi connection");   
  }

  // Send a request every 30 seconds
  delay(30000);  
}
