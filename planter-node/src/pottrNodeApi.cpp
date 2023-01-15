#include "pottrNodeApi.h"

WiFiClient client;
HTTPClient http;

DynamicJsonDocument doc(512);

void post(String serverAddress, String endpoint, DynamicJsonDocument payload) {
    Serial.printf("[HTTP] begin: %s\n", serverAddress.c_str());
    http.begin(client, "http://" + serverAddress + ":4000/" + endpoint);
    http.addHeader("Content-Type", "application/json");
    Serial.printf("[HTTP] POST to endpoint: %s\n", endpoint.c_str());

    String output;
    serializeJson(payload, output);
    int httpCode = http.POST(output);

    if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
}

void sendStatus(bool online, int batteryCharge, String id, String name) {
    JsonObject payload = doc.to<JsonObject>();
    payload["planterID"] = id;
    payload["planterName"] = name;
    payload["online"] = online;
    payload["chargeLevel"] = batteryCharge;

    post("192.168.1.19", "status/update-status", doc);
}

void sendMoistureReport(bool irrigating, int moistureReading, String id, String name) {
    JsonObject payload = doc.to<JsonObject>();
    payload["planterID"] = id;
    payload["planterName"] = name;
    payload["moistureReading"] = moistureReading;
    payload["irrigating"] = irrigating;

    post("192.168.1.19", "moisture/report", doc);
}