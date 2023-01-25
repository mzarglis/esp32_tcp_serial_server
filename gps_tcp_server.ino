/*
 *  This sketch reads GPS NMEA messages from hardware serial UART2
 *  on a esp32-wroom board and writes them to tcp client on port 23 
 *  
 *  You can test the connection with command: telnet $esp32ipaddr 23
 */

#include <WiFi.h>

const char* ssid = "$SSID";
const char* password = "$password";
WiFiServer server(23);                     // init server object on port 23

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  delay(2000);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();                         // start server
  server.setNoDelay(true);                // don't wait to combine small outgoing packets 
}

void loop() {
  WiFiClient client = server.available(); // listen for incoming clients
  Serial.println("Listening for tcp connection on port 23... ");
  delay(2000);

  if (client) {                           // if a client connects
    while (client.connected()) {          // loop while the client's connected
      if (Serial2.available()) {          // if there's bytes to read from GPS UART2 buffer
        while (Serial2.available()) {     // while there is bytes to read from GPS UART2 buffer
          char r = Serial2.read();        // local var to reduce mem usage
          Serial.write(r);                // echo to console
          client.write(r);                // write to tcp connection
        }
      } else {
        Serial.println();
        Serial.println("################################################  GPS UART buffer empty waiting  ######################################################");
        delay(100);
      }
    }
    client.stop();                        // close the connection:
    Serial.println("Client Disconnected.");
  }
}
