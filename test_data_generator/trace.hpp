/**
 * @file trace.hpp
 * @author your name (you@domain.com)
 * @brief 控制台日志
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>

#define LOG_INFO(X) std::cout << "[INFO] " << X << std::endl;
#define LOG_ERROR(X) std::cerr << "[ERROR] " <<  X << std::endl;