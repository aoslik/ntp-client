#include <ntp.h>

Date date;

void Date::setDate(){
    char *strDate = (char*)this->timeClient->getFormattedDate().c_str();
    int buffer;
    if(DEBUG_NTP) Serial.println("NTP: "+this->timeClient->getFormattedDate());
    sscanf(strDate, "%d-%d-%dT%d:%d:%dZ", &buffer, &this->month, (int*)&this->day, (int*)&this->hour, (int*)&this->minute, &buffer);
}

void Date::setTimeFuse(int32_t timeFuse){
    this->timeClient->setTimeOffset(timeFuse);
    this->timeFuse = timeFuse;
}

bool Date::begin(){
    bool result = false;
    if(setup){
        this->timeClient->end();
        this->timeClient->begin();
    }else{
        this->timeClient->begin();
    }
    this->setup = true;
    if(DEBUG_NTP) Serial.println("NTP: Setup NTP server...");
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
    if(DEBUG_NTP) Serial.println(result ? "NTP: Setup NTP server success" : "NTP: Setup NTP server failure");
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

uint32_t Date::getEpoch() const{
    return this->timeClient->getEpochTime();
}

int Date::getDay() const{
    return this->day;
}

int Date::getMonth() const{
    return this->month;
}

int Date::getHour() const{
    return this->hour;
}   

int Date::getMinute() const{
    return this->minute;
}