/**
 * @file real_rec_data_generator.hpp
 * @author your name (you@domain.com)
 * @brief 实时录制业务MRSFileInfo
 *          sessionid生成规则：timestamp(us)-mrsnoderealm-taskcount-isemergency-calltype-callerstr-calleestr
 *          fileid生成规则：(nodeid << 28) + (calltype << 24) + (++count)
 *          nodeinfo生成规则：realm << 16 | nodeid
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "test_rec_data_generator.hpp"
#include <vector>

struct MRSFileInfoEntity
{
    explicit MRSFileInfoEntity(const GeneratorParam& param);

    std::string table;
    std::string sessionId;
    unsigned int fileId { 0 };
    unsigned long long nodeInfo { 0 };
    unsigned int recType { 0 };
    Timestamp begin { 0 };
    Timestamp end { 0 };
    unsigned int emergencyFlag { 0 };
    unsigned int encryptionFlag { 0 };
    unsigned long long caller { 0 };
    unsigned long long callee { 0 };
    unsigned int vpnCaller { 65535 };
    unsigned int vpnCallee { 65535 };
    unsigned int tags1 { 0 };
    unsigned int tags2 { 0 };
    unsigned int fileStatus;
    std::string filePath;
};

struct EncryptionFileInfoEntity
{
    explicit EncryptionFileInfoEntity(const GeneratorParam& param);

    std::string table;
    std::string sessionId;
    unsigned int fileId { 0 };
    unsigned int streamId { 0 };
    unsigned long long ssrc { 0 };
    unsigned int codecType { 0 };
    std::string filePath;
    std::string callerCm;
    std::string calleeCm;
    unsigned int vendorId { 0 };
};

struct RecPttInfoEntity
{
    explicit RecPttInfoEntity(const GeneratorParam& param);

    std::string table;
    std::string sessionId;
    unsigned int fileId { 0 };
    unsigned int eventIdx { 0 };
    unsigned long long groupId { 0 };
    unsigned long long speaker { 0 };
    unsigned long long beginTime { 0 };
    unsigned long long endTime { 0 };
    unsigned long long nodeInfo { 0 };
    unsigned int vpnGroup { 65535 };
};

struct MRSRecDictEntity
{
    explicit MRSRecDictEntity(const GeneratorParam& param);

    std::string tableName;
    unsigned int createType { 0 };
    unsigned int tableType { 0 };
    unsigned int tableStatus { 1 };
    std::string createTime;
    std::string beginTime;
    std::string endTime;
};

class MrsFileInfoDataGenerator : public TestRecDataGenerator
{
public:
    MrsFileInfoDataGenerator() = default;
    virtual ~MrsFileInfoDataGenerator() = default;

private:
    virtual std::string GenRecord(const GeneratorParam& param) override;
    // 主表从表均同时生成
    virtual int GenAllRecord(const GeneratorParam& param, std::vector<std::string>& sqlVec) override;
    std::string GenSessionId(const GeneratorParam& param);
    unsigned int GenFileId(const GeneratorParam& param, unsigned int fileCount = 1);
    unsigned long long GenNodeInfo(const GeneratorParam& param);
    std::string GenInsertSql(const MRSFileInfoEntity& entity);
};

class EncFileInfoDataGenerator : public TestRecDataGenerator
{
public:
    explicit EncFileInfoDataGenerator(const std::string& sid, unsigned int fid)
        : sessionId(sid), fileId(fid) {}
    virtual ~EncFileInfoDataGenerator() = default;
    virtual std::string GenRecord(const GeneratorParam& param) override;
private:
    std::string GenInsertSql(const EncryptionFileInfoEntity& entity);

    std::string sessionId;
    unsigned int fileId { 0 };
};

class RecPttInfoDataGenerator : public TestRecDataGenerator
{
public:
    explicit RecPttInfoDataGenerator(const std::string& sid, unsigned int fid)
        : sessionId(sid), fileId(fid) {}
    virtual ~RecPttInfoDataGenerator() = default;
    virtual std::string GenRecord(const GeneratorParam& param) override;
private:
    std::string GenInsertSql(const RecPttInfoEntity& entity);

    std::string sessionId;
    unsigned int fileId { 0 };
};

class MrsDictInfoDataGenerator : public TestRecDataGenerator
{
public:
    MrsDictInfoDataGenerator() = default;
    virtual ~MrsDictInfoDataGenerator() = default;
private:
    virtual std::string GenRecord(const GeneratorParam& param) override;
    std::string GenInsertSql(const MRSRecDictEntity& entity);
};