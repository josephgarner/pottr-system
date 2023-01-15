#include "sensors.h"

int analogInPin = A0;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int getBatteryPercentage() {
    float voltage = (((analogRead(analogInPin) * 3.3) / 1024) * 2 + 0.414);
    int bat_percentage = mapfloat(voltage, 2.8, 4.2, 0, 100);
    if (bat_percentage >= 100) {
        bat_percentage = 100;
    }
    if (bat_percentage <= 0) {
        bat_percentage = 1;
    }
    return bat_percentage;
}

int getMoistureReading(Adafruit_ADS1015 ads) {
    int16_t adc0, adc1, adc2, adc3;
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);

    int meanFour = (adc0 + adc1 + adc2 + adc3) / 4;
    return meanFour;
}
