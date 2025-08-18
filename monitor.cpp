#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

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

// ---- ALERT/OUTPUT ----
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
  blinkAlarm(3);  // default 3 blinks
}

// ---- WRAPPER LOGIC ----
struct VitalCheck {
  std::function<bool(float)> check;
  float value;
  std::string message;
};

int vitalsOk(float temperature, float pulseRate, float spo2) {
  std::vector<VitalCheck> checks = {
    {isTemperatureOk, temperature, "Temperature is critical!"},
    {isPulseOk, pulseRate, "Pulse Rate is out of range!"},
    {isSpO2Ok, spo2, "Oxygen Saturation out of range!"}
  };

  for (const auto& vital : checks) {
    if (!vital.check(vital.value)) {
      showAlert(vital.message);
      return 0; // fail fast
    }
  }
  return 1;
}
