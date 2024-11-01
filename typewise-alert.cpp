#include "typewise-alert.h"
#include <stdio.h>

TypewiseAlert::BreachType TypewiseAlert::inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return BreachType::TOO_LOW;
  }
  else if(value > upperLimit) {
    return BreachType::TOO_HIGH;
  }
  else
  {
    return BreachType::NORMAL;
  }
}

TypewiseAlert::BreachType TypewiseAlert::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  if (coolingType == CoolingType::PASSIVE_COOLING) 
  {
    upperLimit = 35;
  }
  else if (coolingType == CoolingType::HI_ACTIVE_COOLING) 
  {
    upperLimit = 45;
  }
  else
  {
    upperLimit = 40;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void TypewiseAlert::sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void TypewiseAlert::sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType == BreachType::TOO_LOW)
  {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
  }
  else if (breachType == BreachType::TOO_HIGH)
  {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
  }
  else
  {
  }
}

void TypewiseAlert::checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  if (alertTarget == AlertTarget::TO_CONTROLLER) 
  {
    sendToController(breachType);
  } 
  else 
  {
    sendToEmail(breachType);
  }
}
