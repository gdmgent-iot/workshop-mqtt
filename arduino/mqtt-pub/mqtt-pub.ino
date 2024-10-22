#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include "secrets.h"
 
char ssid[] = SECRET_SSID;    // WiFi netwerknaam
char pass[] = SECRET_PASS;       // WiFi wachtwoord
const char* server = "numbersapi.com";  // Serveradres voor NumbersAPI
int maxReconnectAttempts = 5;       // Maximaal aantal pogingen om verbinding te maken
 
WiFiClient wifiClient;                  // WiFiClient object
MqttClient mqttClient(wifiClient);      // MQTT object

const char broker[] = "mqtt.eclipseprojects.io";
int port = 1883;
const char topic[] = "games123";

void connectToWiFi() {
  int attempts = 0;
 
  // Probeer verbinding te maken met het netwerk
  while (WiFi.status() != WL_CONNECTED && attempts < maxReconnectAttempts) {
    Serial.print("Verbinden met netwerk: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    // Wacht 5 seconden voor de volgende poging
    delay(5000);
    attempts++;
  }
 
  // Controleer of de verbinding geslaagd is
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("JUIJ! WE ZIJN VERBONDEN!");
    Serial.print("Mijn IP-adres is: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Verbinding mislukt na meerdere pogingen.");
  }
}

void setup() {
  Serial.begin(9600);    // Start seriële verbinding
 
  // Verbinden met WiFi
  connectToWiFi();

  // Verbinden met de broker
  Serial.print("Attempt connect to broker: ");
  Serial.println(broker);

  if(!mqttClient.connect(broker, port)) {
    Serial.print("Error :");
    Serial.println(mqttClient.connectError());

    // stop here!
    while(1);    
  }

  Serial.print("Connected to broker");
  Serial.println();
}
 
void loop() {
  // Controleer of er verbinding is, en probeer opnieuw verbinding te maken als deze verloren is gegaan
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Verbinding verloren! Probeer opnieuw te verbinden...");
    connectToWiFi();
  }
 
  mqttClient.poll();
  Serial.println("Aight, we are sending muchos love to you");
  mqttClient.beginMessage(topic);
  mqttClient.print("Roses are yummy, violets are too, rabbits love poetry, banana");
  mqttClient.endMessage();
  Serial.println("Message sent");
 
  // Wacht 10 seconden voor de volgende iteratie
  delay(10000);
}
 
