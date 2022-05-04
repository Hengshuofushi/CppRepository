/**
 * @file test_rec_data_generator.hpp
 * @author your name (you@domain.com)
 * @brief 基类抽象类
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "generator_define.hpp"
#include "generator_param.hpp"
#include <vector>
#include <memory>

class TestRecDataGenerator
{
public:
    TestRecDataGenerator() = default;
    virtual ~TestRecDataGenerator() = default;
    virtual int Generate(const GeneratorParam& param, std::vector<std::string>& sqlVec) { return GenAllRecords(param, sqlVec); }
protected:
    // single record for single table
    virtual std::string GenRecord(const GeneratorParam& param) = 0;
    // signle record for all table
    virtual int GenAllRecord(const GeneratorParam& param, std::vector<std::string>& sqlVec);
    // multiple record for single table
    virtual int GenRecords(const GeneratorParam& param, std::vector<std::string>& sqlVec);
    // multiple record for all table
    virtual int GenAllRecords(const GeneratorParam& param, std::vector<std::string>& sqlVec);
    // generate batch inser sql
    std::string GenBatchInsertSql(const std::vector<std::string>& sqlVec);
};

using P_TestRecDataGenerator_T = std::shared_ptr<TestRecDataGenerator>;

