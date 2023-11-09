#include <stdio.h>
#include <stdlib.h>

#include "Money.h"
#include "MoneyRecord.h"
#include <iostream>
#include <iomanip>
#include <limits>
void test(){
    Money total(20U,96U);           //20.96
    ShowMoney(total,true);

    total.Add(Money(0U,4U));    //21.00
    ShowMoney(total,true);

    total.Add(Money(3U,99U));    //24.99
    ShowMoney(total,true);

    total.SubSafe(Money(4U,99U));   //20.00
    ShowMoney(total,true);

    total.SubSafe(Money(0U,1U));   //19.99
    ShowMoney(total,true);

    total.Add(Money(0U,1U));    //20.00
    ShowMoney(total,true);

    total = total.SubSafe(Money(41U,26U));   //21.26
    ShowMoney(total,true);

    total.Add(Money(1623U,35U)); //1644.61
    ShowMoney(total,true);

    total.SubSafe(Money(1600U,1U));   //44.6
    ShowMoney(total,true);

    total.Add(Money(1623U,35U)); //1667.95
    ShowMoney(total,true);

    Money rul = total.SubSafe(Money(11451U,4U));   //9783.09
    ShowMoney(total,true);
    ShowMoney(rul, true);

    Money addv(10,6);
    rul = rul + addv;           //9783.09 + 10.06 = 9793.15
    rul += addv;                //9793.15 + 10.06 = 9803.21
    ShowMoney(rul, true);

    addv.SetCents(99U);
    rul += addv;                    //9803.21+10.99=9814.2
    ShowMoney(rul, true);

    rul.SetCents(99U);      //9814.99+10.99=9825.98
    rul += addv;
    ShowMoney(rul, true);

    rul.SetCents(0U);
    rul.SubSafe(addv);          //9825.00 - 10.99 =9814.01
    rul.SubSafe(Money(0U,0U));
    ShowMoney(rul, true);

    rul.Times(62U);
    ShowMoney(rul, true);

    rul.Times(2U);
    ShowMoney(rul, true);

    rul.Times(10U);
    ShowMoney(rul, true);
    //608468.62
    //1216937.24
    //12169372.40

    rul.Times(10U);
    ShowMoney(rul, true);

    rul.Times(100U);
    ShowMoney(rul, true);
    //rul.Times(353U);//Overflow
}

void time_test(){
    MoneyRecord mtest;
    mtest.SetDate(2022,6,1);
    mtest.SetTime(18,43,26);
    mtest.SetMoney(Money(56U,50U));
    mtest.SetPositivity(false);

    MoneyRecord::MoneyTime date(mtest.GetTime());
    //date.SetYMD(2022,6,1);
    //date.SetTime(19,5,59);

    printf("在%d年%d月%d日 %02d:%02d ",date.Year(),date.Month(),date.Day(),date.Hour(),date.Minute());
    if(mtest.GetPositivity()) { printf("收入"); }
    else                      { printf("支出"); }
    printf("%llu.%u CNY\n",mtest.GetMoney().GetUnits(),mtest.GetMoney().GetCents());
}

int main(){
    //Money Savings Tracker V1



    return EXIT_SUCCESS;
}

