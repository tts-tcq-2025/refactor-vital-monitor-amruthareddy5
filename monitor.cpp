#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isTemperatureOk(float temperature) {
  return temperature >= 95 && temperature <= 102;
}

bool isPulseOk(float pulseRate) {
  return pulseRate >= 60 && pulseRate <= 100;
}

bool isSpO2Ok(float spo2) {
  return spo2 >= 90;
}

void blinkAlarm(int times) {
  for (int i = 0; i < times; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
  cout << "\n";
}

void showAlert(const std::string& message) {
  cout << message << "\n";
  blinkAlarm();
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  if (!isTemperatureOk(temperature)) {
    showAlert("Temperature is critical!");
    return 0;
  }
  if (!isPulseOk(pulseRate)) {
    showAlert("Pulse Rate is out of range!");
    return 0;
  }
  if (!isSpO2Ok(spo2)) {
    showAlert("Oxygen Saturation out of range!");
    return 0;
  }
  return 1;
}
