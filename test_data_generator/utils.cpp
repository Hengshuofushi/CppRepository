#include "utils.hpp"
#include <ctime>

Timestamp DateToTimestamp(const std::string& date)
{
    Timestamp ts = 0;
    if (date.empty())
    {
        return ts;
    }
    tm timeStu { 0 };
    strptime(date.c_str(), "%Y-%m-%d %H:%M:%S", &timeStu);
    time_t time = mktime(&timeStu);
    if (time < 0) return ts;
    ts = time * 1000000;
    return ts;
}

Timestamp NowTimestamp()
{
    time_t t = time(nullptr);
    return t * 1000000;
}

Timestamp FirstDayTimestamp()
{
    time_t t = time(nullptr);
    tm *tStu = localtime(&t);
    tStu->tm_mday = 1;
    return mktime(tStu) * 1000000;
}

Timestamp SecondDayTimestamp()
{
    time_t t = time(nullptr);
    tm *tStu = localtime(&t);
    tStu->tm_mday = 2;
    return mktime(tStu) * 1000000;
}