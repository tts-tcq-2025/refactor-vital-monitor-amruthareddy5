#include <gtest/gtest.h>
#include "./monitor.h"

// ---- Pure function tests ----
TEST(TemperatureCheck, Boundaries) {
  EXPECT_TRUE(isTemperatureOk(95));
  EXPECT_TRUE(isTemperatureOk(102));
  EXPECT_FALSE(isTemperatureOk(94.9));
  EXPECT_FALSE(isTemperatureOk(102.1));
}

TEST(PulseCheck, Boundaries) {
  EXPECT_TRUE(isPulseOk(60));
  EXPECT_TRUE(isPulseOk(100));
  EXPECT_FALSE(isPulseOk(59));
  EXPECT_FALSE(isPulseOk(101));
}

TEST(SpO2Check, Boundaries) {
  EXPECT_TRUE(isSpO2Ok(90));
  EXPECT_FALSE(isSpO2Ok(89));
  EXPECT_TRUE(isSpO2Ok(95));
}

// ---- Integration tests (vitalsOk) ----
TEST(Monitor, TemperatureOutOfRange) {
  EXPECT_FALSE(vitalsOk(104, 80, 95)); // too high temp
  EXPECT_FALSE(vitalsOk(90, 80, 95));  // too low temp
}

TEST(Monitor, PulseOutOfRange) {
  EXPECT_FALSE(vitalsOk(98, 55, 95));  // too low pulse
  EXPECT_FALSE(vitalsOk(98, 120, 95)); // too high pulse
}

TEST(Monitor, SpO2OutOfRange) {
  EXPECT_FALSE(vitalsOk(98, 80, 85));  // low oxygen
}

TEST(Monitor, AllVitalsOk) {
  EXPECT_TRUE(vitalsOk(98.6, 72, 96)); // healthy range
}
