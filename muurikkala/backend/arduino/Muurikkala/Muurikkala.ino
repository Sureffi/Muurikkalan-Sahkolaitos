#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoHttpClient.h>

// Analog pins
const int pinA0 = A0;
const int pinA1 = A1;
const int pinA2 = A2;
const int pinA3 = A3;
const int pinA4 = A4;
const int pinA5 = A5;
const int pin4 = A6;
const int pin6 = A7;
const int pin8 = A8;
const int pin9 = A9;
const int pin10 = A10;
const int pin12 = A11;

// Digital pins for relays
const int relayPin1 = 2; // Rasvain
const int relayPin2 = 3; // moottori 1 isommalle
const int relayPin3 = 5; // moottori 1 pienemmalle
const int relayPin4 = 7; // moottori 2 isommalle
const int relayPin5 = 11; // moottori 2 pienemmalle



// MAC address of the Ethernet shield
byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0x95, 0x68 };
// IP address of the Arduino
IPAddress ip(192, 168, 100, 201);
// port number to listen to
int port = 80;
// Ethernet server
EthernetServer server(80);

//----------- FOR SENDING REQUESTS --------------
// Request destination server IP
IPAddress serverIP(192, 168, 1, 100);
// Ethernet client
EthernetClient ethClient;
// Http Client
HttpClient client = HttpClient(ethClient, serverIP);
//-----------------------------------------------


void setup() {
  Serial.begin(9600);

  // Configure pins
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);

  // Start the ethernet server
  Ethernet.begin(mac, ip);
  server.begin();
  delay(1000) // Time for initializing

  Serial.print("Serving on http://");
  Serial.println(Ethernet.localIP());
}

void loop() {
  receiveRequest();
}



void receiveRequest() {
  EthernetClient client = server.available();
  if (client) {
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (request.endsWith("\r\n\r\n")) {
          break;
        }
      }
    }
    // Check if the request is a GET request with a URL of the form /relays/{id}
    if (request.startsWith("GET /relays/")) {
      // Extract the id parameter from the URL
      int id_start = request.indexOf("/relays/") + 8;
      int id_end = request.indexOf(" ", id_start);
      String id_str = request.substring(id_start, id_end);
      int id = id_str.toInt();

      // Check the number of the relay and power the correct pin
      if (id == 1) {
        digitalWrite(relayPin1, HIGH);
        delay(5000);
        digitalWrite(relayPin1, LOW);
      } else if (id == 2) {
        digitalWrite(relayPin2, HIGH);
        delay(5000);
        digitalWrite(relayPin2, LOW);
      } else if (id == 3) {
        digitalWrite(relayPin3, HIGH);
        delay(5000);
        digitalWrite(relayPin3, LOW);
      } else if (id == 4) {
        digitalWrite(relayPin4, HIGH);
        delay(5000);
        digitalWrite(relayPin4, LOW);
      } else if (id == 5) {
        digitalWrite(relayPin5, HIGH);
        delay(5000);
        digitalWrite(relayPin5, LOW);
      }

      // Send a response to the client
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      client.print("<html><body><h1>Relay ");
      client.print(id);
      client.println(" was toggled.</h1></body></html>");
      client.stop();
    }
  }
}