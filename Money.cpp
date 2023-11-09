//
// Created by 付宏仁 on 2023/11/8.
//
#include "Money.h"
#include "printf.h"

//MONEY 构造函数
Money::Money(): units_(0U), cents_(0U)
{ ; }

Money::Money(const Money &kOrgMoney): units_(kOrgMoney.units_), cents_(kOrgMoney.cents_)
{ ; }

Money::Money(const MoneyUnit& kUnits,const MoneyCent& kCents): units_(0U), cents_(0U) {
    SetUnits(kUnits);
    SetCents(kCents);
}

Money::~Money()
{ ; }

//MONEY OPERATOR
Money& Money::operator=(const Money &rhs) {
    if(this == &rhs) { return *this; }

    units_ = rhs.units_;
    cents_ = rhs.cents_;

    return *this;
}

Money Money::operator+(const Money &rhs)const {
    Money result = *this;
    result.Add(rhs);
    return result;
}

Money& Money::operator+=(const Money &rhs) {
    Add(rhs);
    return *this;
}

//MONEY
void Money::SetUnits(const MoneyUnit &kUnits) { units_ = kUnits; }

void Money::SetCents(const MoneyCent &kCents) {
    if(kCents > Money::CENTS_MAX) {
        throw MoneyException(MoneyError::CENT_FORMAT);
    }
    cents_ = kCents;
}

const MoneyUnit& Money::GetUnits() const { return units_; }

const MoneyCent& Money::GetCents() const { return cents_; }

void Money::AddUnits(const MoneyUnit &kUnits) {
    MoneyUnit new_units = units_ + kUnits;
    if(new_units < units_ || new_units > UNITS_MAX){
        throw MoneyException(MoneyError::UNIT_OVERFLOW);
    }
    units_ = new_units;
}

void Money::AddCents(const MoneyCent &kCents) {
    if(kCents > Money::CENTS_MAX){
        throw MoneyException(MoneyError::CENT_FORMAT);
    }

    MoneyCent new_cents = cents_ + kCents;
    if(new_cents > Money::CENTS_MAX){
        AddUnits(1U);
        new_cents -= 100U;
    }

    cents_ = new_cents;
}

void Money::SubUnits(const MoneyUnit &kUnits) {
    MoneyUnit new_units = units_ - kUnits;
    if(new_units > units_){
        throw MoneyException(MoneyError::UNIT_OVERFLOW);
    }

    units_ = new_units;
}

void Money::SubCents(const MoneyCent &kCents) {
    if(kCents > Money::CENTS_MAX){
        throw MoneyException(MoneyError::CENT_FORMAT);
    }

    if(kCents > cents_){
        if(cents_ == 0U) { cents_ = 100U - kCents; }
        else if(cents_ <= 9) {cents_ = 100U - kCents + cents_; }
        else             { cents_ = kCents - cents_; }

        SubUnits(1U);
    }
    else{
        cents_ = cents_ - kCents;
    }
}

void Money::Add(const Money &rhs) {
    MoneyUnit org_units = units_;
    MoneyCent org_cents = cents_;
    try{
        AddCents(rhs.cents_);
        AddUnits(rhs.units_);
    } catch (const MoneyException& money_error_pack){
        units_ = org_units;
        cents_ = org_cents;
        throw MoneyException(money_error_pack.GetError());
    }
}

void Money::Sub(const Money &rhs){
    MoneyUnit org_units = units_;
    MoneyCent org_cents = cents_;
    try{
        SubCents(rhs.cents_);
        SubUnits(rhs.units_);
    } catch (const MoneyException& money_error_pack){
        units_ = org_units;
        cents_ = org_cents;
        throw MoneyException(money_error_pack.GetError());
    }
}

Money Money::SubSafe(const Money &rhs) {
    Money differ;
    if(rhs > *this){
        differ = rhs;
        differ.Sub(*this);
        SetUnits(0U);
        SetCents(0U);
    }
    else{
        Sub(rhs);
    }
    return differ;
}

void Money::Times(const MoneyUnit &rhs) {
    MoneyUnit temp = GetUnitsCents();
    MoneyUnit overflowCheck = temp;
    temp = overflowCheck * rhs;
    if(temp / rhs != overflowCheck){
        throw MoneyException(MoneyError::TIMES_OVERFLOW);
    }
    SetUnitsCents(temp);
}

//Other Operator
bool operator>(const Money &lhs, const Money &rhs) {
    if(lhs.GetUnits() > rhs.GetUnits()) {
        if (lhs.GetCents() == rhs.GetCents()) {
            return lhs.GetCents() > rhs.GetCents();
        }
        return true;
    }
    return false;
}

bool operator==(const Money& lhs, const Money& rhs){
    if(lhs.GetUnits() == rhs.GetUnits()) {
        return lhs.GetCents() == rhs.GetCents();
    }
    return false;
}

void ShowMoney(const Money& kMoney, const bool kEnter){
    printf("%02llu.%02u", kMoney.GetUnits(), kMoney.GetCents());
    if(kEnter){ printf("\n"); }
}