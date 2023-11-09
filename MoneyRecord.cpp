//
// Created by 付宏仁 on 2023/11/9.
//
#include "MoneyRecord.h"
#include <chrono>

MoneyRecord::MoneyRecord():
        record_pack_({true, {0U, 0U}}),
        timestamp_(GetCurrentTimeMsec())
{ ; }

MoneyRecord::MoneyRecord(const Money &kMoney, const bool kPositivity):
        record_pack_({kPositivity, kMoney}),
        timestamp_(GetCurrentTimeMsec())
{ ; }

//MoneyRecord::MoneyRecord(const time_t &kTime, const Money &kMoney, const bool kPositivity):
//        record_pack_({kPositivity, kMoney}),
//        timestamp_(kTime)
//{ ; }

const MoneyRecord::MoneyPack& MoneyRecord::GetRecord() const { return record_pack_; }

const Money& MoneyRecord::GetMoney() const { return record_pack_.record_; }

MoneyRecord::MoneyTime MoneyRecord::GetTime() const { return MoneyRecord::MoneyTime(timestamp_); }

bool MoneyRecord::GetPositivity() const { return record_pack_.record_positivity_; }

void MoneyRecord::SetRecord(const MoneyRecord::MoneyPack &kRecord) { record_pack_ = kRecord; }

void MoneyRecord::SetMoney(const Money &kMoney) { record_pack_.record_ = kMoney; }

void MoneyRecord::SetPositivity(const bool &kPositivity) { record_pack_.record_positivity_ = kPositivity; }

bool MoneyRecord::SetDate(const int kYear, const int kMonth, const int kDay) {
    MoneyRecord::MoneyTime new_time{timestamp_};
    if(!new_time.SetYMD(kYear,kMonth,kDay)){ return false; }
    timestamp_ = new_time.timestamp_;
    return true;
}

bool MoneyRecord::SetTime(const int kHour, const int kMinute, const int kSecond) {
    MoneyRecord::MoneyTime new_time{timestamp_};
    if(!new_time.SetTime(kHour,kMinute,kSecond)){ return false; }
    timestamp_ = new_time.timestamp_;
    return true;
}

