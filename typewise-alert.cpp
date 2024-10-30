#include "typewise-alert.h"
#include <sstream>
#include <vector>
#include <string>

// Global instance of MessageStore
MessageStore messageStore;

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return (value < lowerLimit) ? TOO_LOW :
         (value > upperLimit) ? TOO_HIGH :
         NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = coolingLimits[coolingType].lowerLimit;
    int upperLimit = coolingLimits[coolingType].upperLimit;

    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  if(alertTarget == TO_CONTROLLER) {
    sendToController(breachType);
  } else {
    sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  std::ostringstream message;
  message << std::hex << header << " : " << breachType;
  messageStore.addMessage(message.str());
}

void sendToEmail(BreachType breachType) {
  if (breachType == NORMAL) return;

  const char* recipient = "a.b@c.com";
  std::string message = (breachType == TOO_LOW) 
                        ? "Hi, the temperature is too low" 
                        : "Hi, the temperature is too high";

  messageStore.addMessage("To: " + std::string(recipient));
  messageStore.addMessage(message);
}
