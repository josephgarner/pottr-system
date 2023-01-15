#include <Adafruit_ADS1X15.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

#include "io.h"
#include "pottrNodeApi.h"
#include "sensors.h"

const char *ssid = "ESP8266-Access-Point";
const char *password = "123456789";

AsyncWebServer server(80);

const char *PARAM_INPUT_1 = "name";
const char *PARAM_INPUT_2 = "host_ssid";
const char *PARAM_INPUT_3 = "host_password";

const char complete_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style>
      html {
        font-family: Arial;
        text-align: center;
        display: flex;
        width: 100%;
        justify-content: center;
      }
      body {
        display: flex;
        width: 100%;
        justify-content: center;
        flex-direction: column;
        align-items: center;
      }
      h2 {
        font-size: 2rem;
      }
      p {
        margin-bottom: 2rem;
      }
    </style>
  </head>
  <body>
    <h2>Pottr Node</h2>
    <p>
      Completing setup...
      <br />
      <br /
      <br />
      <br />
      Device will reboot once configuration is complete
    </p>
  </body>
  <script>
    setTimeout(() => {
       window.location.href = "/";
    }, 7000);
  </script>
</html>)rawliteral";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style>
      html {
        font-family: Arial;
        text-align: center;
        display: flex;
        width: 100%;
        justify-content: center;
        background-color: #b7d6f3;
      }
      body {
        display: flex;
        width: 100%;
        justify-content: center;
        flex-direction: column;
        align-items: center;
      }
      h2 {
        font-size: 2rem;
        margin-top: 1rem;
        margin-bottom: 1rem;
      }
      div {
        display: flex;
        flex-direction: column;
        flex-wrap: nowrap;
        width: 100%;
      }
      form {
        display: flex;
        flex-direction: column;
        flex-wrap: nowrap;
        width: 100%;
        max-width: 40rem;
      }
      .label {
        margin-top: 0.5rem;
        font-weight: 700;
        margin-bottom: 0.5rem;
      }
      .margin {
        margin-bottom: 1rem;
      }
      input {
        position: relative;
        cursor: text;
        font-size: 18px;
        line-height: 20px;
        padding: 0 16px;
        height: 48px;
        background-color: #fff;
        border: 1px solid #d6d6e7;
        border-radius: 3px;
        color: rgb(35, 38, 59);
        box-shadow: inset 0 1px 4px 0 rgb(119 122 175 / 30%);
        overflow: hidden;
        transition: all 100ms ease-in-out;
      }
      input:focus {
        border-color: #3c4fe0;
        box-shadow: 0 1px 0 0 rgb(35 38 59 / 5%);
      }
      button {
        margin-top: 1rem;
        appearance: none;
        background-color: #2ea44f;
        border: 1px solid rgba(27, 31, 35, 0.15);
        border-radius: 6px;
        box-shadow: rgba(27, 31, 35, 0.1) 0 1px 0;
        box-sizing: border-box;
        color: #fff;
        cursor: pointer;
        display: inline-block;
        font-family: -apple-system, system-ui, "Segoe UI", Helvetica, Arial,
          sans-serif, "Apple Color Emoji", "Segoe UI Emoji";
        font-size: 14px;
        font-weight: 600;
        line-height: 20px;
        padding: 12px 16px;
        position: relative;
        text-align: center;
        text-decoration: none;
        user-select: none;
        -webkit-user-select: none;
        touch-action: manipulation;
        vertical-align: middle;
        white-space: nowrap;
      }
      button:focus:not(:focus-visible):not(.focus-visible) {
        box-shadow: none;
        outline: none;
      }

      button:hover {
        background-color: #2c974b;
      }

      button:focus {
        box-shadow: rgba(46, 164, 79, 0.4) 0 0 0 3px;
        outline: none;
      }

      button:disabled {
        background-color: #94d3a2;
        border-color: rgba(27, 31, 35, 0.1);
        color: rgba(255, 255, 255, 0.8);
        cursor: default;
      }

      button:active {
        background-color: #298e46;
        box-shadow: rgba(20, 70, 32, 0.2) 0 1px 0 inset;
      }
    </style>
  </head>
  <body>
    <h2>Pottr Node Config</h2>
    <p>
      You need to provide a human readable name so you can easily identify the
      planter box later on.<br />
      Please provide the Server address, WiFi name (SSID) and Password.<br />
      Once these details are saved the device will reboot and attempt to connect
      to the server.
    </p>
    <form action="/save" method="post">
      <div class="margin">
        <text class="label">Pottr Node Name:</text>
        <input type="text" name="name" placeholder="Herb Box" />
      </div>
      <div class="margin">
        <text class="label">Server Address:</text>
        <input type="text" name="name" placeholder="server.local:4000" />
      </div>
      <div>
        <text class="label">WiFi SSID:</text>
        <input type="text" name="host_ssid" placeholder="Wifi-Name" />
      </div>
      <div>
        <text class="label">WiFi Password:</text>
        <input type="password" name="host_password" />
      </div>
      <button type="submit">Save Infomation</button>
    </form>
  </body>
