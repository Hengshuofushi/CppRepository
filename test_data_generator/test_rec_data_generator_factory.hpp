/**
 * @file test_rec_data_generator_factory.hpp
 * @author your name (you@domain.com)
 * @brief 测试数据生成器工厂
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include "real_rec_data_generator.hpp"
#include "sds_data_generator.hpp"
#include "ueupload_data_generator.hpp"
#include "ipcupload_data_generator.hpp"
#include "generator_define.hpp"

class DataGenFactory
{
public:
    DataGenFactory() = delete;
    ~DataGenFactory() = delete;
    static P_TestRecDataGenerator_T CreateGenerator(DataGeneratorType type);
};