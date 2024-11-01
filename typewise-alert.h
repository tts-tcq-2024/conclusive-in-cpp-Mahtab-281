#pragma once
using namespace std;
#include <string>

class TypewiseAlert
{
public:
  enum class CoolingType{
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
  };

  enum class BreachType{
    NORMAL,
    TOO_LOW,
    TOO_HIGH
  };

  enum class AlertTarget{
    TO_CONTROLLER,
    TO_EMAIL
  };

  struct BatteryCharacter {
        CoolingType coolingType;
        string brand;
  };

  static BreachType inferBreach(double value, double lowerLimit, double upperLimit);
  static BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
  
  static void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
  
  static void sendToController(BreachType breachType);
  static void sendToEmail(BreachType breachType);
};
