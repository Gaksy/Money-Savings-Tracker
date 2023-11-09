//
// Created by 付宏仁 on 2023/11/8.
//

#ifndef MONEY_SAVINGS_TRACKER_V1_MONEY_H
#define MONEY_SAVINGS_TRACKER_V1_MONEY_H

#include <exception>
#include <string>
#include <cinttypes>

typedef uint64_t MoneyUnit;
typedef uint8_t MoneyCent;

enum MoneyError{
    CENT_FORMAT,
    UNIT_OVERFLOW,
    TIMES_OVERFLOW
};

class MoneyException: public std::exception{
public:
    explicit MoneyException(const MoneyError& kMoneyError);
    const char* what() const noexcept override;
    const MoneyError& GetError()const;

private:
    MoneyError error_;
    std::string message_;
};

class Money{
public:
    Money();
    Money(const Money& kOrgMoney);
    Money(const MoneyUnit& kUnits, const MoneyCent& kCents);
    ~Money();

public:
    Money& operator=(const Money& rhs);
    Money operator+(const Money& rhs)const;
    Money& operator+=(const Money& rhs);

public:
    void SetUnits(const MoneyUnit & kUnits);
    void SetCents(const MoneyCent & kCents);

    [[nodiscard]] const MoneyUnit& GetUnits()const;
    [[nodiscard]] const MoneyCent& GetCents()const;

    void AddUnits(const MoneyUnit & kUnits);
    void AddCents(const MoneyCent & kCents);

    void SubUnits(const MoneyUnit & kUnits);
    void SubCents(const MoneyCent & kCents);

    void Add(const Money& rhs);
    void Sub(const Money& rhs);
    Money SubSafe(const Money& rhs);
    void Times(const MoneyUnit& rhs);

public:
    static const MoneyUnit UNITS_MAX = 999999999999999999LLU;
    static const MoneyCent CENTS_MAX = 99U;

private:
    inline MoneyUnit GetUnitsCents()const{
        return units_ * 100U + cents_;
    }
    inline void SetUnitsCents(MoneyUnit val){
        units_ = val / 100U;
        cents_ = val - units_ * 100U;
    }

private:
    MoneyUnit units_;
    MoneyCent cents_;
};

bool operator>(const Money& lhs, const Money& rhs);
inline bool operator<(const Money& lhs, const Money& rhs) { return !(lhs > rhs); }
bool operator==(const Money& lhs, const Money& rhs);

void ShowMoney(const Money& kMoney, const bool kEnter = false);

#endif //MONEY_SAVINGS_TRACKER_V1_MONEY_H
