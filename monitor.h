#ifndef MONITOR_H
#define MONITOR_H

enum class VitalStatus {
  Normal,
  TemperatureCritical,
  PulseRateCritical,
  Spo2Critical
};

struct VitalLimits {
  float tempMin = 95.0f;
  float tempMax = 102.0f;
  float pulseMin = 60.0f;
  float pulseMax = 100.0f;
  float spo2Min = 90.0f;
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2, const VitalLimits& limits);
void blinkAlarm(int times = 6, int intervalSec = 1);
int vitalsOk(float temperature, float pulseRate, float spo2);

#endif // MONITOR_H
