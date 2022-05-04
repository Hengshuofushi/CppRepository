/**
 * @file sds_data_generator.hpp
 * @author your name (you@domain.com)
 * @brief 短彩信模拟数据
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "test_rec_data_generator.hpp"

class SdsDataGenerator : public TestRecDataGenerator
{
public:
    virtual std::string GenRecord(const GeneratorParam& param) override;
};