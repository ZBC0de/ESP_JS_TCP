#include "Wire.h"
#include <WiFi.h>
#include <ArduinoJson.h>

// WiFi setup vars
const char* ssid = "netgear89";
const char* password = "mightylotus540";
const IPAddress serverIP(10,1,1,161);
const int serverPort = 3000; //3000 for client & 3001 for server
WiFiClient client;



// JSON setup
String incomingData = "";
bool jsonStarted = false;
char startChar = '{';
char endChar = '}';
StaticJsonDocument<200> jsonDocument;  // Use this for connection-related data

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500; // 500ms update interval


void setup()
{
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  String ip = WiFi.localIP().toString();
  Serial.println();
  Serial.print("WiFi connected with IP: ");
  Serial.println(ip);

  jsonDocument["type"] = "connect";
  jsonDocument["ip"]   = ip;

  delay(1000);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdateTime >= 5000) {
    //checkConn
  }

  // TCP connection
  if (!client.connected()) {
    if (client.connect(serverIP, serverPort)) {
      String jsonString;
      serializeJson(jsonDocument, jsonString);  // Use jsonDocument here
      Serial.println("Client connected, sending packet");
      client.print(jsonString);
    } else {
      Serial.println("Connection to host failed");
      delay(1000);
    }
  }

  // Process incoming data
  while (client.available()) {
    char c = client.read();
    if (c == startChar) {
      incomingData = startChar;
      jsonStarted = true;
    } else if (jsonStarted) {
      incomingData += c;
      if (c == endChar) {
        // Complete JSON object received, parse it
        StaticJsonDocument<200> receivedJson;
        DeserializationError error = deserializeJson(receivedJson, incomingData);
        if (!error) {
          const char* recMsg = receivedJson["type"];
          std::string checkCon = "checkCon";
          if(recMsg == checkCon){
            String jsonString;
            jsonDocument["type"] = "isAlive";
            serializeJson(jsonDocument, jsonString);  // Use jsonDocument here
            client.print(jsonString);
          }
          // JSON parsing successful, you can access receivedJson here
          // Handle the received JSON data as needed
        } else {
          Serial.print("JSON parsing error: ");
          Serial.println(error.c_str());
        }
        incomingData = "";
        jsonStarted = false;
      }
    }
  }
}