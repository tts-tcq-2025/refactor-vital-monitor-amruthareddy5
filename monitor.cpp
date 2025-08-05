#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

VitalStatus checkVitals(float temperature, float pulseRate, float spo2, const VitalLimits& limits) {
  if (temperature < limits.tempMin || temperature > limits.tempMax) {
    return VitalStatus::TemperatureCritical;
  }
  if (pulseRate < limits.pulseMin || pulseRate > limits.pulseMax) {
    return VitalStatus::PulseRateCritical;
  }
  if (spo2 < limits.spo2Min) {
    return VitalStatus::Spo2Critical;
  }
  return VitalStatus::Normal;
}

void blinkAlarm(int times, int intervalSec) {
  for (int i = 0; i < times; ++i) {
    cout << "\r* " << flush;
    sleep_for(seconds(intervalSec));
    cout << "\r *" << flush;
    sleep_for(seconds(intervalSec));
  }
  cout << "\n";
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
  VitalLimits limits;
  VitalStatus status = checkVitals(temperature, pulseRate, spo2, limits);

  switch (status) {
    case VitalStatus::Normal:
      return 1;
    case VitalStatus::TemperatureCritical:
      cout << "Temperature is critical!\n";
      break;
    case VitalStatus::PulseRateCritical:
      cout << "Pulse Rate is out of range!\n";
      break;
    case VitalStatus::Spo2Critical:
      cout << "Oxygen Saturation out of range!\n";
      break;
  }

  blinkAlarm();
  return 0;
}
