#pragma once
#include <string>
bool isTemperatureOk(float temperature);
bool isPulseOk(float pulseRate);
bool isSpO2Ok(float spo2);
int vitalsOk(float temperature, float pulseRate, float spo2);
void showAlert(const std::string& message);
void blinkAlarm(int times);
