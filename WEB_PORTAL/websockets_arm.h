#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

WebSocketsServer webSocket = WebSocketsServer(81);

int yaw_web_input = 90;
int elbow_web_input = 90;
int shoulder_web_input = 90;
int wrist_web_input = 90;
int gripper_web_input = 0;

int s1Inp, s2Inp, s3Inp, s4Inp, s5Inp, s6Inp, s7Inp, s8Inp;

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[WS] Client connected: %s\n", ip.toString().c_str());
        break;
      }

    case WStype_DISCONNECTED:
      Serial.printf("[WS] Client %u disconnected\n", num);
      break;

    case WStype_TEXT:
      {
        StaticJsonDocument<256> doc;
        DeserializationError err = deserializeJson(doc, payload, length);
        if (err) {
          Serial.print("[WS] JSON Parse Error: ");
          Serial.println(err.f_str());
          return;
        }

        // if (doc.containsKey("yaw")) yaw_web_input = doc["yaw"];
        // if (doc.containsKey("elbow")) elbow_web_input = doc["elbow"];
        // if (doc.containsKey("shoulder")) shoulder_web_input = doc["shoulder"];
        // if (doc.containsKey("wrist")) wrist_web_input = doc["wrist"];
        // if (doc.containsKey("gripper")) gripper_web_input = doc["gripper"];

        if(doc.containsKey("s1")) s1Inp = doc["s1"];
        if(doc.containsKey("s2")) s2Inp = doc["s2"];
        if(doc.containsKey("s3")) s3Inp = doc["s3"];
        if(doc.containsKey("s4")) s4Inp = doc["s4"];
        if(doc.containsKey("s5")) s5Inp = doc["s5"];
        if(doc.containsKey("s6")) s6Inp = doc["s6"];
        if(doc.containsKey("s7")) s7Inp = doc["s7"];
        if(doc.containsKey("s8")) s8Inp = doc["s8"];
        

        // Serial.printf("[WS] Updated: Y:%d E:%d S:%d W:%d G:%d\n",
        //               yaw_web_input, elbow_web_input, shoulder_web_input, wrist_web_input, gripper_web_input);
        break;
      }

    default:
      break;
  }
}

void setupWebSocket() {
  webSocket.begin();
  webSocket.onEvent(handleWebSocketEvent);
  Serial.println("[WS] WebSocket server started on port 81");
}

void updateWebSocket() {
  webSocket.loop();
}

void sendServoStatus() {
  StaticJsonDocument<256> doc;
  doc["yaw"] = yaw_web_input;
  doc["elbow"] = elbow_web_input;
  doc["shoulder"] = shoulder_web_input;
  doc["wrist"] = wrist_web_input;
  doc["gripper"] = gripper_web_input;

  String json;
  serializeJson(doc, json);
  webSocket.broadcastTXT(json);
}

#endif
