#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(20.0, 0.0, 35.0), NORMAL);
    EXPECT_EQ(inferBreach(-5.0, 0.0, 35.0), TOO_LOW);
    EXPECT_EQ(inferBreach(40.0, 0.0, 35.0), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -5.0), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40.0), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, AlertsControllerWhenBreachDetected) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    
    // Test TOO_HIGH breach alert to controller
    messageStore.clearMessages();
    checkAndAlert(TO_CONTROLLER, batteryChar, 40.0);
    auto log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 1);
    EXPECT_EQ(log[0], "feed : 2");

    // Test TOO_LOW breach alert to controller
    messageStore.clearMessages();
    checkAndAlert(TO_CONTROLLER, batteryChar, -10.0);
    log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 1);
    EXPECT_EQ(log[0], "feed : 1");

    // Test NORMAL condition alert to controller (expect NORMAL message)
    messageStore.clearMessages();
    checkAndAlert(TO_CONTROLLER, batteryChar, 20.0);
    log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 1);
    EXPECT_EQ(log[0], "feed : 0");
}

TEST(TypeWiseAlertTestSuite, SendsEmailWhenBreachDetected) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandY"};

    // Test TOO_HIGH breach alert to email
    messageStore.clearMessages();
    checkAndAlert(TO_EMAIL, batteryChar, 40.0);
    auto log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 2);
    EXPECT_EQ(log[0], "To: a.b@c.com");
    EXPECT_EQ(log[1], "Hi, the temperature is too high");

    // Test TOO_LOW breach alert to email
    messageStore.clearMessages();
    checkAndAlert(TO_EMAIL, batteryChar, -10.0);
    log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 2);
    EXPECT_EQ(log[0], "To: a.b@c.com");
    EXPECT_EQ(log[1], "Hi, the temperature is too low");

    // Test NORMAL condition alert to email (no output expected)
    messageStore.clearMessages();
    checkAndAlert(TO_EMAIL, batteryChar, 20.0);
    log = messageStore.getMessages();
    EXPECT_EQ(log.size(), 0);
}
