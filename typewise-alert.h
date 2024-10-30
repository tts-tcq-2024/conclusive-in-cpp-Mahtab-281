#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  noOfCoolingTypes
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  noOfBreachTypes
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  noOfAlertTargets
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  std::string brand;
} BatteryCharacter;

std::string checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

std::string sendToController(BreachType breachType);
std::string sendToEmail(BreachType breachType);

void setLowerAndUpperLimits(int lowerLimitList[] ,int upperLimitList[]);
