#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
  EXPECT_EQ(TypewiseAlert::inferBreach(20, 0, 40), TypewiseAlert::BreachType::NORMAL);
  EXPECT_EQ(TypewiseAlert::inferBreach(-15, 0, 40), TypewiseAlert::BreachType::TOO_LOW);
  EXPECT_EQ(TypewiseAlert::inferBreach(55, 0, 40), TypewiseAlert::BreachType::TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite,classifyTemperatureBreachAccordingToType) {
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::PASSIVE_COOLING, 30), TypewiseAlert::BreachType::NORMAL);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::PASSIVE_COOLING, -5), TypewiseAlert::BreachType::TOO_LOW);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::PASSIVE_COOLING, 38), TypewiseAlert::BreachType::TOO_HIGH);
  
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, 42), TypewiseAlert::BreachType::NORMAL);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, -5), TypewiseAlert::BreachType::TOO_LOW);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, 50), TypewiseAlert::BreachType::TOO_HIGH);
  
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, 38), TypewiseAlert::BreachType::NORMAL);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, -5), TypewiseAlert::BreachType::TOO_LOW);
  EXPECT_EQ(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, 42), TypewiseAlert::BreachType::TOO_HIGH);
}
