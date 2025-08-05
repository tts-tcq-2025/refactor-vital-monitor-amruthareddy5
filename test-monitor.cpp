#include "./monitor.h"
#include <assert.h>

void testVitalsLogic() {
  VitalLimits limits;

  assert(checkVitals(98.6, 75, 95, limits) == VitalStatus::Normal);
  assert(checkVitals(104.0, 75, 95, limits) == VitalStatus::TemperatureCritical);
  assert(checkVitals(98.6, 55, 95, limits) == VitalStatus::PulseRateCritical);
  assert(checkVitals(98.6, 75, 85, limits) == VitalStatus::Spo2Critical);
}

