/**
 * @file command_parser.hpp
 * @author your name (you@domain.com)
 * @brief 解析命令参数
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include "generator_param.hpp"
#include <map>
#include <sstream>
#include <type_traits>

class CommandParser
{
public:
    CommandParser() = default;
    ~CommandParser() = default;
    void ParseParameter(const std::string& cmd);
    void ParseParameter(GeneratorParam& param);
private:
    template<typename T>
    T StringConvert(const std::string& value)
    {
        T t;
        std::stringstream ss;
        ss << value;
        ss >> t;
        return t;
    }

    template<typename T>
    inline void UpdateParam(typename std::enable_if<!std::is_same<T, std::string>::value, T>::type& field, const std::string& key)
    {
        if (paramMap.count(key) == 0)
        {
            return;
        }
        field = StringConvert<T>(paramMap[key]);
    }

    inline void UpdateParam(std::string& field, const std::string& key)
    {
        if (paramMap.count(key) == 0)
        {
            return;
        }
        field = paramMap[key];
    }

    std::map<std::string, std::string> paramMap;
};

#endif