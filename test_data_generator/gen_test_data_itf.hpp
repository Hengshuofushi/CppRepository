/**
 * @file gen_test_data_itf.hpp
 * @author your name (you@domain.com)
 * @brief 模拟数据生成器接口，供API集成
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GEN_TEST_DATA_ITF_HPP_
#define GEN_TEST_DATA_ITF_HPP_

#include <string>
#include <vector>
#include "test_rec_data_generator_factory.hpp"
#include "generator_param.hpp"

bool GenTestDataSql(const GeneratorParam& param, std::vector<std::string>& sqlVec);

#endif