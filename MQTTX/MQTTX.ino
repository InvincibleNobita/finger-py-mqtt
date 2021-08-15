#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"
#define AWW analogWrite
#define GLOW digitalWrite
#define LED1 14
#define LED2 12
#define LED3 4
#define LED4 5
#define PWM1 9        //DEFINE A PWM GPIO HERE
#define PWM2 10       //TODO: 

// WiFi
const char* ssid = WIFI_SSID;
const char* pass = WIFI_PASS;

// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "MOVEMENT";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str())) {
          Serial.println("Public mosquitto mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String s="";
  for (int i = 0; i < length; i++) {
      Serial.print((char) payload[i]);
      s+=(char)payload[i];
  }
  switch(s.toInt())
  {
    case 1:AWW(PWM1,124);
           AWW(PWM2,124);
           GLOW(LED1,HIGH);
           GLOW(LED2,LOW);
           GLOW(LED3,HIGH);
           GLOW(LED4,LOW);
    break;
    case 2:AWW(PWM1,124);
           AWW(PWM2,124);
           GLOW(LED1,LOW);
           GLOW(LED2,HIGH);
           GLOW(LED3,LOW);
           GLOW(LED4,HIGH);
    break;
    case 3:AWW(PWM1,80);
           AWW(PWM2,80);
          GLOW(LED1,HIGH);
          GLOW(LED2,LOW);
          GLOW(LED3,LOW);
          GLOW(LED4,HIGH);
          AWW(PWM1,124);
           AWW(PWM2,124);
    break;
    case 4: AWW(PWM1,80);
           AWW(PWM2,80);
            GLOW(LED1,LOW);
            GLOW(LED2,HIGH);
            GLOW(LED3,HIGH);
            GLOW(LED4,LOW);
            AWW(PWM1,124);
           AWW(PWM2,124);
    break;
    default: AWW(PWM1,0);
           AWW(PWM2,0);
    // default: GLOW(LED1,LOW);
    //         GLOW(LED2,LOW);
    //         GLOW(LED3,LOW);
    //         GLOW(LED4,LOW);
    break;
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  client.loop();
}
