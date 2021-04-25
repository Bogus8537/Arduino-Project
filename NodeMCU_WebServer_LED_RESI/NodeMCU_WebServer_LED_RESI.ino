#include <ESP8266WiFi.h>

// Declare WiFi to connect (Change it to your WiFi's Info)
#define ssid      "WiFi's Name"
#define password  "WiFi's Password"

#define RESI A0       // CDS Sensor Pin
#define LED_I     D3  // LED 1  Pin
#define LED_II    D5  // LED 2  Pin
#define LED_III   D7  // LED 3  Pin

WiFiServer server(80);  // Declare Port number : 80 to communicate on HTTP

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connecting to : ");
  Serial.println(ssid);

  Serial.println("\nWiFi Connected!");

  Serial.print("Connected IP Address : ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server Started!\n");
  
  pinMode(RESI, INPUT);
  pinMode(LED_I, OUTPUT);
  pinMode(LED_II, OUTPUT);
  pinMode(LED_III, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int val = analogRead(RESI);

  Serial.print("Val : ");
  Serial.println(val);

  WiFiClient client = server.available();
  
  client.println("HTTP/1.1 200 OK");                                                                    // Response status code informs successsing!
  client.println("Content-Type: text/html");                                                            // Content's Type : Text/HTML
  client.println("Connection: close");                                                                  // The connection will be closed after completion of the response.
  client.println("Refresh: 1");                                                                         // Refreshing the webpage every second.
  client.println("<!DOCTYPE html>");                                                                    // Inform the webpage's written as HTML5
  client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");                                        // Specify to HTML validity check.
  client.println("<head>\n<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");

  client.println("<title>LED_Resistor Control for test</title>");                                       // Set Webpage's Title
  client.println("</head>\n<body>");
  client.println("<center>");
  client.println("<H1>NodeMCU ESP8266 0.9 - LED + Resistor Control</H1>");                             	// Page's Content Title

  client.println("<br>");
  client.println("<br>");


  // Setting CDS Sensor's value to LED ON / OFF
  if (val < 250)
  {
    client.print("<H2>Day</H2>");
    client.println("<H3>LED_BUILTIN ON!</H3>");
    client.println("<H4>RESI Sensor Value</H4>");
    client.println(val);
    
    digitalWrite(LED_I, LOW);
    digitalWrite(LED_II, LOW);
    digitalWrite(LED_III, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED BUILTIN - ON!!\n");
  }
  
  else if ( (val > 250) && (val < 450) )
  {
    client.print("<H2>Dusk</H2>");
    client.println("<H3>LED (1) - ON!!</H3>");
    client.println("<H4>RESI Sensor Value</H4>");
    client.println(val);
    
    digitalWrite(LED_I, HIGH);
    digitalWrite(LED_II, LOW);
    digitalWrite(LED_III, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED (1) - ON!!\n");
  }

  else if ( (val > 450) && (val < 600) )
  {
    client.print("<H2>Night</H2>");
    client.println("<H3>LED (1) (2) - ON!!!</H3>");
    client.println("<H4>RESI Sensor Value</H4>");
    client.println(val);
    
    digitalWrite(LED_I, HIGH);
    digitalWrite(LED_II, HIGH);
    digitalWrite(LED_III, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED (1) (2) - ON!!\n");
  }

  else if ( (val > 600))
  {
    client.print("<H2>Midnight</H2>");
    client.println("<H3>LED (1) (2) (3) - ON!!</H3>");
    client.println("<H4>RESI Sensor Value</H4>");
    client.println(val);
    
    digitalWrite(LED_I, HIGH);
    digitalWrite(LED_II, HIGH);
    digitalWrite(LED_III, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED (1) (2) (3) - ON!!\n");
  }
  
  client.println("<br>");
  client.println("<br>");
 
  client.println("<pre>");
  client.print("</body>\n</html>");
  
  delay(1000);
}
