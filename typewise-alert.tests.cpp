#include "gtest/gtest.h"
#include "typewise-alert.h"


TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
  BatteryCharacter battery1;
  battery1.coolingType = HI_ACTIVE_COOLING;
  std::string s = "";//checkAndAlert(TO_EMAIL, battery1, 85);
  
  int lowerLimit[noOfCoolingTypes];
  int upperLimit[noOfCoolingTypes];
  setLowerAndUpperLimits(lowerLimit,upperLimit);
  
  std::string expected[2] = {"feed : 1\nfeed : 0\nfeed : 0\nfeed : 0\nfeed : 2\n", 
                              "To: a.b@c.com\nHi, the temperature is too low\nTo: a.b@c.com\nHi, the temperature is too high\n"};
  
  for(int i = TO_CONTROLLER; i < noOfAlertTargets; ++i) {
    for(int j = PASSIVE_COOLING; j < noOfCoolingTypes; ++j) {
      AlertTarget alertTarget = static_cast<AlertTarget>(i);
      CoolingType coolingType = static_cast<CoolingType>(j);
      battery1.coolingType = coolingType;
      s = checkAndAlert(alertTarget, battery1, (lowerLimit[battery1.coolingType] - 1));
      s += checkAndAlert(alertTarget, battery1, lowerLimit[battery1.coolingType]);
      s += checkAndAlert(alertTarget, battery1, ((upperLimit[battery1.coolingType] + lowerLimit[battery1.coolingType])/2));
      s += checkAndAlert(alertTarget, battery1, upperLimit[battery1.coolingType]);
      s += checkAndAlert(alertTarget, battery1, (upperLimit[battery1.coolingType] + 1));
    }
    EXPECT_EQ((s == expected[i]), 1);
  }
}
