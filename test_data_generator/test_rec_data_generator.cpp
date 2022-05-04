#include "test_rec_data_generator.hpp"
#include "generator_param.hpp"
#include "utils.hpp"
#include "trace.hpp"
#include <sstream>

int TestRecDataGenerator::GenAllRecord(const GeneratorParam& param, std::vector<std::string>& sqlVec)
{
    sqlVec.push_back(GenRecord(param));
    return sqlVec.size();
}

int TestRecDataGenerator::GenRecords(const GeneratorParam& param, std::vector<std::string>& sqlVec)
{
    unsigned int recnum = param.recnum;
    Timestamp beginTime = param.beginTimestamp;
    Timestamp endTime = param.endTimestamp;
    if (!param.beginDate.empty())
    {
        beginTime = DateToTimestamp(param.beginDate);
    }
    if (!param.endDate.empty())
    {
        endTime = DateToTimestamp(param.endDate);
    }
    if (beginTime == 0)
    {
        beginTime = FirstDayTimestamp();
    }
    if (endTime == 0)
    {
        endTime = SecondDayTimestamp();
    }
    if (endTime <= beginTime)
    {
        return ERRCODE_FAILED;
    }
    
    GeneratorParam p = param;
    p.beginTimestamp = beginTime;
    p.endTimestamp = endTime;
    Timestamp delta = (endTime - beginTime) / recnum;
    while (recnum--)
    {
        p.beginTimestamp += delta;
        std::string sql = GenRecord(p);
        sqlVec.push_back(sql);
    }
    return sqlVec.size();
}

int TestRecDataGenerator::GenAllRecords(const GeneratorParam& param, std::vector<std::string>& sqlVec)
{
    unsigned int recnum = param.recnum;
    Timestamp beginTime = param.beginTimestamp;
    Timestamp endTime = param.endTimestamp;
    if (!param.beginDate.empty())
    {
        beginTime = DateToTimestamp(param.beginDate);
    }
    if (!param.endDate.empty())
    {
        endTime = DateToTimestamp(param.endDate);
    }
    if (beginTime == 0)
    {
        beginTime = FirstDayTimestamp();
    }
    if (endTime == 0)
    {
        endTime = SecondDayTimestamp();
    }
    if (endTime <= beginTime)
    {
        return ERRCODE_FAILED;
    }
    GeneratorParam p = param;
    p.beginTimestamp = beginTime;
    p.endTimestamp = endTime;
    Timestamp delta = (endTime - beginTime) / recnum;
    while (recnum--)
    {
        p.beginTimestamp += delta;
        std::vector<std::string> sqlContains;
        GenAllRecord(p, sqlContains);
        sqlVec.insert(sqlVec.end(), sqlContains.begin(), sqlContains.end());
    }
    return sqlVec.size();
}

std::string TestRecDataGenerator::GenBatchInsertSql(const std::vector<std::string>& sqlVec)
{
    if (sqlVec.empty())
    {
        return "";
    }
    std::stringstream ss;
    std::string head = sqlVec[0];
    std::string label = "values";
    std::string tailLabel = ";";
    auto index = head.find(label);
    if (index == std::string::npos)
    {
        return "";
    }
    head = head.substr(0, index + label.size());
    ss << head;
    for (size_t i = 0; i < sqlVec.size(); ++i)
    {
        auto posTail = sqlVec[i].rfind(tailLabel);
        auto posMedium = sqlVec[i].find(label);
        if (posMedium >= posTail)
        {
            return "";
        }
        std::string dataPart = sqlVec[i].substr(posMedium + label.size(), posTail - posMedium - label.size());
        ss << dataPart;
        if (i < sqlVec.size() - 1)
        {
            ss << ",";
        }
    }

    ss << ";";
    std::string sql = ss.str();
    return sql;
}

