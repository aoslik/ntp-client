#pragma once

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>

#define DEBUG_NTP 1

class Date{
    private:
    bool setup {false};
    int day;
    int month;
    int hour;
    int minute;
    int32_t timeFuse {-0}; // intial timezone default (GMT-0)

    WiFiUDP* ntpUDP = new WiFiUDP();
    NTPClient* timeClient = new NTPClient((*ntpUDP));

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

    /// @return current epoch on ntp client 
    uint32_t getEpoch() const;

    /// @brief Pivate property
    /// @return day 
    int getDay() const;

    /// @brief Pivate property
    /// @return month
    int getMonth() const;

    /// @brief Pivate property
    /// @return hour
    int getHour() const;

    /// @brief Private property
    /// @return minute
    int getMinute() const;
};

extern Date date;

