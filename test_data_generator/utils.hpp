#pragma once

#include "generator_define.hpp"
#include <string>

Timestamp DateToTimestamp(const std::string& date);

Timestamp NowTimestamp();

Timestamp FirstDayTimestamp();

Timestamp SecondDayTimestamp();