</html>)rawliteral";

#define RTCMEMORYSTART 65
#define MAXHOUR 6

ESP8266WiFiMulti WiFiMulti;
Adafruit_ADS1015 ads;

typedef struct {
    int counter;
} rtcStore;

rtcStore rtcMem;

String NodeName;

void initalSetup() {
    Serial.printf("[SETUP] AP Mode Activated\n");

    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.printf("[SETUP] AP IP address: %s\n", IP.toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send_P(200, "text/html", index_html); });

    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        String message;
        Serial.println("[CONFIG] Saving node infomation");
        int params = request->params();
        for (int i = 0; i < params; i++) {
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("[POST] %s: %s\n", p->name().c_str(), p->value().c_str());
            if (p->name().equals(PARAM_INPUT_1)) {
                Serial.printf("[CONFIG] Save Name: %s\n", p->value().c_str());
                writeFile(LittleFS, "/name.txt", p->value().c_str());
            }
            if (p->name().equals(PARAM_INPUT_2)) {
                Serial.printf("[CONFIG] Save SSID: %s\n", p->value().c_str());
                writeFile(LittleFS, "/host_ssid.txt", p->value().c_str());
            }
            if (p->name().equals(PARAM_INPUT_3)) {
                Serial.printf("[CONFIG] Save Password: %s\n", p->value().c_str());
                writeFile(LittleFS, "/host_password.txt", p->value().c_str());
            }
        }
        request->send_P(200, "text/html", complete_html);
        delay(3000);
        ESP.restart();
    });

    server.begin();
}

void setup() {
    Serial.begin(9600);

    Serial.println();
    Serial.println();
    Serial.println();

    if (!LittleFS.begin()) {
        Serial.println("[ERROR] An Error has occurred while mounting LittleFS");
        return;
    }

    char ssidInput[32];
    readFile(LittleFS, "/host_ssid.txt").toCharArray(ssidInput, 32);

    Serial.printf("SSID: %s\n", ssidInput);
    if (strlen(ssidInput) > 0) {
        Serial.printf("[SETUP] Device setup connecting to network\n");
        WiFi.mode(WIFI_AP);
        char passwordInput[32];
        readFile(LittleFS, "/host_password.txt").toCharArray(passwordInput, 32);
        if (WiFi.getMode() & WIFI_AP) {
            WiFi.softAPdisconnect(true);
        }
        WiFiMulti.addAP(ssidInput, passwordInput);
        while (WiFiMulti.run() != WL_CONNECTED) {
            Serial.printf("[SETUP] Connecting...\n");
            delay(100);
        }
        String ip = WiFi.localIP().toString();
        Serial.printf("[SETUP] WiFi Connected %s\n", ip.c_str());
        Serial.printf("[ID] Unique Identifier %s\n", WiFi.macAddress().c_str());
        NodeName = readFile(LittleFS, "/name.txt");
        if (!ads.begin()) {
            Serial.println("[ADS] Failed to initialize.");
            while (1)
                ;
        }

        sendStatus(true, getBatteryPercentage(), WiFi.macAddress(), NodeName);
        sendMoistureReport(false, getMoistureReading(ads), WiFi.macAddress(), NodeName);
    } else {
        initalSetup();
    }
}

void loop() {
    // String nameINput = readFile(LittleFS, "/name.txt");
    // Serial.print("*** Your name: ");
    // Serial.println(nameINput);

    // String ssidInput = readFile(LittleFS, "/host_ssid.txt");
    // Serial.print("*** Your host_ssid: ");
    // Serial.println(ssidInput);

    // String passwordInput = readFile(LittleFS, "/host_password.txt");
    // Serial.print("*** Your host_password: ");
    // Serial.println(passwordInput);
    // delay(10000);
}