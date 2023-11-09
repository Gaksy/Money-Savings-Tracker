//
// Created by 付宏仁 on 2023/11/8.
//

#ifndef MONEY_SAVINGS_TRACKER_V1_MONEYRECORD_H
#define MONEY_SAVINGS_TRACKER_V1_MONEYRECORD_H

#include <ctime>
#include <chrono>
#include "Money.h"



class MoneyRecord{
public:
    struct MoneyPack{
        bool record_positivity_;
        Money record_;
    };
    struct MoneyTime{
    public:
        MoneyTime();
        explicit MoneyTime(const time_t& kTime);
        MoneyTime(const MoneyTime& rhs);

        [[nodiscard]] inline int Year()const{ return localtime(&timestamp_)->tm_year + 1900; }
        [[nodiscard]] inline int Month()const{ return localtime(&timestamp_)->tm_mon + 1; }
        [[nodiscard]] inline int Day()const{ return localtime(&timestamp_)->tm_mday; }
        [[nodiscard]] inline int Hour()const{ return localtime(&timestamp_)->tm_hour; }
        [[nodiscard]] inline int Minute()const{ return localtime(&timestamp_)->tm_min; }
        [[nodiscard]] inline int Second()const{ return localtime(&timestamp_)->tm_sec; }

        bool SetYear(int kYear);
        bool SetMonth(int kMonth);
        bool SetDay(int kDay);
        bool SetYMD(int kYser, int kMonth, int kDay);

        bool SetHour(int kHour);
        bool SetMinute(int kMinute);
        bool SetSecond(int kSecond);
        bool SetTime(int kHour, int kMinute, int kSecond);

    public:
        time_t timestamp_;
    };

public:
    MoneyRecord();
    explicit MoneyRecord(const Money& kMoney, bool kPositivity = true);

public:
    const MoneyRecord::MoneyPack& GetRecord()const;
    const Money& GetMoney()const;
    MoneyRecord::MoneyTime GetTime()const;
    bool GetPositivity()const;

    void SetRecord(const MoneyRecord::MoneyPack& kRecord);
    void SetMoney(const Money& kMoney);
    void SetPositivity(const bool& kPositivity);
    bool SetDate(const int kYear, const int kMonth, const int kDay);
    bool SetTime(const int kHour, const int kMinute, const int kSecond);

private:
    MoneyRecord::MoneyPack record_pack_;
    time_t timestamp_;
};

inline time_t GetCurrentTimeMsec(){
    auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    time_t timestamp = time.time_since_epoch().count();
    return timestamp;
}


#endif //MONEY_SAVINGS_TRACKER_V1_MONEYRECORD_H
