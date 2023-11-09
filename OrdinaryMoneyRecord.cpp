//
// Created by 付宏仁 on 2023/11/9.
//

#include "OrdinaryMoneyRecord.h"

OrdinaryMoneyRecord::OrdinaryMoneyRecord():title_(""), describe_("")
{ ; }

OrdinaryMoneyRecord::OrdinaryMoneyRecord(const OrdinaryMoneyRecord &rhs):title_(rhs.title_), describe_(rhs.describe_)
{ ; }

OrdinaryMoneyRecord::OrdinaryMoneyRecord(const std::string &kTitle, const std::string &kDescribe):title_(kTitle), describe_(kDescribe)
{ ; }

void OrdinaryMoneyRecord::SetTitle(const std::string &kTitle) { title_ = kTitle; }

void OrdinaryMoneyRecord::SetDescribe(const std::string kDescribe) { describe_ = kDescribe; }

const std::string &OrdinaryMoneyRecord::GetTitle() const { return title_; }

const std::string &OrdinaryMoneyRecord::GetDescribe() const { return describe_; }

