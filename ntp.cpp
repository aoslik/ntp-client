#include <ntp.h>

Date date;

void Date::setDate(){
    char *strDate = (char*)this->timeClient->getFormattedDate().c_str();
    int buffer;
    sscanf(strDate, "%d-%d-%dT%d:%d:%dZ", &buffer, &this->month, &this->day, &this->hour, &this->minute, &buffer);
}

void Date::setTimeFuse(int32_t timeFuse){
    this->timeClient->setTimeOffset(timeFuse);
    this->timeFuse = timeFuse;
}

bool Date::begin(){
    bool result = false;
    this->ntpUDP = new WiFiUDP;
    this->timeClient = new NTPClient((*this->ntpUDP), this->timeFuse);
    this->timeClient->begin();
    if(DEBUG_NTP) Serial.println("Setup NTP server...");
    for(int attempt = 0; attempt < 6; attempt++){
        if(this->timeClient->update()){
            this->update();
            result = true;
            break;
        }else{
            if(timeClient->forceUpdate()){
                this->update();
                result = true;
                break;
            }
            delay(500);
        }
    }
    if(DEBUG_NTP) Serial.println(result ? "Setup NTP server success" : "Setup NTP server failure");
    return result;
}

void Date::update(ulong lastEpoch, bool updateNTP){
    if(lastEpoch){
        this->timeClient->setEpochTime(lastEpoch - this->timeFuse);
    }
    if(updateNTP && WiFi.isConnected()){
        this->timeClient->update();
    }
    this->setDate();
}

int32_t Date::getTimeFuse() const{
    return this->timeFuse;
}

uint8_t Date::getDay() const{
    return this->day;
}

uint8_t Date::getMonth() const{
    return this->month;
}

uint8_t Date::getHour() const{
    return this->hour;
}   

uint8_t Date::getMinute() const{
    return this->minute;
}