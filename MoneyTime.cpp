//
// Created by 付宏仁 on 2023/11/9.
//
#include "MoneyRecord.h"

MoneyRecord::MoneyTime::MoneyTime():timestamp_(0)
{ ; }

MoneyRecord::MoneyTime::MoneyTime(const time_t &kTime):timestamp_(kTime)
{ ; }

MoneyRecord::MoneyTime::MoneyTime(const MoneyRecord::MoneyTime &rhs):timestamp_(rhs.timestamp_)
{ ; }

bool MoneyRecord::MoneyTime::SetYear(const int kYear){
    if(kYear < 1900 || kYear > 2038) { return false; }
    time_t new_times = timestamp_;

    struct tm* time_info = localtime(&new_times);
    time_info->tm_year = kYear - 1900;
    new_times = mktime(time_info);

    MoneyTime test{new_times};
    if(!test.SetDay(Day())) { return false; }

    timestamp_ = new_times;

    return true;
}

bool MoneyRecord::MoneyTime::SetMonth(const int kMonth){
    if(kMonth < 1 || kMonth > 12) { return false; }
    struct tm* time_info = localtime(&timestamp_);
    time_info->tm_mon = kMonth - 1;
    timestamp_ = mktime(time_info);
    return true;
}

bool MoneyRecord::MoneyTime::SetDay(const int kDay){
    //static
    const static uint8_t MONTHS[12]{31U,28U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U};
    //static

    if(kDay <= 0 || kDay > 32) { return false; }

    int this_year = Year();
    if((this_year % 4 == 0 && this_year %100 != 0) || (this_year % 400 == 0)){
        if(Month() == 2){ if(kDay > 29) { return false; } }
        else if(kDay > MONTHS[Month() - 1]) { return false; }
    }
    else {
        if(kDay > MONTHS[Month() - 1]) { return false; }
    }

    struct tm* time_info = localtime(&timestamp_);
    time_info->tm_mday = kDay;
    timestamp_ = mktime(time_info);

    return true;
}

bool MoneyRecord::MoneyTime::SetYMD(const int kYser, const int kMonth, const int kDay){

    MoneyTime new_times{timestamp_};
    new_times.SetMonth(1);
    new_times.SetDay(1);

    if(!new_times.SetYear(kYser)){ return false; }
    if(!new_times.SetMonth(kMonth)){ return false; }
    if(!new_times.SetDay(kDay)){ return false; }

    timestamp_ = new_times.timestamp_;
    return true;
}

bool MoneyRecord::MoneyTime::SetHour(const int kHour){
    if(kHour < 0 || kHour > 24) { return false; }
    struct tm* time_info = localtime(&timestamp_);
    time_info->tm_hour = kHour;
    timestamp_ = mktime(time_info);
    return true;
}

bool MoneyRecord::MoneyTime::SetMinute(const int kMinute){
    if(kMinute < 0 || kMinute > 59) { return false; }
    struct tm* time_info = localtime(&timestamp_);
    time_info->tm_min = kMinute;
    timestamp_ = mktime(time_info);
    return true;
}

bool MoneyRecord::MoneyTime::SetSecond(const int kSecond){
    if(kSecond < 0 || kSecond > 60) { return false; }
    struct tm* time_info = localtime(&timestamp_);
    time_info->tm_sec = kSecond;
    timestamp_ = mktime(time_info);
    return true;
}

bool MoneyRecord::MoneyTime::SetTime(const int kHour, const int kMinute, const int kSecond){
    MoneyTime new_times{timestamp_};
    if(!new_times.SetHour(kHour)){ return false; }
    if(!new_times.SetMinute(kMinute)){ return false; }
    if(!new_times.SetSecond(kSecond)){ return false; }

    timestamp_ = new_times.timestamp_;
    return true;
}