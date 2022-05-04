#include "generator_param.hpp"
#include "utils.hpp"
#include "trace.hpp"

std::string GeneratorParam::MakeTableName(const std::string& baseTable) const
{
    size_t pos = tableName.find("_");
    pos = tableName.find("_", pos + 1);
    if (pos == std::string::npos)
    {
        return baseTable;
    }
    std::string table = tableName;
    table.replace(0, pos, baseTable);
    return table;
}
bool GeneratorParam::Validate()
{
    if (mode < DATA_GENERATOR_REAL_REC || mode >= DataGeneratorType::DATA_GENERATOR_DICT)
    {
        LOG_ERROR("GeneratorParam::Validate invalid mode: " << mode)
        return false;
    }
    if (tableName.empty())
    {
        LOG_ERROR("GeneratorParam::Validate empty tableName")
        return false;
    }
    if (mode == DATA_GENERATOR_REAL_REC &&
        (recType < DAO_REC_TYPE_P2P_AUDIO || recType > DAO_REC_TYPE_UPLOAD_VIDEO))
    {
        LOG_ERROR("GeneratorParam::Validate rec type is not match mode: recType=" << recType << ", mode=" << mode)
        return false;
    }
    else if (mode == DATA_GENERATOR_UE_UPLOAD && recType != DAO_REC_TYPE_UE_UPLOAD)
    {
        LOG_ERROR("GeneratorParam::Validate rec type is not match mode: recType=" << recType << ", mode=" << mode)
        return false;
    }
    else if (mode == DATA_GENERATOR_IPC_UPLOAD && recType != DAO_REC_TYPE_RECORDER_UPLOAD)
    {
        LOG_ERROR("GeneratorParam::Validate rec type is not match mode: recType=" << recType << ", mode=" << mode)
        return false;
    }
    else if (mode == DATA_GENERATOR_SDS && recType != DAO_REC_TYPE_SDS)
    {
        LOG_ERROR("GeneratorParam::Validate rec type is not match mode: recType=" << recType << ", mode=" << mode)
        return false;
    }

    if (!beginDate.empty())
    {
        Timestamp tmp = DateToTimestamp(beginDate);
        if (tmp > 0)
        {
            beginTimestamp = tmp;
        }
        else
        {
            LOG_ERROR("GeneratorParam::Validate invalid begin date: " << beginDate)
            return false;
        }
    }
    if (!endDate.empty())
    {
        Timestamp tmp = DateToTimestamp(endDate);
        if (tmp > 0)
        {
            endTimestamp = tmp;
        }
        else
        {
            LOG_ERROR("GeneratorParam::Validate invalid end date: " << endDate)
            return false;
        }
    }
    if (beginTimestamp == 0)
    {
        beginTimestamp = FirstDayTimestamp();
    }
    if (endTimestamp == 0)
    {
        endTimestamp = SecondDayTimestamp();
    }
    if (endTimestamp < beginTimestamp)
    {
        return false;
    }
    if (recnum <= 0)
    {
        return false;
    }
    return true;
}