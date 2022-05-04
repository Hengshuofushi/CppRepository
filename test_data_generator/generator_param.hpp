/**
 * @file generator_param.hpp
 * @author your name (you@domain.com)
 * @brief 模拟数据构造参数
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include "generator_define.hpp"

using GeneratorParam = struct GeneratorParam
{
    unsigned int mode           { 0 };              // [M] 0 - real_rec, 1 - ue_upload, 2 - ipc_upload, 3 - sds, 4 - dict
    std::string tableName;                          // [M] 要生成记录的表名
    unsigned int tableStatus    { 1 };              // [M] 表状态
    unsigned int nodeId         { 1 };              // [M] 节点ID
    unsigned int realm          { 0 };              // [M] 节点realm
    unsigned int recType        { 0 };              // [M] 录制类型
    std::string beginDate;                          // [O] 记录开始时间，格式为"2022-05-02 12:12:12"，如果为空则使用beginTimestamp
    std::string endDate;                            // [O] 记录开始时间，格式为"2022-05-03 12:12:12"，如果为空则使用endTimestamp
    Timestamp beginTimestamp    { 0 };              // [O] 记录开始时间，单位为us，如果为0则使用本月第一天，用作记录的起始时间最小值
    Timestamp endTimestamp      { 0 };              // [O] 记录开始时间，单位为us，如果为0则使用本月第二天，用作记录的起始时间最大值
    unsigned long long caller   { 1001 };           // [O] 主叫/视频源，默认为1001
    unsigned long long callee   { 1002 };           // [O] 被叫/群组，默认为1002
    unsigned int encryptionFlag { 0 };              // [O] 加密标识，默认为0
    unsigned int emergencyFlag  { 0 };              // [O] 紧急标识，默认为0
    unsigned int tag1           { 0 };              // [O] 自定义标签，默认为0
    unsigned int tag2           { 0 };              // [O] 永久标签，默认为0
    std::string filePath;                           // [O] 录制文件路径
    unsigned int recnum         { 1 };              // [O] 生成记录条数，这些记录将按时间均匀方式生成，默认为1
    std::string outfile;                            // [O] 输出文件，如果没有则输出到控制台，如果和appfile同时存在则以appfile为准
    std::string appfile;                            // [O] 追加写

    std::string MakeTableName(const std::string& baseTable) const;
    bool Validate();
};