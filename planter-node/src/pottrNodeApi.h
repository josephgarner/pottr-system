#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

void sendStatus(bool online, int batteryCharge, String id, String name);
void sendMoistureReport(bool irrigating, int moisturePercentage, String id, String name);