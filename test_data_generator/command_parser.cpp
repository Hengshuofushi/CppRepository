#include "command_parser.hpp"
#include <exception>

void CommandParser::ParseParameter(const std::string& cmd)
{
    auto index = cmd.find_first_of("=");
    if (index == std::string::npos)
    {
        throw std::exception();
    }
    auto index2 = cmd.find_first_of("--");
    if (index2 == std::string::npos)
    {
        throw std::exception();
    }

    std::string left = cmd.substr(index2 + 2, index - index2 - 2);
    std::string right = cmd.substr(index + 1);
    paramMap[left] = right;
}

void CommandParser::ParseParameter(GeneratorParam& param)
{
    UpdateParam<unsigned int>(param.mode, "mode");
    UpdateParam<unsigned int>(param.nodeId, "nodeid");
    UpdateParam<unsigned int>(param.realm, "realm");
    UpdateParam<unsigned int>(param.recType, "rectype");
    UpdateParam<unsigned long long>(param.beginTimestamp, "begintime");
    UpdateParam<unsigned long long>(param.endTimestamp, "endtime");
    UpdateParam<unsigned long long>(param.caller, "caller");
    UpdateParam<unsigned long long>(param.callee, "callee");
    UpdateParam<unsigned int>(param.encryptionFlag, "encflag");
    UpdateParam<unsigned int>(param.emergencyFlag, "emerflag");
    UpdateParam<unsigned int>(param.tag1, "tag1");
    UpdateParam<unsigned int>(param.tag2, "tag2");
    UpdateParam<unsigned int>(param.recnum, "recnum");
    UpdateParam<unsigned int>(param.tableStatus, "tabstatus");
    UpdateParam(param.tableName, "table");
    UpdateParam(param.filePath, "filepath");
    UpdateParam(param.beginDate, "begindate");
    UpdateParam(param.endDate, "enddate");
    UpdateParam(param.outfile, "outfile");
    UpdateParam(param.appfile, "appfile");
}