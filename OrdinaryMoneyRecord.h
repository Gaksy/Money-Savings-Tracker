//
// Created by 付宏仁 on 2023/11/9.
//

#ifndef MONEY_SAVINGS_TRACKER_V1_ORDINARYMONEYRECORD_H
#define MONEY_SAVINGS_TRACKER_V1_ORDINARYMONEYRECORD_H

#include "MoneyRecord.h"
#include <string>

class OrdinaryMoneyRecord: public MoneyRecord{
public:
    OrdinaryMoneyRecord();
    OrdinaryMoneyRecord(const OrdinaryMoneyRecord& rhs);
    OrdinaryMoneyRecord(const std::string& kTitle, const std::string& kDescribe = "");

public:
    void SetTitle(const std::string& kTitle);
    void SetDescribe(const std::string kDescribe);

    const std::string& GetTitle()const;
    const std::string& GetDescribe()const;

private:
    std::string title_;
    std::string describe_;
};


#endif //MONEY_SAVINGS_TRACKER_V1_ORDINARYMONEYRECORD_H
