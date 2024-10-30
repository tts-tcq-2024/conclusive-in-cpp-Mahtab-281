#pragma once

#include <vector>
#include <string>

// Enum for cooling types
enum CoolingType {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
};

// Enum for breach types
enum BreachType {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
};

// Structure to hold cooling limits
struct CoolingLimits {
    int lowerLimit;
    int upperLimit;
};

// Cooling limits for different cooling types
const CoolingLimits coolingLimits[] = {
    {0, 35},  // PASSIVE_COOLING
    {0, 45},  // HI_ACTIVE_COOLING
    {0, 40}   // MED_ACTIVE_COOLING
};

// Function prototypes
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

// Enum for alert targets
enum AlertTarget {
    TO_CONTROLLER,
    TO_EMAIL
};

// Structure for battery character
struct BatteryCharacter {
    CoolingType coolingType;
    char brand[48];
};

// Message store structure
struct MessageStore {
    std::vector<std::string> messages;

    void addMessage(const std::string& message) {
        messages.push_back(message);
    }

    void clearMessages() {
        messages.clear();
    }

    std::vector<std::string> getMessages() const {
        return messages;
    }
};

// Global instance of MessageStore
extern MessageStore messageStore;

// Alert checking function
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
