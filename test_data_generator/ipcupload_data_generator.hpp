/**
 * @file ipcupload_data_generator.hpp
 * @author your name (you@domain.com)
 * @brief 执法记录仪视频回传
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "test_rec_data_generator.hpp"

class IpcUploadDataGenerator : public TestRecDataGenerator
{
public:
    virtual std::string GenRecord(const GeneratorParam& param) override;
};