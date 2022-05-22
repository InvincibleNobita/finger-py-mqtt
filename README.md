# Gesture controlled Bot

This is a basic MQTT application utilizing the Hands module from Mediapipe library.
The Aim was to control a MQTT bot(3-wheeler) using interaction of hand-gestures from web cam feed using OpenCV

Libraries Used:
<ul>
  <li>ESP8266WiFi.h(Arduino)</li>
  <li>PubSubClient.h(Arduino)</li>
  <li>opencv-python</li>
  <li>paho.mqtt.client.py(Python)</li>
  <li>mediapipe(Python)</li>
</ul>

MQTT broker used: test.mosquitto.org
We can also setup a local mosquitto server to avoid latency and down time lag.
