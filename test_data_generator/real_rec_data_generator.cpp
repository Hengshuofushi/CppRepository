#include "real_rec_data_generator.hpp"
#include "utils.hpp"
#include "trace.hpp"
#include <sstream>

MRSFileInfoEntity::MRSFileInfoEntity(const GeneratorParam& param)
{
    table = param.MakeTableName("TBL_MRSFileInfo");
    recType = param.recType;
    begin = param.beginTimestamp;
    end = param.beginTimestamp + 10;
    end = (end > param.endTimestamp) ? param.endTimestamp : end;
    emergencyFlag = param.emergencyFlag;
    encryptionFlag = param.encryptionFlag;
    caller = param.caller;
    callee = param.callee;
    tags1 = param.tag1;
    tags2 = param.tag2;
    filePath = param.filePath;
}

EncryptionFileInfoEntity::EncryptionFileInfoEntity(const GeneratorParam& param)
{
    table = param.MakeTableName("TBL_EncryptionFileInfo");
    filePath = param.filePath;
}

RecPttInfoEntity::RecPttInfoEntity(const GeneratorParam& param)
{
    table = param.MakeTableName("TBL_RecPttInfo");
    groupId = param.callee;
    nodeInfo = (param.realm << 16 | param.nodeId);
}


std::string MrsFileInfoDataGenerator::GenRecord(const GeneratorParam& param)
{
    // 视频点呼一个session对应两个文件记录
    std::stringstream ss;
    MRSFileInfoEntity entity(param);
    entity.sessionId = GenSessionId(param);
    entity.fileId = GenFileId(param, 1);
    entity.nodeInfo = GenNodeInfo(param);
    std::vector<std::string> sqlVec;
    sqlVec.push_back(GenInsertSql(entity));
    if (param.recType == DAO_REC_TYPE_P2P_VIDEO)
    {
        entity.fileId = GenFileId(param, 2);
        sqlVec.push_back(GenInsertSql(entity));
    }
    return GenBatchInsertSql(sqlVec);
}

int MrsFileInfoDataGenerator::GenAllRecord(const GeneratorParam& param, std::vector<std::string>& sqlVec)
{
    MRSFileInfoEntity entity(param);
    entity.sessionId = GenSessionId(param);
    entity.fileId = GenFileId(param, 1);
    entity.nodeInfo = GenNodeInfo(param);
    sqlVec.push_back(GenInsertSql(entity));
    if (param.encryptionFlag > 0)
    {
        EncFileInfoDataGenerator encGen(entity.sessionId, entity.fileId);
        sqlVec.push_back(encGen.GenRecord(param));
    }
    if (param.recType == DAO_REC_TYPE_P2P_VIDEO)
    {
        entity.fileId = GenFileId(param, 2);
        sqlVec.push_back(GenInsertSql(entity));
        if (param.encryptionFlag > 0)
        {
            EncFileInfoDataGenerator encGen(entity.sessionId, entity.fileId);
            sqlVec.push_back(encGen.GenRecord(param));
        }
    }
    else if (param.recType == DAO_REC_TYPE_PTT_AUDIO)
    {
        RecPttInfoDataGenerator pttInfoGen(entity.sessionId, entity.fileId);
        sqlVec.push_back(pttInfoGen.GenRecord(param));
    }
    return sqlVec.size();
}

std::string MrsFileInfoDataGenerator::GenInsertSql(const MRSFileInfoEntity& entity)
{
    std::stringstream ss;
    ss << "insert into " << entity.table << " (SessionId, FileId, RecType, caller, callee, fullBeginTime, fullEndTime, emergy_flag, EncryptionFlag, "
        << "tags1, tags2, node_info, FilePath, FileStatus, vpn_caller, vpn_callee) values ('"
        << entity.sessionId << "'," << entity.fileId << "," << entity.recType << "," << entity.caller << "," << entity.callee << ","
        << entity.begin << "," << entity.end << "," << entity.emergencyFlag << "," << entity.encryptionFlag << "," << entity.tags1 << "," 
        << entity.tags2 << "," << entity.nodeInfo << ",'" << entity.filePath << "'," << entity.fileStatus << "," << entity.vpnCaller << "," << entity.vpnCallee
        << ");";
    return ss.str();
}

std::string MrsFileInfoDataGenerator::GenSessionId(const GeneratorParam& param)
{
    std::stringstream ss;
    ss << param.beginTimestamp << "-"
        << param.realm << "-"
        << 1 << "-"                             // taskcount
        << param.emergencyFlag << "-"
        << param.recType << "-"
        << param.caller << "-"
        << param.callee;
    return ss.str();
}
unsigned int MrsFileInfoDataGenerator::GenFileId(const GeneratorParam& param, unsigned int fileCount)
{
    return (param.nodeId << 28) + (param.recType << 24) + fileCount;
}
unsigned long long MrsFileInfoDataGenerator::GenNodeInfo(const GeneratorParam& param)
{
    return param.realm << 16 | param.nodeId;
}

