#pragma once

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>

#define DEBUG_NTP 1

class Date{
    private:
    uint8_t day;
    uint8_t month;
    uint8_t hour;
    uint8_t minute;
    int32_t timeFuse {-10800}; // intial timezone default Sao Paulo (GMT-3)

    WiFiUDP* ntpUDP;
    NTPClient* timeClient;

    /// @brief Set all private property of time with ntp client
    void setDate();

    public:

    /// @brief Set private property of time zone
    /// @param timeFuse time zone ex. Sao Paulo (GMT-3) -10800
    void setTimeFuse(int32_t timeFuse);

    /// @brief Setup ntp server and update all property of time with ntp server
    /// @return true on success, false on failure 
    bool begin();

    /// @brief Set all private property of time with ntp client
    /// @param lastEpoch update ntp client with desired epoch if > 0
    /// @param updateNTP update ntp client with ntp server 
    void update(ulong lastEpoch = 0, bool updateNTP = false);

    /// @brief Private property
    /// @return timeFuse
    int32_t getTimeFuse() const;

    /// @brief Pivate property
    /// @return day 
    uint8_t getDay() const;

    /// @brief Pivate property
    /// @return month
    uint8_t getMonth() const;

    /// @brief Pivate property
    /// @return hour
    uint8_t getHour() const;

    /// @brief Private property
    /// @return minute
    uint8_t getMinute() const;
};

extern Date date;

