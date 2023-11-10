//
// Created by 付宏仁 on 2023/11/8.
//

#include "Money.h"

//EXCEPTION
MoneyException::MoneyException(const MoneyError& kMoneyError):message_(""){
    if(kMoneyError == MoneyError::CENT_FORMAT) { message_ = "Cent格式错误，其最大值是99。（1角=10分）"; }
    if(kMoneyError == MoneyError::UNIT_OVERFLOW) { message_ = "该操作会使Unit溢出。"; }
    if(kMoneyError == MoneyError::TIMES_OVERFLOW) { message_ = "乘法操作导致了溢出。"; }
}

const char *MoneyException::what() const noexcept {
    return message_.c_str();
}

const MoneyError& MoneyException::GetError()const {
    return error_;
}