std::string EncFileInfoDataGenerator::GenRecord(const GeneratorParam& param)
{
    EncryptionFileInfoEntity entity(param);
    entity.sessionId = sessionId;
    entity.fileId = fileId;
    entity.ssrc = param.caller;
    entity.codecType = CODEC_TYPE_AMR;
    entity.callerCm = "xxxxx";
    entity.calleeCm = "yyyyy";
    std::vector<std::string> sqlVec;
    sqlVec.push_back(GenInsertSql(entity));
    if (param.recType == DAO_REC_TYPE_P2P_AUDIO)
    {
        entity.ssrc = param.callee;
        sqlVec.push_back(GenInsertSql(entity));
    }
    else if (param.recType == DAO_REC_TYPE_P2P_VIDEO)
    {
        entity.codecType = CODEC_TYPE_H264;
        sqlVec.push_back(GenInsertSql(entity));
        entity.ssrc = param.callee;
        sqlVec.push_back(GenInsertSql(entity));
        entity.codecType = CODEC_TYPE_AMR;
        sqlVec.push_back(GenInsertSql(entity));
    }
    else if (param.recType == DAO_REC_TYPE_UPLOAD_VIDEO)
    {
        entity.codecType = CODEC_TYPE_H264;
        sqlVec.push_back(GenInsertSql(entity));
    }
    
    return GenBatchInsertSql(sqlVec);
}

std::string EncFileInfoDataGenerator::GenInsertSql(const EncryptionFileInfoEntity& entity)
{
    std::stringstream ss;
    ss << "insert into " << entity.table << " (taskId, fileId, streamId, ssrc, codecType, encFilePath, callerCm, calleeCm, vendorId) values ('"
        << entity.sessionId << "'," << entity.fileId << "," << entity.streamId << "," << entity.ssrc << "," << entity.codecType << ",'"
        << entity.filePath << "','" << entity.callerCm << "','" << entity.calleeCm << "'," << entity.vendorId << ");";
    return ss.str();
}

std::string RecPttInfoDataGenerator::GenRecord(const GeneratorParam& param)
{
    RecPttInfoEntity entity(param);
    entity.sessionId = sessionId;
    entity.fileId = fileId;
    entity.eventIdx = 1;
    entity.speaker = param.caller;
    entity.beginTime = param.beginTimestamp;
    entity.endTime = param.beginTimestamp + 2;

    std::vector<std::string> sqlVec;
    sqlVec.push_back(GenInsertSql(entity));
    entity.eventIdx = 2;
    entity.speaker = param.caller + 1;
    entity.beginTime = param.beginTimestamp + 3;
    entity.endTime = param.beginTimestamp + 5; 
    sqlVec.push_back(GenInsertSql(entity));
    entity.eventIdx = 3;
    entity.speaker = param.caller + 2;
    entity.beginTime = param.beginTimestamp + 6;
    entity.endTime = param.beginTimestamp + 8; 
    sqlVec.push_back(GenInsertSql(entity));
    return GenBatchInsertSql(sqlVec);
}

std::string RecPttInfoDataGenerator::GenInsertSql(const RecPttInfoEntity& entity)
{
    std::stringstream ss;
    ss << "insert into " << entity.table << " (task_id, file_id, event_idx, group_id, speaker, begin_time, end_time, node_info, vpn_group) values ("
        << entity.sessionId << "," << entity.fileId << "," << entity.eventIdx << "," << entity.groupId << "," << entity.speaker << ","
        << entity.beginTime << "," << entity.endTime << "," << entity.nodeInfo << "," << entity.vpnGroup << ");";
    return ss.str();
}

MRSRecDictEntity::MRSRecDictEntity(const GeneratorParam& param)
{
    tableName = param.tableName;
    tableStatus = param.tableStatus;
    createTime = param.beginDate;
    beginTime = param.beginDate;
    endTime = param.endDate;
}

std::string MrsDictInfoDataGenerator::GenRecord(const GeneratorParam& param)
{
    MRSRecDictEntity entity(param);
    return GenInsertSql(entity);
}

std::string MrsDictInfoDataGenerator::GenInsertSql(const MRSRecDictEntity& entity)
{
    std::stringstream ss;
    ss << "insert into TBL_MRSRecHistoryTables (tbl_name, create_type, tbl_type, tbl_status, create_time, begin_time, end_time) values ('"
        << entity.tableName << "'," << entity.createType << "," << entity.tableType << "," << entity.tableStatus << ",'"
        << entity.createTime << "','" << entity.beginTime << "','" << entity.endTime << "');";
    return ss.str();
}